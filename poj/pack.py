#!/bin/python2
import pyperclip 
import re
import sys
import os

def pack(filename):
	abspath = os.path.abspath(filename)
	dirname = os.path.dirname(abspath)
	os.chdir(dirname)
	file = open(abspath, "r")
	data = ""
	pattern = re.compile('#include *"(.*)"')
	for line in file.readlines():
		m = pattern.match(line)
		if not m :
			data += line
		else:
			include_filename =  m.groups()[0]
			data += '// begin of ' + include_filename + '\n'
			data += pack(include_filename)
			data += '// end of ' + include_filename + '\n'
		
	return data
				

root_filename = sys.argv[1]
pyperclip.copy(pack(root_filename))

