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

"body::before{content:'';position:fixed;inset:0;background:rgba(0, 0, 0, 0.66);pointer-events:none;}"

".container{display:flex;width:100vw;height:100vh;}"

/* USERS PANEL */
".users{width:250px;background:rgba(0, 0, 0, 0.68);backdrop-filter:blur(15px);"
"color:white;padding:10px;overflow-y:auto;border-right:1px solid rgba(255, 255, 255, 0.52);} "

".user{padding:10px;margin:5px 0;border-radius:8px;cursor:pointer;"
"background:rgba(255,255,255,0.08);display:flex;justify-content:space-between;align-items:center;}"

".user:hover{background:rgba(76, 175, 79, 0.56);}"

/* ACTIVE */
".active{border:2px solid #2196f3;background:rgba(33, 149, 243, 0.41);}"

/* ONLINE DOT */
".online{width:8px;height:8px;background:#4caf50;border-radius:50%;display:inline-block;margin-left:5px;}"

/* UNREAD DOT */
".unread{width:8px;height:8px;background:#2196f3;border-radius:50%;display:inline-block;margin-left:5px;}"

/* CHAT */
".chatbox{flex:1;display:flex;flex-direction:column;color:white;}"

".topbar{padding:10px;margin:10px;background:rgba(255, 255, 255, 0.44);border-radius:10px;}"

".chat{flex:1;overflow-y:auto;padding:10px;display:flex;flex-direction:column;gap:8px;}"

/* MESSAGE COLORS (FIXED AS YOU SAID) */
".msg{max-width:65%;padding:10px;border-radius:12px;white-space:pre-wrap;"
"color:#fff;display:flex;justify-content:space-between;align-items:center;}"

/* YOU → GREEN */
".me{align-self:flex-end;background:rgba(73, 232, 78, 0.98);color:white;}"

/* OTHER → BLUE */
".other{align-self:flex-start;background:rgba(33, 149, 243, 0.94);color:white;}"

/* INPUT (SAME THEME AS YOUR ORIGINAL) */
".inputbar{display:flex;gap:8px;padding:10px;margin:10px;"
"background:rgba(11, 0, 0, 0.29);border-radius:10px;}"

".inputbar input,.inputbar textarea{"
"border:none;border-radius:8px;"
"background:rgba(5, 5, 5, 0.36);"
"color:white;outline:none;padding:10px;"
"}"

"#to{width:130px;}"

"#msg{flex:1;resize:none;min-height:40px;max-height:120px;overflow-y:auto;}"

".inputbar button{width:90px;border:none;border-radius:8px;"
"background:#4caf50;color:white;cursor:pointer;}"

"</style></head><body>"

"<div class='container'>"

/* USERS */
"<div id='users' class='users'></div>"

/* CHAT */
"<div class='chatbox'>"

"<div id='top' class='topbar'>Chatting with: None</div>"
"<div id='chat' class='chat'></div>"

"<div class='inputbar'>"
"<input id='to' placeholder='User'>"
"<textarea id='msg' placeholder='Message'></textarea>"
"<button onclick='sendMsg()'>Send</button>"
"</div>"

"</div></div>"

"<script>"

"let uid=new URLSearchParams(location.search).get('uid');"
"let ws=new WebSocket(`ws://${location.host}`);"

"let chat=document.getElementById('chat');"
"let users=document.getElementById('users');"
"let current=null;"

/* TRACK UNREAD */
"let unread = {};"

"ws.onopen=()=>ws.send('LOGIN:'+uid);"
"ws.onmessage=e=>handle(e.data);"

/* HANDLE */
"function handle(d){"

/* USERS */
"if(d.startsWith('USERS:')){"
"users.innerHTML='';"
"d.substring(6).split(',').forEach(u=>{"
"if(!u)return;"

"let x=document.createElement('div');"
"x.className='user';"

"let name=document.createElement('span');"
"name.innerText=u;"

"let right=document.createElement('span');"

/* ONLINE DOT */
"let dot=document.createElement('span');"
"dot.className='online';"
"right.appendChild(dot);"

/* UNREAD DOT */
"if(unread[u]){"
"let ud=document.createElement('span');"
"ud.className='unread';"
"right.appendChild(ud);"
"}"

"x.appendChild(name);"
"x.appendChild(right);"

"x.onclick=()=>selectUser(x,u);"

"users.appendChild(x);"
"});return;}"

/* HISTORY */
"if(d.startsWith('HISTORY:')){"
"let data=d.split(':').slice(2).join(':');"
"chat.innerHTML='';"

"data.split('|').forEach(m=>{"
"if(!m)return;"
"let i=m.indexOf(':');"
"let sender=m.substring(0,i);"
"let text=m.substring(i+1);"
"add(text,sender===uid);"
"});"

/* CLEAR UNREAD */
"unread[current]=false;"
"return;"
"}"

/* LIVE MSG */
"if(d.startsWith('MSG|')){"
"let p=d.split('|');"
"let from=p[1];"
"let to=p[2];"
"let text=p.slice(3).join('|');"

"if(from===current || to===current){"
"add(text,from===uid);"
"} else {"
"unread[from]=true;"
"}"
"}"
"}"

/* SELECT */
"function selectUser(el,u){"
"current=u;"
"document.querySelectorAll('.user').forEach(x=>x.classList.remove('active'));"
"el.classList.add('active');"
"document.getElementById('to').value=u;"
"chat.innerHTML='';"
"ws.send('GET:'+u);"
"}"

/* ADD */
"function add(t,self){"
"let x=document.createElement('div');"
"x.className='msg '+(self?'me':'other');"

"let span=document.createElement('span');"
"span.innerText=t;"

"let btn=document.createElement('button');"
"btn.innerText='⧉';"
"btn.style.background='transparent';"
"btn.style.border='none';"
"btn.style.color='white';"

"btn.onclick=()=>{"
"document.getElementById('msg').value=t;"
"};"

"x.appendChild(span);"
"x.appendChild(btn);"

"chat.appendChild(x);"
"chat.scrollTop=chat.scrollHeight;"
"}"

/* SEND */
"function sendMsg(){"
"let to=document.getElementById('to').value;"
"let m=document.getElementById('msg').value;"
"if(!to||!m)return;"
"ws.send('MSG:'+to+':'+m);"
"document.getElementById('msg').value='';"
"}"

/* SHIFT ENTER */
"document.getElementById('msg').addEventListener('keydown',function(e){"
"if(e.key==='Enter' && e.shiftKey){"
"e.preventDefault();"
"sendMsg();"
"}"
"});"

"</script></body></html>";
#endif