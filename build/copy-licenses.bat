@echo off

echo [BUILD]: COPYING LICENSES
copy "..\source\thirdparty\discord\discord-license"          "bin\licenses"
copy "..\source\thirdparty\hook\hardware-breakpoint-license" "bin\licenses"
copy "..\source\thirdparty\hook\kiero-license"               "bin\licenses"
copy "..\source\thirdparty\hook\minhook\minhook-license"     "bin\licenses"
copy "..\source\thirdparty\json\json-license"                "bin\licenses"
copy "..\source\thirdparty\t7api\t7api-license"              "bin\licenses"