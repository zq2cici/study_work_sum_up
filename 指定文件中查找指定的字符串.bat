@echo off&setlocal enabledelayedexpansion
rem 注意：以双引号作为间隔截取字符串的写法
for /f tokens^=1^,2^ delims^=^" %%i in (%cd%\source\c\main.c)do (
rem    	echo %%i %%j
	echo %%i|findstr "VERSION" >nul&&(
	set str=%%j  
)
)

rem  去掉首尾空格
:intercept_left
if "%str:~0,1%"==" " set "str=%str:~1%"&goto intercept_left
:intercept_right
if "%str:~-1%"==" " set "str=%str:~0,-1%"&goto intercept_right

rem del .\Listings\*.lst
rem del .\Objects\*.obj
copy .\Objects\*.hex .\download_file\"%str%".hex
echo copy to .\download_file\"%str%".hex
rem echo copy to %cd%\download_file\"%str%".hex
rem pause