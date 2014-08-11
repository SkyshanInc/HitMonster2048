#!/usr/bin/python
import os
import subprocess
import sys
import argparse
import zipfile 
import resourceJson

proj_dir = os.path.abspath(
os.path.join(os.path.dirname(__file__), '../'))
TexturePacker = '/usr/local/bin/TexturePacker'
sd_Resources = os.path.join(proj_dir, 'Resources/sd')
hd_Resources = os.path.join(proj_dir, 'Resources/hd')

sd_font = os.path.join(proj_dir, 'Resources/sd_other')
hd_font = os.path.join(proj_dir, 'Resources/hd_other')

sd_output_dir = os.path.join(proj_dir, 'HitMonster2048/res/sd')
hd_output_dir = os.path.join(proj_dir, 'HitMonster2048/res/hd')
studio_output_dir = os.path.join(proj_dir, 'studio_res')

Encryptionkey = 'dd83d78cf8526835421473ba2d441d53'

def is_images(name):
    return name.lower().endswith('png')

def is_json(name):
    return name.lower().endswith('json') 

def mkdir_if_needed():
    parser = argparse.ArgumentParser(description='Process args')
    parser.add_argument('-d', '--directory', help='directory to handle')
    parser.add_argument('-t', '--target', help='target platform')
    parser.add_argument('-file','--file',help='file name')
    parser.add_argument('-opt',"--opt",help='texture opt')
    parser.add_argument('-scale',"--s",help='contentScale')
    parser.add_argument('-m', '--mm', help='use img encryption, Encryption key (128bit),as 32 hex digits')
    args = parser.parse_args()

    subprocess.call(["rm", "-r", sd_output_dir])
    subprocess.call(["rm", "-r", studio_output_dir])
    
    one_file = args.file;
    
    res = sd_output_dir
    studio_out = os.path.join(studio_output_dir, 'sd')
    if args.target == "hd":
        res = hd_output_dir
        subprocess.call(["rm", "-r", hd_output_dir])
        studio_out = os.path.join(studio_output_dir, 'hd')
    if not os.path.exists(res):
        os.makedirs(res)
    for group in os.listdir(res):
        group_dir =  os.path.join(res, group)
        if is_json(group_dir):
            continue
        
        # if not one_file==None:
        #     l = group.split('.')
        #     if one_file==l[0]:
        #         subprocess.call(["rm", "-r", group_dir])
        # else:
        #     subprocess.call(["rm", "-r", group_dir])


        
    if not os.path.exists(studio_out):
        os.makedirs(studio_out)
    for group in os.listdir(studio_out):
        group_dir =  os.path.join(studio_out, group)
        # if is_json(group_dir):
        #     continue
        # if not one_file==None:
        #     l = group.split('.')
        #     if one_file==l[0]:
        #         subprocess.call(["rm", "-r", group_dir])
        # else:
        #     subprocess.call(["rm", "-r", group_dir])

def run_tp(files, options):
    global proj_dir
    opts = { # TexturePacker --help
        "dither-fs-alpha": "",
        "format": "cocos2d",
        "algorithm": "MaxRects",
        "max-size": "2048",
        "opt": "PVRTC4",
        "verbose": "",
        "reduce-border-artifacts": "",
        #"premultiply-alpha": "",
    }
    for f in files:
        if not os.path.isfile(f):
            print 'ERROR: ', f, 'is not a file. Skipped'
            return
    files = [os.path.relpath(f, proj_dir) for f in files]
    opts.update(options)
    args = [TexturePacker]
    for key in sorted(opts):
        args.append('--' + key)
        value = opts[key]
        if value:
            args.append(value)
    process = subprocess.Popen(
        args + sorted(files),
        stderr = subprocess.STDOUT,
        cwd = proj_dir)
    result = process.wait()
    #assert result == 0, 'TexturePacker failed ' + str(args+files)

def process():
    parser = argparse.ArgumentParser(description='Process args')
    parser.add_argument('-d', '--directory', help='directory to handle')
    parser.add_argument('-t', '--target', help='target platform')
    parser.add_argument('-file','--file',help='file name')
    parser.add_argument('-opt','--opt',help='texture opt')
    parser.add_argument('-scale',"--s",help='contentScale')
    parser.add_argument('-m', '--mm', help='use img encryption, Encryption key (128bit),as 32 hex digits')
    
    args = parser.parse_args()
    global sd_output_dir
    global hd_output_dir
    one_file = args.file
    res = sd_Resources
    resFont = sd_font
    output = sd_output_dir
    studio_out = os.path.join(studio_output_dir, "sd")
    if args.target == "hd":
        res = hd_Resources
        resFont = hd_font
        output = hd_output_dir
        studio_out = os.path.join(studio_output_dir, "hd")
    
    if one_file==None:
        for group in os.listdir(resFont):
            group_dir = os.path.join(resFont, group)
            # if is_json(group_dir):
            #     zipName = group.split('.')[0]+".zip"
            #     zip_file(zipName,output,group_dir)
               
            subprocess.call(["cp", "-rf", group_dir, output])
            subprocess.call(["cp", "-rf", group_dir, studio_out])
    
    for group in os.listdir(res):
    	group_dir = os.path.join(res, group)
        
        if  not one_file==None:
            if  not one_file==group:
                continue
                

        if not os.path.isdir(group_dir):
            continue
        if args.directory:
            if group not in args.directory.split('-'):
                print 'ignore ', group_dir
                continue
        print 'start handling %s' % group_dir

     	files = [name for name in os.listdir(group_dir) 
                    if is_images(name)]
        assert args.target in ['sd', 'hd', None]

        options = {
                'data': os.path.join(output, group+'.plist'),
                'sheet': os.path.join(output, group+'.pvr.ccz'),
                "scale": "1",
            }

        if args.s != None:
            options.update({'scale':args.s}),
        #jimi
        if args.mm == "true":
            options.update({'content-protection':Encryptionkey})

        #studio no Encryption
        options.update({'opt':'RGBA4444'})
        if not args.opt==None:
            options.update({'opt':args.opt})
        options.update({'size-constraints':'NPOT'})
        run_tp([os.path.join(group_dir, name) for name in files],
            options)

        options = {
                'data': os.path.join(studio_out, group+'.plist'),
                'sheet': os.path.join(studio_out, group+'.png'),
                "scale": "1",
            }

        if args.s != None:
            options.update({'scale':args.s}),

        options.update({'opt':'RGBA4444'})

        if not args.opt==None:
            options.update({'opt':args.opt})
        options.update({'size-constraints':'NPOT'})
        run_tp([os.path.join(group_dir, name) for name in files],
            options)
        


if __name__ == '__main__':
    mkdir_if_needed();
    process();
    print "=======  resourceJson ------------"
    resourceJson.main();




