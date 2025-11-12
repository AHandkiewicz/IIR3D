*Custom Compiler Version S-2021.09
*Sat Feb 11 12:40:48 2023
*L=5-100(n), W=5nm, SHEETS=3 
*Lpmos    14  27  40  52  64  77  89 101 114 126
*Lnmos    10  20  30  40  50  60  70  80  90 100
*IB(uA)   15  10 7.8 6.4 5.4 4.6 4.1 3.7 3.3   3
*IB for Iin=0, min/max Iin=+-6uA for k=12
.hdl "./source/bsimcmg.va"
.include "./modelcard_HP_3nm.nmos"
.include "./modelcard_HP_3nm.pmos"
.include "./InvDiod.sp"

*signal parameters
.param fp=0.1Giga vp=0.35 vm=-0.35 k=12

v1 ndd 0 dc=vp
v2 nss 0 dc=vm
v3 0 ni  PWL( 0 0 '0.2/fp' 0 '0.4/fp' 'vp/k' '0.6/fp' 'vp/k' '0.8/fp' 0 '1/fp' 0 '1.2/fp' 'vm/k' '1.4/fp' 'vm/k' '1.6/fp' 0 )

xinp ndd nss ni nia INV_X5
vcontr nia  nib  0
vB ndd nddB 0
xd0 nddB nss nib D_X1

.TEMP 25
.TRAN 0.01/fp 2/fp
*.IC V(n9)=1.1
*.IC V(n9)=0
.print i(vcontr)
.options list node post

