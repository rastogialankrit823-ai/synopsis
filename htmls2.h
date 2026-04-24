#ifndef HTMLS2_H
#define HTMLS2_H
#include <string>


std::string login =
"<!DOCTYPE html>"
"<html><head>"
"<title>Login</title>"
"<meta name='viewport' content='width=device-width, initial-scale=1.0'>"

"<style>"
"body{margin:0;font-family:Arial;height:100vh;display:flex;justify-content:center;align-items:center;"
"background:url('bg.jpg') center/cover no-repeat;overflow:hidden;}"

"body::before{content:'';position:fixed;inset:0;background:rgba(0,0,0,0.55);backdrop-filter:blur(3px);}"

".card{"
"position:relative;"
"background:rgba(255,255,255,0.08);"
"backdrop-filter:blur(18px);"
"border:1px solid rgba(255,255,255,0.15);"
"padding:35px;"
"border-radius:16px;"
"color:white;"
"width:320px;"
"box-shadow:0 10px 40px rgba(0,0,0,0.5);"
"animation:fade .4s ease;"
"}"

"@keyframes fade{from{transform:translateY(10px);opacity:0;}to{transform:translateY(0);opacity:1;}}"

"h2{text-align:center;margin-bottom:20px;letter-spacing:1px;}"

"input{width:100%;padding:12px;margin:10px 0;border:none;border-radius:8px;outline:none;"
"background:rgba(255,255,255,0.15);color:white;}"

"button{width:100%;padding:12px;border:none;border-radius:8px;"
"background:linear-gradient(90deg,#4caf50,#2ecc71);color:white;font-weight:bold;cursor:pointer;}"

".link{text-align:center;margin-top:10px;color:#4caf50;cursor:pointer;font-size:14px;}"

"#msg{text-align:center;color:#ff6b6b;margin-top:8px;}"

"</style></head><body>"

"<div class='card'>"
"<h2>LOGIN</h2>"
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
"else document.getElementById('msg').innerText='Invalid credentials';"
"});}"
"function goSignup(){location.href='/signup';}"
"</script>"

"</body></html>";

 
std::string signup =
"<!DOCTYPE html><html><head>"
"<title>Signup</title>"
"<meta name='viewport' content='width=device-width, initial-scale=1.0'>"

"<style>"
"body{margin:0;font-family:Arial;height:100vh;display:flex;justify-content:center;align-items:center;"
"background:url('bg.jpg') center/cover no-repeat;overflow:hidden;}"
"body::before{content:'';position:fixed;inset:0;background:rgba(0,0,0,0.55);backdrop-filter:blur(3px);}"

".card{"
"background:rgba(255,255,255,0.08);"
"backdrop-filter:blur(18px);"
"border:1px solid rgba(255,255,255,0.15);"
"padding:35px;"
"border-radius:16px;"
"color:white;"
"width:320px;"
"box-shadow:0 10px 40px rgba(0,0,0,0.5);"
"}"

"h2{text-align:center;margin-bottom:20px;}"

"input{width:100%;padding:12px;margin:10px 0;border:none;border-radius:8px;"
"background:rgba(255,255,255,0.15);color:white;}"

"button{width:100%;padding:12px;border:none;border-radius:8px;"
"background:linear-gradient(90deg,#4caf50,#2ecc71);color:white;font-weight:bold;cursor:pointer;}"

".link{text-align:center;margin-top:10px;color:#4caf50;cursor:pointer;}"

"#msg{text-align:center;color:#90ee90;}"

"</style></head><body>"

"<div class='card'>"
"<h2>SIGN UP</h2>"
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
"if(d==='ok'){document.getElementById('msg').innerText='Account created';setTimeout(()=>location.href='/',1000);}"
"});}"
"function goLogin(){location.href='/';}"
"</script>"

"</body></html>";

 
std::string home =
"<!DOCTYPE html><html><head>"
"<title>Chat</title>"
"<meta name='viewport' content='width=device-width, initial-scale=1.0'>"

"<style>"

