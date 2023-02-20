pkg load video
%compressed video sequence is generated
clear all;

r = VideoReader("gbicycle.avi")
%r = VideoReader("gflower.avi")
%r = VideoReader("coastguard.avi")
    nf = r.NumberOfFrames;
%	nf = 30;
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
    I(i,j,k) = img(i,j,1);
   end
  end
  end
 end

   for k=1:nf
     j1 = 1; 
     for j=1:nc
	 i1 = 1;
	 if (j/2 == floor(j/2))
      for i=1:nr
	   if (i/2 == floor(i/2))
       I1(i1,j1,k)=I(i,j,k);
	   i1=i1+1;
	   end
	  end
	  j1=j1+1;
     end
	 end
   end	 

 
 w = VideoWriter ("compress.avi");
 open (w);
   for k=1:nf
     for j=1:nc/2
      for i=1:nr/2
       z(i,j,1)=z(i,j,2)=z(i,j,3)=I1(i,j,k);
      end
     end
    writeVideo (w, z);
   end
 close (w)
 VideoReader ("compress.avi")
