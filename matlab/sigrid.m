function[ ] = sigrid(sig)

%SIGRID  Generate s-plane grid lines for a root locus or pole-zero map.
%
%       SIGRID generates a grid over an existing continuous s-plane root 
%       locus or pole-zero map.  Lines of constant sigma are drawn in. 
%       To be used with SGRID if sigma, zeta, and Wn requirements are required
%       simultaneously.  Can also be used by itself.
%
%       See also: RLOCUS, ZGRID, SGRID, JGRID, and PZMAP.

error(nargchk(1,1,nargin));

hold on

%Plot sigma line
    limits = axis;
    mx=limits(1,4);
    mn=limits(1,3);
    stz=abs(mx)+abs(mn);
    st=stz/50;
    im=mn:st:mx;
    lim=length(im);
    for i=1:lim
        re(i)=-sig;
    end  
    re(:);
    plot(re,im,'.')

hold off

return