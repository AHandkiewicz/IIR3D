%Frequency responses of the 5-th order filter pair
pkg load video
pkg load signal
clear all;

%frequency responses
Q=[1 1.82409 3.07201 3.21886 2.09342 1.26088];
%w=logspace(0.0001,0.1,248);
w=linspace(0,4,512);
%lowpass output
Pl=[0 0.46813 0 1.59449 0 1.26088];
Hl=freqs(Pl,Q,w);
%highpass output
Ph=[1 0 1.51793 0 0.53493 0];
Hh=freqs(Ph,Q,w);

figure 1
%plot(w,abs(Hl),"-",w,abs(Hh),"--");
plot(w,abs(Hl),w,abs(Hh));
axis([0 4 0 1.1]);
xlabel("Frequency [rad/sample]");
ylabel("Amplitude responses");
grid on
figure 2
plot(w,20*log10(abs(Hl)),"-",w,20*log10(abs(Hh)),".");
axis([0 4 -60 4]);
xlabel("Frequency [rad/sample]");
ylabel("Amplitude [dB]");
grid on