clear; close all; clc; 

rng(0, 'twister');
% Problem declaration n = 5;
PG = zeros(n); end R0 = eye(3); % nominal attitude
Rtrue = zeros(3, 3, n); ttrue = zeros(3, 1, n); for i = 1 : n
Rtrue(:, :, i) = R0; ttrue(:, :, i) = [cos(2*pi*i/n), sin(2*pi*i/n), 0]'; end
% SDP
MQQ = zeros(3*n); MQT = zeros(3*n, n); MTT = zeros(n); for i = 1 : n - 1 for j = i + 1 : n if PG(i, j) == 1 ei = zeros(n, 1); ei(i) = 1; ej = zeros(n, 1); ej(j) = 1; Ei = kron(ei, eye(3)); Ej = kron(ej, eye(3));
ptb1 = 0.1*randn(3, 1); ptb2 = 0.01*randn(3, 1); Rij = expm([0 -ptb1(3) ptb1(2);
ptb1(3) 0 -ptb1(1); -ptb1(2) ptb1(1) 0]); tij = ttrue(:,:,j) ttrue(:,:,i) + ptb2; MQQ = MQQ - 1/2*(Ei*Rij*Ej' +
Ej*Rij'*Ei');
MQT = MQT - Ei*tij*(ej-ei)'; MTT = MTT + (ej - ei)*(ej ei)'; end end end M = [MQQ MQT; MQT' MTT];
cvx_begin SDP variable Lambda0(3, 3, n) symmetric; Lambda = Lambda0(:, :, 1); for i = 2 : n
Lambda = blkdiag(Lambda,
Lambda0(:, :, i)); end
maximize(trace(Lambda)) subject to 0 <= M - blkdiag(Lambda, zeros(n));
cvx_end
Lambda2 = full(Lambda); X = null(M - blkdiag(Lambda2, zeros(n)));
% pose graph
for i = 1 : n - 1 PG(i, i + 1) = 1;