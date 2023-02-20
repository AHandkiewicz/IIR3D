%Tis program visulizes filtred images
clear all;

%fid=fopen('tI','w');
%fprintf(fid,'%f\n',1);
%for i=2:4*4*16
%fprintf(fid,'%f\n',0);
%end

rows=32;
cols=32;
rows=64;
cols=64;
rows=128;
cols=128;
rows=256;
cols=256;

%ideal image
fid=fopen('t0','r');
I = fscanf(fid,'%f\n',[rows,cols]);
fclose(fid);
I = I + 0.5;
figure, imshow(I)

%noised image
fid=fopen('tI','r');
J = fscanf(fid,'%f\n',[rows,cols]);
fclose(fid);
J = J + 0.5;
figure, imshow(J)

%designed filter
fid=fopen('tOut','r');
I1 = fscanf(fid,'%f\n',[rows,cols]);
fclose(fid);
I1 = I1 + 0.5;
figure, imshow(I1)

PSNR = 0;
for i=1:rows
  for j=1:cols
    I2(i,j) = I(i,j)-I1(i,j);
%    I2(i,j) = I(i,j)-J(i,j);
    PSNR = PSNR+I2(i,j)^2;
  end
end
PSNR = PSNR/rows/cols;
PSNR = -10*log10(PSNR)
figure, imshow(I2)
