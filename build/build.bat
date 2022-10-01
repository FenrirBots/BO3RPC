@echo off
cls

setlocal

set BuildTools32=
set BuildTools64=

if ["%1"]==[""] (
	echo [BUILD]: No build tools provided, searching known directories

	:: I hate this...
	if exist "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\" (
		set BuildTools32="C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat"
		set BuildTools64="C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
		echo [BUILD]: Visual Studio Build Tools 2022 found
	) else (
		if exist "C:\Program Files\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\" (
			set BuildTools32="C:\Program Files\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars32.bat"
			set BuildTools64="C:\Program Files\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
			echo [BUILD]: Visual Studio Build Tools 2019 found
		) else (
			if exist "C:\Program Files\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\" (
				set BuildTools32="C:\Program Files\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars32.bat"
				set BuildTools64="C:\Program Files\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat"
				echo [BUILD]: Visual Studio Build Tools 2017 found
			) else (
				echo [BUILD]: No build tools found, please provide them as an argument and try again...	
				goto :pausethenend
			)
		)
	)
)

call %BuildTools64%
call cl.exe /nologo /c /EHsc /W4 /O2 /MD /D_USRDLL /D_WINDLL /D_NDEBUG /Fo"bin\intermediate\\" /I"..\source" /I"..\source\thirdParty" /TP "..\source\main.cpp" "..\source\thirdparty\leohook\leohook.cpp" "..\source\discord\thread.cpp" "..\source\discord\discord.cpp" "..\source\config\config.cpp" "..\source\engine\cg.cpp" "..\source\engine\ddl.cpp" "..\source\engine\lobbysession.cpp" "..\source\engine\com.cpp" "..\source\parser\parser.cpp"
call link.exe /nologo /dll /subsystem:windows /out:"bin\RichPresence.dll" "bin\intermediate\*.obj" "discord.lib" "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib" 

if ["%ERRORLEVEL%"] NEQ ["0"] (
	echo An error occoured during the build process...
)

:pausethenend
pause

:end
endlocal