#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> 파이썬해킹프로그래밍,
'''
import pickle
import sys
import random
from ctypes import *

kernel32 = windll.kernel32
GENERIC_READ = 0x80000000
GENERIC_WRITE = 0x40000000
OPEN_EXISTING = 0x3

# pickle 파일을 열고 dictionary를 구한다
fd = open(sys.argv[1],"rb")
master_list = pickle.load(fd)
ioctl_list = master_list['ioctl_list']
device_list = master_list['device_list']
fd.close()

for device_name in device_list:
		# 해당 디바이스 이름으로의 접근이 가능한지 확인한다.
		device_file = u"\\\\.\\%s" % device_name.split("\\")[::-1][0]
		print "[*] Testing for device: %s" % device_file
		driver_handle = kernel32.CreateFileW(device_file, GENERIC_READ|\
																				 GENERIC_WRITE,0,None,OPEN_EXISTING,0,None)

		if driver_handle:
				print "[*] SUCCESS! %s is a valid device!"
				if device_file not in valid_devices:
						valid_devices.append(device_file)
				kernel32.CloseHandle(driver_handle)
		else:
				print "[*] Failed! %s NOT a valid device."

if not len(valid_devices):
		print "[*] No valid devices found. Exiting..."
		sys.exit(0)

# 드라이버 테스트 케이스를 이용해 퍼징을 끊임없이 수행한다
# 퍼징을 종료시키려면 ctrl + c 를 누른다..
while 1:
		# 먼저 로그파일을 연다
		fd = open('my_ioctl_fuzzer.log','a')
		# 임의의 디바이스 이름을 선택한다
		current_device = valid_devices[random.randint(0,len(valid_devices)-1)]
		fd.write("[*] Fuzzing: %s\n" % current_device)

		#임의의 IOCTL 코드를 선택한다
		current_ioctl = ioctl_list[random.randint(0,len(ioctl_list)-1)]
		fd.write("[*] With IOCTL: 0x%08x \n" % current_ioctl)

		# 버퍼의 길이를 선택한다.
		current_length = random.randint(0,10000)
		fd.write("[*] Buffer length: %d\n" % current_length)

		# A 문자로 버퍼를 채운다.
		# 나름대로의 테스트 케이스를 원한다면 이 곳을 수정하면 된다.
		in_buffer = "A" * current_length

		# out_buffer 를 설정한다
		out_buf = (c_char * current_lengt)()
		bytes_returned = c_ulong(current_length)

		# 핸들을 구한다
		driver_handle = kernel32.CreateFileW(device_file , 
                                                    GENERIC_READ| GENERIC_WRITE,
                                                    0,
                                                    None,
                                                    OPEN_EXISTING,
                                                    0,
                                                    None)

		fd.write("!!FUZZ!!\n")

		# 테스트 케이스를 실행한다.
		kernel32.DeviceIoControl(driver_handle, current_ioctl,in_buffer, 
                                        current_length,byref(out_buf), current_length,byref(bytes_returned),None)

		fd.write("[*] Test case finished. %d bytes returned. \n\n" %  bytes_returned.value)

		# 핸들을 닫는다
		kernel32.CloseHandle(driver_handle)
		fd.close()
