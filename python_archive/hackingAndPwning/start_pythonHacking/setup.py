from distutils.core import setup
import py2exe

options = {                                       #(1)
	"bundle_files" : 1,
	"compressed" : 1,
	"optimize"     : 2,
}

setup (                                           #(2)
	console = ["backdoorClient.py"],
	options = {"py2exe" : options},
	zipfile = None
)
