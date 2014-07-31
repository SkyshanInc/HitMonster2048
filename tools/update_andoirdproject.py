#coding=utf-8
import glob
import os
import sys
import shutil
import subprocess

file_list=["LOCAL_SRC_FILES := hellocpp/main.cpp"]
source_code=u"../Classes"
source_code_path = "../../../"

def GetCppList(path):
    global file_list
    for fn in glob.glob(path + os.sep + "*.cpp"):
        file_list.append(source_code_path+fn)

    for fn in glob.glob(path + os.sep + "*.c"):
        file_list.append(source_code_path+fn)

def ReadAndroidMK():
    path="./Android.mk"
    file_object = open(path)
    all_the_text = ""
    try:
         all_the_text = file_object.read( )

    finally:
         file_object.close()
    return all_the_text

def UpdateMK(project):
    #CopySourceCodeToAndroidClassesDir()
    global file_list
    file_list=["LOCAL_SRC_FILES := hellocpp/main.cpp"]
    GetCppList(source_code)
    GetCppList(source_code + r"/android/")
    GetCppList(source_code + "/../libs/bs-common/common")
    GetCppList(source_code + "/../libs/bs-common/ui")
    GetCppList(source_code + "/../libs/bs-common/core")
    file_list.append(source_code_path + '../libs/cJSON/cJSON.c')
    str=" \\\n"
    cpp_list_str = str.join(file_list)

    all_the_text = ReadAndroidMK()
    index = all_the_text.find("#BEGIN")
    index += len("#BEGIN")
    mk_file_list = []
    mk_file_list.append(all_the_text[:index])

    mk_file_list.append(cpp_list_str)
    mk_file_list.append("LOCAL_C_INCLUDES := $(LOCAL_PATH)/"+source_code_path+source_code)
    mk_file_list.append("LOCAL_C_INCLUDES += $(LOCAL_PATH)/"+source_code_path+"../libs/cJSON")
    mk_file_list.append("LOCAL_C_INCLUDES += $(LOCAL_PATH)/"+source_code_path+"../libs/cocos2dx/cocos2dx/platform/third_party/android/prebuilt/libcurl/include/curl")
    mk_file_list.append("LOCAL_C_INCLUDES += $(LOCAL_PATH)/"+source_code_path+"../libs/cocos2dx/external/Box2D")
    mk_file_list.append("LOCAL_C_INCLUDES += $(LOCAL_PATH)/"+source_code_path+"../libs/cocos2dx/cocos2dx")
    mk_file_list.append("LOCAL_C_INCLUDES += $(LOCAL_PATH)/"+source_code_path+"../libs/bs-common/common")
    mk_file_list.append("LOCAL_C_INCLUDES += $(LOCAL_PATH)/"+source_code_path+"../libs/bs-common/ui")
    mk_file_list.append("LOCAL_C_INCLUDES += $(LOCAL_PATH)/"+source_code_path+"../libs/bs-common/core")
    index = all_the_text.find("#END")
    mk_file_list.append(all_the_text[index:])

    str="\n"
    export_str = str.join(mk_file_list)
    print u"Update "+project+" Android.mk"
    output=open("./android-"+project+"/proj.android/jni/Android.mk","w")
    output.write(export_str)
    output.close()

def UpdateBuildNativeSh(project):
    if project == "":
        path = "./android/proj.android"
    else:
        path = "./android-"+project+"/proj.android"
#    if project == "91":
#        path = "./android-91/proj.android"
#    else:
#        path = "./android/proj.android"

    file = open(os.path.join(path,"build_native.sh.copy"))
    file_data = file.read()
    path_file = open("./path.txt", "r")
    path_data = path_file.read()
    start = file_data.index("#BEGIN\n") + len("#BEGIN\n")
    end = file_data.index("#END")
    file_data = file_data[:start] + path_data + file_data[end:]
    file = open(os.path.join(path, "build_native.sh"), "w")
    file.write(file_data)
    file.close()
    #给程序赋予指定权限
    subprocess.call(["chmod", "u+x", os.path.join(path, "build_native.sh")])

def UpdateProjectFile():
    shutil.copy2("./local.properties", "./android-main/proj.android/local.properties")    #修改build_native.sh
    shutil.copy2("./local.properties", "./android-BW/proj.android/local.properties")    #修改build_native.sh
    shutil.copy2("./local.properties", "./android-UC/proj.android/local.properties")
    shutil.copy2("./local.properties", "./android-AZ/proj.android/local.properties")
    shutil.copy2("./local.properties", "./android-DX/proj.android/local.properties")
    shutil.copy2("./local.properties", "./android-XM/proj.android/local.properties")
    shutil.copy2("./local.properties", "./android-360/proj.android/local.properties")
    shutil.copy2("./local.properties", "./android-TWDGD/proj.android/local.properties")
    shutil.copy2("./local.properties", "./android-TWApp01/proj.android/local.properties")
    shutil.copy2("./local.properties", "./android-TWHami/proj.android/local.properties")
    shutil.copy2("./local.properties", "./android-91/proj.android/local.properties")
    shutil.copy2("./local.properties", "./android-Dangle/proj.android/local.properties")
    #修改build_native.sh
    shutil.copy2("./local.properties", "./android-UC/gamecomb_sdk_uc_lod_Libproject/local.properties")
    #修改build_native.sh
    shutil.copy2("./local.properties", "./android-BW/gamecomb_sdk_landscape_Libproject/local.properties")
    #修改build_native.sh
    if not os.path.exists("./android-BW/gamecomb_sdk_landscape_Libproject/src"):
        os.mkdir("./android-BW/gamecomb_sdk_landscape_Libproject/src")
        #subprocess.call("mkdir", "./android-BW/gamecomb_sdk_landscape_Libproject/src")    #修改build_native.sh
    #UpdateBuildNativeSh("main")
    #修改java工程的Bin目录文件
    path = "../libs/cocos2dx/cocos2dx/platform/android/java"
    shutil.copy2("./local.properties", path)
    path = os.path.join(path, "bin")
    shutil.copy2("./build.prop", os.path.join(path, "build.prop"))
    shutil.copy2("./java.jar", os.path.join(path, "java.jar"))
    shutil.copy2("./classes.jar", os.path.join(path, "classes.jar"))
    print "Update project ok"

#第一次要更新工程文件
if len(sys.argv) >= 2 and sys.argv[1] == "first":
    UpdateProjectFile()
    UpdateMK("main")
    UpdateMK("BW")
    UpdateMK("UC")
    UpdateMK("AZ")
    UpdateMK("DX")
    UpdateMK("XM")
    UpdateMK("360")
    UpdateMK("TWDGD")
    UpdateMK("TWApp01")
    UpdateMK("TWHami")
    UpdateMK("91")
    UpdateMK("Dangle")
elif len(sys.argv) < 2:
    UpdateMK("main")
    UpdateMK("BW")
    UpdateMK("UC")
    UpdateMK("AZ")
    UpdateMK("DX")
    UpdateMK("XM")
    UpdateMK("360")
    UpdateMK("TWDGD")
    UpdateMK("TWApp01")
    UpdateMK("TWHami")
    UpdateMK("91")
    UpdateMK("Dangle")
else:
    UpdateMK(sys.argv[1])
print "Update MK ok"

