import os, stat, mimetypes, httplib
import urllib, urllib2
from cookielib import CookieJar
import time

cj = CookieJar()                                                        #(1)
opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cj))          #(2)

url = "http://server/wordpress/wp-login.php"

values = {
    'log': "python",
    'pwd': "python"
}
headers = {
    'User-Agent':'Mozilla/4.0(compatible;MISE 5.5; Windows NT)',
    'Referer':'http://server/wordpress/wp-admin/'
}

data = urllib.urlencode(values)
request = urllib2.Request(url, data, headers)
response = opener.open(request)                                          #(3)
