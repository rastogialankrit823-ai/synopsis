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
class user{
    str uid;
    str name;
    str pass;
    int sid;
    public:
      friend void make(user &a,str uid,str name,str pass,int sid);
};
void make(user &a,str uid,str name,str pass,int sid){
    a.uid=uid;
    a.name=name;
    a.pass=pass;
    a.sid=sid;
}
int main(){
    return 0;
}
