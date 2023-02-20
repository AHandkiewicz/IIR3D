pkg load video
%signal to be filtered is captureded from video sequence
clear all;

%    nFrames = r.NumberOfFrames
%	 img = readFrame (r);

%B - block dimension (B*B*B)
%M - margin for the block
B=12;
M=2;
%B=16;
%M=0;
%starting pixel in the sequence
%----bicycle
%start=[100 200 1];
%Nr = 6;
%Nc = 8;
%----flower
%start=[96 3 36];
%Nr = 4;
%Nc = 6;
%start=[3 3 36];
%Nr = 14;
%Nc = 20;
%----guard
start=[3  3 60];
Nr = 10;
Nc = 10;
%Nr = 8;
%Nc = 8;
Bm = B+2*M;
fras=[start(3), start(3)+Bm-1];
%Nr,Nc - number of blocks (Nr*Nc)

for ic=1:Nc
 for ir=1:Nr
%r = VideoReader("gbicycle.avi")
%r = VideoReader("gflower.avi")
r = VideoReader("coastguard.avi")
%r = VideoReader("compress.avi")
 rows = [start(1)+(ir-1)*B-M, start(1)+ir*B-1+M];
 cols = [start(2)+(ic-1)*B-M, start(2)+ic*B-1+M];
 k = 0;
im = [];
% while (! isempty (img = readFrame (r)))
 while (r.hasFrame())
   img = readFrame (r);
   if (isempty (im))
     im = image (img);
     axis off;
   else
     set (im, "cdata", img);
%     im = image (img);
   end
  k = k+1;
  if (fras(1)<=k && k<=fras(2))
  for j=cols(1):cols(2)
   for i=rows(1):rows(2)
    I(i-rows(1)+1,j-cols(1)+1,k-fras(1)+1) = img(i,j,1);
   end
  end
  end
   drawnow
 end
I1 = im2double(I);
I1 = I1 - 0.5;
inF = "tI";
sr = int2str(ir);
sc = int2str(ic);
inF = [inF sr " " sc];
fid=fopen(inF,'w');
fprintf(fid,'%f\n',I1);
fclose(fid);
 end
end