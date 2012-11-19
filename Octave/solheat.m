function [u] = solheat(x,nmax,t,u0,L,nu)
	u=u0*(1.-x/L);
	for n=1:nmax
		if mod(n,2)==0
			u=u+4*u0/(n*pi)*(-(-1)^(n/2))*sin(n*pi*x/(2*L))*exp(-n^2*pi^2*nu*t/(4*L^2));
		end
	end
end