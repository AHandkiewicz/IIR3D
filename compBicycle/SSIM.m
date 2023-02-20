function s=SSIM(video1,video2)
%the function calculates SSIM (Structural SIMilarity) 
%index for the video sequences "video1" and "video2"
K = [0.01 0.03];
%L = 255;
L = 1;
s=1;
C1 = (K(1)*L)^2;
C2 = (K(2)*L)^2;

r1 = VideoReader(video1);
    nf1 = r1.NumberOfFrames;
    nr1 = r1.Height;
    nc1  = r1.Width;
    isRGB1 = strcmpi(r1.VideoFormat,'RGB24');
 while (r1.hasFrame())
   img = readFrame (r1);
  for k=1:nf1
   for j=1:nc1
    for i=1:nr1
    I1(i,j,k) = img(i,j,1);
    end
   end
  end
 end

r2 = VideoReader(video2);
    nf2 = r2.NumberOfFrames;
    nr2 = r2.Height;
    nc2  = r2.Width;
    isRGB2 = strcmpi(r2.VideoFormat,'RGB24');
 while (r2.hasFrame())
   img = readFrame (r2);
  for k=1:nf2
   for j=1:nc2
    for i=1:nr2
    I2(i,j,k) = img(i,j,1);
    end
   end
  end
 end
 
nf= nf1;
if (nf2 < nf1) nf = nf2; end
nc = nc1;
if (nc2 < nc1) nc = nc2; end
nr = nr1;
if (nr2 < nr1) nr = nr2; end
%im2double(I), im2int16, im2uint8, im2uint16. 
I1 = im2double(I1);
I2 = im2double(I2);
%I=floor(255*I);

mu1 = 0; 
mu2 = 0; 
   for k=1:nf
     for j=1:nc
      for i=1:nr
       mu1 = mu1 + I1(i,j,k);
	   mu2 = mu2 + I2(i,j,k);
      end
     end
   end
mu1 = mu1/(nf*nc*nr);
mu2 = mu2/(nf*nc*nr);

sigma1 = 0; 
sigma2 = 0; 
sigma12 = 0; 
   for k=1:nf
     for j=1:nc
      for i=1:nr
       sigma1 = sigma1 + (I1(i,j,k)-mu1)*(I1(i,j,k)-mu1);
	   sigma2 = sigma2 + (I2(i,j,k)-mu2)*(I2(i,j,k)-mu2);
	   sigma12 = sigma12 + (I1(i,j,k)-mu1)*(I2(i,j,k)-mu2);
      end
     end
   end
sigma1 = sqrt(sigma1/(nf*nc*nr-1));
sigma2 = sqrt(sigma2/(nf*nc*nr-1));
sigma12 = sigma12/(nf*nc*nr-1);
s = (2*mu1*mu2+C1)/(mu1^2+mu2^2+C1)*(2*sigma12+C2)/(sigma1^2+sigma2^2+C2);
disp(["Index SSIM for " ,video1, " and " ,video2, " results ",num2str(s),", ideal=1."]);
endfunction
