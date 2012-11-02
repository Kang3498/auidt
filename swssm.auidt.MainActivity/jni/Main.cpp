#include "Main.h"

class Main{
private:
	//========== ���� �ʿ��� �� =========
	JavaCallManager *javaCallManager;
	TextureManager *textureManager;
	ParticleManager *particleManager;
	//====================================

	//=========== �⺻ ���� ===============
	GLfloat screenW, screenH;
	int layoutOrder0;                 // ���̾ƿ� ������� ��ȣ ����
	int layoutOrder1;   
	int layoutOrder2;   
	int layoutOrder3;   
	//====================================

	//=========== 3D ������ ==============
	RotationLayout* rotationLayout1;
	std::vector<LayoutWidget*> layoutWidget;
	std::vector<Object*> object;
	//====================================


	//=========== TEMP ===================
	int temp;
	bool isFirstDraw;
	//====================================
public:
	Main();
	~Main();
	//=========== jni-ndk ��ſ� =========
	void onSurfaceCreate();
	void onSurfaceChanged(int width, int height);
	void updateLoop();
	void onTouchEvent(int x, int y, int flag);	
	void eventListener();
	void setTextureData(int id, char *data, int width, int height);
	void setSystemTextureData(int id, int textureId);
	void customobjectLoad(int *textureID, int size, float *verts, float *normals, float *coords);
	//===================================

	//=========== ���� ���� =============
	void layoutLoad(int flag, int x, int y, float ratio, int size);
	void objectLoad(int flag, int *textureID);
	void layoutDelete(int pos);
	void objectDelete(int layoutPos, int pos);

	void widgetLoad();            // �����ҷ�����
	//==================================

	//=========== openGL �۵��� =========         
	void initialize();            // GL�ʱ�ȭ
	void screenChanged();         // ��ũ������
	void update();                  // ȭ�鰻��
	void reset();
	void draw_Background();
	//==================================

	//=========== Java Call ���� ========
	void Javacall_Initialize(JNIEnv* env, jobject obj, jclass cls);
	//===================================

};



#pragma region jni-ndk ��ſ� �Լ�
//=========== jni-ndk ��ſ� ==============================================================
Main::Main(){
	temp=0;
	layoutOrder0 = 0;
	layoutOrder1 = 0;
	layoutOrder2 = 0;
	layoutOrder3 = 0;
	isFirstDraw=false;
	this->onSurfaceCreate();
}
Main::~Main(){
	free(javaCallManager);
	free(textureManager);
	free(particleManager);
	free(rotationLayout1);
}


void Main::reset(){
	LOG("reset");
	temp=0;          // temp ó��
	layoutOrder0 = 0;
	layoutOrder1 = 0;
	layoutOrder2 = 0;
	layoutOrder3 = 0;
	layoutWidget.clear();LOG("reset1");
	object.clear();LOG("reset2");

}
void Main::onSurfaceCreate(){
	
	javaCallManager = new JavaCallManager();
	textureManager = new TextureManager();
	

	this->initialize();
}

void Main::onSurfaceChanged(int width, int height){
	screenW = width;
	screenH = height;

	this->widgetLoad();
	this->screenChanged();
	
		particleManager = new ParticleManager(screenW, screenH);
	particleManager->setTexture(textureManager->getTextureData_System(4));
}

void Main::updateLoop(){


	this->update();
}

void Main::eventListener(){
	JNIEnv* env;
	jobject obj;
}

void Main::onTouchEvent(int x, int y, int flag){
	if(layoutWidget.size() != 0){



		std::vector<LayoutWidget*>::iterator it ;
		for (it = layoutWidget.begin() ; it!= layoutWidget.end() ; it++){
			(*it)->getXY(x,y,flag);
		}
	}

	particleManager->getXY(x,y,flag);
}

void Main::setTextureData(int id, char *data, int width, int height){
	
	textureManager->addTexture(id, data, width, height);
}

void Main::setSystemTextureData(int id, int textureId){
	
	textureManager->addTexture_System(id, textureId);

}

void Main::customobjectLoad(int *textureID, int size, float *verts, float *normals, float *coords)
{
	LOG("   -<Object Created : CUSTOM>");

	std::vector<LayoutWidget*>::iterator it = layoutWidget.end()-1;	
	Object *obj = new CustomObject(size, verts, normals, coords);
	obj->setTexture(0,textureManager->getTextureData(textureID[0]));
	(*it)->addObejct(obj);
}
//========================================================================================
#pragma endregion

#pragma region ���� ���� �Լ�
//=========== ���� ���� ==================================================================
void Main::layoutLoad(int flag, int x, int y, float ratio, int size){
	LayoutWidget *layout = 0;

	switch(flag){
	case FLAG_LAYOUT_ROTATION:
		LOG("<Layout Created : ROTATION>");
		layout = new RotationLayout();
		layout->init(x,y,screenW, screenH, ratio);

		layout->setLayoutID(layoutOrder0);
		layoutOrder0++;

		break;
	case FLAG_LAYOUT_DOCK: 
		LOG("<Layout Created : DOCK>");
		layout = new DockLayout();
		layout->init(x,y,screenW, screenH, ratio);
		((DockLayout*)layout)->getFloorTexture(textureManager->getTextureData_System(2));
		layout->setLayoutID(layoutOrder1);
		layoutOrder1++;

		break;
	case FLAG_LAYOUT_DIAL:
		LOG("<Layout Created : DIAL>");
		layout = new DialLayout();
		layout->init(x,y,screenW, screenH, ratio);
		((DialLayout*)layout)->getFloorTexture(textureManager->getTextureData_System(3));
		layout->setLayoutID(layoutOrder2);
		layoutOrder2++;

		break;
	case FLAG_LAYOUT_ROLL:
		LOG("<Layout Created : ROLL>");

		layout = new RollLayout();
		layout->init(x,y,screenW, screenH, ratio);

		layout->setLayoutID(layoutOrder3);
		layoutOrder3++;

		break;


	}
	temp+= screenH/3;
	layoutWidget.push_back(layout);
}

