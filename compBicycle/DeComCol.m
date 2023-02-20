pkg load video
%compressed video sequence is generated
clear all;
r = VideoReader("inCom1.avi")
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

r = VideoReader("inCom1H6.avi")
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
     for j=1:2*nc
      for i=1:nr
   	  if (j/2 == floor(j/2))
       I(i,j,k)=I2(i,j/2,k);
	  else
       I(i,j,k)=I1(i,floor(j/2)+1,k);
	  end
	  end
	 end
   end	 

 
 w = VideoWriter ("DeCom.avi");
 open (w);
   for k=1:nf
     for j=1:2*nc
      for i=1:nr
       z(i,j,1)=z(i,j,2)=z(i,j,3)=I(i,j,k);
      end
     end
    writeVideo (w, z);
   end
 close (w)
 VideoReader ("DeCom.avi")
