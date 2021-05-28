function [F] = calculate_fundamental_matrix(x1,x2)

% get the centroid.
centroid = mean(x1, 2);

% compute the distance to the centroid.
dist = sqrt(sum((x1 - repmat(centroid, 1, size(x1, 2))) .^ 2, 1));

% get the mean distance.
mean_dist = mean(dist);

% normalization homography matrix.
H1norm = [sqrt(2) / mean_dist, 0, -sqrt(2) / mean_dist * centroid(1);
           0, sqrt(2) / mean_dist, -sqrt(2) / mean_dist * centroid(2);
           0, 0, 1];
       
centroid = mean(x2, 2);
dist = sqrt(sum((x2 - repmat(centroid, 1, size(x2, 2))) .^ 2, 1));
mean_dist = mean(dist);
H2norm = [sqrt(2) / mean_dist, 0, -sqrt(2) / mean_dist * centroid(1);
           0, sqrt(2) / mean_dist, -sqrt(2) / mean_dist * centroid(2);
           0, 0, 1];       
       
x1 = H1norm * x1;
x2 = H2norm * x2;
x1 = transpose(x1 ./ repmat(x1(3,:), [3,1]));
x2 = transpose(x2 ./ repmat(x2(3,:), [3,1]));

% estimate fundamental matrix.
A = zeros(8, 9);
A(:, 1) = x1(:, 1).*x2(:, 1);
A(:, 2) = x1(:, 2).*x2(:, 1);
A(:, 3) = x2(:, 1);
A(:, 4) = x1(:, 1).*x2(:, 2);
A(:, 5) = x1(:, 2).*x2(:, 2);
A(:, 6) = x2(:, 2);
A(:, 7) = x1(:, 1);
A(:, 8) = x1(:, 2);
A(:, 9) = ones(8, 1);

% first SVD to get F0.
[~, ~, v] = svd(A);
f = v(:, end);
F0 = transpose(reshape(f, [3, 3])); % 3x3

% second SVD to get Fnorm.
[u, d, v] = svd(F0);
d(3,3) = 0;
Fnorm = u*d*v';

% finally get F.
F = H2norm' * Fnorm * H1norm;
end

