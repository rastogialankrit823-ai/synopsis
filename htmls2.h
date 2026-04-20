#ifndef HTMLS_H
#define HTMLS_H
#include <string>

std::string login =
"<!DOCTYPE html>"
"<html>"
"<head>"
"<title>Login</title>"
"<meta name='viewport' content='width=device-width, initial-scale=1.0'>"

"<style>"
"body {"
"  margin:0;"
"  font-family: Arial, sans-serif;"
"  background: linear-gradient(135deg,#1e3c72,#2a5298);"
"  display:flex;"
"  justify-content:center;"
"  align-items:center;"
"  height:100vh;"
"}"

".card {"
"  background:#111;"
"  padding:30px;"
"  border-radius:12px;"
"  width:300px;"
"  box-shadow:0 0 15px rgba(0,0,0,0.5);"
"  color:white;"
"}"

"h2 { text-align:center; margin-bottom:20px; }"

"input {"
"  width:100%;"
"  padding:10px;"
"  margin:10px 0;"
"  border:none;"
"  border-radius:6px;"
"}"

"button {"
"  width:100%;"
"  padding:10px;"
"  margin-top:10px;"
"  background:#4caf50;"
"  border:none;"
"  border-radius:6px;"
"  color:white;"
"  font-size:16px;"
"  cursor:pointer;"
"}"

"button:hover { background:#45a049; }"

".link {"
"  text-align:center;"
"  margin-top:10px;"
"  cursor:pointer;"
"  color:#4caf50;"
"}"

"#msg {"
"  text-align:center;"
"  margin-top:10px;"
"  color:#ff6b6b;"
"}"
"</style>"
"</head>"

"<body>"

"<div class='card'>"
"<h2>🔐 Login</h2>"

"<input id='u' placeholder='User ID'>"
"<input id='p' type='password' placeholder='Password'>"

"<button onclick='login()'>Login</button>"

"<div class='link' onclick='goSignup()'>Create account</div>"

"<p id='msg'></p>"
"</div>"

"<script>"

"function login(){"
"const uid=document.getElementById('u').value;"
"const pass=document.getElementById('p').value;"

"if(!uid || !pass){"
"document.getElementById('msg').innerText='Fill all fields';"
"return;"
"}"

"fetch('/login',{"
"method:'POST',"
"headers:{'Content-Type':'application/json'},"
"body:JSON.stringify({uid:uid,pass:pass})"
"})"
".then(r=>r.text())"
".then(data=>{"
"if(data==='ok'){"
"window.location.href='/home?uid='+uid;"
"}else{"
"document.getElementById('msg').innerText='Invalid credentials';"
"}"
"})"
".catch(()=>{"
"document.getElementById('msg').innerText='Server error';"
"});"
"}"

"function goSignup(){"
"window.location.href='/signup';"
"}"

"document.getElementById('p').addEventListener('keypress',function(e){"
"if(e.key==='Enter') login();"
"});"

"</script>"

"</body></html>";


std::string signup =
"<!DOCTYPE html>"
"<html>"
"<head>"
"<title>Sign Up</title>"
"<meta name='viewport' content='width=device-width, initial-scale=1.0'>"

"<style>"
"body {"
"  margin:0;"
"  font-family: Arial, sans-serif;"
"  background: linear-gradient(135deg,#1e3c72,#2a5298);"
"  display:flex;"
"  justify-content:center;"
"  align-items:center;"
"  height:100vh;"
"}"

".card {"
"  background:#111;"
"  padding:30px;"
"  border-radius:12px;"
"  width:300px;"
"  box-shadow:0 0 15px rgba(0,0,0,0.5);"
"  color:white;"
"}"

"h2 { text-align:center; margin-bottom:20px; }"

"input {"
"  width:100%;"
"  padding:10px;"
"  margin:10px 0;"
"  border:none;"
"  border-radius:6px;"
"}"

"button {"
"  width:100%;"
"  padding:10px;"
"  margin-top:10px;"
"  background:#4caf50;"
"  border:none;"
"  border-radius:6px;"
"  color:white;"
"  font-size:16px;"
"  cursor:pointer;"
"}"

"button:hover { background:#45a049; }"

".link {"
"  text-align:center;"
"  margin-top:10px;"
"  cursor:pointer;"
"  color:#4caf50;"
"}"

"#msg {"
"  text-align:center;"
"  margin-top:10px;"
"  color:#90ee90;"
"}"
"</style>"
"</head>"

"<body>"

"<div class='card'>"
"<h2>📝 Sign Up</h2>"

"<input id='u' placeholder='User ID'>"
"<input id='p' type='password' placeholder='Password'>"

"<button onclick='signup()'>Create Account</button>"

"<div class='link' onclick='goLogin()'>Already have an account?</div>"

"<p id='msg'></p>"
"</div>"

"<script>"

"function signup(){"
"const uid=document.getElementById('u').value;"
"const pass=document.getElementById('p').value;"

"if(!uid || !pass){"
"document.getElementById('msg').innerText='Fill all fields';"
"return;"
"}"

"fetch('/signup',{"
"method:'POST',"
"headers:{'Content-Type':'application/json'},"
"body:JSON.stringify({uid:uid,pass:pass})"
"})"
".then(r=>r.text())"
".then(data=>{"
"if(data==='ok'){"
"document.getElementById('msg').innerText='Account created! Redirecting...';"
"setTimeout(()=>{ window.location.href='/'; },1000);"
"}else{"
"document.getElementById('msg').innerText='Error';"
"}"
"})"
".catch(()=>{"
"document.getElementById('msg').innerText='Server error';"
"});"
"}"

