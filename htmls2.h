#ifndef HTMLS_H
#define HTMLS_H
#include <string>

/* ================= LOGIN ================= */

std::string login =
"<!DOCTYPE html>"
"<html>"
"<head>"
"<title>Login</title>"
"<meta name='viewport' content='width=device-width, initial-scale=1.0'>"

"<style>"
"body{margin:0;font-family:Arial;height:100vh;display:flex;justify-content:center;align-items:center;"
"background:url(\"bg.jpg\") center/cover no-repeat;}"

"body::before{content:'';position:fixed;inset:0;background:rgba(0,0,0,0.6);z-index:-1;}"

".card{"
"background:rgba(255,255,255,0.08);"
"backdrop-filter:blur(12px);"
"padding:30px;"
"border-radius:12px;"
"color:white;"
"width:300px;"
"box-shadow:0 0 25px rgba(0,0,0,0.6);"
"}"

"input{width:100%;padding:10px;margin:10px 0;border:none;border-radius:6px;}"
"button{width:100%;padding:10px;background:#4caf50;border:none;border-radius:6px;color:white;cursor:pointer;}"
".link{margin-top:10px;text-align:center;cursor:pointer;color:#4caf50;}"
"#msg{text-align:center;color:#ff6b6b;}"
"</style>"
"</head>"

"<body>"
"<div class='card'>"
"<h2>Login</h2>"
"<input id='u' placeholder='User ID'>"
"<input id='p' type='password' placeholder='Password'>"
"<button onclick='login()'>Login</button>"
"<div class='link' onclick='goSignup()'>Create account</div>"
"<p id='msg'></p>"
"</div>"

"<script>"
"function login(){"
"let u=document.getElementById('u').value;"
"let p=document.getElementById('p').value;"
"fetch('/login',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify({uid:u,pass:p})})"
".then(r=>r.text()).then(d=>{"
"if(d==='ok')location.href='/home?uid='+u;"
"else document.getElementById('msg').innerText='Invalid';"
"});}"
"function goSignup(){location.href='/signup';}"
"</script>"

"</body></html>";

/* ================= SIGNUP ================= */

std::string signup =
"<!DOCTYPE html>"
"<html>"
"<head>"
"<title>Signup</title>"
"<meta name='viewport' content='width=device-width, initial-scale=1.0'>"

"<style>"
"body{margin:0;font-family:Arial;height:100vh;display:flex;justify-content:center;align-items:center;"
"background:url(\"bg.jpg\") center/cover no-repeat;}"

"body::before{content:'';position:fixed;inset:0;background:rgba(0,0,0,0.6);z-index:-1;}"

".card{background:rgba(255,255,255,0.08);backdrop-filter:blur(12px);padding:30px;border-radius:12px;color:white;width:300px;box-shadow:0 0 25px rgba(0,0,0,0.6);}"

"input{width:100%;padding:10px;margin:10px 0;border:none;border-radius:6px;}"
"button{width:100%;padding:10px;background:#4caf50;border:none;border-radius:6px;color:white;cursor:pointer;}"
".link{margin-top:10px;text-align:center;cursor:pointer;color:#4caf50;}"
"#msg{text-align:center;color:#90ee90;}"
"</style>"
"</head>"

"<body>"
"<div class='card'>"
"<h2>Sign Up</h2>"
"<input id='u' placeholder='User ID'>"
"<input id='p' type='password' placeholder='Password'>"
"<button onclick='signup()'>Create</button>"
"<div class='link' onclick='goLogin()'>Back to login</div>"
"<p id='msg'></p>"
"</div>"

"<script>"
"function signup(){"
"let u=document.getElementById('u').value;"
"let p=document.getElementById('p').value;"
"fetch('/signup',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify({uid:u,pass:p})})"
".then(r=>r.text()).then(d=>{"
"if(d==='ok'){document.getElementById('msg').innerText='Created';setTimeout(()=>location.href='/',1000);}"
"});}"
"function goLogin(){location.href='/';}"
"</script>"

"</body></html>";

/* ================= HOME ================= */

std::string home =
"<!DOCTYPE html>"
"<html>"
"<head>"
"<title>Chat</title>"
"<meta name='viewport' content='width=device-width, initial-scale=1.0'>"

