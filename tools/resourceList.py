#!/usr/bin/python

import os;
import json;
import hashlib;
import json;

def md5_for_file(f, block_size=2**20):
    md5 = hashlib.md5()
    while True:
        data = f.read(block_size)
        if not data:
            break
        md5.update(data)
    return md5.hexdigest()

#read in ignore list
ignore_file = open("resource.ignore")
ignores = []
line = ignore_file.readline()
while line:
    ignores.append(line.rstrip())
    line = ignore_file.readline()
ignore_file.close()
#iterate all files
res_list = {}
res_dir = ''
if os.path.exists(os.path.join(os.path.dirname(__file__), '../updateResource/')):
    res_dir = os.path.join(os.path.dirname(__file__), '../updateResource/')
else:
    res_dir = os.path.join(os.path.dirname(__file__), '..')
for root, dirs, files in os.walk(res_dir):
    for f in files:
        print f
        if f not in ignores:
            res_rel_path = os.path.relpath(root, res_dir);
            if res_rel_path == '.':
                res_rel_path = ''

            if res_rel_path in ignores:
                print 'ignore folder: %s' % res_rel_path;
                continue;
            res_path = os.path.join(res_rel_path, f);
            res_abs_path = os.path.join(root, f);
            res_list[res_path] = md5_for_file(open(res_abs_path));
        else:
            print 'ignore file: %s' % f;
print res_list;
#write to resource list file
res_list_file = open(os.path.join(res_dir, "resource_internal.lst"), 'w')
res_list_file.write(json.dumps(res_list, indent=4))
res_list_file.close()
#increment resource version
if os.path.exists(os.path.join(res_dir, "resource_internal.ver")):
    res_ver_file = open(os.path.join(res_dir, "resource_internal.ver"), 'r')
    res_ver = int(res_ver_file.readline().rstrip())
    res_ver_file.close()
    res_ver_file = open(os.path.join(res_dir, "resource_internal.ver"), 'w')
    res_ver += 1
    res_ver_file.write(str(res_ver))
    res_ver_file.close()
