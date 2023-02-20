%Frequency responses of the 5-th order filter pair
pkg load video
pkg load signal
clear all;

zAn1e4; zAn2e4; zAn3e4; zAd1e4; zAd2e4; zAd3e4;

w=linspace(0,4,1024);
HL=freqz(zAn1,zAd1,w);
HC=freqz(zAn2,zAd2,w);
HH=freqz(zAn3,zAd3,w);
figure 1
plot(w,20*log10(abs(HL)),'.',w,20*log10(abs(HC)),w,20*log10(abs(HH)),".");
axis([0 4 -40 10]);
xlabel("Frequency [rad/sample]");
ylabel("Amplitude [dB]");
grid on

zAn1e5; zAn2e5; zAn3e5; zAd1e5; zAd2e5; zAd3e5;

w=linspace(0,4,1024);
HL=freqz(zAn1,zAd1,w);
HC=freqz(zAn2,zAd2,w);
HH=freqz(zAn3,zAd3,w);
figure 2
plot(w,20*log10(abs(HL)),'.',w,20*log10(abs(HC)),w,20*log10(abs(HH)),".");
axis([0 4 -60 10]);
%xlabel("Frequency [rad/sample]");
%ylabel("Amplitude [dB]");
grid on