"body{margin:0;font-family:Arial;height:100vh;display:flex;"
"background:url('bg.jpg') center/cover no-repeat;overflow:hidden;}"

"body::before{content:'';position:fixed;inset:0;background:rgba(0,0,0,0.6);}"


".container{display:flex;width:100vw;height:100vh;position:relative;}"


".users{width:250px;backdrop-filter:blur(15px);"
"background:rgba(0,0,0,0.45);color:white;padding:10px;overflow:auto;"
"border-right:1px solid rgba(255,255,255,0.1);} "

".user{padding:10px;margin:5px 0;border-radius:8px;cursor:pointer;"
"background:rgba(255,255,255,0.08);transition:.2s;}"

".user:hover{background:rgba(76,175,80,0.4);}"


".active{border:2px solid #2196f3;background:rgba(33,150,243,0.15);}"


".chatbox{flex:1;display:flex;flex-direction:column;padding:15px;color:white;}"


".topbar{padding:10px 15px;margin-bottom:10px;"
"background:rgba(255,255,255,0.08);backdrop-filter:blur(10px);"
"border-radius:10px;font-weight:bold;}"


".chat{flex:1;overflow:auto;padding:10px;display:flex;flex-direction:column;gap:8px;}"


".msg{max-width:65%;padding:10px;border-radius:12px;word-wrap:break-word;}"

".me{align-self:flex-end;background:rgba(33,150,243,0.35);}"
".other{align-self:flex-start;background:rgba(76,175,80,0.25);}"


".row{display:flex;gap:8px;margin-top:10px;}"

"#to{width:150px;padding:12px;border:none;border-radius:8px;"
"background:rgba(255,255,255,0.15);color:white;}"

"#msg{flex:1;padding:12px;border:none;border-radius:8px;"
"background:rgba(255,255,255,0.15);color:white;}"

".row button{width:90px;border:none;border-radius:8px;"
"background:#2196f3;color:white;font-weight:bold;cursor:pointer;}"

"</style></head><body>"

"<div class='container'>"


"<div id='users' class='users'></div>"


"<div class='chatbox'>"

"<div id='top' class='topbar'>Chatting with: None</div>"

"<div class='chat' id='chat'></div>"


"<div class='row'>"
"<input id='to' placeholder='User'>"
"<input id='msg' placeholder='Message'>"
"<button onclick='sendMsg()'>Send</button>"
"</div>"

"</div></div>"

"<script>"

"let uid=new URLSearchParams(location.search).get('uid');"
"let ws=new WebSocket(`ws://${location.host}`);"

"let chat=document.getElementById('chat');"
"let users=document.getElementById('users');"
"let topbar=document.getElementById('top');"

"let current=null;"
"let history={};"   

"ws.onopen=()=>ws.send('LOGIN:'+uid);"
"ws.onmessage=e=>handle(e.data);"


"function handle(d){"

"if(d.startsWith('USERS:')){"
"users.innerHTML='';"
"d.substring(6).split(',').forEach(u=>{"
"if(!u)return;"
"let x=document.createElement('div');"
"x.innerText=u;"
"x.className='user';"
"x.onclick=()=>selectUser(x,u);"
"users.appendChild(x);"
"});return;}"


"if(d.startsWith('MSG|')){"
"let p=d.split('|');"
"let from=p[1];"
"let to=p[2];"
"let text=p.slice(3).join('|');"

"let other = (from===uid)?to:from;"


"if(!history[other])history[other]=[];"
"history[other].push({text:text,self:(from===uid)});"


"if(current===other)add(text,(from===uid));"
"}"
"}"


"function selectUser(el,u){"

"document.querySelectorAll('.user').forEach(x=>x.classList.remove('active'));"
"el.classList.add('active');"

"current=u;"
"document.getElementById('to').value=u;"
"topbar.innerText='Chatting with: '+u;"

"chat.innerHTML='';"


"if(history[u]){"
"history[u].forEach(m=>add(m.text,m.self));"
"}"
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
"}"

"</script></body></html>";
#endif