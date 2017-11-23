function main()

% colors
   red      = [0.867    0.06    0.14];
   blue     = [0        129     205]/256;
   green    = [0        200     70]/256;
   black    = [0        0       0];
   white    = [1        1       1]*0.99;
   cardinal = [196      30      58]/256;
   cerulean = [0        123     167]/256;
   denim    = [21       96      189]/256;
   cobalt   = [0        71      171]/256;
   pblue    = [0        49      83]/256;
   teracotta= [226      114     91]/256;
   tene     = [205      87      0]/256;
   wall_color   = pblue;
   spring_color = cobalt;
   mass_color   = tene;
   a=0.65; bmass_color   = a*mass_color+(1-a)*black;
   % linewidth and fontsize
   lw=2;
   fs=20;

   ww = 0.5;  % wall width
   ms = 0.25; % the size of the mass        
   sw=0.1;    % spring width
   curls = 8;

   A = 0.2; % the amplitude of spring oscillations
   B = -1; % the y coordinate of the base state (the origin is higher, at the wall)

   %  Each of the small lines has length l
   l = 0.05;

   N = 30;  % times per oscillation 
   No = 3; % number of oscillations
   for i = 1:N*No

      % set up the plotting window
      figure(1); clf; hold on; axis equal; axis off;
   
      t = 2*pi*(i-1)/(N-0)+pi/2; % current time
      H= A*sin(t) +  B;      % position of the mass

      % plot the spring from Start to End
      Start = [0, 0]; End = [0, H];
      [X, Y]=do_plot_spring(Start, End, curls, sw);
      plot(X, Y, 'linewidth', lw, 'color', spring_color); 

      % Here we cheat. We modify the point B so that the mass is attached exactly at the end of the
      % spring. This should not be necessary. I am too lazy to to the exact calculation.
      K = length(X); End(1) = X(K); End(2) = Y(K);
            
      % plot the wall from which the spring is hanging
      plot_wall(-ww/2, ww/2, l, lw, wall_color);

      % plot the mass at the end of the spring
      X=[-ms/2 ms/2 ms/2 -ms/2 -ms/2 ms/2]+End(1); Y=[0 0 -ms -ms 0 0]+End(2);
      H=fill(X, Y, mass_color, 'EdgeColor', bmass_color, 'linewidth', lw);

          % the bounding box
          Sx = -0.4*ww;  Sy = B-A-ms+0.05;
          Lx = 0.4*ww+l; Ly=l;
          axis([Sx, Lx, Sy, Ly]);
          plot(Sx, Sy, '*', 'color', white); % a hack to avoid a saveas to eps bug
          
      %saveas(gcf, sprintf('Spring_frame%d.eps', 1000+i), 'psc2') %save the current frame
      disp(sprintf('Spring_frame%d', 1000+i)); %show the frame number we are at
      
      pause(0.01);
      
   end

% The following command was used to create the animated figure.    
% convert -antialias -loop 10000  -delay 7 -compress LZW Spring_frame10* Simple_harmonic_oscillator.gif
   

function [X, Y]=do_plot_spring(A, B, curls, sw);
%  plot a 3D spring, then project it onto 2D. theta controls the angle of projection.
%  The string starts at A and ends at B

   % will rotate by theta when projecting from 1D to 2D
   theta=pi/6;
   Npoints = 500;
   
   % spring length
   D = sqrt((A(1)-B(1))^2+(A(2)-B(2))^2);
   
   X=linspace(0, 1, Npoints);

   XX = linspace(-pi/2, 2*pi*curls+pi/2, Npoints);
   Y=-sw*cos(XX);
   Z=sw*sin(XX);
   
%  b gives the length of the small straight segments at the ends
%  of the spring (to which the wall and the mass are attached)
   b= 0.05; 

% stretch the spring in X to make it of length D - 2*b
   N = length(X);
   X = (D-2*b)*(X-X(1))/(X(N)-X(1));
   
% shift by b to the rigth and add the two small segments of length b
   X=[0, X+b X(N)+2*b]; Y=[Y(1) Y Y(N)]; Z=[Z(1) Z Z(N)]; 

   % project the 3D spring to 2D
   M=[cos(theta) sin(theta); -sin(theta) cos(theta)];
   N=length(X);
   for i=1:N;
      V=M*[X(i), Z(i)]';
      X(i)=V(1); Z(i)=V(2);
   end

%  shift the spring to start from 0
   X = X-X(1);
   
% now that we have the horisontal spring (X, Y) of length D,
% rotate and translate it to go from A to B
   Theta = atan2(B(2)-A(2), B(1)-A(1));
   M=[cos(Theta) -sin(Theta); sin(Theta) cos(Theta)];

   N=length(X);
   for i=1:N;
      V=M*[X(i), Y(i)]'+A';
      X(i)=V(1); Y(i)=V(2);
   end

function plot_wall(S, E, l, lw, wall_color)

%  Plot a wall from S to E.
   no=20; spacing=(E-S)/(no-1);
   
   plot([S, E], [0, 0], 'linewidth', 1.8*lw, 'color', wall_color);

   V=l*(0:0.1:1);

   for i=0:(no-1)
      plot(S+ i*spacing + V, V, 'color', wall_color)
   end