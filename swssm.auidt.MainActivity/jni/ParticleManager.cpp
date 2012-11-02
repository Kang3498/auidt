#include <jni.h>
#include <math.h>

#define TOTAL_PARTICLE 300

class ParticleManager{
private:
	
	GLuint texture;
	int screenW, screenH;
	int X,Y, Flag;
	int count;

	Particle *particle[TOTAL_PARTICLE];


public:
	ParticleManager(int screenW, int screenH);
	void setTexture(GLuint t);
	void getXY(int x, int y, int flag);
	void update();
	void draw();
	void particleLifeCheck();
};


ParticleManager::ParticleManager(int screenW,int screenH){
	this->screenW = screenW;
	this->screenH = screenH;
	count=0;

}

void ParticleManager::setTexture(GLuint t){
	this->texture = t;
	for (int i=0 ; i < TOTAL_PARTICLE ; i++){
		particle[i] = new Particle(t);
	}
}

void ParticleManager::getXY(int x, int y, int flag){
	this->X = x;
	this->Y = y;
	this->Flag = flag;
	
	//if(flag == 2){ // ¹«ºê
		particle[count]->setXY(((float)X) / screenW * 6.0f - 3.0f, 4.0f - ((float)Y) / screenH * 8.0f);
	

	count++;
	if(count == TOTAL_PARTICLE)
		count = 0;
}

void ParticleManager::update(){

	this->draw();
}
void ParticleManager::particleLifeCheck(){

}
void ParticleManager::draw(){

	glViewport(0, 0, screenW, screenH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustumf(-1.0f, 1.0f, -1.5f, 1.5f, 1.0f, 20.0f);      

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	for (int i=0 ; i < TOTAL_PARTICLE ; i++){

		particle[i]->update();

	}

}