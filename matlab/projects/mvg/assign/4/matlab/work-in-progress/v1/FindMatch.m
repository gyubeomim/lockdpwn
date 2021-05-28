% FindMatch Find point correspondences in two images
%
%   [x1, x2] = FindMatch(I1, I2) extracts SIFT descriptors, matches point
%   correspondences using knnsearch, filters the matches using ratio test,
%   and performs bi-directional consistency check.
%
%   Input:
%       I1  = gray-scale image with uint8 format (first image)
%       I2  = gray-scale image with uint8 format (second image)
%
%   Output:
%       x1  = nx2 matrix with co-ordinates of matching points in I1
%       x2  = nx2 matrix with co-ordinates of matching points in I2

function [x1, x2] = FindMatch(I1, I2)

    % Extract descriptors of I1 and I2 using vl_sift
    [fa, da] = vl_sift(single(I1));
    [fb, db] = vl_sift(single(I2));
    
    % Match descriptors from I1 to I2 using knnsearch
    [Idx_i1Toi2, Dist_i1Toi2] =...
        knnsearch(double(db'), double(da'), 'K', 2);
    
    % Filter the matches using ratio test
    index_filter_i1Toi2 =...
        (Dist_i1Toi2(:, 1) ./ Dist_i1Toi2(:, 2)) < 0.7;
    Idx_i1Toi2 = Idx_i1Toi2(index_filter_i1Toi2, 1);
    Idx_da = 1:size(da, 2);
    matches_i1Toi2 = [Idx_da(1, index_filter_i1Toi2); Idx_i1Toi2'];
    
    
    % Match descriptors from I2 to I1 using knnsearch
    [Idx_i2Toi1, Dist_i2Toi1] =...
        knnsearch(double(da'), double(db'), 'K', 2);
    
    % Filter the matches using ratio test
    index_filter_i2Toi1 =...
        (Dist_i2Toi1(:, 1) ./ Dist_i2Toi1(:, 2)) < 0.7;
    Idx_i2Toi1 = Idx_i2Toi1(index_filter_i2Toi1, 1);
    Idx_db = 1:size(db, 2);
    matches_i2Toi1 = [Idx_i2Toi1'; Idx_db(1, index_filter_i2Toi1)];
    
   
    % Bidirectional consistency check
    matches = intersect(matches_i1Toi2', matches_i2Toi1', 'rows')';
    
    x1 = [fa(1,matches(1,:))' fa(2,matches(1,:))'];
    x2 = [fb(1,matches(2,:))' fb(2,matches(2,:))'];
    x1 = round(x1);
    x2 = round(x2);
end