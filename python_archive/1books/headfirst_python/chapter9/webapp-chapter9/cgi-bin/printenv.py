#! /usr/local/bin/python3

import cgi
import sys

import yate

print(yate.start_response('text/html'))
print(cgi.print_environ())

print('---------------------------------------')
print(cgi.print_environ_usage())

