#include <iostream>
#include <thread>
#include <vector>
#include <map>
#include <mutex>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sstream>
#define ll long long
#define PORT 8080
#define BUFFER_SIZE 1024
#define str string
using namespace std;
ll ps=0;
map<ll,ll>clients;
map<str,str>ids;
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
void handler(int server,int cid){
    str req=reqread(clients[cid]);
     if(req.find("GET / ") != string::npos || req.find("GET /HTTP") != string::npos) {

        str html =
        "<!DOCTYPE html>"
        "<html><body>"
        "<h2>Login</h2>"
        "<input id='u' placeholder='user'><br><br>"
        "<input id='p' type='password' placeholder='pass'><br><br>"
        "<button onclick='login()'>Login</button>"

        "<script>"
        "function login(){"
        "fetch('/login',{"
        "method:'POST',"
        "headers:{'Content-Type':'application/json'},"
        "body:JSON.stringify({"
        "uid:document.getElementById('u').value,"
        "pass:document.getElementById('p').value"
        "})"
        "})"
        ".then(r=>r.text()).then(alert);"
        "}"
        "</script>"

        "</body></html>";

        respsend(clients[cid], html, "text/html");
    }
    if(req.find("POST /login") != string::npos) {

        string body = req.substr(req.find("\r\n\r\n") + 4);
        str uid = "", pass = "";

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
        str rep="";
        if(ids.find(uid)!=ids.end() && ids[uid]==pass){
            rep="ok";
        }
        else rep="dead dude";
        respsend(clients[cid],rep);
        close(clients[cid]);
    }
}

int main(){
    int server = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server, (sockaddr*)&address, sizeof(address));
    listen(server, 5);

    //cout << "Chat server running on port " << PORT << "\n";
    bool status=true;
    ll cur=0;
    while(status){
        sockaddr_in address;
        socklen_t len=sizeof(address);
        ll cid=accept(server, (sockaddr*)&address,&len);
        cur++;
        clients[cur]=cid;
        thread(handler,server,cur).detach();
    }
    return 0;
}