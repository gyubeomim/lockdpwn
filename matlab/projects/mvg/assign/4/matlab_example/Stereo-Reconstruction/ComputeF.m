function [F] = ComputeF(x1, x2)

    n = size(x1, 1);
    bestInNum = 0;
    bestIdx = [];
    
    ransac_thr = 1;
    ransac_iter = 1000;
    for i = 1:ransac_iter
        % We need 8 points to calculate fundamental matrix.
        idx = randperm(n, 8); % Dim.: 8x1
        x1_sampled = x1(idx, :); x2_sampled = x2(idx, :); % Dim.: 8x2
        
        % Compute fundamental matrix using the four sampled points
        F = ComputeFundamentalMatrix(x1_sampled, x2_sampled);
        
        % Calculate inliers
        diff = setdiff(1:n, idx);
        x1_unsampled = x1(diff, :); % (n-8)x2
        x2_unsampled = x2(diff, :); % (n-8)x2
        
        x1_unsampled_padded = [x1_unsampled ones(n-8, 1)]; % (n-8)x3
        x2_unsampled_padded = [x2_unsampled ones(n-8, 1)]; % (n-8)x3
        
        Lu = transpose(F * transpose(x1_unsampled_padded)); % Dim.: (n-8)x3

        distance = abs(sum(Lu .* x2_unsampled_padded, 2))...
            ./ sqrt(sum(Lu(:, 1:2) .* Lu(:, 1:2), 2));
        
        inlierIdx = find(distance <= ransac_thr);
        inlierNum = length(inlierIdx);
        
        % Update best sample points
        if inlierNum >= bestInNum
             bestInNum = inlierNum;
             bestIdx = idx;
        end
    end
    
    % Calculate affine transform using best sampled points
    x1_best = x1(bestIdx, :); % 8x2
    x2_best = x2(bestIdx, :); % 8x2
    
    F = ComputeFundamentalMatrix(x1_best, x2_best);

    VisualizeMatches(x1_best, x2_best, F);
    pause(0.1);
end

function [F] = ComputeFundamentalMatrix(x1, x2)
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

    [~, ~, v] = svd(A);
    f = v(:, end);
    F = transpose(reshape(f, [3, 3])); % 3x3

    % SVD Clean up
    [u, d, v] = svd(F);
    d(3,3) = 0;
    F = u*d*v';
end