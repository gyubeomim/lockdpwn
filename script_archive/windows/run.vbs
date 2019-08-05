' vbs ==> hacking15, install.vbs 파일에 의해 시작프로그램으로 등록되는 코드
Dim ws, fso
Set ws = wscript.createobject("wscript.shell")

ws.run "calc.exe"
wscript.sleep 2000


