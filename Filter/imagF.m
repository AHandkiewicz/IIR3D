%images to be filtered are obtained
clear all;
imglist = {
'cameraman.tif', ... cameraman
'coins.png', ... monety10
'eight.tif', ... monety4
'durer', ... Durer
'gatlin', ... Gatlinburg
};
%1
rows=[101 132];
cols=[117 148];
rows=[101 164];
cols=[117 180];
rows=[37 164];
cols=[53 180];
rows=[1 256];
cols=[1 256];
%3
%rows=[80 111];
%cols=[117 148];
%rows=[58 121];
%cols=[101 164];
[I0 map] = imread(imglist{1},'PixelRegion',{rows,cols});
%[I0 map] = imread(imglist{2});
I=I0;
%load(imglist{5},'X','map');
%imshow(X,map);
%for i=rows(1):rows(2)
%  for j=cols(1):cols(2)
%    I(i,j)=X(i,j);
%  end
%end
%figure, imshow(I,map)
I = im2double(I);
figure, imshow(I,map)
J = imnoise(I,'gaussian',0,0.01);
%J = imnoise(I,'salt & pepper', 0.02);
K = medfilt2(J);
figure, imshow(J,map), figure(10), imshow(K,map)
%J = im2double(J);
J = J - 0.5;
fid=fopen('tI','w');
fprintf(fid,'%f\n',J);
fclose(fid);
I = I - 0.5;
fid=fopen('t0','w');
fprintf(fid,'%f\n',I);
fclose(fid);
%RGB = ind2rgb(I0,map); 
%figure, imshow(I0)