function R = isolateRed(I, delta)

m = size(I,1);
n = size(I,2);
J = imsubtract(I(:,:,1), rgb2gray(I));
M = max(max(J));
R = zeros(m,n);
count = 1;
for i=1:m
   % M = max(J(i,:));
    for j=1:n
        if J(i,j) > delta 
            R(i,j) = J(i,j);
            count = count+1;
        end
    end
end

         
            

end
