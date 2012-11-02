#include <jni.h>
#include <math.h>

class Particle
{
public:
	GLuint texture;
	bool alive;
	float X, Y;
	float WIDTH, HEIGHT , termX,termY;
	int power,frame;
public:
	Particle(GLuint t);
	void reset();

	void setXY(float x, float y);
	void update();
	void draw();
};

Particle::Particle(GLuint t){
	this->texture = t;
	alive = false;
	X = 0.0f;
	Y = 0.0f;
	frame = 0;
	WIDTH = 0.5f;
	HEIGHT = 0.5f;
	termX = 0.01f;
	termY = 0.01f;
}
void Particle::reset(){

	alive = false;
	X = 0.0f;
	Y = 0.0f;
	frame = 0;
	WIDTH  =0.5f;
	HEIGHT = (rand() % 4000) / 10000.0f + 0.3f;
	termX = WIDTH / 50.0f;
	termY = HEIGHT / 50.0f;
	
}
void Particle::setXY(float x, float y){
	this->reset();
	this->X = x;
	this->Y = y;
	alive = true;
}
void Particle::update(){
	
	
	frame++;
	if(frame == 50){
		this->reset();
	}

	if(alive)
		this->draw();
}
void Particle::draw(){


	float x = WIDTH - termX * frame;
	float y = WIDTH - termX * frame ;
	float z = -1.01f;

	float Verts [] = {
		-x, -y, z,
		0, 0,
		-x,  y, z,
		0, 1,
		x,  y, z,
		1, 1,

		-x, -y, z,
		0, 0,
		x,  y, z,
		1, 1,
		x, -y, z,
		1, 0,
	};




	glPushMatrix();
	{
		//화면의 사이즈를 구성

		glVertexPointer(3, GL_FLOAT, sizeof(GLfloat)*5, Verts);
		glTexCoordPointer(2,GL_FLOAT,sizeof(GLfloat)*5,&Verts[0]+3);

		glEnableClientState(GL_VERTEX_ARRAY);

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		{

			glEnable(GL_BLEND );
			glDisable(GL_DEPTH_TEST);
			glBlendFunc( GL_SRC_ALPHA  , GL_ONE_MINUS_SRC_ALPHA + 1.00f );
			glFrontFace(GL_CW);


			glTranslatef(X, Y ,-2.0f);

			glBindTexture(GL_TEXTURE_2D, texture);		
			glDrawArrays(GL_TRIANGLES, 0, 6);			
			glDisable(GL_BLEND );
			glEnable(GL_DEPTH_TEST);
		}
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

	}
	glPopMatrix();
}
