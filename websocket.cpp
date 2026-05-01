#include <exception>
#include <iostream>
#include <thread>
#include <bits/stdc++.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/sha.h>
#include <fstream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "htmls2.h"

using namespace std;

#define PORT 8080

struct Task{
    int type;
    string u,v,msg;
};

class SharedData{
public:
    map<string,string> ids;
    map<string,int> online;
    map<string, map<string, vector<string>>> inbox;
    map<string,string> settings;

    queue<Task> q;
    mutex mtx;
    condition_variable cv;
};

class Handler{
public:
    virtual void info() = 0;  
    virtual ~Handler(){}
};
class FileHandler:public Handler{
    SharedData &data;

public:
    FileHandler(SharedData &d):data(d){}
    void info(){
        cout<<"FILE HANDLER THREAD ALIVE"<<endl;
    }
    void load_settings(){
        ifstream f("settings.txt");
        string line;
        while(getline(f,line)){
            int p=line.find('|');
            if(p==string::npos) continue;
            string u=line.substr(0,p);
            string bg=line.substr(p+1);

            data.settings[u]=bg;
        }cout<<"Settings loaded\n"; 
    }

    void save_settings(){
        ofstream f("settings.txt");

        for(auto &p:data.settings){
            f<<p.first<<"|"<<p.second<<"\n";
        }
    }

    void load_ids(){
        ifstream f("ids.txt");
        string u,p;
        while(f>>u>>p) data.ids[u]=p;
        cout<<"IDs loaded\n";
    }

    void load_msgs(){
        ifstream f("inbox.txt");
        string line;

        while(getline(f,line)){
            int p1=line.find('|');
            int p2=line.find('|',p1+1);

            if(p1==string::npos || p2==string::npos) continue;

            string u=line.substr(0,p1);
            string v=line.substr(p1+1,p2-p1-1);
            string m=line.substr(p2+1);

            data.inbox[u][v].push_back(m);
        }

        cout<<"Messages loaded\n";
    }

    void file_worker(){
        while(true){
            unique_lock<mutex> lock(data.mtx);
            data.cv.wait(lock,[&]{return !data.q.empty();});

            Task t=data.q.front();
            data.q.pop();
            lock.unlock();

            if(t.type==1){
                ofstream f("inbox.txt",ios::app);
                f<<t.u<<"|"<<t.v<<"|"<<t.msg<<"\n";
            }
            else if(t.type==2){
                ofstream f("ids.txt");
                for(auto &p:data.ids){
                    f<<p.first<<" "<<p.second<<"\n";
                }
            }
        }
    }

    void save_msg(string u,string v,string msg){
        {
            lock_guard<mutex> lock(data.mtx);
            data.q.push({1,u,v,msg});
        }
        data.cv.notify_one();
    }

    void save_ids(){
        {
            lock_guard<mutex> lock(data.mtx);
            data.q.push({2,"","",""});
        }
        data.cv.notify_one();
    }
};

class HttpHandler : public Handler{
    SharedData &data;
    FileHandler &fileHandler;

public:
    HttpHandler(SharedData &d,FileHandler &f):data(d),fileHandler(f){}
     void info(){
        cout<<"HTTP HANDLER ALIVE"<<endl;
    }   
    void send_http(int c,string body,string type="text/html"){
        string res =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: "+type+"\r\n"
        "Connection: close\r\n\r\n"+body;

        write(c,res.c_str(),res.size());
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

            string body=req.substr(req.find("\r\n\r\n")+4);

            string u=body.substr(body.find("uid")+6);
            u=u.substr(0,u.find("\""));

            string p=body.substr(body.find("pass")+7);
            p=p.substr(0,p.find("\""));

            if(u.empty() || p.empty()){
                send_http(client,"fail","text/plain");
                return;
            }

            if(data.ids.count(u) && data.ids[u]==p)
                send_http(client,"ok","text/plain");
            else
                send_http(client,"fail","text/plain");
        }

        else if(req.find("POST /signup")!=string::npos){

            string body=req.substr(req.find("\r\n\r\n")+4);

            string u=body.substr(body.find("uid")+6);
            u=u.substr(0,u.find("\""));

            string p=body.substr(body.find("pass")+7);
            p=p.substr(0,p.find("\""));

            if(u.empty() || p.empty()){
                send_http(client,"fail","text/plain");
                return;
            }

            data.ids[u]=p;
            fileHandler.save_ids();

            send_http(client,"ok","text/plain");
        }

