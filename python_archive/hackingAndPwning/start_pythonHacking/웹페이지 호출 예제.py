import urllib
import urllib2

url = "http://server/wordpress/wp-login.php"                              #(1)

values = {'log': 'python', 'pwd': 'python1'}                              #(2)
headers = {'User-Agent': 'Mozilla/4.0(compatible;MISE 5.5; Windows NT)'}  #(3)
data = urllib.urlencode(values)                                           #(4)

request = urllib2.Request(url, data, headers)                             #(5)
response = urllib2.urlopen(request)                                       #(6)

print "#URL:%s"  % response.geturl()                                       #(7)
print "#CODE:%s" % response.getcode()
print "#INFO:%s" % response.info()
print "#DATA:%s" % response.read()
