function I = im2array(J)
%J =m x n unit8 bw image file
S = size(J);
m = S(1);
n = S(2);
N = nnz(J); %number of nonzeros
I = zeros(N,3);

s=1;
for i=1:m
    for j=1:n
        if J(i,j)~=0
            I(s,:) = [j,i,1];
            s=s+1;
        else
        end
    end
end




    