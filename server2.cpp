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
map<ll,ll>user;
map<str,str>ids;
void gen(int server,ll cci){
    sockaddr_in address;
    socklen_t len=sizeof(address);
    ll cid=accept(server, (sockaddr*)&address,&len);
    //int client_sock = accept(server_fd, (sockaddr*)&address, (socklen_t*)&addrlen);
    clients[cci]=cid;
    char uid[1024],pass[1024];
    read(cid, uid, 1024);
    read(cid, pass, 1024);
    str cuid(uid),cpass(pass);
    if(ids.find(cuid)==ids.end())ps=0; 

    //return ps;
}
void genc(int server,ll cci){
    sockaddr_in address;
    socklen_t len=sizeof(address);
    ll cid=accept(server,(sockaddr*)&address,&len);
    user[cci]=cid;
    
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
        ll pcur=0;
        vector<thread>threads1;
        while(pcur<=100){
            ps=1;
            threads1.emplace_back(gen,server,pcur);
            if(ps==1){
                cur++;
            }
            pcur++;
        }
        for(auto &f1:threads1)f1.join();

    }
    return 0;
}