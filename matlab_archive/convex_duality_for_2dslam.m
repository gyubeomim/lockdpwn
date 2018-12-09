%{
Convex HW for implementing "Duality-based Verification Techniques for 2D  SLAM Code"
        composed by Edward Im
        strongly inspired from [Luca Carlone] the author of the paper
%}
clear all
close all
clc

%% Create Random Pose-Graph
nrNodes = 10;  % 그래프에서  노드의 개수( 랜덤 생성)
sigmaR = 0.1;  % 회전운동의 noise 표준편차
sigmaT = 0.1;  % 병진운동의 noise 표준편차
pLC = 0.1;     % 두 노드가 연결될 확률 (Loop Clousre)

[edges, thGT, posesGT] = buildRandomPoseGraph(nrNodes, sigmaR, sigmaT, pLC);

%% Gauss-Newton 방법을 이용해 Primal 문제를 푼다
posesGNfromGT = refinePose2DvectToMat(edges, thGT, posesGT);
pstar = evaluatePrimalPose2D(edges, posesGNfromGT);

%% Duality 문제를 풀기 위한 Matrix 생성
Wcpx_r = buildPGOmatrices(edges);

%% Dual 문제 계산
cvx_begin SDP
cvx_precision best
variable lambda_r(nrNodes)
maximize( sum(lambda_r) )
subject to
Wcpx_r - diag([zeros(nrNodes-1,1) ; lambda_r]) >= 0;
cvx_end

dstar = sum(lambda_r);

%% Primal <-> Dual의 차이 계산
dgap = pstar - dstar;
fprintf('pstar = %g \n',pstar)
fprintf('dstar_r = %g \n',dstar)
fprintf('dgap = %g \n',dgap)



%% function1 : 랜덤 Pose Graph를 생성하는 함수
function [edges, thGT, posesGT] = buildRandomPoseGraph(nrNodes, sigmaR, sigmaT, pLC)
cartesianBounds = 10;
posesGT = zeros(nrNodes,3);
for i=1:nrNodes
    xy = cartesianBounds * rand(1,2);
    th = 2*pi * (rand-0.5); % in [-pi,pi]
    posesGT(i,:) = [xy th];
end

