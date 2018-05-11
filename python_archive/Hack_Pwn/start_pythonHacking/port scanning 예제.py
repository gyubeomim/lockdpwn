import sys
import os
import socket
import nmap                                                        #(1)

nm = nmap.PortScanner()                                            #(2)

nm.scan(remoteServerIP, '1-1024')                                  #(3)

for host in nm.all_hosts():                                        #(4)
    print('----------------------------------------------------')
    print('Host : {0} ({1})'.format(host, nm[host].hostname()))    #(5)
    print('State : {0}'.format(nm[host].state()))                  #(6)

    for proto in nm[host].all_protocols():                         #(7)
        print('----------')
        print('Protocol : {0}'.format(proto))                        

        lport = list(nm[host][proto].keys())                       #(8)
        lport.sort()
        for port in lport:
            print('port : {0}\tstate : {1}'.format(port, nm[host][proto][port]))   #(9)
print('----------------------------------------------------')
