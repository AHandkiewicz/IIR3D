%Tis program visulizes filtred images
pkg load video
clear all;
%B - block dimension
%M - margin for the block
B=12;
M=2;
%B=16;
%M=0;
Bm = B + 2*M;
rows=Bm;
cols=Bm;
fras=Bm;
%Nr,Nc - number of blocks (Nr*Nc)
Nr = 23;
Nc = 29;
Nr = 22;
Nc = 57;

%input image
for c=1:Nc
 for r=1:Nr
inF = "tI";
s1 = int2str(r);
s2 = int2str(c);
inF = [inF s1 " " s2];
fid=fopen(inF,'r');
ii = fscanf(fid,'%f\n');
fclose(fid);
ii = ii + 0.5;
for k=1:fras
  for j=1+(c-1)*Bm:cols + (c-1)*Bm
% 'if' to omit margin pixels in columns
   if ((((c-1)*B + (2*c-1)*M) < j) && (j <= (c*B + (2*c-1)*M)))
    jIm = j - (2*c-1)*M;
    for i=1+(r-1)*Bm:rows + (r-1)*Bm
% 'if' to omit margin pixels in rows
	 if ((((r-1)*B + (2*r-1)*M) < i) && (i <= (r*B + (2*r-1)*M))) 
	  iIm = i - (2*r-1)*M;
      I(iIm,jIm,k)=ii(i-(r-1)*Bm+(j-1-(c-1)*Bm)*rows+(k-1)*rows*cols);
     end
	end
   end
  end
end
end
end
%figure 1
w = VideoWriter ("inp.avi");
 open (w);
   for k=1:fras
     for j=1:Nc*B
      for i=1:Nr*B
       z(i,j,1)=z(i,j,2)=z(i,j,3)=I(i,j,k);
      end
     end
    zi = image (z);
    drawnow
	z=255*z;
    writeVideo (w, z);
   end
 close (w)
 VideoReader ("inp.avi")

%filtered image
for c=1:Nc
 for r=1:Nr
outF = "tOut";
s1 = int2str(r);
s2 = int2str(c);
outF = [outF s1 " " s2];
fid=fopen(outF,'r');
ii = fscanf(fid,'%f\n');
fclose(fid);
ii = ii + 0.5;
%    J(i,j,k)=ii(i-(r-1)*B+(j-1-(c-1)*B)*rows+(k-1)*rows*cols);
for k=1:fras
  for j=1+(c-1)*Bm:cols + (c-1)*Bm
% 'if' to omit margin pixels in columns
   if ((((c-1)*B + (2*c-1)*M) < j) && (j <= (c*B + (2*c-1)*M)))
    jIm = j - (2*c-1)*M;
    for i=1+(r-1)*Bm:rows + (r-1)*Bm
% 'if' to omit margin pixels in rows
	 if ((((r-1)*B + (2*r-1)*M) < i) && (i <= (r*B + (2*r-1)*M))) 
	  iIm = i - (2*r-1)*M;
      J(iIm,jIm,k)=ii(i-(r-1)*Bm+(j-1-(c-1)*Bm)*rows+(k-1)*rows*cols);
     end
	end
   end
  end
end
end
end

%figure 2
w = VideoWriter ("out.avi");
 open (w);
   for k=1:fras
     for j=1:Nc*B
      for i=1:Nr*B
       z(i,j,1)=z(i,j,2)=z(i,j,3)=J(i,j,k);
      end
     end
    zi = image (z);
    drawnow
	z=255*z;
    writeVideo (w, z);
   end
 close (w)
VideoReader ("out.avi")
