#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> violent python, PDF 파일을 읽어서 메타데이터를 출력해주는 예제 코드
'''
import optparse
import pyPdf
from pyPdf  import PdfFileReader
import sys

# UTF-8으로 설정 안해주면 Unicode 오류가 난다 (git-bash에서만)
reload(sys)
sys.setdefaultencoding('utf8')

def printMeta(fileName):
	pdfFile = PdfFileReader(file(fileName, 'rb'))
	docInfo = pdfFile.getDocumentInfo()

	print '[*] PDF MetaData For : ' + str(fileName)

	for metaItem in docInfo:
		print '[+] ' + metaItem + ':' + docInfo[metaItem]

def main():
	parser = optparse.OptionParser('usage%prog  "+ "-f <pdf file name>')

	parser.add_option('-f', dest = 'fileName', type = 'string',\
					  help = 'specify pdf file name')

	(options, args) = parser.parse_args()
	fileName = options.fileName

	if fileName == None :
		print parser.usage
		exit(0)
	else:
		printMeta(fileName)


if __name__ == '__main__':
	main()
