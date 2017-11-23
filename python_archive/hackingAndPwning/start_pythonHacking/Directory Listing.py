from ftplib import FTP

apacheDir = "htdocs"
serverName = "server"
serverID = "server"
serverPW = "server"

def getDirList(cftp, name):
    dirList = []
    if("." not in name):
        if(len(name) == 0):
            dirList = ftp.nlst()
        else:
            dirList = ftp.nlst(name)               
    return dirList

def checkApache(dirName1, dirName2):
    if(dirName1.lower().find(apacheDir) >= 0):
        print dirName1
    if(dirName2.lower().find(apacheDir) >= 0):
        print dirName1 +"/"+ dirName2

ftp = FTP(serverName, serverID, serverPW)

dirList1 = getDirList(ftp, "")

for name1 in dirList1:
    checkApache(name1,"")
    dirList2 = getDirList(ftp, name1)
    for name2 in dirList2:
        checkApache(name1, name2)
        dirList3 = getDirList(ftp, name1+"/"+name2)
