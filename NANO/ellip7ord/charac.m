%Frequency responses of the 5-th order filter pair
pkg load video
pkg load signal
clear all;

%frequency responses
Q=[1.00000 1.14091 2.64085 2.12978 2.12027 1.08843 0.49362 0.10726];
Qs=[0.999912 1.141109  2.640937 2.129562 2.120159 1.088682 0.493753 0.107005];
%w=logspace(0.0001,1,1024);
w=linspace(0,4,1024);
%lowpass output
P=[0 0.00659 0.00000 0.05802 0.00000 0.14345 0.00000 0.10726];
Ps=[0 0.006468 0.00000 0.058096 0.00000 0.143396 0.00000 0.107292];
H=freqs(P,Q,w);
Hs=freqs(Ps,Qs,w);

figure 1
plot(w,abs(H),w,abs(Hs),".");
axis([0 4 0 1.1]);
xlabel("Frequency [rad/sample]");
ylabel("Amplitude responses");
grid on
figure 2
plot(w,20*log10(abs(H)),w,20*log10(abs(Hs)),".");
axis([0 4 -120 6]);
xlabel("Frequency [rad/sample]");
ylabel("Amplitude [dB]");
grid on