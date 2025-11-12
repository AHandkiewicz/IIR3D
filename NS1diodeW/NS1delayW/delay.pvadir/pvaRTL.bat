
@Echo off

:-------------------------------------------------------
: Product : Hspice
: File:  pvaRTL.bat   12:45:42 05/12/2025
:
: VB  :  synmake_pva_build 
: Copyright (c) 2010 Synopsys Inc., All Rights Reserved.
:-------------------------------------------------------

SET GCC_EXEC_PREFIX=
SET GCC="C:\synopsys\Hspice_S-2021.09\GNU\win64\bin\gcc"
SET PVA_CDEFS=-DGMAKE -DWIN32 -DSynopsys_WindowsNT -DI32_NT_4 -D_SN_=20090619-I32_NT_4
SET PVA_GCC_FLAGS=-g
SET PVA_GCC_DLL_FLAGS=-w -shared -ffast-math

: COMPILE
%GCC% %PVA_CDEFS% %PVA_GCC_FLAGS% %PVA_GCC_DLL_FLAGS% -DWIN32 "Z:\SIdesign\NS1delayW\delay.pvadir\pvaSetExtern.o" "Z:/SIdesign/NS1delayW/delay.pvadir/bsimcmg.o" -o "Z:\SIdesign\NS1delayW\delay.pvadir\pvaRTL_win64.dll"
