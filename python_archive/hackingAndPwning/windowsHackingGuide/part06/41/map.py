import immlib
import re
import pefile

def usage(imm):
	imm.log("!map [mapfile]")
	imm.log(" ex) !map c:\\test.map")

def load_map(imm,filename):
	map_list = []
	f = open(filename, "r")
	contents = f.read()
	
	m=re.findall("\s+([\d\S]{4}):([\d\S]{8})\s+([^\d]\S+)",contents,re.M)
	if len(m) > 0:
		for line in m:
			map_list.append([int(line[0])-1, (int(line[1],16)), line[2]])
	return map_list

def main(args):
	imm = immlib.Debugger()
	imm.log("[*] Map v1.0 by hyunmini")
	if not args:
		usage(imm)
		return " [-] Not found map file"
	filename = args[0]
	map_list = load_map(imm,filename) 
	
	module = imm.getDebuggedName()
	mod = imm.getModule(module)
	pe = pefile.PE(mod.getPath()) 
	for map in map_list:
		base = mod.getBaseAddress()
		section = pe.sections[map[0]].VirtualAddress
		func_offset = map[1]
		lable = map[2]
		lable_addr = base + section + func_offset
		imm.setLabel(lable_addr, lable)
	return "[+] Finish!! %d symbols" % len(map_list)