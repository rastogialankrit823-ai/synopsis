#include <iostream>
#include <thread>
#include <vector>
#include <map>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>
#include <sstream>
#include "htmls.h"
#define ll long long
#define PORT 8080
#define BUFFER_SIZE 1024
#define str string
using namespace std;
map<ll,ll>clients;
map<str,str>ids;


class users{
    public:
    str name;
    str pass;
    int cid;
};
map<str,users>datause;
map<str,vector<users>>friends;
map<str,vector<str>>inbox;


str reqread(int client) {
    str req;
    char data[1024];

    while(req.find("\r\n\r\n") == str::npos) {
        int n = read(client, data, sizeof(data));
        if(n <= 0) break;
        req.append(data, n);
    }
    int pos = req.find("Content-Length:");
    if(pos != str::npos) {
        int len = stoi(req.substr(pos + 15));
        int body_start = req.find("\r\n\r\n") + 4;

        while((int)(req.size() - body_start) < len) {
            int n = read(client, data, sizeof(data));
            if(n <= 0) break;
            req.append(data, n);
        }
    }

    return req;
}
void respsend(int client, string body, string type="text/plain") {
    string res =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: " + type + "\r\n"
        "Connection: close\r\n"
        "\r\n" + body;

    write(client, res.c_str(), res.size());
}
void redirect(int client,str a){
    string res ="HTTP/1.1 302 Found\r\n"
"Location: "+a+"\r\n"
"Connection: close\r\n"
"\r\n";
write(client, res.c_str(), res.size());
}

void get(str &req,str &uid,str &pass){
    string body = req.substr(req.find("\r\n\r\n") + 4);

        int u = body.find("uid");
        if(u != string::npos) {
            uid = body.substr(u + 6);
            uid = uid.substr(0, uid.find("\""));
        }

        int p = body.find("pass");
        if(p != string::npos) {
            pass = body.substr(p + 7);
            pass = pass.substr(0, pass.find("\""));
        }
}


void handler(int server,int cid){
    str req=reqread(clients[cid]);
    str uid="",pass="";
     if(req.find("GET / ") != string::npos || req.find("GET /HTTP") != string::npos) {
        respsend(clients[cid], login,"text/html");
    }
    if(req.find("GET /home") != string::npos) {


    respsend(clients[cid],home, "text/html");
    }
     if(req.find("GET /signup") != string::npos){
        respsend(clients[cid], sign, "text/html");

     }

     if(req.find("POST /login") != string::npos) {

        get(req,uid,pass);
        str rep="";
        str a=" ";
        if(ids.find(uid)!=ids.end() && ids[uid]==pass){
            rep="ok";
            datause[uid].name=uid;
            datause[uid].pass=pass;
            datause[uid].cid=clients[cid];
            friends["a"].push_back(datause[uid]);
        }
        else rep="dead dude";
        respsend(clients[cid],rep,"text/html");
       // cout<<clients[cid]<<endl;
    }
    if(req.find("POST /signup") != string::npos) {

        get(req,uid,pass);
        str rep="";
        str a=" ";
        if(ids.find(uid)!=ids.end() && ids[uid]==pass){
            rep="dead dude";
        }
        else {
            rep="ok";
            ids[uid]=pass;
        }
        respsend(clients[cid],rep,"text/html");
    }
    if(req.find("POST /home") != string::npos) {
       str toid = "", data = "";
        get(req,toid,data);
      //  ll touid=stoi(toid);
        str rep=("yo!! i "+datause[uid].name+" know you");
        inbox[toid].push_back(uid+": "+data);
        respsend(datause[uid].cid,rep,"text/html");
    }
    if(req.find("GET /get") != string::npos) {
        str res=datause[uid].name;
        for(str &cur:inbox[uid])res+= "\n"+cur;
        respsend(datause[uid].cid,res,"text/html");
    }
    if(req.find("GET /friends") != string::npos) {
        str res=datause[uid].name;
        for(auto &cur:friends[uid])res+= "/n"+cur.name;
        respsend(datause[uid].cid,res,"text/html");
    }
    close(clients[cid]);
}



int main(){
    int server = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in address;
    ids["a"]="1";
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server, (sockaddr*)&address, sizeof(address));
    listen(server, 10);

    cout << "Chat server running on port " << PORT << "\n";
    bool status=true;
    ll cur=0;
    while(status){
        sockaddr_in addres;
        socklen_t len=sizeof(addres);
        ll cid=accept(server, (sockaddr*)&addres,&len);
        cur++;
        clients[cur]=cid;
        thread(handler,server,cur).detach();
    }
    return 0;
}