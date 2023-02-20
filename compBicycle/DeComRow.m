pkg load video
%compressed video sequence is generated
clear all;
r = VideoReader("inCom2.avi")
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

r = VideoReader("inCom2H4.avi")
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
    I2(i,j,k) = img(i,j,1);
   end
  end
  end
 end

   for k=1:nf
     for i=1:2*nr
      for j=1:nc
	  if (i/2 == floor(i/2))
	   I(i,j,k)=I2(i/2,j,k);
	  else
       I(i,j,k)=I1(floor(i/2)+1,j,k);
	  end
	  end
     end
   end	 

 
 w = VideoWriter ("DeComH4r.avi");
 open (w);
   for k=1:nf
     for j=1:nc
      for i=1:2*nr
       z(i,j,1)=z(i,j,2)=z(i,j,3)=I(i,j,k);
      end
     end
    writeVideo (w, z);
   end
 close (w)
 VideoReader ("DeComH4r.avi")
