*Custom Compiler Version S-2021.09
*L=5-100(n), W=5nm, SHEETS=3 
*Lpmos    14  27  40  52  64  77  89 101 114 126
*Lnmos    10  20  30  40  50  60  70  80  90 100
*IB(uA)   15  10 7.8 6.4 5.4 4.6 4.1 3.7 3.3   3
*IB for Iin=0, min/max Iin=+-6uA for Rin=50k and k=1
.hdl "./source/bsimcmg.va"
.include "./modelcard_HP_3nm.nmos"
.include "./modelcard_HP_3nm.pmos"
.include "InvDiod.sp"

*signal parameters
.param fp=0.1Giga vp=0.35 vm=-0.35 k=12

vdd ndd 0 dc=vp
vss nss 0 dc=vm
vinp ninp 0  PWL( 0 0 '0.2/fp' 0 '0.4/fp' 'vp/k' '0.6/fp' 'vp/k' '0.8/fp' 0 '1/fp' 0 '1.2/fp' 'vm/k' '1.4/fp' 'vm/k' '1.6/fp' 0 )
vinn 0 ninn  PWL( 0 0 '0.2/fp' 0 '0.4/fp' 'vp/k' '0.6/fp' 'vp/k' '0.8/fp' 0 '1/fp' 0 '1.2/fp' 'vm/k' '1.4/fp' 'vm/k' '1.6/fp' 0 )

xip ndd nss ninp nia INV_X10
vip nia  nip  0
xdip ndd nss nip D_X10
xinp ndd nss nip niop INV_X10
voutp niop  nilp  0
xdop ndd nss nilp D_X10

xin ndd nss ninn nib INV_X10
vin nib  nin  0
xdin ndd nss nin D_X10
xinn ndd nss nin nion INV_X10
voutn nion  niln  0
xdon ndd nss niln D_X10

.TEMP 25
.TRAN 0.01/fp 2/fp
*.IC V(nil)=0
.print i(vip) i(vin) i(voutp) i(voutn)
.options list node post

