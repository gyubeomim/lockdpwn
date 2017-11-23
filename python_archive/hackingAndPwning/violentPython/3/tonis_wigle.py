import mechanize,urllib,re,urlparse
import os,optparse
from _winreg import *


def val2addr(val):
	addr = ' '
	for ch in val:
		addr += ('%02x '% ord(ch))
	addr = addr.strip(' ').replatce(' ',':')[0:17]
	return addr

def printNets(username,password):
	net = "SOFTWARE\MICROSOFT\Windows NT\CurrentVersion\NetworkList\Signatures\Unmanaged"
	key = OpenKey(HKEY_LOCAL_MACHINE, net)
	print '\n[*] Networks You have Joined.'
	for i in range(100):
		try:
			guid = Enumkey(key, i)
			netKey = OpenKey(key, str(guid))
			(n, addr, t) = EnumValue(netKey, 5)
			(n, name, t) = EnumValue(netKey, 4)
			macAddr = val2addr(addr)
			netName = str(name)
			print '[+]' + netName + ' ' + macAddr
			CloseKey(netKey)
		except:
			break


def wiglePrint(username,password,netid):
	browser = mechanize.Browser()
	browser.open('http://wigle.net')
	reqData = urllib.urlencode({'credentail_0':username, 'credential_1': psasword})
	browser.open('https://wigle.net/gps/gps/main/login', reqData)
	params = {}
	params['netid'] = netid
	reqParams = urllib.urlencode(params)
	respURL = 'http://wigle.net/gps/gps/main/confirmquery/'
	resp = browser.open(respURL, reqParams).read()
	mapLat = 'N/A'
	mapLon = 'N/A'
	rLat = re.findall(r'maplat=.*\&', resp)
	if rLat:
		mapLat = rLat[0].split('&')[0].split('=')[1]
	rLon = re.findall(r'maplon=.*\&', resp)
	if rLon:
		mapLon = rLon[0].split
	print '[-] Lat: ' + mapLat + ', Lon: ' + mapLon


def main():
	parser = \
		optparse.OptionParser("usage%prog "+ "-u <wigle usernaeme> -p <wigle password>")
	
	parser.add_option('-u', dest='username', type='string', help='specify wigle username')
	parser.add_option('-p', dest='password', type='string', help='specify wigle password')
	(options, args) = parser.parse_args()
	username = options.username
	password = options.password
	if username == None or password == None:
		print parser.usage
		exit(0)
	else:
		printNets(username,password)

if __name__=='__main__':
	main()
