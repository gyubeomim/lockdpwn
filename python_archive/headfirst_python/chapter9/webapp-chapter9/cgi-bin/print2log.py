#! /usr/local/bin/python3

import os
import time
import sys

import yate

print(yate.start_response('text/plain'))

addr = os.environ['REMOTE_ADDR']
host = os.environ['REMOTE_HOST']
method = os.environ['REQUEST_METHOD']

cur_time = time.asctime(time.localtime())

print(host + ", " + addr + ", " + cur_time + ": " + method, file=sys.stderr)

print('OK.')
