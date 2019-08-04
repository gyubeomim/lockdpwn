%Load and setup engine tables
%----------------------------
% Engine Table
load map_ford.dat;

N_div = 20;

we_max = max(map_ford(:,1));
we_min = min(map_ford(:,1));
we_table = linspace(we_min, we_max, N_div)';

alpha_max = max(map_ford(:,4));
alpha_min = min(map_ford(:,4));
alpha_table = linspace(alpha_min, alpha_max, N_div);

    % tnet_table(:,p) = torque output with same engine speed and changing throttle angle.
    % tnet_table(q,:) = torque output with same throttle angle and changing engine speed.
tnet_table = griddata(map_ford(:,1), map_ford(:,4), map_ford(:,2), we_table, alpha_table);

    % To replace the Nan data, extrapolate the 2nd, and 3rd column tnet_table data and
    %           estimate the first colummn

tnet_table(1,:) = (tnet_table(3,:)-tnet_table(2,:))./(alpha_table(3)-alpha_table(2))...
    .*(alpha_table(1)-alpha_table(2)) + tnet_table(2,:);

data = load('tc.dat');
throttle_table = data(:,1);
TC_table = data(:,2);

save enginemap;

%figure(1)
%mesh(we_table,alpha_table,tnet_table)
%title('engine map')
%xlabel('engine speed')
%ylabel('throttle angle')