void Main::objectLoad(int flag, int *textureID){
	
	
	std::vector<LayoutWidget*>::iterator it = layoutWidget.end()-1;
	Object *obj;


	switch(flag){
	case FLAG_OBJECT_CUBE:
		LOG("   -<Object Created : CUBE>");
		obj = new Cube();
		for(int i=0 ; i < 6; i++)
		{
			obj->setTexture(i,textureManager->getTextureData(textureID[i]));
		}

		(*it)->addObejct(obj);	
		break;
	case FLAG_OBJECT_FLAT:
		LOG("   -<Object Created : FLAT>");
		obj = new Flat();
		obj->setTexture(0,textureManager->getTextureData(textureID[0]));
		(*it)->addObejct(obj);	

		break;
	case FLAG_OBJECT_CIRCLE:
		LOG("   -<Object Created : CIRCLE>");
		obj = new Circle();
		obj->setTexture(0,textureManager->getTextureData(textureID[0]));
		(*it)->addObejct(obj);	

		break;
	case FLAG_OBJECT_CUSTOM:
	
		break;
	}

}

void Main::layoutDelete(int pos){
	LOG("LayoutDelete pos : %d ", pos);
	//delete (*it);
	layoutWidget.erase( layoutWidget.begin() + pos);
}

void Main::objectDelete(int layoutPos, int pos){
	std::vector<LayoutWidget*>::iterator it = layoutWidget.begin();
	it+= layoutPos;
	(*it)->deleteObject(pos);
}
void Main::widgetLoad(){


}
//========================================================================================
#pragma endregion

#pragma region  openGL �۵��� �Լ�
//=========== openGL �۵��� ==============================================================
void Main::update(){
	
	if(!isFirstDraw){
		isFirstDraw = true;

	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ���� ��Ʈ��
	float am = 0.8f;
	float lightAmbient[] = {am,am,am,am};
	float lightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
	float lightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	float lightPosition[] = {0.0f, 0.0f, 0.0f, 15.0f};
	float spotlightPosition[] = {0.0f, 0.0f, -40.0f};

	glLightfv(GL_LIGHT1,GL_AMBIENT, lightAmbient);		
	glLightfv(GL_LIGHT1,GL_DIFFUSE, lightDiffuse);	
	glLightfv(GL_LIGHT1,GL_SPECULAR, lightSpecular);	
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	GLfloat white[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightf( GL_LIGHT1,GL_SPOT_EXPONENT, 80.0f );
	glLightf( GL_LIGHT1,GL_SPOT_CUTOFF, 100.0f );
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotlightPosition );

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 55.0f);

	// GL����
	glEnable(GL_FRONT_AND_BACK);
	glEnable( GL_AMBIENT_AND_DIFFUSE);
	//glEnable( GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);




	this->draw_Background();
	std::vector<LayoutWidget*>::iterator it ;
	if(layoutWidget.size() != 0)
	{
		for (it = layoutWidget.begin() ; it!= layoutWidget.end() ; it++)
		{
			(*it)->update();
		}
	}
	particleManager->update();
}

void Main::initialize(){



	glShadeModel(GL_SMOOTH);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	glClearDepthf(1.0f);
	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);


}

void Main::screenChanged(){
	glViewport(0, 0, screenW, screenH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustumf(-1.0f, 1.0f, -1.5f, 1.5f, 1.0f, 20.0f);      

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
}

void Main::draw_Background(){

	this->screenChanged();

	glPushMatrix();
	{
		//ȭ���� ����� ����

		float x = 10.0f;
		float y = 10.0f * screenH / screenW;
		float z = -10.0f;

		float backgroundVerts [] = {
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

		float backgroundNormal [] = {
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,

		};
		


		glVertexPointer(3, GL_FLOAT, sizeof(GLfloat)*5, backgroundVerts);
		glTexCoordPointer(2,GL_FLOAT,sizeof(GLfloat)*5,&backgroundVerts[0]+3);
		glNormalPointer(GL_FLOAT, 0 , backgroundNormal);


		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		{
			glFrontFace(GL_CW);

			glBindTexture(GL_TEXTURE_2D, textureManager->getTextureData_System(0));		
			glDrawArrays(GL_TRIANGLES, 0, 6);			
		}
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	}
	glPopMatrix();
}
//========================================================================================
#pragma endregion

#pragma region Java Call ����
//=========== Java Call ���� ==============================================================
void Main::Javacall_Initialize(JNIEnv* env, jobject obj, jclass cls){
	javaCallManager->getContext(env,obj,cls);
	
	std::vector<LayoutWidget*>::iterator it1;
	int i=0;
	for(it1 = layoutWidget.begin() ; it1 != layoutWidget.end() ; it1++, i++){
		(*it1)->setJavaCallManager(javaCallManager);
	}

}
//========================================================================================
#pragma endregion


#pragma region ����׸����ø�
#pragma endregion
