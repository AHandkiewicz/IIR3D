*Custom Compiler Version S-2021.09
*L=5-100(n), W=5nm, SHEETS=3 
*Lpmos    14  27  40  52  64  77  89 101 114 126
*Lnmos    10  20  30  40  50  60  70  80  90 100
*IB(uA)   15  10 7.8 6.4 5.4 4.6 4.1 3.7 3.3   3
*IB for Iin=0, min/max Iin=+-6uA for Rin=50k and k=1
.hdl "./source/bsimcmg.va"
.include "./modelcard_HP_3nm.nmos"
.include "./modelcard_HP_3nm.pmos"
.include "./clock.sp"
.include "./delay2.sp"
.include "./delay3.sp"
.include "InvDiod.sp"

*signal parameters, for fp=0.2G (clock rise/fall time) and k>10 Iin=Iout
.param fp=0.2G vp=0.35 vm=-0.35 k=11

vdd ndd 0 dc=0.35
vss nss 0 dc=-0.35
vinp ninp 0  PWL( 0 0 '0.02/fp' 0 '0.04/fp' 'vp/k' '0.51/fp' 'vp/k' '0.53/fp' 0 '1/fp' 0 '1.02/fp' 'vm/k' '1.04/fp' 'vm/k' '1.49/fp' 'vm/k' '1.51/fp' )
vinn 0 ninn  PWL( 0 0 '0.02/fp' 0 '0.04/fp' 'vp/k' '0.51/fp' 'vp/k' '0.53/fp' 0 '1/fp' 0 '1.02/fp' 'vm/k' '1.04/fp' 'vm/k' '1.49/fp' 'vm/k' '1.51/fp' )

.param td='0.022/fp' tr='0.002/fp' tf='0.002/fp' tp='0.047/fp' tpe='0.098/fp'
xclk1 clkp clkn td tr tf tp tpe CLOCK

xinp ndd nss ninp nip INV_X5
vip nip  niip  0

xinn ndd nss ninn nin INV_X5
vin nin  niin  0

xdel ndd nss niip niin niop nion clkp clkn DELAY2
*xdel ndd nss niip niin niop1 nion1 niop2 nion2 clkp clkn DELAY3

voutp niop  nilp1  0
xdop1 ndd nss nilp1 D_X5

voutn nion  niln1  0
xdon1 ndd nss niln1 D_X5

*voutp1 niop1  nilp1  0
*xdop1 ndd nss nilp1 D_X4

*voutn1 nion1  niln1  0
*xdon1 ndd nss niln1 D_X4

*voutp2 niop2  nilp2  0
*xdop2 ndd nss nilp2 D_X4

*voutn2 nion2  niln2  0
*xdon2 ndd nss niln2 D_X4


.TEMP 25
.TRAN 0.01/fp 2/fp
*.IC V(nil)=0
.print i(vip) i(vin) i(voutp) i(voutn)
.options list node post

