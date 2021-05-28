for i=1:5
    images{i} = imread(sprintf('%d.jpg',i));
end

%size(images{1});
%imshow(images{1});

corners=zeros(63,2,5);

for i=1:5
    [corners(:,:,i), ~] = detectCheckerboardPoints(images{i});
end


%for i=1:5
%    I = images{i};
%    subplot(2,3,i);
%    imshow(I);
%    hold on;
%    plot(corners(:,1,i), corners(:,2,i),'ro');
%end

X = zeros(63,4);
a = 20; % [mm]

for j=1:9
    for i=1:7
        X(7*(j-1)+i,:) = [(j-1)*a (i-1)*a 0 1];
    end
end

% test
%params = estimateCameraParameters(corners, X(:,1:2));

H = zeros(3,3,5);

for i=1:5
    H(:,:,i) = homography2d(X, corners(:,:,i));
end

k = sym('k', [1 6]);
KtinvKinv = [k(1) k(2) k(3); k(2) k(4) k(5); k(3) k(5) k(6)];
eqs = zeros(10,6);

for i=1:5
    eqs(2*i-1,:) = equationsToMatrix(transpose(H(:,1,i))*KtinvKinv*H(:,2,i)==0, k);
    eqs(2*i,:) = equationsToMatrix(transpose(H(:,1,i))*KtinvKinv*H(:,1,i) - transpose(H(:,2,i))*KtinvKinv*H(:,2,i)==0, k);
end

[U,D,V] = svd(eqs);
KtinvKinv_ = subs(KtinvKinv, k, transpose(V(:,6)));
KtinvKinv_ = double(KtinvKinv_);

% cholesky decompose 
pseudoKinv = chol(KtinvKinv_);
K = inv(pseudoKinv);
K = K/K(3,3);
Kinv = inv(K);

R = zeros(3,3,5);
t = zeros(3,5);

for i=1:5
    r1 = Kinv * H(:,1,i);
    r2 = Kinv * H(:,2,i);
    r3 = cross(r1,r2);
    R_ = [r1 r2 r3];
    [u,d,v] = svd(R_);
    R(:,:,i) = u*v'; % rotation

    lambda = 1 / norm(r1);
    t(:,i) = lambda * Kinv * H(:,3,i); % translation
end