% Spanning Tree 형태로 Pose Graph를 생성한다
edges = [];
for k=1:nrNodes-1 
    p_i = posesGT(k,:)';
    p_j = posesGT(k+1,:)';    
    deltaPoseNoisy = poseGraphSubNoisy(p_j , p_i, sigmaT, sigmaR);
    edges(end+1,1:11) = [k k+1 deltaPoseNoisy' 1/sigmaT^2 0 0 1/sigmaT^2 0 1/sigmaR^2];
end

thGT = posesGT(:,3);

% 랜덤 확률로 노드 간 Loop Closure를 설정하는 코드
n = size(edges,1);
nrNodes = n+1;
for i=1:nrNodes
  otherNodes = setdiff(randperm(nrNodes),i);
  for j = otherNodes
    if  length(find(edges(:,1)==i & edges(:,2)==j))==0 && ... % edge가 없는 경우만 Loop Closure 추가
        length(find(edges(:,2)==i & edges(:,1)==j))==0
      
      % loop 값에 확률값 (Noise) 추가
      if rand < pLC
        p_i = posesGT(i,:)';
        p_j = posesGT(j,:)';
        deltaPoseNoisy = poseGraphSubNoisy(p_j , p_i, sigmaT, sigmaR);
        edges(end+1,1:11) = [i j deltaPoseNoisy' 1/sigmaT^2 0 0 1/sigmaT^2 0 1/sigmaR^2];
      end
    end
  end
end
end

%% function2 : Poses 값들을 2D Vector에서 Matrix로 변환해주는 함ㅅ
function posesMat3xN = refinePose2DvectToMat(edges, thEst, posesInit)
m = size(edges,1);
nrNodes = length(thEst); % thEst : orientation의 추정값
n = nrNodes-1;           % 관측가능한 노드의 개수

J = sparse(spalloc(4*m, 3*nrNodes, 6*4*m)); 
fhat = sparse(zeros(4*m,1));
Mij = [-1 0; 0 -1];
cost = 1e+20; % 초기 cost 값

% 초기 poseEst 값
poseEst = [reshape(posesInit(:,1:2)',2*nrNodes,1); posesInit(:,3)]; 

nonAnchorInds = [3:2*nrNodes,2*nrNodes+2:3*nrNodes];
JR = spalloc(4*m, nrNodes, 2*4*m);  
JC = spalloc(4*m, 2*nrNodes, 4*4*m);

for iter=1:10 
    % 선형화
  costPrec = cost;
  for k=1:m  
    tic
    id1 = edges(k,1);
    id2 = edges(k,2);
    Ri = rot2D(poseEst(2*nrNodes+id1));
    Rj = rot2D(poseEst(2*nrNodes+id2));
    Rij = rot2D(edges(k,5));
    Deltaij = edges(k,3:4)';
    DeltaijMat = [Deltaij(1)  -Deltaij(2); Deltaij(2)  Deltaij(1)];
    
    id1c = BlockToMatIndices(id1,2);
    p1 = poseEst(id1c);
    id2c = BlockToMatIndices(id2,2);
    p2 = poseEst(id2c);
    
    fcart = p2 - p1 - DeltaijMat * Ri(:,1);
    frot  = Rij * Ri(:,1) + Mij * Rj(:,1);   
    
    inf_th = sqrt ( edges(k,11) );  % 회전운동 측정값 표준편차의 inverse
    inf_cart = sqrt ( edges(k,6) ); % 병진운동 측정값 표준편차의 inverse

    
    % f=[fcart frot] , f -> R^4
    rowInd = BlockToMatIndices(k,4);
    fhat(rowInd) = [inf_cart * fcart; inf_th * frot];
 
    JR(rowInd,id1) = [ - inf_cart * DeltaijMat * Ri(:,2); 
                         inf_th * Rij * Ri(:,2) ];
    JR(rowInd,id2) = [ zeros(2,1)          ; 
                       inf_th * Mij * Rj(:,2) ];
     
    JC(rowInd,id1c) = [-inf_cart * eye(2) ; 
                        zeros(2,2)]; 
    JC(rowInd,id2c) = [ inf_cart * eye(2) ; 
                        zeros(2,2)]; 
  end
  cost = norm(fhat)^2;
  Jtot = [JC(:,3:end) JR(:,2:end)];          
  corrEst = - (Jtot'*Jtot) \ (Jtot' * fhat);  % fhat 값으로 인해 (-)를 추가한다
  
  poseEst(nonAnchorInds) = poseEst(nonAnchorInds) + corrEst; % 추정값 Update
  
  % cost가 특정 값 이하로 작아질 때까지 반복한다
  relCostChange = abs((cost - costPrec)/costPrec);
  if norm(corrEst) < 1e-4 || relCostChange < 1e-5
    break;
  end
end

nrNodes = length(poseEst)/3;
posesMat3xN = zeros(nrNodes,3);

for i=1:nrNodes
  posesMat3xN(i,1:3) = [poseEst(2*i-1:2*i)'  poseEst(2*nrNodes+i)];
end
end

%% function3 : Primal Solution을 푸는 함수
function [cost2D] = evaluatePrimalPose2D(edges, poseEst)
[nrNodes,m] = SizeDataset(edges);

temp = zeros(3*nrNodes,1); 

for i=1:nrNodes
    idi = BlockToMatIndices(i,2);
    temp(idi) = poseEst(i,1:2)';       % positions
    temp(2*nrNodes+i) = poseEst(i,3);  % rotations
end
poseEst = temp;

thEst = poseEst(2*nrNodes+1:end); 

cost2D = 0;
rotCost = 0;
cartCost = 0;

% 각각의 측정마다 루프를 돈다 (m개의 측정)
for k=1:m 
  id1 = edges(k,1);
  id2 = edges(k,2);
  Ri = rot2D(thEst(id1));
  Rj = rot2D(thEst(id2));
  Rij = rot2D(edges(k,5));
  Deltaij = edges(k,3:4)';
  
  inf_th = sqrt ( edges(k,11) );  % 회전운동 측정값 표준편차의 inverse
  inf_cart = sqrt ( edges(k,6) ); % 병진운동 측정값 표준편차의 inverse
  
  X = inf_th * (Ri * Rij - Rj);
  id1c = BlockToMatIndices(id1,2);
  id2c = BlockToMatIndices(id2,2);
  Xcart =  inf_cart * (poseEst(id2c) - poseEst(id1c) - Ri * Deltaij);
  
  cost2D = cost2D + 0.5 * norm(X,'fro')^2 + norm(Xcart)^2;
  
  rotCost = rotCost   + norm(X,'fro')^2;
  cartCost = cartCost + norm(Xcart)^2;
end
end

%% function4 : Pose Graph Optimization(PGO)을 위한 Matrix Wcpx를 만드는 코드 
function [Wcpx_r] = buildPGOmatrices(edges)
[nrNodes,m] = SizeDataset(edges);

barDtilde = spalloc(m,nrNodes,m);
barQtilde = sparse(zeros(nrNodes,nrNodes));
barU = spalloc(m,nrNodes,2*m); 
barAtilde = ReducedIncidenceMatrix(edges); % barA : augmented incidence matrix

for k=1:m
  % information for whitening
  infAng  =  sqrt(edges(k,11));
  infCart =  sqrt(edges(k,6));
  
  % whiten barAtilde
  barAtilde(k,:) = infCart * barAtilde(k,:); 
  
  % create barD
  Deltaij = edges(k,3:4)';
  DeltaijMat = [Deltaij(1)  -Deltaij(2); Deltaij(2)  Deltaij(1)];
  Rij = rot2D(edges(k,5));
  
  i = edges(k,1);
  barDtilde(k,i) = - infCart * RealMat2Complex(DeltaijMat);
  
  % create barQ
  j = edges(k,2);
  deltaij = norm(Deltaij);
  barQtilde(i,i) = barQtilde(i,i) + (infAng^2 + infCart^2 * deltaij^2);
  barQtilde(j,j) = barQtilde(j,j) + infAng^2;
  barQtilde(i,j) = barQtilde(i,j) - infAng^2 * RealMat2Complex(Rij');
  barQtilde(j,i) = barQtilde(j,i) - infAng^2 * RealMat2Complex(Rij);
end

Wcpx = [barAtilde'*barAtilde   barAtilde'*barDtilde;   barDtilde'*barAtilde  barQtilde];
Wcpx_r = Wcpx(2:end,2:end);  % 1행 1열은 제외한다 (해당 노드는 fixed pose로 가정한다)
end

%% function5
function [At_full] = ReducedIncidenceMatrix(edges_id)
m = size(edges_id,1);
n = max(  max(edges_id(:,1)), max(edges_id(:,2))  ) - 1; 

row_ids = [ [1:m] [1:m] ]; 
col_ids = [ edges_id(:,1); edges_id(:,2) ];
values = [ -ones(1,m) ones(1,m) ]; 
At_full = sparse(row_ids,col_ids,values,m,n+1);

end


%% function6 : 실수 행렬 ==> 복소수 행렬로 변환해주는 함수
function mtilde = RealMat2Complex(M)
im = sqrt(-1);
a = norm([M(1,1) , M(2,1)]);

M = M/a;
th = atan2(M(2,1) , M(1,1) ); 
mtilde = a * exp( im * th );
end

%% funstion7 : 2D 회전행렬
function R = rot2D(th)
R = [cos(th)    -sin(th)
     sin(th)     cos(th)];
end

%% function8 : Pose Graph에 Noise항을 추가하는 함수
function [deltaPoseNoisy] = poseGraphSubNoisy(p_j , p_i, sigmaT, sigmaR)
p_j = p_j(:);
p_i = p_i(:);

rho_i = p_i(1:2);
rho_j = p_j(1:2);
th_i = p_i(3);
th_j = p_j(3);

R = rot2D(th_i);

delta_th = wrapToPi(th_j - th_i);

deltaPose = [ R' * (rho_j   -  rho_i)
                            delta_th  ];

noise = [sigmaT*randn(2,1) ;  sigmaR*randn];  % 가우시안 Noise

deltaPoseNoisy = deltaPose + noise;
deltaPoseNoisy(3) = wrapToPi(deltaPoseNoisy(3)); 
end


%% function9
function matrixIndices = BlockToMatIndices(blockIndex, blockSize)

numBlocks = length(blockIndex);
matrixIndices = zeros(numBlocks*blockSize,1);

for i=1:numBlocks
  matrixIndices(blockSize*i-(blockSize-1) : blockSize*i) = [blockSize*blockIndex(i)-(blockSize-1) : blockSize*blockIndex(i)];
end
end


%% function10 :  데이터셋의 크기를 반환하는 함수
function [nrNodes,m,l,n] = SizeDataset(edges)
nrNodes = max ( max(edges(:,1)), max(edges(:,2)) );
n = nrNodes - 1; %  노드의 개수-1 
m = size(edges,1);
l = m-n;
end
