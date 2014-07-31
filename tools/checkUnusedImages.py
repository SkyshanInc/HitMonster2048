# -*- coding: utf-8 -*-
import os
import json
import commands

json_path = "../Resources/sd_other/"
img_path = "../Resources/sd/"
code_path = "../pokoSanguo/Resources/src/"

used_dict = {}

def appendUsedImagesFromFile(file_name):
	global used_dict
	def appendImgFromDict(dict_info):
		if not dict_info["path"]:
			return
		if not used_dict.has_key(dict_info["plistFile"]):
			used_dict[dict_info["plistFile"]] = []
		img_arr = used_dict[dict_info["plistFile"]]
		try:
			img_arr.index(dict_info["path"])
		except:
			img_arr.append(dict_info["path"])
			
	def appendChildrenImg(children):
		for child in children:
			if child.has_key("options"):
				options = child["options"]
				for key in options.keys():
					if isinstance(options[key], dict):
						val = options[key]
						if val.has_key("resourceType") and val["resourceType"] == 1:
							appendImgFromDict(val)
			appendChildrenImg(child["children"])

	f = open("%s%s" % (json_path, file_name))
	widget_data = json.loads(f.read())
	#print widget_data["widgetTree"]
	appendChildrenImg(widget_data["widgetTree"]["children"])


for file_name in os.listdir(json_path):
	if file_name.endswith(".json"):
		appendUsedImagesFromFile(file_name)

def checkStrInCode(str):
	output = commands.getstatusoutput("grep %s %s -R|wc -l" % (str, code_path))
	return int(output[1]) > 0

for img_dir in os.listdir(img_path):
	if not used_dict.has_key("%s.plist" % img_dir):
		if not checkStrInCode(img_dir):
			print "Dir not used in json files: %s" % img_dir
		continue
	for file_name in os.listdir("%s%s" % (img_path, img_dir)):
		if file_name == ".DS_Store" or file_name.startswith("icon_"):
			continue
		try:
			used_dict["%s.plist" % img_dir].index(file_name)
		except:
			if not checkStrInCode(file_name[:-6]):
			    print "%s/%s" % (img_dir, file_name)

