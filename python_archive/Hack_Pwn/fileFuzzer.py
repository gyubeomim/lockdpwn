#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> 윈도우해킹가이드, File Fuzzer를 직접 작성해본 코드
'''
try:
	from pydbg import *
	from pydbg.defines import *

except ImportError:
	raise ImportError(u'[Error!!] pyDBG가 존재하지 않습니다.')

import random
import threading
import shutil
import utils
import time
import os
import sys
import glob
from datetime import datetime
import gc
import subprocess
import smtplib


def send_gmail(gmail_id, gmail_pass, to, subject , body):
	session = smtplib.SMTP('smtp.gmail.com', 587)
	session.ehlo()
	session.starttls()
	session.ehlo
	session.login(gmail_id, gmail_pass)
	session = session

	headers =[
		"From: " + gmail_id,
		"Subject: " + subject,
		"To: " + to,
		"MIME-Version: 1.0",
		"Content-Type: text/html"]

	headers = "\r\n".join(headers)
	session.sendmail(
		gmail_id,
		to,
		headers + "\r\n\r\n" + body)


def Print_Usage():
	print " Usage : %s [target] [ext]" % sys.argv[0]
	print "  ex) %s \"c:\\test\\target.exe\" jpg"  % sys.argv[0]
	sys.exit()


class fileFuzzer:
	def __init__(self, target ,ext):
		self.base_path = os.getcwd() + "\\"
		self.target = target
		self.target_path = self.base_path + os.path.basename(target) + "\\"
		self.sample_path = self.base_path + "samples\\"
		self.test_path = self.target_path + "test\\"
		self.crash_path = self.target_path + "crash\\"

		self.sample_ext = ext

		self.sample_stream = None
		self.case_name = None
		self.iter = 1
		self.running = False
		self.crash_count = 0
		self.dbg = None

		# 폴더 생성
		if not os.path.exists(self.target_path):
			os.mkdir(self.target_path)
		if not os.path.exists(self.sample_path):
			os.mkdir(self.sample_path)
		if not os.path.exists(self.test_path):
			os.mkdir(self.test_path)
		if not os.path.exists(self.crash_path):
			os.mkdir(self.crash_path)


	def File_Picker(self):
		sample_list = glob.glob(self.sample_path + "*." + self.sample_ext)

		if len(sample_list) < 1:
			print u" [-] 샘플이 존재하지 않습니다. sample폴더를 확인해주세요"
			sys.exit()

		sample = random.choice(sample_list)
		self.sample_stream = open(sample, "rb").read()
		return


	def Mutate(self):
		# case 0 : 값을 랜덤하게 변경한다
		# case 1 : 값을 랜덤하게 삽입한다
		global mutated_stream
		global mutate_byte

		test_cases = [ "\x00", "\xff", "\x41", "%s"]
		test_cases.append(str(random.randint(0,255)))  # 랜덤한 문자열 추가

		case = random.randint(0, 1)

		mutate_count = random.randint(1, 10)
		mutate_byte = random.choice(test_cases)

		if case == 0: # replace
			for i in range(mutate_count):
				mutate_offset = random.randint(1, len(self.sample_stream))
				mutate_len = random.randint(1,4)

				mutated_stream = self.sample_stream[0:mutate_offset]
				mutated_stream += mutate_byte * mutate_len
				mutated_stream += self.sample_stream[mutate_offset + mutate_len:]

				print "[+] Mutated %d counts(replace %d bytes)" % (mutate_count, mutate_len)

		else:  # insert
			mutate_offset = random.randint(1, len(self.sample_stream))
			mutate_len = random.randint(1,3000)

			mutated_stream = self.sample_stream[0:mutate_offset]
			mutated_stream += mutate_byte * mutate_len
			mutated_stream += self.sample_stream[mutate_offset:]

			print "[+] Mutated %d bytes(add)" % (mutate_len)


		self.case_name = self.test_path + "case-%s.%s" % (str(self.iter), self.sample_ext)

		f = open(self.case_name , "wb")
		f.write(mutated_stream)
		f.close()

		return


	def Run (self):
		self.running = True
		self.dbg = pydbg()

		# 크래시 콜백 처리함수 등록
		self.dbg.set_callback(EXCEPTION_ACCESS_VIOLATION, self.Crash_Handler)
		args = "\"" + self.case_name + "\""

		self.dbg.load(self.target, args) # dbg로 대상프로그램 로딩
		self.dbg.run()


	def Monitor(self):
		time.sleep(1.5)

		if self.dbg.debugger_active:
			self.dbg.terminate_process() # 프로세스 강제 종료

		self.running = False


	def Crash_Handler(self,dbg ):
		print "[+] Target Crashed !!"
		global crash_binn

		crash_binn = utils.crash_binning.crash_binning()
		crash_binn.record_crash(dbg)
		currtime = datetime.now().strftime("%Y%m%d_%H%M%S")

		crash_fname = self.crash_path + 'crash_case_' + str(self.iter) + '_' + currtime + '.' + self.sample_ext
		context_fname = self.crash_path + 'crash_case_' + str(self.iter) + '_' + currtime + '.txt'

		print '[+] Copy Crash File : ' , crash_fname
		shutil.copyfile(self.case_name , crash_fname)

		f = open(context_fname, 'w')
		f.write(crash_binn.crash_synopsis())
		f.close()
		self.crash_count += 1

		if dbg.debugger_active:
			dbg.terminate_process()

		self.running  = False
		return DBG_CONTINUE


	def Clean(self):
		print u" [+] 파일 및 메모리 정리중입니다"
		flist = glob.glob(self.test_path + "*." + self.sample_ext)

		try:
			for f  in flist:
				os.remove(f)
		except:
			pass

		print u" [*] %d 개의 테스트 파일을 삭제했습니다 " % len(flist)
		# 메모리 정리
		print u" [*] %d 개의 객체가 정리되었습니다 " % gc.collect()


	def Fuzzing(self, count ):
		while True:
			while True:
				if self.running == True:
					time.sleep(1)
				else:
					break

			print "\n[+] Fuzzing ... [Case : %d] " % self.iter

			self.File_Picker()
			self.Mutate()

			pydbg_thread = threading.Thread(target = self.Run)
			pydbg_thread.setDaemon(0)
			pydbg_thread.start()

			monitor_thread = threading.Thread(target = self.Monitor)
			monitor_thread.setDaemon(0)
			monitor_thread.start()

			if self.iter % 100 == 0:
				self.Clean()
			#if self.iter % 20 == 0:
		#		self.Report()

			self.iter += 1


	def Report(self):
		print "create Report and Tranmitting..."
		title = "lockdpwn Fuzzer Report - " + os.path.basename(self.target) + datetime.now().strftime("%Y%m%d_%H%M%S")
		if self.crash_count > 0:
			title += "[crashes: %d]" % self.crash_count

		body = "<b> [Fuzzer Report] </b><br><br>"
		body += "Total Tested : %d <br><br>" % self.iter
		body += "Crashes : %d <br><br>" % self.crash_count
		body += "Target : %s <br><br>" % os.path.basename(self.target)
		body += "Ext : %s <br><br>" % self.sample_ext
		#body += "<br><br><img src=http://www.secuholic.com/img/secuholic_ci.PNG"
		send_gmail('id', 'pass', 'aa@gmail.com', title, body)





if __name__ == '__main__':
	print u"\n\t[*] file format dumb Fuzzer v0.1 by lockdpwn"

	if len(sys.argv) != 3:
		Print_Usage()

	myfuzzer = fileFuzzer(sys.argv[1] , sys.argv[2])
	myfuzzer.Fuzzing(10000)
