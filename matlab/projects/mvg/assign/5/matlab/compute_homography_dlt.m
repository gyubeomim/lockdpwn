function [H] = compute_homography_dlt(x_left, x_right)
    % get centroid of four points.
    centroid1 = [sum(x_left(1,:))/4, sum(x_left(2,:))/4];
    centroid2 = [sum(x_right(1,:))/4, sum(x_right(2,:))/4];
    
    % average distance from the origin.
    dist1 = 0;
    dist2 = 0;
    
    for i=1:4 
       x1 = x_left(1,i);
       y1 = x_left(2,i);
       x2 = x_right(1,i);
       y2 = x_right(2,i);
       dist1 = dist1 + sqrt((x1-centroid1(1))^2 + (y1-centroid1(2))^2);
       dist2 = dist2 + sqrt((x2-centroid2(1))^2 + (y2-centroid2(2))^2);
    end
    
    dist1 = dist1/4;
    dist2 = dist2/4;
    
    % compute T for each of the 2 sets of points
    T1 = [ 1/dist1/sqrt(2), 0, -centroid1(1)/dist1/sqrt(2); ...
          0, 1/dist1/sqrt(2), -centroid1(2)/dist1/sqrt(2); ...
          0, 0, 1];
    T2 = [ 1/dist2/sqrt(2), 0, -centroid2(1)/dist2/sqrt(2); ...
          0, 1/dist2/sqrt(2), -centroid2(2)/dist2/sqrt(2); ...
          0, 0, 1];
    
    % compute the transformed x values for each of the 2 sets of points
    pts1_norm = cat(1, x_left, ones(1,4));
    pts2_norm = cat(1, x_right, ones(1,4));
    
    x1_tf = T1*pts1_norm;
    x2_tf = T2*pts2_norm;
    x1_tf = x1_tf(1:2,:);
    x2_tf = x2_tf(1:2,:);

    A = zeros(8,9);
    for i=1:4
        x = x1_tf(1,i);
        y = x1_tf(2,i);
        u = x2_tf(1,i);
        v = x2_tf(2,i);
        A(2*i-1,:) = [-x, -y, -1, 0, 0, 0, u*x, u*y, u];
        A(2*i,:) = [0, 0, 0, -x, -y, -1, v*x, v*y, v];
    end
    
    % compute h as the nullspace of A.
    h = null(A);
    H = [h(1), h(2), h(3); ...
        h(4), h(5), h(6); ...
        h(7), h(8), h(9)];

    % finally get H.
    H = inv(T2)*H*T1;
end