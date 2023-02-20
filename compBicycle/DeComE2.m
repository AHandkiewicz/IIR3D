pkg load video
%compressed video sequence is generated
clear all;
r = VideoReader("comBic2.avi")
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
    I1(i,j,k) = img(i,j,1);
   end
  end
  end
 end

   for k=1:nf
     for j=1:2*nc
      for i=1:nr
   	  if (j/2 == floor(j/2))
      if j<2*nc jj=j; else jj=2*nc-2; end
       I2(i,j,k)=I1(i,jj/2,k)/2+I1(i,jj/2+1,k)/2;
	  else
       I2(i,j,k)=I1(i,floor(j/2)+1,k);
	  end
	  end
	 end
   end	 

   for k=1:nf
     for i=1:2*nr
      for j=1:2*nc
	  if (i/2 == floor(i/2))
      if i<2*nr ii=i; else ii=2*nr-2; end
       I(i,j,k)=I2(ii/2,j,k)/2+I2(ii/2+1,j,k)/2;
	  else
       I(i,j,k)=I2(floor(i/2)+1,j,k);
	  end
	  end
     end
   end	 
 
 w = VideoWriter ("DeComE2.avi");
 open (w);
   for k=1:nf
     for j=1:2*nc
      for i=1:2*nr
       z(i,j,1)=z(i,j,2)=z(i,j,3)=I(i,j,k);
      end
     end
    writeVideo (w, z);
   end
 close (w)
 VideoReader ("DeComE2.avi")
