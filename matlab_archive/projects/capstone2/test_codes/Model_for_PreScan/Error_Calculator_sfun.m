function Error_Calculator_sfun(block)
setup(block);
end

function setup( block )

block.NumInputPorts  = 4;
block.NumOutputPorts = 2;

Input_Dim  = [ 1  2  3  4;...
               5  1  1  1];
Output_Dim = [ 1  2;...
               1  1];

block.SetPreCompInpPortInfoToDynamic;
block.SetPreCompOutPortInfoToDynamic;

for i = Input_Dim;
    block.InputPort(i(1)).Complexity = 'Inherited';
    block.InputPort(i(1)).DataTypeId = 0;
    block.InputPort(i(1)).SamplingMode = 'Sample';
    block.InputPort(i(1)).Dimensions = i(2);
end

for k = Output_Dim;
    block.OutputPort(k(1)).Complexity = 'Inherited';
    block.OutputPort(k(1)).DataTypeId = 0;
    block.OutputPort(k(1)).SamplingMode = 'Sample';
    block.OutputPort(k(1)).Dimensions = k(2);
end

block.AllowSignalsWithMoreThan2D = true;
block.RegBlockMethod('Outputs', @Outputs);

block.SetAccelRunOnTLC(true);
end


function Outputs(block)
A   = block.InputPort(1).Data;
Xcg = block.InputPort(2).Data;
Ycg = block.InputPort(3).Data;
psi = block.InputPort(4).Data;

psi = psi + 6*pi;
psi = mod(psi,2*pi);

Dead_angle = 5;

A_temp = A;

if psi < Dead_angle*pi/180 || psi > (360-Dead_angle)*pi/180
    
    Y_int = A(1)*Xcg.^4+ A(2)*Xcg.^3 + A(3)*Xcg.^2 +A(4)*Xcg + A(5);
    X_int = (Y_int-Ycg)/(-1/tan(psi)) + Xcg;
    
    Y_cond = Y_int;
    
    Offset_Lat = sqrt((Xcg-X_int)^2+(Ycg-Y_int)^2);
    
    
else
    A(end-1) = A(end-1) + 1/tan(psi);
    A(end) = A(end) - (Xcg/tan(psi) + Ycg);

    path_func = @(x) A(1)*x.^4+ A(2)*x.^3 + A(3)*x.^2 +A(4)*x + A(5);

    X_int = fzero(path_func,Xcg);
    Y_int = (-1/tan(psi))*(X_int-Xcg)+Ycg;

    Offset_Lat = sqrt((Xcg-X_int)^2+(Ycg-Y_int)^2);

    Y_cond = tan(psi)*(X_int-Xcg)+Ycg;
    
end

if     psi > (360-Dead_angle)*pi/180 && Y_cond < Ycg,   Offset_Lat = -Offset_Lat;
elseif psi > (360-Dead_angle)*pi/180 && Y_cond > Ycg,   Offset_Lat =  Offset_Lat;
elseif psi < Dead_angle*pi/180 && Y_cond > Ycg,         Offset_Lat =  Offset_Lat;
elseif psi < Dead_angle*pi/180 && Y_cond < Ycg,         Offset_Lat =  -Offset_Lat;
elseif (psi > 3/2*pi  || psi < pi/2)   && Y_cond > Ycg, Offset_Lat = -Offset_Lat;
elseif (psi > 3/2*pi  || psi < pi/2)   && Y_cond < Ycg, Offset_Lat = Offset_Lat;
elseif (psi > pi/2    && psi < 3/2*pi) && Y_cond > Ycg, Offset_Lat = Offset_Lat;
elseif (psi > pi/2    && psi < 3/2*pi) && Y_cond < Ycg, Offset_Lat = -Offset_Lat;
elseif psi == pi/2   && X_int > X_cg,                   Offset_Lat = -Offset_Lat;
elseif psi == pi/2   && X_int < X_cg,                   Offset_Lat =  Offset_Lat;
elseif psi == 3/2*pi && X_int > X_cg,                   Offset_Lat =  Offset_Lat;
elseif psi == 3/2*pi && X_int < X_cg,                   Offset_Lat = -Offset_Lat;
end

Slop = 4*A_temp(1)*X_int^3+ 3*A_temp(2)*X_int^2 + 2*A_temp(3)*X_int +A_temp(4);

Path_angle = atan(Slop);

Path_angle = Path_angle + 6*pi;
Path_angle = mod(Path_angle,2*pi);

Angular_Error = Path_angle-psi;

Angular_Error = Angular_Error + 6*pi;
Angular_Error = mod(Angular_Error,2*pi);

if Angular_Error > pi
    Angular_Error = Angular_Error - 2*pi;
end

block.OutputPort(1).Data = Offset_Lat;
block.OutputPort(2).Data = Angular_Error;
end