"function goLogin(){"
"window.location.href='/';"
"}"

"document.getElementById('p').addEventListener('keypress',function(e){"
"if(e.key==='Enter') signup();"
"});"

"</script>"

"</body></html>";

std::string home =
"<!DOCTYPE html>"
"<html>"
"<head>"
"<title>Chat</title>"
"<meta name='viewport' content='width=device-width, initial-scale=1.0'>"

"<style>"

/* BACKGROUND */
"body {"
"  margin:0;"
"  font-family: Arial, sans-serif;"
"  background: linear-gradient(135deg,#1e3c72,#2a5298);"
"  height:100vh;"
"  display:flex;"
"  justify-content:center;"
"  align-items:center;"
"}"

/* CARD */
".card {"
"  width:800px;"
"  height:450px;"
"  background:#111;"
"  border-radius:12px;"
"  display:flex;"
"  flex-direction:column;"
"  padding:15px;"
"  box-shadow:0 0 20px rgba(0,0,0,0.6);"
"  color:white;"
"}"

/* HEADER */
".header {"
"  text-align:center;"
"  margin-bottom:10px;"
"}"

/* CHAT */
".chat {"
"  flex:1;"
"  overflow-y:auto;"
"  border:1px solid #333;"
"  border-radius:8px;"
"  padding:10px;"
"  background:#000;"
"  display:flex;"
"  flex-direction:column;"
"  position:relative;"
"}"

/* MESSAGE */
".msg {"
"  margin:5px 0;"
"  padding:8px 12px;"
"  border-radius:10px;"
"  max-width:70%;"
"}"

".me { background:#4caf50; margin-left:auto; }"
".other { background:#444; }"

".name { font-size:10px; opacity:0.7; }"

/* INPUT */
".input-area { margin-top:10px; }"

"input {"
"  width:100%;"
"  padding:10px;"
"  margin:5px 0;"
"  border:none;"
"  border-radius:6px;"
"}"

"button {"
"  width:100%;"
"  padding:10px;"
"  background:#4caf50;"
"  border:none;"
"  border-radius:6px;"
"  color:white;"
"  font-size:16px;"
"  cursor:pointer;"
"}"

"button:hover { background:#45a049; }"

/* 🟡 BALL */
".ball {"
"  position:absolute;"
"  left:30px;"
"  top:0;"
"  font-size:18px;"
"  animation: dropBall 0.7s ease-in forwards;"
"}"

/* ⚡ ASCII LINES */
".lines {"
"  position:absolute;"
"  left:25px;"
"  top:0;"
"  color:white;"
"  font-family: monospace;"
"  white-space: pre;"
"  animation: dropBall 0.7s ease-in forwards;"
"  opacity:0.8;"
"}"

/* ANIMATION */
"@keyframes dropBall {"
"  0% { transform: translateY(-80px); opacity:0; }"
"  70% { transform: translateY(200px); opacity:1; }"
"  100% { transform: translateY(180px); }"
"}"

"</style>"
"</head>"

"<body>"

"<div class='card'>"

"<div class='header'>"
"<h3>💬 Chat</h3>"
"<small id='user'></small>"
"</div>"

"<input id='to' placeholder='Send to user'>"

"<div id='chat' class='chat'></div>"

"<div class='input-area'>"
"<input id='msg' placeholder='Type a message...'>"
"<button onclick='sendMsg()'>Send</button>"
"</div>"

"</div>"

"<script>"

"let uid = new URLSearchParams(window.location.search).get('uid');"
"document.getElementById('user').innerText = uid;"

"let ws = new WebSocket(`ws://${location.host}`);"
"const chat = document.getElementById('chat');"

"ws.onopen = function(){ ws.send('LOGIN:'+uid); };"
"ws.onmessage = function(event){ handleMsg(event.data); };"

/* 🟡 BALL + ASCII LINES */
"function dropBallAndShow(text, self, sender){"

"  let lines = document.createElement('div');"
"  lines.className = 'lines';"
"  lines.innerText = '| |\\n  |\\n|\\n||';"

"  let ball = document.createElement('div');"
"  ball.className = 'ball';"
"  ball.innerText = '(0)';"

"  chat.appendChild(lines);"
"  chat.appendChild(ball);"

"  setTimeout(() => {"
"    lines.remove();"
"    ball.remove();"
"    addMsg(text, self, sender);"
"  }, 700);"
"}"

"function addMsg(text, self, sender){"
"  let box = document.createElement('div');"
"  box.className = 'msg ' + (self ? 'me' : 'other');"

"  if(!self){"
"    let name = document.createElement('div');"
"    name.className = 'name';"
"    name.innerText = sender;"
"    box.appendChild(name);"
"  }"

"  let content = document.createElement('div');"
"  content.innerText = text;"
"  box.appendChild(content);"

"  chat.appendChild(box);"
"  chat.scrollTop = chat.scrollHeight;"
"}"

"function handleMsg(data){"
"  let parts = data.split(':');"
"  let sender = parts[0];"
"  let text = parts.slice(1).join(':').trim();"
"  dropBallAndShow(text, sender===uid, sender);"
"}"

"function sendMsg(){"
"  const to = document.getElementById('to').value;"
"  const msg = document.getElementById('msg').value;"
"  if(!to || !msg) return;"
"  ws.send('MSG:'+to+':'+msg);"
"  dropBallAndShow(msg, true, uid);"
"  document.getElementById('msg').value='';"
"}"

"document.getElementById('msg').addEventListener('keypress',function(e){"
"  if(e.key==='Enter') sendMsg();"
"});"

"</script>"

"</body></html>";
#endif