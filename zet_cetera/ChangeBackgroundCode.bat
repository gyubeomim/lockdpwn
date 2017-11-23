

reg add "HKCU\Control Panel\Desktop" /v Walpaer /f /t REG_SZ /d C:\Users\admin\Desktop\4.jpg

copy /Y C:\Users\admin\Desktop\4.jpg C\Users\admin\Appdata\Roaming\Microsoft\Windows\Themes\TranscodedWallpaper.jpg

taskkill /im explorer.exe /f

start explorer.exe
