#ifndef USERCLASS_H
#define USERCLASS_H
#define str string
using namespace std;
class user{
    public:
    str uid;
    str name;
    str pass;
    int sid;
      friend void make(user &a,str uid,str name,str pass,int sid);
};
void make(user &a,str uid,str name,str pass,int sid){
    a.uid=uid;
    a.name=name;
    a.pass=pass;
    a.sid=sid;
}
#endif