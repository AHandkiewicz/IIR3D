%RpT;
Rfull;
%N=16;
N=200;%32 for RpT, 80 for Rfull
for i=1:N t(i)=R(i,1); ep(i)=0.001*R(i,2); em(i)=0.001*R(i,3); rp(i)=0.001*R(i,4); rm(i)=0.001*R(i,5); end;
%for i=1:N t(i)=R(i,1); rm(i)=R(i,4); rp(i)=R(i,5); end;
r=(rp-rm);
e=(em-ep);
figure 1;
%plot(t, r, 'k', t, e, 'r');
plot(t, r, 'k', t, e, '--r');
%axes([0, 100, -2, 4])
title('Basic SI integrator response');
xlabel('[ns]');
ylabel('[uA]');
grid on;
%figure 2;
%H=fft(r,128);
%plot(20*log10(abs(H)));
%grid on;