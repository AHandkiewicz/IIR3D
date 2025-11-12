.subckt CLOCK clo cle td tr tf tp tpe
VGO   clo   0    PULSE( vm  vp  td tr tf tp tpe)
VGE   cle   0    PULSE( vp  vm  td tr tf tp tpe)
.ends
