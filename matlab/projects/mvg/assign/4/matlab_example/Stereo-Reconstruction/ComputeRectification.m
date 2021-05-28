function [H1, H2] = ComputeRectification(K, R, C)

    rx = C / norm(C);
    
    rz_tilde = [0; 0; 1];
    rz = (rz_tilde - dot(rz_tilde, rx) .* rx)...
        / norm(rz_tilde - dot(rz_tilde, rx) .* rx);
    ry = cross(rz, rx);
    R_rect = [rx'; ry'; rz'];
    H1 = K * R_rect * inv(K);
    H2 = K * R_rect * R' * inv(K);
end