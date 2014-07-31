#encoding=utf-8
#!/usr/bin/python
# Build native codes
import os
import sys
import codecs
import xlrd
import json

reload(sys)
sys.setdefaultencoding( "utf-8" )

if len(sys.argv) != 3 :
	print "argv count != 3, program exit"
	print "please input excelfilename"
	exit(0)
print "excel to json"
excelFileName = sys.argv[1]
jsonfilename = sys.argv[2]

configJsonFile = open(os.path.join('config.json'))
configJsonData = json.load(configJsonFile)

print u"---------" , configJsonData['json_data']

configJsonFile.close()



def FloatToString (aFloat):
	if type(aFloat) != float:
		return ""
	strTemp = str(aFloat)
	strList = strTemp.split(".")
	print u"strList",strList
	if len(strList) == 1 :
		return int(strTemp)
	else:
		if strList[1] == "0" :
			return int(strList[0])
		else:
			return float(strTemp)

def table2jsn(table, jsonfilename):
	nrows = table.nrows
	ncols = table.ncols
	f = codecs.open(jsonfilename, "w", "utf-8")
	# f.write(u"[\n")
	key_IndexId = configJsonData.get("key_index")
	confgMap = configJsonData['json_data']
	key_indexName = None
	if key_IndexId:
		jj={}
		key_indexName = confgMap.get(key_IndexId)['key']
	else:
		jj = []
	for r in range(nrows-1):
        # f.write(u"\t{")
		tableData = {}
		jjkey = ""
		for c in range(ncols):
			strCellValue = u""
			CellObj = table.cell_value(r+1,c)
			valueType = type(CellObj)
			print u"valueType:" , valueType
			if type(CellObj) == unicode:
				strCellValus = CellObj
			elif type(CellObj) == float:
				strCellValus = FloatToString(CellObj)
				print u"float---:" , strCellValus
			else:
				strCellValus = str(CellObj)

			lineName = table.cell_value(0,c)
			print lineName , c
			congCodData = confgMap.get(lineName)
			if congCodData:
				key = congCodData.get("key")
				tableData[key] = strCellValus
		if key_indexName :
			jjkey = tableData[key_indexName]
			jj[jjkey] = tableData
		else:
			jj.append(tableData)
	f.write(json.dumps(jj,sort_keys=True,indent=4).decode("unicode-escape"))
	# f.write(u"]")
	f.close()
	print "Create", jsonfilename , "successful"
	return

sheetName = configJsonData['xsl_name']
print u'sheetName' , sheetName
data = xlrd.open_workbook(excelFileName)
table = data.sheet_by_name(sheetName)
table2jsn(table, jsonfilename)

print "ALL OK"