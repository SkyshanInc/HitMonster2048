if not exist frameworks\runtime-src\proj.win32\Debug.win32 mkdir frameworks\runtime-src\proj.win32\Debug.win32
if exist frameworks\runtime-src\proj.win32\Debug.win32\Resource rd /s /q frameworks\runtime-src\proj.win32\Debug.win32\Resource
mkdir frameworks\runtime-src\proj.win32\Debug.win32\Resource
mkdir frameworks\runtime-src\proj.win32\Debug.win32\Resource\src
mkdir frameworks\runtime-src\proj.win32\Debug.win32\Resource\res
mkdir frameworks\runtime-src\proj.win32\Debug.win32\Resource\script
xcopy frameworks\js-bindings\bindings\script frameworks\runtime-src\proj.win32\Debug.win32\Resource\script /e /Y
xcopy frameworks\..\src  frameworks\runtime-src\proj.win32\Debug.win32\Resource\src /e /Y
copy frameworks\..\main.js frameworks\runtime-src\proj.win32\Debug.win32\Resource\main.js /Y
copy frameworks\..\project.json frameworks\runtime-src\proj.win32\Debug.win32\Resource\project.json /Y
copy frameworks\..\project.json frameworks\runtime-src\proj.win32\Debug.win32\Resource\resource.json /Y
xcopy frameworks\..\res frameworks\runtime-src\proj.win32\Debug.win32\Resource\res /e /Y