        else if(req.find("GET /bg.jpg")!=string::npos){

            FILE *f=fopen("bg.jpg","rb");

            if(!f){
                send_http(client,"Not Found","text/plain");
                return;
            }

            char buffer[4096];
            string img;
            int n;

            while((n=fread(buffer,1,sizeof(buffer),f))>0){
                img.append(buffer,n);
            }

            fclose(f);

            string res =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: image/jpeg\r\n"
            "Connection: close\r\n\r\n";

            write(client,res.c_str(),res.size());
            write(client,img.c_str(),img.size());
        }
        else if(req.find("GET /bg2.jpg")!=string::npos){

            FILE *f=fopen("bg2.jpg","rb");

            if(!f){
                send_http(client,"Not Found","text/plain");
                return;
            }

            char buffer[4096];
            string img;
            int n;

            while((n=fread(buffer,1,sizeof(buffer),f))>0){
                img.append(buffer,n);
            }

            fclose(f);

            string res =
                        "HTTP/1.1 200 OK\r\n"
                        "Content-Type: image/jpeg\r\n"
                        "Connection: close\r\n\r\n";

            write(client,res.c_str(),res.size());
            write(client,img.c_str(),img.size());
        }
    }
};

class WebSocketHandler:public Handler{
    SharedData &data;
    FileHandler &fileHandler;

    static const string b64;

public:
    WebSocketHandler(SharedData &d,FileHandler &f):data(d),fileHandler(f){}
     void info(){
        cout<<"CLIENT THREAD WORKER ALIVE"<<endl;
    }
    string base64_encode(const unsigned char* input,int len){
        string out;

        for(int i=0;i<len;i+=3){
            int val=(input[i]<<16)+
            ((i+1<len?input[i+1]:0)<<8)+
            (i+2<len?input[i+2]:0);

            out.push_back(b64[(val>>18)&63]);
            out.push_back(b64[(val>>12)&63]);
            out.push_back(i+1<len?b64[(val>>6)&63]:'=');
            out.push_back(i+2<len?b64[val&63]:'=');
        }

        return out;
    }

    string ws_accept(string key){
        string magic=key+"258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
        unsigned char hash[SHA_DIGEST_LENGTH];

        SHA1((unsigned char*)magic.c_str(),magic.size(),hash);

        return base64_encode(hash,SHA_DIGEST_LENGTH);
    }

    void ws_send(int c,string msg){
        unsigned char frame[4096];

        frame[0]=0x81;
        frame[1]=msg.size();

        memcpy(frame+2,msg.c_str(),msg.size());

        write(c,frame,msg.size()+2);
    }

    string ws_read(int c){
        unsigned char buf[4096];

        int n=read(c,buf,4096);
        if(n<=0) return "";

        int len=buf[1]&127;
        int mask=2;
        int dataStart=mask+4;

        string msg;

        for(int i=0;i<len;i++){
            msg+=buf[dataStart+i]^buf[mask+(i%4)];
        }

        return msg;
    }

    void send_user_list(string uid){
        if(!data.online.count(uid)) return;

        string list="USERS:";
        int b =0;
        for(auto &p:data.inbox[uid]){
            list+=p.first+",";
            if(p.first=="emoji")b++;
        }

        if(uid!="emoji" && b==0){
            list+="emoji,";
        }

        ws_send(data.online[uid],list);
    }

    void send_history(int client,string uid,string other){
        string res="HISTORY:";

        for(string &m:data.inbox[uid][other]){
            res+=m+"|";
        }

        ws_send(client,res);
    }

