md ".\Build"
xcopy /e/f/y/i ".\Binaries" ".\Build"
xcopy /e/f/y/i ".\Assets" ".\Build"
xcopy /e/f/y/i ".\Libs\_Build\Win32\Debug\*" ".\Build\Win32\Debug\"
xcopy /e/f/y/i ".\Libs\_Build\x64\Debug\*" ".\Build\x64\Debug\"
xcopy /e/f/y/i ".\Libs\_Build\Win32\Release\*" ".\Build\Win32\Release\"
xcopy /e/f/y/i ".\Libs\_Build\x64\Release\*" ".\Build\x64\Release\"
