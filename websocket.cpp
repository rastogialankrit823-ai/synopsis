#include <iostream>
#include <thread>
#include <bits/stdc++.h>
#include <map>
#include <vector>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/sha.h>
#include "htmls2.h"
using namespace std;

#define PORT 8080

map<string,string> ids;
map<string,int> online;  
map<string, vector<string>> inbox;
static const string b64 =
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

string ascii_simple(string s){
    map<char, vector<string>> f = {
        {'A', {"  /\\  "," /--\\ ","/    \\"}},
        {'B', {"|~~\\ ","|--< ","|__/" }},
        {'C', {" /~~","|   "," \\__"}},
        {'H', {"|  |","|--|","|  |"}},
        {'I', {"|||"," | ","|||"}},
        {'O', {" /\\ ","|  |"," \\/ "}},
        {'L', {"|   ","|   ","|___"}},
        {'E', {"|---","|-- ","|___"}}
    };

    vector<string> res(3, "");

    for(char c: s){
        c = toupper(c);
        if(f.count(c)){
            for(int i=0;i<3;i++){
                res[i] += f[c][i] + "  ";
            }
        } else {
            for(int i=0;i<3;i++) res[i] += "    ";
        }
    }

    string out="";
    for(auto &r:res) out += r + "\n";
    return out;
}

string base64_encode(const unsigned char* input, int len) {
    string out;
    for(int i=0;i<len;i+=3){
        int val = (input[i]<<16) +
        ((i+1<len?input[i+1]:0)<<8) +
        (i+2<len?input[i+2]:0);

        out.push_back(b64[(val>>18)&63]);
        out.push_back(b64[(val>>12)&63]);
        out.push_back(i+1<len?b64[(val>>6)&63]:'=');
        out.push_back(i+2<len?b64[val&63]:'=');
    }
    return out;
}

string ws_accept(string key){
    string magic = key + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1((unsigned char*)magic.c_str(), magic.size(), hash);
    return base64_encode(hash, SHA_DIGEST_LENGTH);
}


void send_http(int c,string body,string type="text/html"){
    string res =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: "+type+"\r\n"
    "Connection: close\r\n\r\n"+body;

    write(c,res.c_str(),res.size());
}

void ws_send(int c,string msg){
    unsigned char frame[2048];
    frame[0]=0x81;
    frame[1]=msg.size();
    memcpy(frame+2,msg.c_str(),msg.size());
    write(c,frame,msg.size()+2);
}

string ws_read(int c){
    unsigned char buf[2048];
    int n=read(c,buf,2048);
    if(n<=0) return "";

    int len = buf[1]&127;
    int mask = 2;
    int data = mask+4;

    string msg;
    for(int i=0;i<len;i++){
        msg += buf[data+i] ^ buf[mask+(i%4)];
    }
    return msg;
}

void handle_ws(int client,string req){

    size_t p = req.find("Sec-WebSocket-Key:");
    string key = req.substr(p+19);
    key = key.substr(0,key.find("\r\n"));

    string accept = ws_accept(key);

    string res =
    "HTTP/1.1 101 Switching Protocols\r\n"
    "Upgrade: websocket\r\n"
    "Connection: Upgrade\r\n"
    "Sec-WebSocket-Accept: "+accept+"\r\n\r\n";

    write(client,res.c_str(),res.size());

    string uid;

    while(true){
        string msg = ws_read(client);
        if(msg=="") break;

        // LOGIN
        if(msg.find("LOGIN:")==0){
    uid = msg.substr(6);
    online[uid]=client;

    if(inbox.count(uid)){
        string list="USERS:";
        for(string u:inbox[uid]) list += u + ",";
        ws_send(client,list);
    }

    continue;
}

        if(msg.find("MSG:")==0){
    int p = msg.find(":",4);
    string to = msg.substr(4,p-4);
    string text = msg.substr(p+1);

    if(online.count(to)){
        ws_send(online[to], uid + ": " + text);
    }

    if(find(inbox[to].begin(), inbox[to].end(), uid) == inbox[to].end()){
        inbox[to].push_back(uid);
    }


    if(online.count(to)){
        string list="USERS:";
        for(string u:inbox[to]) list += u + ",";
        ws_send(online[to], list);
    }
}
    }

    online.erase(uid);
    close(client);
}

void handle_http(int client,string req){

    if(req.find("GET / ")!=string::npos){
        
        send_http(client,login);
    }

    else if(req.find("GET /signup")!=string::npos){
        send_http(client,signup);
    }

    else if(req.find("GET /home")!=string::npos){
        send_http(client,home);
    }

    else if(req.find("POST /login")!=string::npos){
        string body = req.substr(req.find("\r\n\r\n")+4);

        string u = body.substr(body.find("uid")+6);
        u = u.substr(0,u.find("\""));

        string p = body.substr(body.find("pass")+7);
        p = p.substr(0,p.find("\""));

        if(ids[u]==p) send_http(client,"ok","text/plain");
        else send_http(client,"fail","text/plain");
    }

    else if(req.find("POST /signup")!=string::npos){
        string body = req.substr(req.find("\r\n\r\n")+4);

        string u = body.substr(body.find("uid")+6);
        u = u.substr(0,u.find("\""));

        string p = body.substr(body.find("pass")+7);
        p = p.substr(0,p.find("\""));

        ids[u]=p;
        send_http(client,"ok","text/plain");
    }
    else if(req.find("POST /ascii")!=string::npos){
    string body = req.substr(req.find("\r\n\r\n")+4);

    string text = body.substr(body.find("text")+7);
    text = text.substr(0,text.find("\""));

    string result = ascii_simple(text);

    send_http(client,result,"text/plain");
   }
   else if(req.find("GET /bg.jpg") != string::npos){
    FILE *f = fopen("bg.jpg", "rb");
    if(!f){
        send_http(client, "Not Found", "text/plain");
        return;
    }

    char buffer[4096];
    string data;
    int n;

    while((n = fread(buffer,1,sizeof(buffer),f)) > 0){
        data.append(buffer,n);
    }

    fclose(f);

    string res =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: image/jpeg\r\n"
    "Connection: close\r\n\r\n";

    write(client, res.c_str(), res.size());
    write(client, data.c_str(), data.size());
}
}

int main(){
    int server = socket(AF_INET,SOCK_STREAM,0);

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server,(sockaddr*)&addr,sizeof(addr));
    listen(server,10);

    cout<<"Server running on 8080\n";

    while(true){
        int client = accept(server,NULL,NULL);

        thread([client](){
            char buf[4096];
            int n = read(client,buf,sizeof(buf));
            string req(buf,n);

            if(req.find("Upgrade: websocket")!=string::npos){
                handle_ws(client,req);
            } else {
                handle_http(client,req);
                close(client);
            }
        }).detach();
    }
}