%N=16;
N=96;%200
for i=1:N rm(i)=R(i,4); rp(i)=R(i,5); end;
y=rp-rm;
figure 1;
plot(y);
grid on;
