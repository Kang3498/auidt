#include <vector>

class Object{
protected:
	std::vector<GLuint> textureData;
	std::vector<int> textureId;
	std::vector<int> texturePosition;

	float X,Y,Z;
	float rotateX,rotateY,rotateZ;
	float scaleX, scaleY, scaleZ;
	float alpha;

	int objectType;    // 0:Cube, 1:Flat, 2:Spiere, 3:Custom
	int objectId;
public:
	Object();
	int getObjectType();
	int getObjectId();
	void setObjectId(int id);
	void setPosition(float x,float y, float z);
	void setRotate(float rX,float rY, float rZ);
	void setScale(float sX, float sY, float sZ);
	void setAlpha(float alpha);
	void setDegree(float degree);
	void setTexture(int texturePOSITION, GLuint textureDATA);

	float* getPosition();
	float* getRotate();
	float* getScale();
	virtual void draw(); 
};
void Object::draw(){
	LOG("Draw Fail");
}
Object::Object(){

}

int Object::getObjectType(){
	return objectType; 
}
int Object::getObjectId(){
	return objectId;
}
void Object::setObjectId(int id){
	this->objectId = id;
}

float* Object::getPosition(){
	float* result = new float[3];
	result[0] = X;
	result[1] = Y;
	result[2] = Z;

	return result;
}

float* Object::getRotate(){
	float* result = new float[3];
	result[0] = rotateX;
	result[1] = rotateY;
	result[2] = rotateZ;

	return result;
}
float* Object::getScale(){
	float* result = new float[3];
	result[0] = scaleX;
	result[1] = scaleY;
	result[2] = scaleZ;

	return result;
}
void Object::setAlpha(float alpha){
	this->alpha = alpha;
}

void Object::setPosition(float x,float y, float z){
	this->X = x;
	this->Y = y;
	this->Z = z;
}

void Object::setRotate(float rX,float rY, float rZ){
	this->rotateX = rX;
	this->rotateY = rY;
	this->rotateZ = rZ;
}
void Object::setScale(float sX,float sY, float sZ){
	this->scaleX = sX;
	this->scaleY = sY;
	this->scaleZ = sZ;
}

void Object::setTexture(int texturePOSITION, GLuint textureDATA){

	texturePosition.push_back(texturePOSITION);
	textureData.push_back(textureDATA);
	
}