Mac
===

Compile
_______

Create a build directory:

	mkdir build
	cd build

Create build system with cmake:

	cmake ..

Make:

	make

To launch test suit.

	make test

Experiment binary have normaly Jet or Lateral_Jet in their name.
Note that experiment launch an infinit loop.


Structure
_________

All the framework is in directory src.
All the test and experiment are in directory test.
The experiment are infinit loop so need to be stopped.
Output file can be opened with paraview.

Dependency
__________

The code has the following dependency:

- VTK, used for output.
- Umfpack, as linear solver.
- Boost-Python, and python.
- Pyamg, as multigrid solver.

The library linking can be changed in cmake configuration.

