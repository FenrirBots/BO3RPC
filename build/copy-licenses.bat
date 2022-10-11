@echo off

echo [BUILD]: COPYING LICENSES
copy "..\source\thirdparty\discord\discord-license"          "bin\debug\presence\licenses"
copy "..\source\thirdparty\hook\hardware-breakpoint-license" "bin\debug\presence\licenses"
copy "..\source\thirdparty\hook\kiero-license"               "bin\debug\presence\licenses"
copy "..\source\thirdparty\hook\minhook\minhook-license"     "bin\debug\presence\licenses"
copy "..\source\thirdparty\json\json-license"                "bin\debug\presence\licenses"
copy "..\source\thirdparty\t7api\t7api-license"              "bin\debug\presence\licenses"

copy "..\source\thirdparty\discord\discord-license"          "bin\release\presence\licenses"
copy "..\source\thirdparty\hook\hardware-breakpoint-license" "bin\release\presence\licenses"
copy "..\source\thirdparty\hook\kiero-license"               "bin\release\presence\licenses"
copy "..\source\thirdparty\hook\minhook\minhook-license"     "bin\release\presence\licenses"
copy "..\source\thirdparty\json\json-license"                "bin\release\presence\licenses"
copy "..\source\thirdparty\t7api\t7api-license"              "bin\release\presence\licenses"