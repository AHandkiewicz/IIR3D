pkg load video
clear all;

%the function captures the blocks tIij from the video sequence "video"
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
%capture for columns:
start=[8 8 8];
Nr = 23;
Nc = 29;
%capture for rows:
%start=[3 3 1];
%Nr = 22;
%Nc = 57;
Bm = B+2*M;
fras=[start(3), start(3)+Bm-1];
%Nr,Nc - number of blocks (Nr*Nc)

%capture for columns
r = VideoReader("comBic2.avi");
%capture for rows
%r = VideoReader("DeComE2.avi")
    nf = r.NumberOfFrames;
    nr = r.Height;
    nc  = r.Width;
    isRGB = strcmpi(r.VideoFormat,'RGB24');
k = 0;
 while (r.hasFrame())
   img = readFrame (r);
  k = k+1;
  if (1<=k && k<=nf)
  for j=1:nc
   for i=1:nr
    I0(i,j,k) = img(i,j,1);
   end
  end
  end
 end


for ic=1:Nc
 for ir=1:Nr
 rows = [start(1)+(ir-1)*B-M, start(1)+ir*B-1+M];
 cols = [start(2)+(ic-1)*B-M, start(2)+ic*B-1+M];
  for k=fras(1):fras(2)
  for j=cols(1):cols(2)
   for i=rows(1):rows(2)
    I(i-rows(1)+1,j-cols(1)+1,k-fras(1)+1) = I0(i,j,k);
   end
  end
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