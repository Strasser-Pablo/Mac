Upwind
======

A upwind method is a finite difference method that is biased depending on the speed of a cell.

For example for the 1d convection equation given by:
\f[\frac{\partial U}{\partial t}+ U\frac{\partial U}{\partial x}=0\f]

The first order upwind method is given by:
\f{equation}{\frac{\partial U}{\partial t}+ U\frac{\partial U}{\partial x}=\begin{cases} \frac{U^{n+1}_{i}-U^{n}_{i}}{\Delta
t}+U_{i}^{n}\frac{U_{i}^{n}-U_{i-1}^{n}}{\Delta x}&
\text{If $U_{i}^{n}>0$}\\
\frac{U^{n+1}_{i}-U^{n}_{i}}{\Delta
t}+U_{i}^{n}\frac{U^{n}_{i+1}-U^{n}_{i}}{\Delta x}&
\text{If $U_{i}^{n}>0$}
\end{cases}\f}

The motivation of this two different sheme depeding on the speed. Is that we
want to approximate the move of the particle. With this choice we corretly
take the speed were the fluid come from.
