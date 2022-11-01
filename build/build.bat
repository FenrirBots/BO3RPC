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
		if exist "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\" (
			set BuildTools32="C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat"
			set BuildTools64="C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
			echo [BUILD]: Visual Studio Build Tools 2022 found
		) else (
			if exist "C:\Program Files\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\" (
				set BuildTools32="C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat"
				set BuildTools64="C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
				echo [BUILD]: Visual Studio Build Tools 2019 found
			) else (
				if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\" (
					set BuildTools32="C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat"
					set BuildTools64="C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
					echo [BUILD]: Visual Studio Build Tools 2019 found
				) else (				
					if exist "C:\Program Files\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\" (
						set BuildTools32="C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat"
						set BuildTools64="C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
						echo [BUILD]: Visual Studio Build Tools 2017 found
					) else (
						if exist "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Auxiliary\Build\" (
							set BuildTools32="C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat"
							set BuildTools64="C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
							echo [BUILD]: Visual Studio Build Tools 2017 found
						) else (
							echo [BUILD]: No build tools found, please provide them as an argument and try again...	
							goto :pausethenend
						)
					)
				)
			)
		)
	)
) else (
	set BuildTools=%1
	set BuildTools=%BuildTools:"=%
	if exists %BuildTools% (
		BuildTools64="%BuildTools%\vcvars64.bat"
		BuildTools32="%BuildTools%\vcvars32.bat"
	)
)

call %BuildTools64%

echo [BUILD]: COMPILING
call cl.exe /nologo /EHsc /W4 /O2 /MD /std:c++17 /D_USRDLL /D_WINDLL /D_NDEBUG /Fo"bin\rpc\intermediate\\" /I"..\source\rpc" /c ^
/Tp"..\source\rpc\config.cpp" ^
/Tp"..\source\rpc\main.cpp" ^
/Tp"..\source\rpc\update.cpp" ^
/Tp"..\source\rpc\discord\discord.cpp" ^
/Tp"..\source\rpc\discord\presence.cpp" ^
/Tp"..\source\rpc\parser\parser.cpp" ^
/Tp"..\source\rpc\parser\rules.cpp" ^
/Tp"..\source\rpc\thirdparty\t7api\cg.cpp" ^
/Tp"..\source\rpc\thirdparty\t7api\com.cpp" ^
/Tp"..\source\rpc\thirdparty\t7api\ddl.cpp" ^
/Tp"..\source\rpc\thirdparty\t7api\demo.cpp" ^
/Tp"..\source\rpc\thirdparty\t7api\g.cpp" ^
/Tp"..\source\rpc\thirdparty\t7api\livestats.cpp" ^
/Tp"..\source\rpc\thirdparty\t7api\livestorage.cpp" ^
/Tp"..\source\rpc\thirdparty\t7api\lobbysession.cpp" ^
/Tp"..\source\rpc\thirdparty\t7api\settings.cpp" ^
/Tp"..\source\rpc\thirdparty\hook\kiero.cpp" ^
/Tp"..\source\rpc\thirdparty\hook\hardware-breakpoint.cpp" ^
/Tc"..\source\rpc\thirdparty\hook\minhook\hde\hde32.c" ^
/Tc"..\source\rpc\thirdparty\hook\minhook\hde\hde64.c" ^
/Tc"..\source\rpc\thirdparty\hook\minhook\trampoline.c" ^
/Tc"..\source\rpc\thirdparty\hook\minhook\buffer.c" ^
/Tc"..\source\rpc\thirdparty\hook\minhook\hook.c" ^
/Tp"..\source\rpc\threads\attach.cpp" ^
/Tp"..\source\rpc\threads\detach.cpp" 

echo.
echo [BUILD]: LINKING
call link.exe /nologo /dll /subsystem:windows /out:"bin\rpc\presence.dll" "bin\rpc\intermediate\*.obj" "discord.lib" "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib"

:pausethenend
pause

:end
endlocal