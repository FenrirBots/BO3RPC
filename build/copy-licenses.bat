@echo off

echo [BUILD]: COPYING LICENSES
copy "..\source\rpc\thirdparty\discord\discord-license"          "bin\licenses"
copy "..\source\rpc\thirdparty\hook\hardware-breakpoint-license" "bin\licenses"
copy "..\source\rpc\thirdparty\hook\kiero-license"               "bin\licenses"
copy "..\source\rpc\thirdparty\hook\minhook\minhook-license"     "bin\licenses"
copy "..\source\rpc\thirdparty\json\json-license"                "bin\licenses"
copy "..\source\rpc\thirdparty\t7api\t7api-license"              "bin\licenses"