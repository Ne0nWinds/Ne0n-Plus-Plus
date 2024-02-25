
$defines = @("-DPLATFORM_X64", "-DPLATFORM_WIN32", "-D_DEBUG", "-DRENDERAPI_D3D11")

cl.exe -Zi $defines -DSIMD_WIDTH=8 -nologo /utf-8 /EHsc -EHa- /GR- /GL /GS- /Gs9999999 /arch:AVX2 .\main.cpp .\win32_base.cpp -o .\build\ /link /NODEFAULTLIB user32.lib xinput.lib kernel32.lib d3d11.lib /ENTRY:_AppMain /SUBSYSTEM:WINDOWS /STACK:0x100000,0x100000
# clang -Wno-switch -g -nostdlib -fno-exceptions $defines -DSIMD_WIDTH=4 -mfma -mavx2 .\main.cpp .\win32_base.cpp .\win32_base.c -lUser32 -lXinput -lkernel32 -ld3d11 -DPLATFORM_X64 -mavx2 -o .\build\a.exe "-Wl,/ENTRY:_AppMain,/SUBSYSTEM:WINDOWS,/opt:ref" -Xlinker "/STACK:0x100000,0x100000" 
