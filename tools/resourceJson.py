# -*- coding: utf-8 -*-
import sys
import os, os.path
import shutil
import ConfigParser
import subprocess
import re
import json
from contextlib import contextmanager

configNore = ("png","json","plist","ExportJson","tmx")
# def isWriteConfig(name):
# 	if group in not_rotate:
# 		return True
# 	return False
def main():
	project_root = os.path.abspath(os.path.join(os.path.dirname(__file__)))
	res_list_file = open(os.path.join(project_root, "../HitMonster2048/resource.json"), 'w')
	resObj = []
	for root, dirs, files in os.walk(os.path.join(project_root, "../HitMonster2048/res")):
		print "root:" , root
		print "dirs:" , dirs
		for f in files:
			if f.lower().endswith(configNore):
				print f
				resObj.append(f)

	res_list_file.write(json.dumps(resObj, indent=4))
	res_list_file.close()
# -------------- main --------------
if __name__ == '__main__':
    main()