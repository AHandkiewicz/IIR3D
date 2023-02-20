pkg load video
%the function captures a video sequence in a given range 
clear all;
start=[18 16 8];
range=[528 684 16];
start=[9 8 8];
range=[264 342 16];
nr = range(1);
nc = range(2);
nf = range(3);
%r = VideoReader("DeComE2.avi")
r = VideoReader("comBic2.avi")
    nf0 = r.NumberOfFrames;
    nr0 = r.Height;
    nc0  = r.Width;
    isRGB = strcmpi(r.VideoFormat,'RGB24');
k = 0;
 while (r.hasFrame())
   img = readFrame (r);
  k = k+1;
  if (start(3)<=k && k<=start(3)+nf)
  for j=1:nc
   for i=1:nr
    I(i,j,k-start(3)+1) = img(i+start(1),j+start(2),1);
   end
  end
  end
 end

 w = VideoWriter ("videoR.avi");
 open (w);
   for k=1:nf
     for j=1:nc
      for i=1:nr
       z(i,j,1)=z(i,j,2)=z(i,j,3)=I(i,j,k);
      end
     end
    writeVideo (w, z);
   end
 close (w)
 VideoReader ("videoR.avi")
