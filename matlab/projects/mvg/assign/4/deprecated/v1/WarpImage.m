function im_warped = WarpImage(im, H)

im = double(im);
H = inv(H);

[u_x, u_y] = meshgrid(1:(size(im,2)), 1:(size(im,1)));
h = size(u_x, 1); w = size(u_x,2);

v_x = H(1,1)*u_x + H(1,2)*u_y + H(1,3);
v_y = H(2,1)*u_x + H(2,2)*u_y + H(2,3);
v_z = H(3,1)*u_x + H(3,2)*u_y + H(3,3);

v_x = v_x./v_z;
v_y = v_y./v_z;

im_warped(:,:,1) = reshape(interp2(im(:,:,1), v_x(:), v_y(:)), [h, w]);
% im_warped(:,:,2) = reshape(interp2(im(:,:,2), v_x(:), v_y(:)), [h, w]);
% im_warped(:,:,3) = reshape(interp2(im(:,:,3), v_x(:), v_y(:)), [h, w]);

im_warped = uint8(im_warped);
