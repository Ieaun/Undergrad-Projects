function[NoStarfish] =PipeStar5(Starfish)

%convert image to HSV
HSV= rgb2hsv(Starfish);
%use saturation channel
satchannel = HSV(:,:,2);

%create image using only sat channel
SatFish = cat(3,satchannel,satchannel,satchannel);
% convert to black and white
SatFIshbw = im2bw(SatFish);
%fill in holes
e= imfill(SatFIshbw,"holes");
%label items
f = bwlabel(e)
%get area and bounding for each object 
g = regionprops(f,'Area','BoundingBox');

g(1)
%display area for all objects 
area_values = [g.Area]
%Find areas between 7000 and 9000
idx = find((405 < area_values) & (area_values<=900))
h = ismember(f,idx)

% point to location of starfish
stats = regionprops('table',h,'Centroid','MajorAxisLength','MinorAxisLength');
centers = stats.Centroid;
diameters = mean([stats.MajorAxisLength stats.MinorAxisLength],2);
radii = diameters/4;     
NoStarfish = int2str(height(stats)) + " Starfish" ;

figure
subplot(231),imshow(Starfish),title('Original')
subplot(232),imshow(SatFish),title('HSV Sat channel');
subplot(233),imshow(e),title('B/W and Filled in');
subplot(234),imshow(h),title('Area between 400 and 900');
subplot(235),vislabels(h),title(NoStarfish);
