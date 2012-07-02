Convection
==========


\defgroup GR_Convection Convection
\ingroup GR_JetDEau
The notion of convection consist to find in a eulerian grid the change of speed due of the motion
of the field.

It exist primary two different method to calculate this:
	- A upwind method that is a finite different sheme biased with respect the value of the speed.
	- A Semi Laggragien method where a particle is seed backward and the speed is given from the speed of where we arrive.


