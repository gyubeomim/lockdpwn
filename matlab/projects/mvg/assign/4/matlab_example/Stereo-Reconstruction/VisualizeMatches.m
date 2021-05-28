function VisualizeMatches(x1, x2, F)
    
    n = size(x1, 1);
    colors = ['r', 'g', 'b', 'c', 'y', 'm', 'k', 'w'];
    for iIter = 1:n
        color = colors(mod(iIter, 8)+1);
        figure(1);
        p1 = plot(x1(iIter, 1), x1(iIter, 2));
        set(p1, 'LineStyle', 'None', 'color', color,...
            'Marker', 'o', 'MarkerFaceColor', color);

        Lv = transpose(F' * transpose([x2(iIter, :) 1]));
        a = Lv(:, 1); 
        b = Lv(:, 2); 
        c = Lv(:, 3);
        
        x = 1:960; 
        y = round((- a * x - c)/b);
        plot(x, y, 'color', color, 'LineWidth', 1.5);
        
        
        figure(2);
        p2 = plot(x2(iIter, 1), x2(iIter, 2));
        set(p2, 'LineStyle', 'None', 'color', color,...
            'Marker', 'o', 'MarkerFaceColor', color);
        
        Lu = transpose(F * transpose([x1(iIter, :) 1]));
        a = Lu(:, 1); 
        b = Lu(:, 2); 
        c = Lu(:, 3);
                
        x = 1:960; 
        y = round((- a * x - c)/b);
        plot(x, y, 'color', color, 'LineWidth', 1.5);
    end
end