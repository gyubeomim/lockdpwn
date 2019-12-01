<<<<<<< HEAD
function [ts,xs,ys] = rk4zoh(dfun,tf,x0,dt)

% [ts,xs,ys] = rk4zoh(dfun,tf,x0,dt)
%
% This function solves IVP(Initial Value Problem) by fixed step
% Runge Kutta method of 4th order.
% IVP: dx/dt = f(t,x) , x(0) = x0
%
% dfun must be of the form: dx = dfun(t,x) or [dx,y] = dfun(t,x)
% where y is an output vector.
% dx and y must be column vectors.
% When dfun returns y, compute y only when global variable I_EVAL_Y = 1.
%
% In Runge Kutta of 4th order, f(t,x) is computed 4 times in one step. 
% This function sends out the order number that f(t,x) is computed using
% global variable N_EVAL_F. By using this variable, the user can
% implement zero order hold of controls.
%
% input 
%   dfun: function handle that computes dx/dt
%         dfun must have the format: dx = dfun(t,x) or [dx,y] = dfun(t,x) 
%         dx and y must be column vectors
%   tf: final time 
%   x0: initial condition of x (must be a column vector)
%   dt: step size 
%
% output 
%   ts: nt-by-1 array containing time points. 
%   xs: nt-by-nx array containing states at ts. 
%   ys: nt-by-ny array containing outputs at ts. 

% The following global variables need not be initialized.
global N_EVAL_F I_EVAL_Y

t = 0;
x = x0;

ts = t;
xs = x';
ys = []; % ys is filled only when dfun returns two outputs

% ioutput = flag that tells whether y is computed by dfun
ioutput = 0;
if nargout(dfun) == 2
    ioutput = 1;
end

dt2 = dt / 2;

tff = tf - 0.5*dt;

while t < tff
    
    % at each iteration, x(t+dt) and y(t) are computed

    % f(t,x) is computed for the 1st time (compute y when requested)
    N_EVAL_F = 1;
    if ( ioutput == 1 ) % when output is requested
        I_EVAL_Y = 1;
        [dx,y] = dfun(t,x); % this is for finding y at t=0
        ys = [ys; y']; 
    else
        dx = dfun(t,x);
    end
    f1 = dt * dx;
    
    I_EVAL_Y = 0;
    
    % f(t,x) is computed for the 2nd time
    N_EVAL_F = 2;
    f2 = dt * dfun(t+dt2,x+f1/2);
    
    % f(t,x) is computed for the 3rd time
    N_EVAL_F = 3;
    f3 = dt * dfun(t+dt2,x+f2/2);
    
    % f(t,x) is computed for the 4th time
    N_EVAL_F = 4;
    f4 = dt * dfun(t+dt,x+f3);

    x = x + (f1 + 2*f2 + 2*f3 + f4)/6;
    t = t + dt;
    
    ts = [ts; t];
    xs = [xs; x']; 
        
end

% find y at final time after simulation is completed
if ( ioutput == 1 )
    N_EVAL_F = 1;
    I_EVAL_Y = 1;
    [dx,y] = dfun(t,x); % this is for finding y at t+dt
    ys = [ys; y']; 
end
        
=======
function [ts,xs,ys] = rk4zoh(dfun,tf,x0,dt)

% [ts,xs,ys] = rk4zoh(dfun,tf,x0,dt)
%
% This function solves IVP(Initial Value Problem) by fixed step
% Runge Kutta method of 4th order.
% IVP: dx/dt = f(t,x) , x(0) = x0
%
% dfun must be of the form: dx = dfun(t,x) or [dx,y] = dfun(t,x)
% where y is an output vector.
% dx and y must be column vectors.
% When dfun returns y, compute y only when global variable I_EVAL_Y = 1.
%
% In Runge Kutta of 4th order, f(t,x) is computed 4 times in one step. 
% This function sends out the order number that f(t,x) is computed using
% global variable N_EVAL_F. By using this variable, the user can
% implement zero order hold of controls.
%
% input 
%   dfun: function handle that computes dx/dt
%         dfun must have the format: dx = dfun(t,x) or [dx,y] = dfun(t,x) 
%         dx and y must be column vectors
%   tf: final time 
%   x0: initial condition of x (must be a column vector)
%   dt: step size 
%
% output 
%   ts: nt-by-1 array containing time points. 
%   xs: nt-by-nx array containing states at ts. 
%   ys: nt-by-ny array containing outputs at ts. 

% The following global variables need not be initialized.
global N_EVAL_F I_EVAL_Y

t = 0;
x = x0;

ts = t;
xs = x';
ys = []; % ys is filled only when dfun returns two outputs

% ioutput = flag that tells whether y is computed by dfun
ioutput = 0;
if nargout(dfun) == 2
    ioutput = 1;
end

dt2 = dt / 2;

tff = tf - 0.5*dt;

while t < tff
    
    % at each iteration, x(t+dt) and y(t) are computed

    % f(t,x) is computed for the 1st time (compute y when requested)
    N_EVAL_F = 1;
    if ( ioutput == 1 ) % when output is requested
        I_EVAL_Y = 1;
        [dx,y] = dfun(t,x); % this is for finding y at t=0
        ys = [ys; y']; 
    else
        dx = dfun(t,x);
    end
    f1 = dt * dx;
    
    I_EVAL_Y = 0;
    
    % f(t,x) is computed for the 2nd time
    N_EVAL_F = 2;
    f2 = dt * dfun(t+dt2,x+f1/2);
    
    % f(t,x) is computed for the 3rd time
    N_EVAL_F = 3;
    f3 = dt * dfun(t+dt2,x+f2/2);
    
    % f(t,x) is computed for the 4th time
    N_EVAL_F = 4;
    f4 = dt * dfun(t+dt,x+f3);

    x = x + (f1 + 2*f2 + 2*f3 + f4)/6;
    t = t + dt;
    
    ts = [ts; t];
    xs = [xs; x']; 
        
end

% find y at final time after simulation is completed
if ( ioutput == 1 )
    N_EVAL_F = 1;
    I_EVAL_Y = 1;
    [dx,y] = dfun(t,x); % this is for finding y at t+dt
    ys = [ys; y']; 
end
        
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8