"<style>"
"body{margin:0;font-family:Arial;height:100vh;display:flex;"
"background:url(\"bg.jpg\") center/cover no-repeat;}"

"body::before{content:'';position:fixed;inset:0;background:rgba(0,0,0,0.6);z-index:-1;}"

".container{display:flex;width:100vw;height:100vh;background:rgba(255,255,255,0.05);backdrop-filter:blur(10px);}"

/* SIDEBAR */
".users{width:220px;background:rgba(0,0,0,0.5);padding:10px;color:white;overflow:auto;}"
".users div{padding:8px;border-bottom:1px solid #333;cursor:pointer;}"
".users div:hover{background:#222;}"

/* CHAT */
".chatbox{flex:1;display:flex;flex-direction:column;padding:10px;color:white;}"
".chat{flex:1;background:rgba(0,0,0,0.4);padding:10px;border-radius:8px;overflow:auto;display:flex;flex-direction:column;}"

".msg{padding:8px;margin:5px 0;border-radius:8px;max-width:70%;}"
".me{background:#4caf50;margin-left:auto;}"
".other{background:#444;}"

/* INPUT ROW */
".row{display:flex;gap:5px;margin-top:5px;}"
".row input{flex:1;padding:10px;border:none;border-radius:6px;}"
".row button{width:80px;background:#4caf50;border:none;border-radius:6px;color:white;cursor:pointer;}"

/* ASCII */
".ascii{background:#000;color:#00ff90;font-family:monospace;padding:10px;margin-top:10px;border-radius:6px;height:120px;overflow:auto;white-space:pre;}"
"</style>"
"</head>"

"<body>"

"<div class='container'>"

/* USERS */
"<div id='users' class='users'></div>"

/* CHAT */
"<div class='chatbox'>"

"<input id='to' placeholder='Send to user'>"

"<div id='chat' class='chat'></div>"

"<div class='row'>"
"<input id='msg' placeholder='Message'>"
"<button onclick='sendMsg()'>Send</button>"
"</div>"

/* ASCII */
"<input id='botInput' placeholder='ASCII text'>"
"<button onclick='gen()'>Generate</button>"

"<div id='asciiOut' class='ascii'></div>"

"<button onclick='copy()'>Copy</button>"
"<button onclick='sendASCII()'>Send ASCII</button>"

"</div>"
"</div>"

"<script>"
"let uid=new URLSearchParams(location.search).get('uid');"
"let ws=new WebSocket(`ws://${location.host}`);"

"let chat=document.getElementById('chat');"
"let users=document.getElementById('users');"

"ws.onopen=()=>ws.send('LOGIN:'+uid);"
"ws.onmessage=e=>handle(e.data);"

"function handle(d){"
"if(d.startsWith('USERS:')){"
"users.innerHTML='';"
"d.substring(6).split(',').forEach(u=>{"
"if(!u)return;"
"let x=document.createElement('div');"
"x.innerText=u;"
"x.onclick=()=>document.getElementById('to').value=u;"
"users.appendChild(x);"
"});return;}"

"let p=d.split(':');"
"add(p.slice(1).join(':'),false);"
"}"

"function add(t,self){"
"let x=document.createElement('div');"
"x.className='msg '+(self?'me':'other');"
"x.innerText=t;"
"chat.appendChild(x);"
"chat.scrollTop=chat.scrollHeight;"
"}"

"function sendMsg(){"
"let to=document.getElementById('to').value;"
"let m=document.getElementById('msg').value;"
"if(!to||!m)return;"
"ws.send('MSG:'+to+':'+m);"
"add(m,true);"
"}"

"function gen(){"
"fetch('/ascii',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify({text:document.getElementById('botInput').value})})"
".then(r=>r.text()).then(d=>document.getElementById('asciiOut').innerText=d);"
"}"

"function copy(){navigator.clipboard.writeText(document.getElementById('asciiOut').innerText);}"

"function sendASCII(){"
"let to=document.getElementById('to').value;"
"let t=document.getElementById('asciiOut').innerText;"
"if(!to||!t)return;"
"ws.send('MSG:'+to+':'+t);"
"}"

"</script>"

"</body></html>";

#endif