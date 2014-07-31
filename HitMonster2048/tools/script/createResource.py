#! /usr/bin/env python  
# -*- coding: utf-8 -*-  
#@author zcwang3@gmail.com  
#@version 2010-09-25 14:57  
  
import os  
import time 
import subprocess 

sourceDir = "../pokoSanguo/Resources"  
targetDir = "../updateResource"

updateList = "resourceList.py"

copyFileCounts = 0  
def is_js(name):
    return name.lower().endswith('.js') 

def remove(res_dir):
    for root, dirs, files in os.walk(res_dir):
        for f in files:
            if is_js(f):
                res_rel_path = os.path.relpath(root, res_dir);
                res_path = os.path.join(res_rel_path, f);
                res_abs_path = os.path.join(root, f);
                subprocess.call(["rm", "-r", res_abs_path])

def copyFiles(sourceDir, targetDir):  
    global copyFileCounts  
    print sourceDir  
    for f in os.listdir(sourceDir):  
        sourceF = os.path.join(sourceDir, f)  
        targetF = os.path.join(targetDir, f)  
                
        if os.path.isfile(sourceF):  
            #创建目录  
            if not os.path.exists(targetDir):  
                os.makedirs(targetDir)  
            copyFileCounts += 1  
              
            #文件不存在，或者存在但是大小不同，覆盖  
            if not os.path.exists(targetF) :  
                #2进制文件  
                open(targetF, "wb").write(open(sourceF, "rb").read())  
                print "%s %s finish" %(time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time())), targetF)  
            
          
        if os.path.isdir(sourceF):  
            copyFiles(sourceF, targetF)  
          
if __name__ == "__main__":  
    try:  
        import psyco  
        psyco.profile()  
    except ImportError:  
        pass 
    
    remove(targetDir)


    copyFiles(sourceDir,targetDir)

    cmd = [ "python", \
        "cocos2d-console/console/cocos2d.py", \
        "jscompile",\
        "-s", \
        targetDir,\
        "-d", \
        targetDir,\
        ]

    retval = subprocess.call(cmd, 0, None, None, None, None)
            
    execfile(updateList)
    remove(targetDir)
    
