#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> naver, daum 웹툰의 페이지를 가져와 띄워주는 코드 (정상동작 안함)

    code from [http://qkqhxla1.tistory.com/358]
'''
from PyQt4 import QtGui, QtCore
from PyQt4.QtWebKit import *
from PyQt4.QtNetwork import QNetworkAccessManager

import sys
import urllib2
import re
import time
import operator
import win32gui
from _winreg import *

webtoon_list_page = urllib2.urlopen('http://qkqhxla1.tistory.com/381').read().decode('utf-8').split('\'sun\']</p>')[1].split('<p></p><div style=')[0]
webtoon_list_page = re.findall('<p>(.*?)</p>', webtoon_list_page)

original_mouse_scroll_size = 0
SPI_SETWHEELSCROLLLINES = 0x0069

def switch_wheel_scroll_size(on):
    global original_mouse_scroll_size
    if on:
        original = OpenKey(HKEY_CURRENT_USER, "Control Panel\\Desktop")
        value, type = QueryValueEx(original, "WheelScrollLines")
        original_mouse_scroll_size = value
        win32gui.SystemParametersInfo(SPI_SETWHEELSCROLLLINES, 10)
    else:
        win32gui.SystemParametersInfo(SPI_SETWHEELSCROLLLINES, int(original_mouse_scroll_size))


n_today_webtoon = {}
def get_today_webtoon( ):
    global n_today_webtoon, my_webtoon_naver_daum
    days = ['mon', 'tue', 'wed', 'thu', 'fri', 'sat', 'sun']
    today = days[time.localtime().tm_wday]

    for list in webtoon_list_page:
        if list != '':
            l = list.split(', ')
            if len(l)==3 and l[2]==today:
                n_today_webtoon[l[0]] = l[1]
            else:
                for i in xrange(len(l)):
                    if l[i] == today:
                        n_today_webtoon[l[i]] = l[1]
    n_today_webtoon[''] = u'네이버웹툰'
    n_today_webtoon[''] = u'다음웹툰'
    n_today_webtoon = sorted(n_today_webtoon.iteritems(), key=lambda x:x[0])


def main():
    global n_today_webtoon
    get_today_webtoon()

    naver = u'네이버::'; 
    daum = u'다음::';
    app = QtGui.QApplication(sys.argv)
    tabs = QtGui.QTabWidget()

    switch_wheel_scroll_size(True)

    for link,name in n_today_webtoon:
        web = QWebView()
        web.settings().setAttribute(QWebSettings.PluginsEnabled, True)
        web.load(QtCore.QUrl(link))

        tabs.resize(1100, 700)
        tabs.move(100,50)

        if link.find('naver') != -1:
            if name.find(u'신작') != -1:
                tabs.addTab(web, name)
            else:
                tabs.addTab(web, naver+name)
        elif link.find('daum') != -1:
            if name.fin(u'신작') != -1:
                tabs.addTab(web, name)
            else:
                tabs.addTab(web, daum+name)

        tabs.setWindowTitle(u'Comic Viewer')
        tabs.show()
        _exit = app.exec_()
        switch_wheel_scroll_size(False)
        sys.exit(_exit)

if __name__ == '__main__':
    main()

