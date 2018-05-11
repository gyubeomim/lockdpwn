from _winreg import *



def val2addr(val):
	addr = ""
	for ch in val:
		addr += ("%02x "% ord(ch))
	addr = addr.strip(" ").replatce(" ",":")[0:17]
	return addr

def printNets():
	net = "SOFTWARE\MICROSOFT\Windows NT\CurrentVersion\NetworkList\Signature\Unmanaged"
	ket = OpenKey(HKEY_LOAL_MACHINE, net)
	print '\n[*] Networks You have Joined.'
	for i in range(100):
		try:
			guid = Enumkey(key, i)
			netKey = OpenKey(key, str(guid))
			(n, addr, t) = EnumValue(netKey, 5)
			(n, name, t) = EnumValue(netKey, 4)
			macAddr = val2addr(addr)
			netName = str(name)
			print '[+]' + netName + ' ' + macaddr
			CloseKey(netKey)
		except:
			break


def main():
	printNets()

if __name__=="__main__":
	main()
