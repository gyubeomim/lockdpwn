%{
    matlab ==> 캡스톤2, LKAS + State Feedback System을 구현하기 위해
                       상태공간을 사용해 4x4의 상태방정식 계수를 구하는 코드이다
%}

Caf = 72653;   % Front Cornering Stiffness
Car = 121449;  % Rear Cornering Stiffness
Lf = 1.170;    % from CG to Front Tire [m]
Lr = 1.77;     % from CG to Rear Tire  [m]  
m = 1820;      % mass of Vehicle [kg]
Iz = 3746;     % Yaw moment of Inertia
Vx = 19.44;    % Vehicle Longitudinal Velocity 

%%
% 상태공간 계수들을 계산한다.  from paper "lateral dynamics'
a11 = -2*(Caf*Lf^2+Car*Lr^2)/(Iz*Vx);
a12 = 2*(Caf*Lf-Car*Lr)/Iz;
a13 = -2*(Caf*Lf-Car*Lr)/(Iz*Vx);
a31 = 2*(-Caf*Lf+Car*Lr)/(m*Vx);
a32 = 2*(Caf+Car)/m;
a33 = -2*(Caf+Car)/(m*Vx);

b11 = 2*Caf*Lf/Iz;
b31 = 2*Caf/m;

%%
% 상태공간용  X' = AX + B
%             Y = CX + D  를 구한다
A = [a11 a12 a13 0; 1 0 0 0; a31 a32 a33 0; 0 0 1 0];
B = [b11 0 b31 0]';
C = [0 0 0 1];
D = 0;


%%
P_K = [-4 -4 -8 -8];      % Pole for State Feedback
P_L = [-9 -9 -25 -25] ;     % Pole for Observer

K = acker(A, B, P_K); 
L = acker(A', C', P_L); 
L = L';





