HELLO
MICHAEL WROTE THIS

this is a brief overview of what the cell function does and how it does it.

the cell class describes the shape essentially and aims to find the shapes volume, weight and centre of gravity.

to find the volume, it uses functions from the cell class to subtract vectors, and achieve dot product and cross
product calculations, crucial for finding the volume of the tetrahedron.

to simplify the find volume functions and to make it more robust,  the same method to find the volume of a tetrahedron
is used to find the volume of a pyramid and a hexahedron, since those shapes can be divided into tetrahedrons
(a pyramid can be divided into 2 tetrahedrons, and a hexahedron can be divided into 6 tetrahedrons).

the find weight functions are more simplistic, just using the equation, weight = g*volume*density
finding volume from the getvolume functions, and density can be found from the material class.

Finding the centre of gravity is done by finding the midpoint of all the vertices of the cell, since its density is 
uniform, so it should be accurate