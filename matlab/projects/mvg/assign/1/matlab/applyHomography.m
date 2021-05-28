function rectI = applyHomography(img, H)
  tform = maketform('projective',H');
  [boxx boxy]=tformfwd(tform, [1 1 size(img,2) size(img,2)], [1 size(img,1) 1 size(img,1)]);
  minx=min(boxx); maxx=max(boxx);
  miny=min(boxy); maxy=max(boxy);
  rectI =imtransform(img,tform,'XData',[minx maxx],'YData',[miny maxy],'Size',[size(img,1),round(size(img,1)*(maxx-minx)/(maxy-miny))]);
 end