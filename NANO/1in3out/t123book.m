%Responses of the 4-th order filter bank
pkg load video
pkg load signal
clear all;

%impulse responses
t0=[1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
[nL,dL]=ellip(4,1,20,0.3);
yL=filter(nL,dL,t0);
[nC,dC]=ellip(4,1,20,[0.3, 0.6]);
yC=filter(nC,dC,t0);
[nH,dH]=ellip(4,1,20,0.6,'high');
yH=filter(nH,dH,t0);

fid=fopen('t1','w');
fprintf(fid,'%f\n',yL);
fclose(fid);
fid=fopen('t2','w');
fprintf(fid,'%f\n',yC);
fclose(fid);
fid=fopen('t3','w');
fprintf(fid,'%f\n',yH);
fclose(fid);
