#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 
'''
from mechanize import Browser
import re
import os

class ETNEWS:
	_login_url = "https://member.etnews.co.kr/member/login.html"
	_pdf_url = "http://pdf.etnews.co.kr/download_zip.html?p_date="

	def __init__(self):
		self.login("아이디", "패스워드")

	def login(self, username, password):
		self.br = Browser()
		self.br.set_handle_robots(False)
		self.br.open(self._login_url)
		self.br.select_form(name='loginFrm')
		self.br['id'] = username
		self.br['pw'] = password
		self.br.submit()

	def get_pdf_data(self, date):
		print 'Downloading ... : ' + self._pdf_url + date
		file = self.br.open(self._pdf_url + date, "today_news" + date + ".zip").read()
		
		f = open("today_news" + date + ".zip", "wb")
		f.write(file)
		f.close

		print 'Download Complete.'

	def get_content(self): 
		import time
		date = time.strftime("%Y%m%d", time.gmtime())
		self.get_pdf_data(date)


if __name__ == '__main__':
	import sys
	se = ETNEWS()
	se.get_content()
