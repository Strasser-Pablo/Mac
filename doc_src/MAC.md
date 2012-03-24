MAC
===

Idea
----

The idea of this algorithm is to solve the Navier-Stockes equation in using a
staggered grid, but with marker particle used to calculate topology.

Navier-Stockes equation
-----------------------
\f{align}{
\nabla \cdot u(\xi,t)&=0 \\
\frac{\partial u(\xi,t)}{\partial t} +\left(u(\xi,t)\cdot \nabla \right) u(\xi,t)&=-\frac{\nabla p(\xi,t)}{\rho(\xi,t)}+\frac{F(\xi,t)}{\rho(\xi,t)}+\nu \Delta u(\xi,t)
\f}

Where:
	- \f$u\f$ is the eulerian speed.
	- \f$\xi\f$ is the eulerian position.
	- \f$p\f$ is the pressure.
	- \f$\rho\f$ is the mass density.
	- \f$\nu\f$ is the viscosity.
	- \f$F\f$ is the force.

The following variable need to be solved:
	- \f$u\f$
	- \f$p\f$

For a given Force \f$F\f$ a given boundary condition for \f$p\f$ and a given
initial condition for \f$u\f$.

The value of the function and the boundary condition are given by the topology
of the problem and depend of the velocity of the particle at time before.
The topology change is calculated at same time as the equation.

Topology
--------

The topology is given by the type of a cell that can be:
	- Watter.
	- Exterior Air.
	- Interior Air.

The difference between interior and exterior is if we are connected to
infinity.

Data Structure
--------------

The Data Structure consist of:
	- A list of Cell in a given mesh position:
	A Cell contain the following data.
		+ Speed.
		+ Pressure.
		+ CellType. 
	- A list of Particle.
	  A Particle consist of:
		+ A position.



Algorithm
---------

The algorithm is cut in different phase:
	1. Initialisation.
	2. Convection.
	3. Force Application.
	4. Correction of Pressure.
	5. Extrapolation.
	6. Move of Particle.
	7. Output.

Brief Description of phase:
	1. Initialisation:
	
	   The gooal of this stage is to create cell with given cell type and
	   property. It's in this stage that the topology is calculated.

	   Note that in this stage **new cell** velocity is **undefined**.
	2. Convection:
	
	   The convection step is done, to find the velocity in the new time
	   step. The convection step can be made by semi-lagrangien method or upwind
	   method.
	3. Force Application:

	   The velocity is changed to reflect the application of a force.
	4. Correction of Pressure

	   We are no more divergence because of the application of a force. We need to
	   correct the velocity. Let \f$v_{old}\f$ be the speed at this step.
	   The new speed \f$v_{new}\f$ is:
	   \f[v_{new}=v_{old}-\nabla \frac{p}{\rho} \f]
	   The constraint to be divergence free give:
	   \f[\nabla\cdot v_{old}=\Delta \frac{p}{\rho}\f]
	   We solve this linear equation in this step.
	5. Extrapolation.

	   We extrapolate the speed in the neighbouring air cell.
	   This step is currently done by averaging the velocity of neighbouring
	   cell in going layer by layer.
	6. Move of Particle.

	   We move the particle in the velocity field. The velocity field is defined by
	   interpolation from speed on the grid.

	   Actualy we use a RungeKutta algorithm for this step.
	7. Output.

	   We now output all information in a file.

	   The actual output method store the data in a vtk file type. That can be read
	   by Paraview.



