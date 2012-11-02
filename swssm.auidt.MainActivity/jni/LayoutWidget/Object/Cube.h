/*
created with obj2opengl.pl

source file    : .\Cube.obj
vertices       : 8
faces          : 12
normals        : 24
texture coords : 24


// include generated arrays
#import ".\Cube.h"

// set input data to arrays
glVertexPointer(3, GL_FLOAT, 0, CubeVerts);
glNormalPointer(GL_FLOAT, 0, CubeNormals);
glTexCoordPointer(2, GL_FLOAT, 0, CubeTexCoords);

// draw data
glDrawArrays(GL_TRIANGLES, 0, CubeNumVerts);
*/

unsigned int CubeNumVerts = 36;

float CubeVerts [] = {
	// f 1/15/1 2/23/2 4/18/3 3/17/4
	-0.5, -0.5, 0.5,
	0.5, -0.5, 0.5,
	0.5, 0.5, 0.5,
	// f 1/15/1 2/23/2 4/18/3 3/17/4
	-0.5, -0.5, 0.5,
	-0.5, 0.5, 0.5,
	0.5, 0.5, 0.5,
	// f 3/9/5 4/10/6 6/19/7 5/20/8
	-0.5, 0.5, 0.5,
	0.5, 0.5, 0.5,
	0.5, 0.5, -0.5,
	// f 3/9/5 4/10/6 6/19/7 5/20/8
	-0.5, 0.5, 0.5,
	-0.5, 0.5, -0.5,
	0.5, 0.5, -0.5,
	// f 5/11/9 6/12/10 8/14/11 7/22/12
	-0.5, 0.5, -0.5,
	0.5, 0.5, -0.5,
	0.5, -0.5, -0.5,
	// f 5/11/9 6/12/10 8/14/11 7/22/12
	-0.5, 0.5, -0.5,
	-0.5, -0.5, -0.5,
	0.5, -0.5, -0.5,
	// f 7/13/13 8/21/14 2/16/15 1/24/16
	-0.5, -0.5, -0.5,
	0.5, -0.5, -0.5,
	0.5, -0.5, 0.5,
	// f 7/13/13 8/21/14 2/16/15 1/24/16
	-0.5, -0.5, -0.5,
	-0.5, -0.5, 0.5,
	0.5, -0.5, 0.5,
	// f 2/2/17 8/7/18 6/5/19 4/3/20
	0.5, -0.5, 0.5,
	0.5, -0.5, -0.5,
	0.5, 0.5, -0.5,
	// f 2/2/17 8/7/18 6/5/19 4/3/20
	0.5, -0.5, 0.5,
	0.5, 0.5, 0.5,
	0.5, 0.5, -0.5,
	// f 7/8/21 1/1/22 3/4/23 5/6/24
	-0.5, -0.5, -0.5,
	-0.5, -0.5, 0.5,
	-0.5, 0.5, 0.5,
	// f 7/8/21 1/1/22 3/4/23 5/6/24
	-0.5, -0.5, -0.5,
	-0.5, 0.5, -0.5,
	-0.5, 0.5, 0.5,
};

float CubeNormals [] = {
	// f 1/15/1 2/23/2 4/18/3 3/17/4
	0, 0, 1,
	0, 0, 1,
	0, 0, 1,
	// f 1/15/1 2/23/2 4/18/3 3/17/4
	0, 0, 1,
	0, 0, 1,
	0, 0, 1,
	// f 3/9/5 4/10/6 6/19/7 5/20/8
	0, 1, 0,
	0, 1, 0,
	0, 1, 0,
	// f 3/9/5 4/10/6 6/19/7 5/20/8
	0, 1, 0,
	0, 1, 0,
	0, 1, 0,
	// f 5/11/9 6/12/10 8/14/11 7/22/12
	0, 0, -1,
	0, 0, -1,
	0, 0, -1,
	// f 5/11/9 6/12/10 8/14/11 7/22/12
	0, 0, -1,
	0, 0, -1,
	0, 0, -1,
	// f 7/13/13 8/21/14 2/16/15 1/24/16
	0, -1, 0,
	0, -1, 0,
	0, -1, 0,
	// f 7/13/13 8/21/14 2/16/15 1/24/16
	0, -1, 0,
	0, -1, 0,
	0, -1, 0,
	// f 2/2/17 8/7/18 6/5/19 4/3/20
	1, 0, 0,
	1, 0, 0,
	1, 0, 0,
	// f 2/2/17 8/7/18 6/5/19 4/3/20
	1, 0, 0,
	1, 0, 0,
	1, 0, 0,
	// f 7/8/21 1/1/22 3/4/23 5/6/24
	-1, 0, 0,
	-1, 0, 0,
	-1, 0, 0,
	// f 7/8/21 1/1/22 3/4/23 5/6/24
	-1, 0, 0,
	-1, 0, 0,
	-1, 0, 0,
};

float CubeTexCoords [] = {
	// f 1/15/1 2/23/2 4/18/3 3/17/4
	0.000000, 1,
	1.000000, 1,
	1.000000, 0,
	// f 1/15/1 2/23/2 4/18/3 3/17/4
	0.000000, 1,
	0.000000, 0,
	1.000000, 0,
	// f 3/9/5 4/10/6 6/19/7 5/20/8
	0.000000, 1,
	1.000000, 1,
	1.000000, 0,
	// f 3/9/5 4/10/6 6/19/7 5/20/8
	0.000000, 1,
	0.000000, 0,
	1.000000, 0,
	// f 5/11/9 6/12/10 8/14/11 7/22/12
	1.000000, 0,
	0.000000, 0,
	-0.000000, 1,
	// f 5/11/9 6/12/10 8/14/11 7/22/12
	1.000000, 0,
	1.000000, 1,
	-0.000000, 1,
	// f 7/13/13 8/21/14 2/16/15 1/24/16
	0.000000, 1,
	0.000000, 0,
	1.000000, 0,
	// f 7/13/13 8/21/14 2/16/15 1/24/16
	0.000000, 1,
	1.000000, 1,
	1.000000, 0,
	// f 2/2/17 8/7/18 6/5/19 4/3/20
	0.000000, 1,
	1.000000, 1,
	1.000000, 0,
	// f 2/2/17 8/7/18 6/5/19 4/3/20
	0.000000, 1,
	0.000000, 0,
	1.000000, 0,
	// f 7/8/21 1/1/22 3/4/23 5/6/24
	0.000000, 1,
	1.000000, 1,
	1.000000, 0,
	// f 7/8/21 1/1/22 3/4/23 5/6/24
	0.000000, 1,
	0.000000, 0,
	1.000000, 0,
};

