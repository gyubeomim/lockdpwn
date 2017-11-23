import idaapi

print "\n\n=================================="
print "  [*] SecuScan v1.0 by hyunmini   "
print "==================================\n"

vuln_functions = [ "strcpy", "sprintf", "strcat", "scanf" ]
result = []

ea = ScreenEA()
for function_ea in Functions(SegStart(ea), SegEnd(ea)):
	for vuln_func in vuln_functions:
		func_name = GetFunctionName(function_ea)
		if vuln_func in func_name:
			xrefs = CodeRefsTo(function_ea, 0)
			print "[+] Xref %s" % func_name
			for ref in xrefs:
				print " - 0x%08x" % ref
				SetColor(ref, CIC_ITEM, 0x1001FF)
				MakeComm(ref, " [+] Found Vuln Func !!")