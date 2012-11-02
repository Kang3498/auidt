#include <vector>
#include <stdlib.h>
#include <GLES/gl.h>
#include <GLES/glext.h>


#include <jni.h>

#include "JavaCallManager.cpp"
#include "TouchManager.cpp"
#include "TextureManager.cpp"
#include "Particle.cpp"
#include "ParticleManager.cpp"
#include "LayoutWidget/LayoutWidget.h"


#define FLAG_LAYOUT_ROTATION 0
#define FLAG_LAYOUT_DOCK 1
#define FLAG_LAYOUT_DIAL 2
#define FLAG_LAYOUT_ROLL 3

#define FLAG_OBJECT_CUBE 0
#define FLAG_OBJECT_FLAT 1
#define FLAG_OBJECT_CIRCLE 2
#define FLAG_OBJECT_CUSTOM 3
