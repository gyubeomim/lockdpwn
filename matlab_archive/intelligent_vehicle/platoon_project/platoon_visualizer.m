%{
    matlab ==> 지능형자동차, 군집주행 프로젝트에서 차량의 움직임을 시각화하는 코드
%}

%% Cut In Vehicle Senario
figure('rend','painters','pos',[100 500 1400 200])

anim0 = plot(x_lead(1),y,'sk','LineWidth',2,'MarkerSize',6,'MarkerFaceColor','k'); 
anim1 = plot(x1(1),y,'sk','LineWidth',2,'MarkerSize',6,'MarkerFaceColor','b');
anim2 = plot(x2(1),y,'sk','LineWidth',2,'MarkerSize',6,'MarkerFaceColor','g');
animcut = plot(x_cut(1),y,'sr','LineWidth',2,'MarkerSize', 6,'MarkerFaceColor','r');
anim3 = plot(x3(1),y,'sk','LineWidth',2,'MarkerSize', 6,'MarkerFaceColor','c');
anim4 = plot(x4(1),y,'sk','LineWidth',2,'MarkerSize', 6,'MarkerFaceColor','m');

hold on;
axis([0 500 0 2]);
legend('Lead','1st','2nd','Cut In','3rd','4th');
title('Platoon Cut In Senario', 'FontSize', 20);
xlabel('Distance [m]', 'FontSize', 15);
grid on;
xlim manual

delete(anim0)
delete(anim1);
delete(anim2);
delete(animcut);
delete(anim3);
delete(anim4);


for j = 2:1000
  
    % 루프를 돌면서 x,y 값을 받고
    s0 = x_lead(10*j);
    s1 = x1(10*j);
    s2 = x2(10*j);
    scut = x_cut(10*j);
    s3 = x3(10*j);
    s4 = x4(10*j);
    
    y=1;
    
    % 실시간 군집주행 애니메이션을 표현합니다
    anim0 = plot(s0,y,'sk','LineWidth',2,'MarkerSize',6,'MarkerFaceColor','k'); 
    anim1 = plot(s1,y,'sk','LineWidth',2,'MarkerSize',6,'MarkerFaceColor','k');
    anim2 = plot(s2,y,'sk','LineWidth',2,'MarkerSize',6,'MarkerFaceColor','k');
    animcut = plot(scut,y,'sr','LineWidth',2,'MarkerSize',6,'MarkerFaceColor','r');
    anim3 = plot(s3,y,'sk','LineWidth',2,'MarkerSize',6,'MarkerFaceColor','k');
    anim4 = plot(s4,y,'sk','LineWidth',2,'MarkerSize',6,'MarkerFaceColor','k');
    legend('Lead','1st','2nd','Cut In','3rd','4th');
    M(j) = getframe;
    set(gca,'XTick',[0 : 40 : 1200]);
    
    delete(anim0);
    delete(anim1);
    delete(anim2);
    delete(animcut);
    delete(anim3);
    delete(anim4);
end

%% 중간에 1st Vehicle이 이탈하는 시나리오
figure('rend','painters','pos',[100 500 1400 200])

anim0 = plot(x_lead(1),y,'sk','LineWidth',2,'MarkerSize',6,'MarkerFaceColor','k');
anim2 = plot(x2(1),y,'sr','LineWidth',2,'MarkerSize',6,'MarkerFaceColor','r');
anim3 = plot(x3(1),y,'sr','LineWidth',2,'MarkerSize', 6,'MarkerFaceColor','r');
anim4 = plot(x4(1),y,'sr','LineWidth',2,'MarkerSize', 6,'MarkerFaceColor','r');

hold on;
axis([0 800 0 2]);
legend('Lead','2nd','3rd','4th');
title('Platoon 1st Vehicle Eject Senario', 'FontSize', 20);
xlabel('Distance [m]', 'FontSize', 15);
grid on;

delete(anim0)
delete(anim2);
delete(anim3);
delete(anim4);


for j = 2:1000
  
    % 루프를 돌면서 x,y 값을 받고
    s0 = x_lead(20*j);
    s2 = x2(20*j);
    s3 = x3(20*j);
    s4 = x4(20*j);
    
    y=1;
    
    % 실시간 군집주행 애니메이션을 표현합니다
    anim0 = plot(s0,y,'sk','LineWidth',2,'MarkerSize',6,'MarkerFaceColor','k'); 
    anim2 = plot(s2,y,'sr','LineWidth',2,'MarkerSize',6,'MarkerFaceColor','r');
    anim3 = plot(s3,y,'sr','LineWidth',2,'MarkerSize',6,'MarkerFaceColor','r');
    anim4 = plot(s4,y,'sr','LineWidth',2,'MarkerSize',6,'MarkerFaceColor','r');
    legend('Lead','2nd','3rd','4th');
    set(gca,'XTick',[0 : 40 : 1200]);
    M(j) = getframe;
    
    delete(anim0);
    delete(anim2);
    delete(anim3);
    delete(anim4);
end

%% 기본적인 증속, 감속 시나리오
figure('rend','painters','pos',[100 500 1400 200])

anim0 = plot(x_lead(1),y,'sk','LineWidth',2,'MarkerSize',6,'MarkerFaceColor','k');
anim1 = plot(x1(1),y,'sr','LineWidth',2,'MarkerSize',6,'MarkerFaceColor','r');
anim2 = plot(x2(1),y,'sr','LineWidth',2,'MarkerSize',6,'MarkerFaceColor','r');
anim3 = plot(x3(1),y,'sr','LineWidth',2,'MarkerSize', 6,'MarkerFaceColor','r');
anim4 = plot(x4(1),y,'sr','LineWidth',2,'MarkerSize', 6,'MarkerFaceColor','r');

hold on;
axis([0 600 0 2]);
legend('Lead','1st','2nd','3rd','4th');
title('Platoon Normal Senario', 'FontSize', 20);
xlabel('Distance [m]', 'FontSize', 15);
grid on;

delete(anim0);
delete(anim1);
delete(anim2);
delete(anim3);
delete(anim4);


for j = 2:1000
  
    % 루프를 돌면서 x,y 값을 받고
    s0 = x_lead(10*j);
    s1 = x1(10*j);
    s2 = x2(10*j);
    s3 = x3(10*j);
    s4 = x4(10*j);
    
    y=1;
    
    % 실시간 군집주행 애니메이션을 표현합니다
    anim0 = plot(s0,y,'sk','LineWidth',2,'MarkerSize',6,'MarkerFaceColor','k'); 
    anim1 = plot(s1,y,'sr','LineWidth',2,'MarkerSize',6,'MarkerFaceColor','r');
    anim2 = plot(s2,y,'sr','LineWidth',2,'MarkerSize',6,'MarkerFaceColor','r');
    anim3 = plot(s3,y,'sr','LineWidth',2,'MarkerSize',6,'MarkerFaceColor','r');
    anim4 = plot(s4,y,'sr','LineWidth',2,'MarkerSize',6,'MarkerFaceColor','r');
    legend('Lead','2nd','3rd','4th');
    set(gca,'XTick',[0 : 40 : 1200]);
    M(j) = getframe;
    
    delete(anim0);
    delete(anim1);
    delete(anim2);
    delete(anim3);
    delete(anim4);
end