    void handle_ws(int client,string req){

        size_t p=req.find("Sec-WebSocket-Key:");
        string key=req.substr(p+19);
        key=key.substr(0,key.find("\r\n"));

        string accept=ws_accept(key);

        string res =
        "HTTP/1.1 101 Switching Protocols\r\n"
        "Upgrade: websocket\r\n"
        "Connection: Upgrade\r\n"
        "Sec-WebSocket-Accept: "+accept+"\r\n\r\n";

        write(client,res.c_str(),res.size());

        string uid;

        while(true){
            string msg=ws_read(client);
            if(msg=="") break;

            if(msg.find("LOGIN:")==0){
                uid=msg.substr(6);

                if(uid.empty()) continue;

                data.online[uid]=client;
                send_user_list(uid);

                continue;
            }
            if(msg=="GET_PROFILE"){
                string bg="A";
                if(data.settings.count(uid)){
                    bg=data.settings[uid];
                }
                string pass="";

                if(data.ids.count(uid)){
                    pass=data.ids[uid];
                }

                ws_send(client,"PROFILE|"+uid+"|"+pass+"|"+bg);
                continue;
            }

            if(msg.find("SET_BG:")==0){
                string bg=msg.substr(7);

                    if(bg!="A" && bg!="B") continue;

                    data.settings[uid]=bg;
                    fileHandler.save_settings();

                    ws_send(client,"BG_SET|"+bg);
                     continue;
            }
            if(msg.find("GET:")==0){
                string other=msg.substr(4);
                send_history(client,uid,other);

                continue;
            }

            if(msg.find("MSG:")==0){

                int p=msg.find(":",4);
                if(p==string::npos) continue;

                string to=msg.substr(4,p-4);
                string text=msg.substr(p+1);

                if(to.empty() || text.empty()) continue;

                string from=uid;

                if(to=="emoji"){
                    string reply;

                    if(text=="hi") reply="👋";
                    else if(text=="hello") reply="😊";
                    else if(text=="sad") reply="😢";
                    else if(text=="love") reply="❤️";
                    else if(text=="angry") reply="😡";
                    else reply="🤖";

                    data.inbox[from]["emoji"].push_back(from+":"+text);
                    data.inbox[from]["emoji"].push_back("emoji:"+reply);

                    fileHandler.save_msg(from,"emoji",from+":"+text);
                    fileHandler.save_msg(from,"emoji","emoji:"+reply);

                    if(data.online.count(from)){
                        ws_send(data.online[from],"MSG|emoji|"+from+"|"+reply);
                        send_user_list(from);
                    }

                    continue;
                }

                string packet="MSG|"+from+"|"+to+"|"+text;
                string entry=from+":"+text;

                data.inbox[to][from].push_back(entry);
                data.inbox[from][to].push_back(entry);

                fileHandler.save_msg(to,from,entry);
                fileHandler.save_msg(from,to,entry);

                if(data.online.count(to)){
                    ws_send(data.online[to],packet);
                    send_user_list(to);
                }

                if(data.online.count(from)){
                    ws_send(data.online[from],packet);
                    send_user_list(from);
                }
            }
        }

        data.online.erase(uid);
        close(client);
    }
};

const string WebSocketHandler::b64 =
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

class Server{
    SharedData data;
    FileHandler fileHandler;
    HttpHandler httpHandler;
    WebSocketHandler wsHandler;

public:
    Server()
    :fileHandler(data),
     httpHandler(data,fileHandler),
     wsHandler(data,fileHandler)
    {}

    void run(){

        fileHandler.load_ids();
        fileHandler.load_msgs();
        fileHandler.load_settings();
        fileHandler.info();
        httpHandler.info();
        wsHandler.info();

        data.ids["emoji"]="bot";

        thread(&FileHandler::file_worker,&fileHandler).detach();
        try{
            int server=socket(AF_INET,SOCK_STREAM,0);

        sockaddr_in addr;
        addr.sin_family=AF_INET;
        addr.sin_port=htons(PORT);
        addr.sin_addr.s_addr=INADDR_ANY;

        bind(server,(sockaddr*)&addr,sizeof(addr));
        listen(server,100);

        cout<<"Server running on 8080\n";

        while(true){
            int client=accept(server,NULL,NULL);

            thread([this,client](){

                char buf[4096];
                int n=read(client,buf,sizeof(buf));

                if(n<=0){
                    close(client);
                    return;
                }

                string req(buf,n);

                if(req.find("Upgrade: websocket")!=string::npos){
                    wsHandler.handle_ws(client,req);
                }
                else{
                    httpHandler.handle_http(client,req);
                    close(client);
                }

            }).detach();
           }

        }catch(exception &e){
            cout<<"I DIED BECAUSE OF 0 "<<e.what()<<endl;
        }
    }
};

int main(){
    Server server;
    server.run();
}