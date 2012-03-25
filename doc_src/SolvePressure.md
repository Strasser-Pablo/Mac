Solve Pressure
==============

\defgroup GR_Solve_Pressure Solve Pressure
\ingroup GR_JetDEau

Because we need to have a incompressible a final speed. We can choose the pressure to correct the speed.
We need to have a new speed:
\f[v_{new}=v_{old}-\frac{\nabla p}{\rho}\f]
\f[v_{old}=\nabla \cdot \frac{\nabla p}{\rho}\f]

We need to solve this linear equation with given boundary condition.
