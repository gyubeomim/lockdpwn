function [disparity] = DenseMatch(im1, im2)
    [h, w] = size(im1);
    
    lr_pad = zeros(h, 6); tb_pad = zeros(6, w + 6*2);
    im1_padded = [tb_pad; [lr_pad im1 lr_pad]; tb_pad];
    im2_padded = [tb_pad; [lr_pad im2 lr_pad]; tb_pad];
    
    [~, d1]= vl_dsift(single(im1_padded), 'size', 4, 'step', 1, 'fast');
    [~, d2]= vl_dsift(single(im2_padded), 'size', 4, 'step', 1, 'fast');
    
    d1 = reshape(d1', [h w 128]);
    d2 = reshape(d2', [h w 128]);
    
    disparity = zeros(h, w);
    
    for i = 1:h
        X = reshape(d2(i, :, :), [w, 128]);
        Y = reshape(d1(i, :, :), [w, 128]);
        knn_idx = knnsearch(double(X), double(Y));
        disparity(i, :) = abs(knn_idx' - (1:w));
    end
end