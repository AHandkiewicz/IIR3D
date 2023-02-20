%Frequency responses of the 5-th order filter pair
pkg load video
pkg load signal
clear all;

%frequency responses
x=[1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
t= 0:1:15;
%[nL,dL]=ellip(5,1,20,0.3);
%[nL,dL]=ellip(3,1,30,0.3);
[nL,dL]=ellip(4,1,20,0.3);
yL=filter(nL,dL,x);
%[nC,dC]=ellip(5,1,20,[0.3, 0.6]);
%[nC,dC]=ellip(3,1,30,[0.3, 0.6]);
[nC,dC]=ellip(4,1,20,[0.3, 0.6]);
yC=filter(nC,dC,x);
%[nH,dH]=ellip(5,1,20,0.6,'high');
%[nH,dH]=ellip(3,1,30,0.6,'high');
[nH,dH]=ellip(4,1,20,0.6,'high');
yH=filter(nH,dH,x);
figure 1
plot(t,yL,'+r',t,yC,'og',t,yH,'xb');
%axis([0 4 0 1.1]);
%xlabel("Frequency [rad/sample]");
%ylabel("Amplitude responses");
grid on

figure 2
plot(t,yL+yC+yH);
%axis([0 4 0 1.1]);
%xlabel("Frequency [rad/sample]");
%ylabel("Amplitude responses");
grid on

w=linspace(0,4,1024);
HL=freqz(nL,dL,w);
HC=freqz(nC,dC,w);
HH=freqz(nH,dH,w);
figure 3
plot(w,20*log10(abs(HL)),'.',w,20*log10(abs(HC)),w,20*log10(abs(HH)),".");
axis([0 4 -80 4]);
%xlabel("Frequency [rad/sample]");
%ylabel("Amplitude [dB]");
grid on

fid=fopen('t1','w');
fprintf(fid,'%f\n',yL);
fclose(fid);
fid=fopen('t2','w');
fprintf(fid,'%f\n',yC);
fclose(fid);
fid=fopen('t3','w');
fprintf(fid,'%f\n',yH);
fclose(fid);
