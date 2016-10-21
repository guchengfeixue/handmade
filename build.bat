@echo off

set CommonCompilerFlags=-Od -MTd -nologo -fp:fast -fp:except- -Gm- -GR- -EHa- -Zo -Oi -WX -W4 -wd4201 -wd4100 -wd4189 -wd4505 -wd4127 -FC -Z7
set CommonCompilerFlags=-DHANDMADE_PROFILE=1 -DHANDMADE_INTERNAL=1 -DHANDMADE_SLOW=1 -DHANDMADE_WIN32=1 %CommonCompilerFlags%
set CommonLinkerFlags= -incremental:no -opt:ref user32.lib gdi32.lib winmm.lib

REM TODO - can we just build both with one exe?

IF NOT EXIST build mkdir build
pushd build

del *.pdb > NUL 2> NUL

REM Asset file builder build
REM cl %CommonCompilerFlags% -DTRANSLATION_UNIT_INDEX=0 -D_CRT_SECURE_NO_WARNINGS ..\code\test_asset_builder.cpp /link %CommonLinkerFlags%

REM 32-bit build
REM cl %CommonCompilerFlags% ..\code\win32_handmade.cpp /link -subsystem:windows,5.1 %CommonLinkerFlags%

REM 64-bit build
REM Optimization switches /wO2
echo WAITING FOR PDB > lock.tmp
cl %CommonCompilerFlags% -DTRANSLATION_UNIT_INDEX=1 -O2 -c ..\code\handmade_optimized.cpp -Fohandmade_optimized.obj -LD
cl %CommonCompilerFlags% -DTRANSLATION_UNIT_INDEX=0 ..\code\handmade.cpp handmade_optimized.obj -Fmhandmade.map -LD /link -incremental:no -opt:ref -PDB:handmade_%random%.pdb -EXPORT:GameGetSoundSamples -EXPORT:GameUpdateAndRender -EXPORT:DEBUGGameFrameEnd
del lock.tmp
cl %CommonCompilerFlags% -DTRANSLATION_UNIT_INDEX=2 ..\code\win32_handmade.cpp -Fmwin32_handmade.map /link %CommonLinkerFlags%
popd