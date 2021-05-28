function [R,C,X] = DisambiguatePose(R1,C1,X1,R2,C2,X2,R3,C3,X3,R4,C4,X4)
    RMatrix = {R1 R2 R3 R4};
    CMatrix = {C1 C2 C3 C4};
    XMatrix = {X1 X2 X3 X4};
    nValids = zeros(4, 1);

    for iIter = 1:4
        R = RMatrix{iIter};
        X = XMatrix{iIter};
        C = CMatrix{iIter};
        nValids(iIter) = sum(R(3, :) * (X - C')' > 0 & X(:, 3)' > 0);
    end
    
    [~, maxIdx] = max(nValids);
    R = RMatrix{maxIdx};
    C = CMatrix{maxIdx};
    X = XMatrix{maxIdx};
end