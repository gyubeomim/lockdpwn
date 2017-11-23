function [K,L] = state_feedback_Gain(Q1,Q2,R,PL)

global A B

% LKAS State-Space model
C = [1, 0, 0, 0];
D = 0;

% LQR Weighted Matrix
Q = diag([Q1,1,Q2,1]);

% State Feedback Gain
K = lqr(A,B,Q,R);     % lqr을 사용해서 K 게인을 구할 수 있고 Pole을 사용해서 acker()함수로 구할 수도 있다
L = place(A',C',PL);  % place() 대신 acker() 함수를 사용해도 결과가 같게 나온다

end