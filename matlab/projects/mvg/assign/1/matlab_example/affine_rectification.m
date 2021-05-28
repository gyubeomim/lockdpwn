%affine rectification of an image of a textbook

%�̹��� �о���̱� (��ķ� ����)

for i=1:5
    images{i} =  imread(sprintf('line%d.jpg',i));
end   

size(images{1})

imshow(images{1})

%�������� �������� �����س���

for i=1:5
    Line{i} = isolateRed(images{i},30);
end

%������ �������� (������)���� ��ȯ
for i=1:5
    BW{i} = im2bw(Line{i},0.9);
end

imshow(BW{4});

for i=1:5
    E{i} = edge(BW{i},'canny');
end

imshow(E{1})


%Lset = �������� �� 2���� ������ ����
%2x2x5 ������� ��� (�޸� �Ҵ�)
Lset = zeros(2,2,5);
[m,n] = size(E{1});

for u=1:5
    %1�ܰ�: �������� connected component�� ����ϱ�
    %ind(i,j)�� (i,j)��ġ�� �ȼ��� ���° ���Ἲ�п� ���ϴ��� �˷���. ��𿡵� ������ ������ 0.
    [ind,num] = bwlabeln(E{u});
    Line1 = zeros(size(E{u}));
    for i=1:m
        for j=1:n
            if ind(i,j)==1
                Line1(i,j) = 1;  %edge�� �ΰ��� ������Ʈ �� ù��° ������Ʈ�� ���鸸 Line1�� �߰�
            end
        end
    end
    aL = im2array(Line1); aL(:,3) = []; %Line1�� ������ķκ��� �ȼ����� 1�� ������ ����
    numaL = size(aL,1);
    Lset(:,:,u) = [aL(1,:); aL(numaL, :)];%������ �̾� Lset�� ����
end
    

Lset(:,3,:) = 1;

%A = equations of the five lines (normal vector)
A = zeros(5,3);
for i=1:5
    A(i,:) = cross(Lset(1,:,i),Lset(2,:,i));
end


%affine rectification

row1 = transpose(null([A(1,:); A(2,:)]));
%intersection of lines #1 and #2
row1=[row1(1)/row1(3), row1(2)/row1(3),1];
row2 = transpose(null([A(3,:); A(4,:)]));
row2=[row2(1)/row2(3), row2(2)/row2(3),1];
%row2 = intersection of lines #3 and 4
ell = null([row1; row2]);

H = [1 0 0 ; 0 1 0 ; transpose(ell)];

% ȣ��׶��� H�� ������ ����
I = images{1};
bwI = im2bw(I,.5);
abw = im2array(bwI);
J = abw;
HJ = J*transpose(H);

% Euclidean ������� �ű�� (z��ǥ�� 1�� �ٲ�)
N = size(HJ,1);
X = zeros(N,3);
for i=1:N
    X(i,:) = [HJ(i,1)/HJ(i,3), HJ(i,2)/HJ(i,3), 0 ];
end

%rectify�� �̹��� ����
pcshow(X)

% rectification with unidirectional scaling

P1 = H*transpose(row1);
P2 = H*transpose(row2);

P1(3) = 0; P2(3) = 0; %line at infinity�� �����̹Ƿ�

A = inv([P1(1:2), P2(1:2)]);
HA = [A, [0;0]; 0 0 1];
H2 = HA*H;


HJ = J*transpose(H2);

N = size(HJ,1);
X = zeros(N,3);
for i=1:N
    X(i,:) = [HJ(i,1)/HJ(i,3), HJ(i,2)/HJ(i,3), 0 ];
end

pcshow(X)



%metric rectification up to similarity





