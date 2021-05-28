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
        
        x = 1:4032; 
        y = round((- a * x - c)/b);
        plot(x, y, 'color', color, 'LineWidth', 1.5);
        
%         epiLines = epipolarLine(F',x2);
%         %Compute the intersection points of the lines and the image border.
%         points = lineToBorderPoints(epiLines,[2268,4032]);
%         %Show the epipolar lines in the first image
%         line(points(:,[1,3])',points(:,[2,4])');
        
        
        figure(2);
        p2 = plot(x2(iIter, 1), x2(iIter, 2));
        set(p2, 'LineStyle', 'None', 'color', color,...
           'Marker', 'o', 'MarkerFaceColor', color);
        
        Lu = transpose(F * transpose([x1(iIter, :) 1]));
        a = Lu(:, 1); 
        b = Lu(:, 2); 
        c = Lu(:, 3);
                
        x = 1:4032; 
        y = round((- a * x - c)/b);
        plot(x, y, 'color', color, 'LineWidth', 1.5);
        
%         epiLines2 = epipolarLine(F,x1);
%         %Compute the intersection points of the lines and the image border.
%         points2 = lineToBorderPoints(epiLines2,[2268,4032]);
%         %Show the epipolar lines in the first image
%         line(points2(:,[1,3])',points2(:,[2,4])');
    end
end