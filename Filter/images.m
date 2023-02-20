clear all;
%clear X map;
imglist = {'flujet', ... Fluid Jet
           'spine', ... Bone
           'gatlin', ... Gatlinburg
           'durer', ... Durer
           'detail', ... Durer Detail
           'cape', ... Cape Cod
           'clown', ... Clown
           'earth', ... Earth
           'mandrill', ... Mandrill
           'spiral'};

colorlabels = {'default', 'hsv','hot','pink',...
               'cool','bone','prism','flag',...
               'gray','rand'};

rows=[1 256];
cols=[1 256];
load(imglist{4},'X','map');
imshow(X,map);
for i=rows(1):rows(2)
  for j=cols(1):cols(2)
    Y(i,j)=X(i,j);
  end
end
figure; imshow(Y,map);
%imagesc(X);
%colormap(map);
%colormap(colorlabels{1});
axis off;