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
 str login =
"<!DOCTYPE html>"
"<html>"
"<head><title>Login</title></head>"
"<body>"
"<h2>Login</h2>"
"<input id='u' placeholder='User ID'><br><br>"
"<input id='p' type='password' placeholder='Password'><br><br>"
"<button onclick='login()'>Login</button>"
"<button onclick='goSignup()'>Sign Up</button>"
"<p id='msg' style='color:red;'></p>"
"<script>"
"function login(){"
"const uid=document.getElementById('u').value;"
"const pass=document.getElementById('p').value;"
"fetch('/login',{"
"method:'POST',"
"headers:{'Content-Type':'application/json'},"
"body:JSON.stringify({uid:uid,pass:pass})"
"})"
".then(r=>r.text())"
".then(data=>{"
"if(data==='ok'){"
"window.location.href='/home';"
"}else{"
"document.getElementById('msg').innerText='Invalid credentials';"
"}"
"});"
"}"
"function goSignup(){"
"window.location.href='/signup';"
"}"
"</script>"
"</body></html>";



str home =
"<!DOCTYPE html>"
"<html>"
"<head><title>you have logged in successfully</title></head>"
"<body>"
"<h1><b>yo</b></h1>"
"<input id='u' placeholder='TO'><br><br>"
"<input id='p' type='password' placeholder='TEXT'><br><br>"
"<button onclick='sendMsg()'>SEND</button>"
"<p id='msg' style='color:red;'></p>"
"<script>"
"function login(){"
"const uid=document.getElementById('u').value;"
"const pass=document.getElementById('p').value;"
"fetch('/home',{"
"method:'POST',"
"headers:{'Content-Type':'application/json'},"
"body:JSON.stringify({uid:uid,pass:pass})"
"})"
".then(r=>r.text())"
".then(data=>{"
"}"
"});"
"}"
"function sendMsg(){"
    "const to = document.getElementById('u').value;"
    "const msg = document.getElementById('p').value;"

    "fetch('/home',{"
        "method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify({uid:to, pass:msg})});}"

"setInterval(()=>{"
    "fetch('/get')"
    ".then(r=>r.text())"
    ".then(data=>{"
        "if(data){"
            "document.getElementById('msg').innerText += data + '\n';"
        "}"
    "});"
"},200);"

"</script>"
"</body></html>";


str sign =
"<!DOCTYPE html>"
"<html>"
"<head><title>Sign Up</title></head>"
"<body>"
"<h2>Sign Up</h2>"
"<input id='u' placeholder='New User ID'><br><br>"
"<input id='p' type='password' placeholder='New Password'><br><br>"
"<button onclick='signup()'>Save</button>"
"<p id='msg' style='color:green;'></p>"
"<script>"
"function signup(){"
"const uid=document.getElementById('u').value;"
"const pass=document.getElementById('p').value;"
"fetch('/signup',{"
"method:'POST',"
"headers:{'Content-Type':'application/json'},"
"body:JSON.stringify({uid:uid,pass:pass})"
"})"
".then(r=>r.text())"
".then(data=>{"
"document.getElementById('msg').innerText=data;"
"if(data==='ok'){"
"window.location.href='/';"
"}else{"
"document.getElementById('msg').innerText='Invalid credentials';"
"}"
"});"
"}"
"</script>"
"</body></html>";
int main(){
    return 0;
}