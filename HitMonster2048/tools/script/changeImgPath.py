# -*- coding: utf-8 -*-
import os
import json
import commands

json_path = "../Resources/sd_other/"
old_img_name = "img_wjsj_tcfgx.png"
new_img_name = "img_seperate_line.png"
old_plist_file = "wjsj.plist"
new_plist_file = "publicImg.plist"


def checkAndReplace(file_name):
	def checkChildImg(dict_info):
		if not dict_info["path"]:
			return 0
		if dict_info["path"] == old_img_name:
		 	dict_info["path"] = new_img_name
			dict_info["plistFile"] = new_plist_file
		elif dict_info["plistFile"] == old_plist_file:
			return 1
		return 0
			
	def checkChildrenImg(children, result):
		for child in children:
			count = result[0]
			if child.has_key("options"):
				options = child["options"]
			for key in options.keys():
				if isinstance(options[key], dict):
					val = options[key]
					if val.has_key("resourceType") and val["resourceType"] == 1:
						count += checkChildImg(val)
			result[0] = count
			checkChildrenImg(child["children"], result)

	f = open("%s%s" % (json_path, file_name))
	widget_data = json.loads(f.read())
	f.close()

	try:
		widget_data["textures"].index(old_plist_file)
	except Exception, e:
		return

	result = [0]
	checkChildrenImg(widget_data["widgetTree"]["children"], result)
	if result[0] <= 0:
		try:
			index = widget_data["textures"].index(old_plist_file)
			del widget_data["textures"][index]
		except Exception, e:
			pass
		try:
			index = widget_data["textures"].index(new_plist_file)
		except Exception, e:
			widget_data["textures"].append(new_plist_file)

	print "%s: %s" % (file_name, result[0])

	f = open("%s%s" % (json_path, file_name))
	lines = []
	pre_is_texture = False
	pre_is_oldimg = False
	for line in f.readlines():
		lines.append(line)
		if line.find('textures": [') >= 0 and result[0] <= 0:
			pre_is_texture = True
		elif line.find(old_plist_file) >= 0 and pre_is_texture:
			pre_is_texture = False
			del lines[len(lines)-1]
			if line.find(",") < 0:
				lines[len(lines)-1] = lines[len(lines)-1].replace(',', '')
		elif line.find(old_img_name) >= 0:
			lines[len(lines)-1] = line.replace(old_img_name, new_img_name)
			pre_is_oldimg = True
		elif pre_is_oldimg and line.find(old_plist_file):
			lines[len(lines)-1] = line.replace(old_plist_file, new_plist_file)
			pre_is_oldimg = False

	f.close()

	f = open("%s%s" % (json_path, file_name),  "w")
	f.writelines(lines)
	f.close()


#	f = open("%s%s" % (json_path, file_name),  "w")
#	outStr = json.dumps(widget_data, ensure_ascii = False, sort_keys=True, indent=4)
#	f.write(outStr.encode('utf-8'))
#	f.close()


#checkAndReplace("cailiaoLVItem.json")
for file_name in os.listdir(json_path):
	if file_name.endswith(".json"):
		checkAndReplace(file_name)


