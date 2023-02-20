%artificial videos
pkg load video
clear all;
d=6; %white area dimension: dxd
rows=16;
cols=16;
fras=16;
val = 1;
%zeroing of matrices
for i=1:rows
  for j=1:cols
   for k=1:fras
    I(i,j,k)=0;
	Is(i,j,k)=0;
   end
  end
end
%sharp image
for k=1:fras
	for k1=0 : d+1
	 for k2=0 : d+1
      if 1 < k+k1 && 1 < k+k2 && k+k1 <= rows+1 && k+k2 <= cols+1
	   Is(k+k1-1,k+k2-1,k)=val;
	  end
	 end
	end
end
%smooth image
dd=d+2;
for k=1:fras
	for k1=0 : dd+1
	 for k2=0 : dd+1
      if 2 < k+k1 && 2 < k+k2 && k+k1 <= rows+2 && k+k2 <= cols+2
	   I(k+k1-2,k+k2-2,k)=val/3;
	  end
	 end
	end
end
dd=d;
for k=1:fras
	for k1=0 : dd+1
	 for k2=0 : dd+1
      if 1 < k+k1 && 1 < k+k2 && k+k1 <= rows+1 && k+k2 <= cols+1
	   I(k+k1-1,k+k2-1,k)=2*val/3;
	  end
	 end
	end
end
dd=d-2;
for k=1:fras
	for k1=0 : dd+1
	 for k2=0 : dd+1
      if 1 <= k+k1 && 1 <= k+k2 && k+k1 <= rows && k+k2 <= cols
	   I(k+k1,k+k2,k)=val;
	  end
	 end
	end
end

w = VideoWriter ("t0.avi");
 open (w);
   for k=1:fras
     for j=1:cols
      for i=1:rows
       z(i,j,1)=z(i,j,2)=z(i,j,3)=Is(i,j,k);
      end
     end
    image (z);
%	axis off;
    drawnow
    writeVideo (w, getframe (gcf));
   end
 close (w)

w = VideoWriter ("t1.avi");
 open (w);
   for k=1:fras
     for j=1:cols
      for i=1:rows
       z(i,j,1)=z(i,j,2)=z(i,j,3)=I(i,j,k);
      end
     end
    image (z);
%	axis off;
    drawnow
    writeVideo (w, getframe (gcf));
   end
 close (w)
Is=Is-0.5;
fid=fopen('t0','w');
fprintf(fid,'%f\n',Is);
fclose(fid);
I=I-0.5;
fid=fopen('t1','w');
fprintf(fid,'%f\n',I);
fclose(fid);
