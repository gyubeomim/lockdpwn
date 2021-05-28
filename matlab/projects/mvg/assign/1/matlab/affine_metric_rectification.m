%affine rectification of an image of a textbook

%이미지 읽어들이기 (행렬로 저장)
for i=1:4
    images{i} =  imread(sprintf('0%d.png',i));
end   

size(images{1})

imshow(images{1})

%사진에서 빨강색만 축출해내기

for i=1:4
    Line{i} = isolateRed(images{i},120);
end

%사진을 이진영상 (흑백사진)으로 변환
for i=1:4
    BW{i} = im2bw(Line{i},0.9);
end

imshow(BW{4});

for i=1:4
    E{i} = edge(BW{i},'canny');
end

imshow(E{1})


%Lset = 직선에서 각 2개의 끝점을 축출
%2x2x4 영행렬을 잡기 (메모리 할당)
Lset = zeros(2,2,4);
[m,n] = size(E{1});

for u=1:4
    %1단계: 사진에서 connected component를 계산하기
    %ind(i,j)는 (i,j)위치의 픽셀이 몇번째 연결성분에 속하는지 알려줌. 어디에도 속하지 않으면 0.
    [ind,num] = bwlabeln(E{u});
    Line1 = zeros(size(E{u}));
    for i=1:m
        for j=1:n
            if ind(i,j)==1
                Line1(i,j) = 1;  %edge의 두개의 컴포넌트 중 첫번째 컴포넌트의 점들만 Line1에 추가
            end
        end
    end
    aL = im2array(Line1); aL(:,3) = []; %Line1의 이진행렬로부터 픽셀값이 1인 점들을 나열
    numaL = size(aL,1);
    Lset(:,:,u) = [aL(1,:); aL(numaL, :)];%끝점을 뽑아 Lset에 저장
end
    

Lset(:,3,:) = 1;

%Lines = equations of the four lines (normal vector)
Lines = zeros(4,3);
for i=1:4
    Lines(i,:) = cross(Lset(1,:,i),Lset(2,:,i));
end


%affine rectification

%row1 = intersection of lines #1 and #2
row1 = transpose(null([Lines(1,:); Lines(2,:)]));
row1=[row1(1)/row1(3), row1(2)/row1(3),1];

%row2 = intersection of lines #3 and 4
row2 = transpose(null([Lines(3,:); Lines(4,:)]));
row2=[row2(1)/row2(3), row2(2)/row2(3),1];

ell = null([row1; row2]);

H = [1 0 0 ; 0 1 0 ; transpose(ell)];

affine_img = applyHomography(images{1}, H);
imshow(affine_img);


%metric rectification up to similarity
% 두 개의 서로 직교하는 직선 l1,m1, l2,m2를 설정한다.
l1 = Lines(1,:);
l2 = Lines(2,:);
m1 = Lines(4,:);
m2 = Lines(3,:);
l11 = [l1(1)/l1(3) l1(2)/l1(3)];
m11 = [m1(1)/m1(3) m1(2)/m1(3)];
l22 = [l2(1)/l2(3) l2(2)/l2(3)];
m22 = [m2(1)/m2(3) m2(2)/m2(3)];


ortho_constraints = [l11(1)*m11(1)  l11(1)*m11(2)+l11(2)*m11(1)  l11(2)*m11(2);
                     l22(1)*m22(1)  l22(1)*m22(2)+l22(2)*m22(1)  l22(2)*m22(2)];
s = null(ortho_constraints);
% S = KK^T
S = [s(1) s(2); s(2) s(3)];

% cholesky는 S가 항상 Positive Definite이어야 한다는 조건이 있으므로 보다 범용적인 SVD를 사용하여 해를 구한다.
[U,D,V] = svd(S);
    
% S로부터 K 값을 구한다.
K = U*sqrt(D)*U';
Hmetric = eye(3);
Hmetric(1,1) = K(1,1);
Hmetric(1,2) = K(1,2);
Hmetric(2,1) = K(2,1);
Hmetric(2,2) = K(2,2);
 
% Homography 적용 후 이미지 출력
metric_img = applyHomography(images{1}, inv(Hmetric)*H);
figure(2);
imshow(metric_img)

imwrite(metric_img, 'warped_img.png')