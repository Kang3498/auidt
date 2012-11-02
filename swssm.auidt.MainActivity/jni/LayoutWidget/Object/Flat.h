/*
created with obj2opengl.pl

source file    : .\flat.obj
vertices       : 8
faces          : 12
normals        : 24
texture coords : 24


// include generated arrays
#import ".\flat.h"

// set input data to arrays
glVertexPointer(3, GL_FLOAT, 0, flatVerts);
glNormalPointer(GL_FLOAT, 0, flatNormals);
glTexCoordPointer(2, GL_FLOAT, 0, flatTexCoords);

// draw data
glDrawArrays(GL_TRIANGLES, 0, flatNumVerts);
*/

unsigned int flatNumVerts = 36;

float flatVerts [] = {
  // f 1/9/1 2/10/2 4/11/3 3/12/4
  -0.5, -0.046024, 0.5,
  0.5, -0.046024, 0.5,
  0.5, 0.046024, 0.5,
  // f 1/9/1 2/10/2 4/11/3 3/12/4
  -0.5, -0.046024, 0.5,
  -0.5, 0.046024, 0.5,
  0.5, 0.046024, 0.5,
  // f 3/13/5 4/14/6 6/15/7 5/16/8
  -0.5, 0.046024, 0.5,
  0.5, 0.046024, 0.5,
  0.5, 0.046024, -0.5,
  // f 3/13/5 4/14/6 6/15/7 5/16/8
  -0.5, 0.046024, 0.5,
  -0.5, 0.046024, -0.5,
  0.5, 0.046024, -0.5,
  // f 5/17/9 6/18/10 8/19/11 7/20/12
  -0.5, 0.046024, -0.5,
  0.5, 0.046024, -0.5,
  0.5, -0.046024, -0.5,
  // f 5/17/9 6/18/10 8/19/11 7/20/12
  -0.5, 0.046024, -0.5,
  -0.5, -0.046024, -0.5,
  0.5, -0.046024, -0.5,
  // f 7/21/13 8/22/14 2/23/15 1/24/16
  -0.5, -0.046024, -0.5,
  0.5, -0.046024, -0.5,
  0.5, -0.046024, 0.5,
  // f 7/21/13 8/22/14 2/23/15 1/24/16
  -0.5, -0.046024, -0.5,
  -0.5, -0.046024, 0.5,
  0.5, -0.046024, 0.5,
  // f 2/2/17 8/7/18 6/5/19 4/3/20
  0.5, -0.046024, 0.5,
  0.5, -0.046024, -0.5,
  0.5, 0.046024, -0.5,
  // f 2/2/17 8/7/18 6/5/19 4/3/20
  0.5, -0.046024, 0.5,
  0.5, 0.046024, 0.5,
  0.5, 0.046024, -0.5,
  // f 7/8/21 1/1/22 3/4/23 5/6/24
  -0.5, -0.046024, -0.5,
  -0.5, -0.046024, 0.5,
  -0.5, 0.046024, 0.5,
  // f 7/8/21 1/1/22 3/4/23 5/6/24
  -0.5, -0.046024, -0.5,
  -0.5, 0.046024, -0.5,
  -0.5, 0.046024, 0.5,
};

float flatNormals [] = {
  // f 1/9/1 2/10/2 4/11/3 3/12/4
  0, 0, 1,
  0, 0, 1,
  0, 0, 1,
  // f 1/9/1 2/10/2 4/11/3 3/12/4
  0, 0, 1,
  0, 0, 1,
  0, 0, 1,
  // f 3/13/5 4/14/6 6/15/7 5/16/8
  0, 1, 0,
  0, 1, 0,
  0, 1, 0,
  // f 3/13/5 4/14/6 6/15/7 5/16/8
  0, 1, 0,
  0, 1, 0,
  0, 1, 0,
  // f 5/17/9 6/18/10 8/19/11 7/20/12
  0, 0, -1,
  0, 0, -1,
  0, 0, -1,
  // f 5/17/9 6/18/10 8/19/11 7/20/12
  0, 0, -1,
  0, 0, -1,
  0, 0, -1,
  // f 7/21/13 8/22/14 2/23/15 1/24/16
  0, -1, 0,
  0, -1, 0,
  0, -1, 0,
  // f 7/21/13 8/22/14 2/23/15 1/24/16
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

float flatTexCoords [] = {
  // f 1/9/1 2/10/2 4/11/3 3/12/4
  0.000000, 1,
  1.000000, 1,
  1.000000, 0,
  // f 1/9/1 2/10/2 4/11/3 3/12/4
  0.000000, 1,
  0.000000, 0,
  1.000000, 0,
  // f 3/13/5 4/14/6 6/15/7 5/16/8
  0.000000, 1,
  1.000000, 1,
  1.000000, 0,
  // f 3/13/5 4/14/6 6/15/7 5/16/8
  0.000000, 1,
  0.000000, 0,
  1.000000, 0,
  // f 5/17/9 6/18/10 8/19/11 7/20/12
  0.000000, 1,
  1.000000, 1,
  1.000000, 0,
  // f 5/17/9 6/18/10 8/19/11 7/20/12
  0.000000, 1,
  0.000000, 0,
  1.000000, 0,
  // f 7/21/13 8/22/14 2/23/15 1/24/16
  1.000000, 0,
  0.000000, 0,
  0.000000, 1,
  // f 7/21/13 8/22/14 2/23/15 1/24/16
  1.000000, 0,
  1.000000, 1,
  0.000000, 1,
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
