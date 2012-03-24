Interior Algorithm
==================

This algorithm calculate for for a mesh of cell with watter marked cell.
The air region that are interior.

The algorithm is cut in the following sub algorithm:
	- Find all interface surface between air and fluid.
	- Calculate witch surface are in another surface.
	- Fill all air cell in the interior of all maximal outer surface.
	- Create a layer.

Find Interface
--------------

To find all interface surface between air and fluid, we go by recursion.
We first search an interface that we will follow.

To represent the interface, we use a grid subdivide by 2. We will find the air 
pixel in this grid that touche the fluid.

We store the interface with two different object:
	- An object interval to be defined where we store for all interval it's position.
	- A set, where we color pixel when we pass by.

To find the first candidate we look at the neigbour of all fluid cell.
If the neighbour is air, it's a candidate.

To follow an interface we go by recursion. We use a stack with the first
candidate pixel as first point.

While the stack is not empty, we do the following:
	1. We pop the top of the stack.
	2. For each direction(dimension).
        	1. We test the cell in the half in the same direction.
		We have two case:
			- The cell is not fluid.
			We add a candidate in moving one cell in this
direction.	
          		- The celle if fluid.
			We make a lateral move in the same cell. In the
opposite sub cell.


Calculate witch surface is in another surface.
----------------------------------------------


For this part we will use the ordering property of the map and set container.
A map and a set have key always ordered.

We represent a surface in cutting in sub dimension.
Storing in a map with as key one component and as data a class with a
dimension less.

The other case is the one dimensional surface witch consist of 2 set.
One set of minimal and maximal value defining the interior and exterior of the
surface.

To compare 2 surface. We use the fact that we have only 3 non trivial case.

Let A and B be 2 surface. A is in B or B is in A or A is disjoint of B.
We can iterate in dimension in all non trivial one dimensional case (one of
the subset is empty) at the first we will have a solution.

The order of the key can be used to calculate very fast if a sub interval is
in another sub interval.

The cell connected with infinity are now given by the maximal outer set.

Fill Air cell.
--------------

We fill interior air cell using the set calculated before. We test all cell in
the intervall and if it's air cell. We set in interior air cell.

Create A Layer
--------------

To create a layer in the exterior. We set all cell in the boundary in the
maximal set to a layer of 1. And then we iterate in the layer i from 1 to n.
And set the non existing neigbour cell to layer i+1. 
