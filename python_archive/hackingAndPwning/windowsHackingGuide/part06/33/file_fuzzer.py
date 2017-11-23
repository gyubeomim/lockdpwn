# -*- coding: utf-8 -*-
''' 
	## File Format Dumb Fuzzer v0.1 - by hyunmini ##

					Last Updated. 2016.01.02

					Requirements : 
						Python 2.7.x
						PyDBG
'''
# for fuzzer
try:
	from pydbg import *
	from pydbg.defines import *
except ImportError:
	raise ImportError(u'[Error!!] PyDBG 가 존재하지 않습니다. 먼저 PyDBG를 설치해 주세요.')
import random
import math
import os, sys
import threading
import glob
import time
import utils
import shutil
from datetime import datetime
import gc
import subprocess

def Print_Usage():
	print " Usage : %s [target] [ext]" % sys.argv[0]
	print "  ex) %s \"c:\\test\\target.exe\" jpg"  % sys.argv[0]
	sys.exit()
	
class File_Fuzzer:
	'''  Main Fuzzer Class '''
	def __init__(self, target, ext):
		self.base_path = os.getcwd() + "\\"
		self.target = target
		self.target_path = self.base_path + os.path.basename(target) + "\\"
		self.sample_path = self.base_path + "samples\\"
		self.test_path = self.target_path + "test\\"
		self.crash_path = self.target_path +  "crash\\"
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
		sample_list = glob.glob(self.sample_path + "*."+self.sample_ext)
		if len(sample_list) < 1:
			print u" [-] 샘플이 존재하지 않습니다. sample 폴더를 확인해 주세요."
			sys.exit()
		sample = random.choice(sample_list)
		self.sample_stream = open(sample,"rb").read()
		return 

	def Mutate(self):
		# case 0 : 값을 랜덤하게 변경한다.
		# case 1 : 값을 랜덤하게 삽입한다.
		global mutated_stream
		global mutate_byte
		test_cases = [ "\x00", "\xff", "\x41", "%s"]
		case = random.randint(0, 1)
		mutate_count = random.randint(1,10)
		test_cases.append(str(random.randint(0,255)))
		mutate_byte = random.choice(test_cases)

		if case == 0:   # replace
			for i in range(mutate_count):
				mutate_offset = random.randint(1, len(self.sample_stream)) # 변경 offset 
				mutate_len = random.randint(1,4)	# 변경 바이트 길이
				mutated_stream = self.sample_stream[0:mutate_offset]
				mutated_stream += mutate_byte * mutate_len
				mutated_stream += self.sample_stream[mutate_offset + mutate_len:]
			print "  [+] Mutated %d counts(replace %d bytes)" % (mutate_count, mutate_len) 

		else:			# add
			mutate_offset = random.randint(1, len(self.sample_stream)) # 변경 offset 
			mutate_len = random.randint(1,3000)	# 변경 바이트 길이
			mutated_stream = self.sample_stream[0:mutate_offset]
			mutated_stream += mutate_byte * mutate_len
			mutated_stream += self.sample_stream[mutate_offset:]
			print "  [+] Mutated %d bytes(add)" % (mutate_len) 

		self.case_name = self.test_path + "case-%s.%s" % (str(self.iter),self.sample_ext)
		f = open(self.case_name ,"wb")
		f.write(mutated_stream)
		f.close()
		return 

	def Monitor(self):
		time.sleep(3)
		if self.dbg.debugger_active:
			self.dbg.terminate_process()
			
		self.running = False

	def Crash_Handler(self,dbg):
		print " [+] Target Crashed !!"
		global crash_binn
		crash_binn = utils.crash_binning.crash_binning()
		crash_binn.record_crash(dbg)
		currtime = datetime.now().strftime("%Y%m%d_%H%M%S")
		crash_fname = self.crash_path + 'crash_case_' + str(self.iter)+'_'+ currtime + '.' + self.sample_ext
		context_fname = self.crash_path + 'crash_case_' + str(self.iter)+'_'+ currtime + '.txt'

		print '[+] Copy Crash file : ',crash_fname
		shutil.copyfile(self.case_name, crash_fname)
		
		f = open(context_fname,'w')
		f.write(crash_binn.crash_synopsis())
		f.close()
		self.crash_count += 1

		if dbg.debugger_active:
			dbg.terminate_process()
		
		self.running = False

		return DBG_CONTINUE

	def Run(self):
		self.running = True
		self.dbg = pydbg()
		self.dbg.set_callback(EXCEPTION_ACCESS_VIOLATION, self.Crash_Handler)
		args = "\"" + self.case_name + "\""
		self.dbg.load(self.target, args)
		self.dbg.run()

	def Clean(self):
		print u" [+] 파일 및 메모리 정리 중입니다. "
		# 파일 정리 - 크래시 발생하지 않은 파일 모두 삭제 
		flist = glob.glob(self.test_path + "*." + self.sample_ext)
		try:
			for f in flist:
				os.remove(f)
		except:
			pass
		print u"  [*] %d 개의 테스트 파일을 삭제했습니다." % len(flist)
		# 메모리 정리 
		print u"  [*] %d 개의 객체가 정리되었습니다." % gc.collect()

	def Fuzzing(self, count):
		while 1:
			while 1:
				if self.running == True:
					time.sleep(1)
				else:
					break

			print "\n[+] Fuzzing...[Case : %d] " % self.iter
			
			self.File_Picker()
			self.Mutate()
			
			pydbg_thread = threading.Thread(target=self.Run)
			pydbg_thread.setDaemon(0)
			pydbg_thread.start()

			monitor_thread = threading.Thread(target=self.Monitor)
			monitor_thread.setDaemon(0)
			monitor_thread.start()

			if self.iter % 100 == 0:
				self.Clean()
				
			self.iter += 1
	
				
if __name__ == '__main__':
	print u"\n\t[*] File Format Dumb Fuzzer v0.1 by hyunmini \n"
	if len(sys.argv) != 3:
		Print_Usage()
	myfuzzer = File_Fuzzer(sys.argv[1], sys.argv[2])
	myfuzzer.Fuzzing(50000)