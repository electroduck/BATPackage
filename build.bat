@ECHO OFF

del *.err
del *.obj
del *.exe
del *.bak

wcl386 pad.c

wcl386 loader.c util.c -fe=loader.exe
pad loader.exe 40000

wcl386 compile.c util.c -fe=exefrombat.exe

mkdir GUI\Debug
copy loader.exe GUI\Debug\loader.exe
mkdir GUI\Release
copy loader.exe GUI\Release\loader.exe

pause