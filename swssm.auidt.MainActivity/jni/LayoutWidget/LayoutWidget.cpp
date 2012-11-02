
class LayoutWidget{
protected:
	int layoutType;
	int layoutID;
	int layoutIDcount;

	int objectLen;

	int x,y;
	float Aspect_Ratio;
	float ratio;
	float LayoutW, LayoutH;
	float ScreenW, ScreenH; 
	TouchManager* touchManager;
	
	std::vector<Object*> objectData;

public:
	JavaCallManager* javaCallManager;
	LayoutWidget();
	int getlayoutType();
	void setLayoutID(int layoutId);
	int getlayoutID();
	void init(int x, int y, float LayoutW, float LayoutH, float ratio );
	void setJavaCallManager(JavaCallManager* javaCallManager);
	void drawLayoutLine();
	void addObejct(Object* obj);
	void deleteObject(int pos);
	void getXY(int x, int y, int flag);

	virtual void update();
};

LayoutWidget::LayoutWidget(){
	Aspect_Ratio = 1.5f;

}

void LayoutWidget::update(){

}

int LayoutWidget::getlayoutType(){
	return layoutType;
}

void LayoutWidget::setLayoutID(int layoutId){
	this->layoutID = layoutId;
}
int LayoutWidget::getlayoutID(){
	return layoutID;
}


void LayoutWidget::init(int x, int y, float ScreenW, float ScreenH, float ratio ){
	layoutIDcount = 0;
	this->x = x;
	this->y = y;
	this->ScreenW = ScreenW;
	this->ScreenH = ScreenH;
	 
	this->LayoutW = ScreenW * ratio;
	this->LayoutH = ScreenW * Aspect_Ratio * ratio;

	touchManager = new TouchManager(ScreenW, ScreenH ,x, y, LayoutW, LayoutH);
	touchManager->setTartgetLayout(layoutType);
}
void LayoutWidget::setJavaCallManager(JavaCallManager* _javaCallManager){
	
	this->javaCallManager = _javaCallManager;
}

void LayoutWidget::drawLayoutLine(){

	glPushMatrix();
	{
		//화면의 사이즈를 구성
	

		unsigned int cubeNumVerts =2;




		float x1 = 1;
		float y1 = 1; 
		float z1 = -4.99;

		float x = 1;
		float y = y1 * Aspect_Ratio; 
		float z = -1.01;

		float cubeVerts [] = {
			-x, -y, z,
			-x,  y, z,
			x,  y, z,
			x, -y, z,
			-x, -y, z,

			-x1, -y1, z1,
			-x1,  y1, z1,
			x1,  y1, z1,
			x1, -y1, z1,
			-x1, -y1, z1,

		};


		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

		glVertexPointer(3, GL_FLOAT, sizeof(GLfloat)*3, cubeVerts);

		glFrontFace(GL_CW);

		glEnableClientState(GL_VERTEX_ARRAY);

		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		glDrawArrays(GL_LINES, 0, 2);

		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
		glDrawArrays(GL_LINES, 1, 2);

		glColor4f(1.0f,1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_LINES, 2, 2);

		glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
		glDrawArrays(GL_LINES, 3, 2);

		
		//glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
		
		glDisableClientState(GL_VERTEX_ARRAY);

	}
	glPopMatrix();
}


void LayoutWidget::addObejct(Object* obj){

	obj->setObjectId(layoutIDcount);;
	objectData.push_back(obj);
	layoutIDcount++;
	
	objectLen = objectData.size();
	
}
void LayoutWidget::deleteObject(int pos){
	LOG("ObjectDelete pos : %d ", pos);
	std::vector<Object*>::iterator it = objectData.begin();
	it+= pos;

	//delete (*it);

	objectData.erase( objectData.begin() + pos);
}
void LayoutWidget::getXY(int x, int y, int flag){

	touchManager->getXY(x, y, flag);
}

