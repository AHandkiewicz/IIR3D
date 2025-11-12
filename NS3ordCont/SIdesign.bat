@echo off
title SI Maker
echo SI Maker operation in two steps
@echo on
SImaker EQUE 3ellip1D.vhdla SI3ellip.equ
SImaker SCHE SI3ellip.equ SI3ellip.vhdl
@echo off
pause