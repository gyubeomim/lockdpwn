#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 
'''
from immlib import *

def main(args):
    imm = Debugger()
    search_code = " ".join(args)
    search_bytes = imm.Assemble(search_code)
    search_results = imm.Search(search_bytes)

    for hit in search_results:
        code_page = imm.getMeomoryPagebyAddress(hit)
        access = code_page.getAccess(human = True)

        if "execute" in access.lower():
                imm.log("[*] Found: %s (0x%08x)" % ( searchh_code,hit), address = hit)

    return "[*] Finished searcching for instructions, check the Log window."
