function [u] = solheat(x,nmax,t,u0,L,nu)
	u=u0.*(1.-x/L);
	for n=1:nmax
		if mod(n,2)==0
			u=u-1/L*(3*u0*2*L/(n*pi)*(-1)^(n/2)+(-1)^(n/2+1)*(2*L)/(n*pi)*(u0/L))*sin(n*pi*x/(2*L))*exp(-n^2*pi^2*nu*t/(4*L));
		end
	end
end