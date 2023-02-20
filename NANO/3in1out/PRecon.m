%Frequency responses of the 5-th order filter pair
pkg load video
pkg load signal
clear all;

tOutS; tOutA;
t= 0:1:15;

figure 1
plot(t,tA,t,tS);
axis([0 15 -0.2 1.1]);
xlabel("#sample");
ylabel("Sample value");
grid on
