#include <GLES/gl.h>
#include <GLES/glext.h>


class DialLayout : public LayoutWidget{
private:
	GLuint dialTexture;
	float dial_RotateX,dial_RotateY,dial_RotateZ;
	bool isInit;
	bool touchLock;
	bool isObjectZoom;
	int objectZoomCount;
	int action;
	int actionCount;
	int rotationFlag;
	float orbitHeight;
	float orbitWidth;

	int focusedObject;
	int focusedObjectType, focusedObjectId, focusedObjectFace;

	float targetX, targetY, targetZ;
	float targetX_ani, targetY_ani, targetZ_ani;
	float targetAngleX,targetAngleY,targetAngleZ;
	float targetScaleX_ani,targetScaleY_ani,targetScaleZ_ani;

	float non_targetX, non_targetY, non_targetZ;
	float non_targetAngleX, non_targetAngleY, non_targetAngleZ;

public:
	DialLayout();
	void init();
	void update();
	void draw();
	void drawDial();
	void touch();
	void getFloorTexture(GLuint m);
	void getEvent(int* event);
};
DialLayout::DialLayout(){
	layoutType = 2;
	Aspect_Ratio = 1.5f; // 위젯의 비율( 세로 / 가로 )

	objectZoomCount = 0;

	orbitWidth = 3.0f;
	orbitHeight = 3.0f;

	isObjectZoom = false;
	isInit = false;
	touchLock = false;
	action = 0;
	actionCount = 0;
	rotationFlag=0;

	dial_RotateX = 0.0f;
	dial_RotateY = 0.0f;
	dial_RotateZ = 0.0f;

	targetX = 0;
	targetY = 0;
	targetZ = 0;
	targetX_ani = 0;
	targetY_ani = 0;
	targetZ_ani = 0;


	targetAngleX = 0;
	targetAngleY = 0;
	targetAngleZ = 0;

	targetScaleX_ani = 0;
	targetScaleY_ani = 0;
	targetScaleZ_ani = 0;

	non_targetX = 0;
	non_targetY = 0;
	non_targetZ = 0;

	non_targetAngleX = 0;
	non_targetAngleY = 0;
	non_targetAngleZ = 0;

	focusedObjectType=0;
	focusedObjectId=0;
	focusedObjectFace=0;
	focusedObject = 0;
}
void DialLayout::init(){

	objectLen = objectData.size();
	touchManager->getClickedObject(0);
}
void DialLayout::update(){
	
	objectLen = objectData.size();
	if (objectLen == 0)
	{
		return;
	}
	// 0. 레이아웃 초기화
	if(isInit){
		this->init();

		isInit = false;
	}

	// 1. 터치가 허가되었는지 안되었는지 설정
	// 2. 터치클래스에서 터치의 결과에 대한 통보받음
	// 3. 결과를 적용
	// 4. 화면에 출력

	touchManager->touchLockstate(touchLock);         // 1
	this->getEvent(touchManager->getGesture_DockLayout(objectLen));      // 2, 3

	this->draw();
	this->drawDial();
}
void DialLayout::getEvent(int* event){

	// 1. 터치결과 넘겨 받음
	// 2. 적용

	float interval = (360 / ((float)objectLen));
	std::vector<Object*>::iterator it = objectData.begin();

	if (!touchLock)
		action = 10 * event[0] + event[1];
	// 1. 터치결과 넘겨 받음

	if (!touchLock) {
		switch(event[0]){
		case 0:

			break;
		case 1:
			// 359 ~ 0 생각하기
			for(int i=0; i < objectLen ; i++, it++){
				if(interval*i - (interval / 3.0f) < event[1] && event[1] < interval*i + (interval / 3.0f)){
					event[1] = interval*i;
					focusedObject = i;
					focusedObjectType = (*it)->getObjectType();
					focusedObjectId =(*it)->getObjectId();
					touchManager->getClickedObject(focusedObjectType);
					break;
				}

				if (i == objectLen - 1) {
					focusedObject = -1;
					objectZoomCount = 0;
					non_targetAngleX = 0;
				}
			}

			dial_RotateZ = (float)event[1];

			action = 0;
			break;
		case 2:

			break;
		case 3:

			break;
		case 4:

			break;

		}

	}





	//LOG("action : %d . focusedObject: %d", action,focusedObject);
	float temp_dif = 2.2f;
	switch(action){
	case 0:


		break;
	case 21:  // 확대
		if(focusedObject == -1)
		{
			actionCount=0;
			touchManager->setTouchmode(0);
			touchManager->stop();
			return;
		}

		isObjectZoom = true;

		if(actionCount == 0){

			//(*it)->setPosition((orbitHeight-temp_dif) * cos((- interval * i - 90) * MATH_PI / 180), (orbitWidth-temp_dif) * sin((- interval * i - 90) * MATH_PI / 180), -2.0f );
			targetX_ani =  - (orbitHeight-temp_dif) * cos((- interval * focusedObject - 90) * MATH_PI / 180) / 10.0f;
			targetY_ani =  - (orbitWidth-temp_dif) * sin((- interval * focusedObject - 90) * MATH_PI / 180) / 10.0f;
			targetZ_ani =  0.05f;

			targetX = (orbitHeight-temp_dif) * cos((- interval * focusedObject - 90) * MATH_PI / 180);
			targetY = (orbitWidth-temp_dif) * sin((- interval * focusedObject - 90) * MATH_PI / 180);
			targetZ = -2.0f;

		}else if(actionCount == 10){
			focusedObjectFace = 0;
			rotationFlag = 0;
			touchLock=false;
			targetAngleX=0;
			targetAngleY=0;
			targetAngleZ=0;
			touchManager->stop();
			actionCount=0;
			break;

		}
		touchLock = true;
		actionCount++;

		targetX += targetX_ani;
		targetY += targetY_ani;
		targetZ += targetZ_ani;

		break;
	case 22:  // 축소

		if(actionCount == 0){

			  //(*it)->setPosition((orbitHeight-temp_dif) * cos((- interval * i - 90) * MATH_PI / 180), (orbitWidth-temp_dif) * sin((- interval * i - 90) * MATH_PI / 180), -2.0f );
			targetX_ani = - (orbitHeight-temp_dif) * cos((- interval * focusedObject - 90) * MATH_PI / 180) / 10.0f;
			targetY_ani = - (orbitWidth-temp_dif) * sin((- interval * focusedObject - 90) * MATH_PI / 180) / 10.0f;
			targetZ_ani =  0.05f;

		}else if(actionCount == 10){
			focusedObjectFace=0;
			isObjectZoom = false;
			touchLock=false;
			targetAngleX=0;
			targetAngleY=0;
			targetAngleZ=0;
			touchManager->stop();
			touchManager->setTouchmode(0);
			actionCount=0;
			break;

		}
		touchLock=true;
		actionCount++;

		targetX -= targetX_ani;
		targetY -= targetY_ani;
		targetZ -= targetZ_ani;

		break;



	case 31:  // 오른회전
		touchLock=true;
		if(actionCount == 10){                 // 행동 종료
			touchLock=false;
			rotationFlag = (rotationFlag - 1 + 12) % 6;
			focusedObjectFace = rotationFlag;
			actionCount=0;
			touchManager->pause();

			LOG("targetAngleX: %f, targetAngleY: %f, targetAngleZ: %f",targetAngleX, targetAngleY, targetAngleZ);

			break;
		}

		targetAngleX = (((int)(targetAngleX * 1000) + 720000) % 360000) / 1000;
		targetAngleY = (((int)(targetAngleY * 1000) + 720000) % 360000) / 1000;
		targetAngleZ = (((int)(targetAngleZ * 1000) + 720000) % 360000) / 1000;

		// A : (   0,   0,   0)
		// B : (  90,   0,   0)
		// C : (   0, 180,   0)
		// D : ( 270,  90,   0)
		// E : ( 180, 270, 180)
		// F : (   0,  90,   0)

		switch(rotationFlag){

		case 0: // F
			targetAngleX -= 0;
			targetAngleY -= 27;
			targetAngleZ -= 0;
			break;
		case 1: // A
			targetAngleX -= 9;
			targetAngleY -= 0;
			targetAngleZ -= 0;
			break;
		case 2: // B
			targetAngleX -= 27;
			targetAngleY -= 18;
			targetAngleZ -= 0;
			break;
		case 3: // C
			targetAngleX -= 27;
			targetAngleY -= 27;
			targetAngleZ -= 0;
			break;
		case 4: // D 	
			targetAngleX -= 27;
			targetAngleY -= 18;
			targetAngleZ -= 18;
			break;
		case 5: // E
			targetAngleX -= 18;
			targetAngleY -= 18;
			targetAngleZ -= 18;
			break;


		}
		actionCount++;

		break;
	case 32:  // 왼회전
		touchLock=true;
		if(actionCount == 10){                 // 행동 종료
			touchLock=false;
			rotationFlag = (rotationFlag + 1 + 12) % 6;
			focusedObjectFace =rotationFlag;
			actionCount=0;
			touchManager->pause();

			LOG("targetAngleX: %f, targetAngleY: %f, targetAngleZ: %f",targetAngleX, targetAngleY, targetAngleZ);

			break;
		}


		// A : (   0,   0,   0)
		// B : (  90,   0,   0)
		// C : (   0, 180,   0)
		// D : ( 270,  90,   0)
		// E : ( 180, 270, 180)
		// F : (   0,  90,   0)

		targetAngleX = (((int)(targetAngleX * 1000) + 720000) % 360000) / 1000;
		targetAngleY = (((int)(targetAngleY * 1000) + 720000) % 360000) / 1000;
		targetAngleZ = (((int)(targetAngleZ * 1000) + 720000) % 360000) / 1000;


		switch(rotationFlag){

		case 0: // B
			targetAngleX += 9;
			targetAngleY += 0;
			targetAngleZ += 0;
			break;
		case 1: // C   
			targetAngleX += 27;
			targetAngleY += 18;
			targetAngleZ += 0;
			break;
		case 2: // D  
			targetAngleX += 27;
			targetAngleY += 27;
			targetAngleZ += 0;
			break;
		case 3: // 	E
			targetAngleX += 27;
			targetAngleY += 18;
			targetAngleZ += 18;
			break;
		case 4: // F
			targetAngleX += 18;
			targetAngleY += 18;
			targetAngleZ += 18;
			break;
		case 5: // A
			targetAngleX += 0;
			targetAngleY += 27;
			targetAngleZ += 0;
			break;

		}
		actionCount++;


		break;

	case 41:



		if(actionCount == 0){
			this->touch();
			//(*it)->setPosition((orbitHeight-temp_dif) * cos((- interval * i - 90) * MATH_PI / 180), (orbitWidth-temp_dif) * sin((- interval * i - 90) * MATH_PI / 180), -2.0f );
			targetX_ani = - (orbitHeight-temp_dif) * cos((- interval * focusedObject - 90) * MATH_PI / 180) / 10.0f;
			targetY_ani = - (orbitWidth-temp_dif) * sin((- interval * focusedObject - 90) * MATH_PI / 180) / 10.0f;
			targetZ_ani =  0.05f;

		}else if(actionCount == 10){
			focusedObjectFace=0;
			isObjectZoom = false;
			touchLock=false;
			targetAngleX=0;
			targetAngleY=0;
			targetAngleZ=0;
			touchManager->stop();
			touchManager->setTouchmode(0);
			actionCount=0;
			break;

		}
		touchLock=true;
		actionCount++;

		targetX -= targetX_ani;
		targetY -= targetY_ani;
		targetZ -= targetZ_ani;

		break;




	case 99:

			break;
	}

}
void DialLayout::touch(){
	LOG("TOUCHED layoutType: %d, layoutID: %d, focusedObjectType: %d, focusedObjectId: %d, focusedObjectFace: %d", layoutType, layoutID, focusedObjectType, focusedObjectId, focusedObjectFace);
	javaCallManager->call(layoutType, layoutID, focusedObjectType, focusedObjectId, focusedObjectFace);

}
void DialLayout::draw(){

	glPushMatrix();
	{

		glViewport(x, ScreenH - y - LayoutH, LayoutW, LayoutH);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glFrustumf(-1.0f, 1.0f, -1.0f * Aspect_Ratio, 1.0f * Aspect_Ratio, 1.0f, 20.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


		//this->drawLayoutLine();   // 레이아웃 범위 선 그리기


		std::vector<Object*>::iterator it;
		if(objectLen == 1){
			int i = 0;
			float interval = (360 / ((float)objectLen));
			for(it = objectData.begin() ; it != objectData.end() ;i++, it++){

				(*it)->setRotate(0.0f, 0.0f, 0.0f);                                               // 겉절이들
				(*it)->setScale(1.5f,1.5f,1.5f);
				(*it)->setPosition(orbitHeight * cos((- interval * i + 90) * MATH_PI / 180), orbitWidth * sin((- interval * i + 90) * MATH_PI / 180), -6.0f );
				(*it)->draw();

				if(i == focusedObject){															  // 포커싱된것을 클릭햇을경우
					float temp_dif = 2.2f;
					(*it)->setRotate(0.0f, 0.0f, 0.0f);
					(*it)->setScale(1.0f,1.0f,1.0f);
					if(isObjectZoom){
						(*it)->setRotate(targetAngleX, targetAngleY, targetAngleZ);
						(*it)->setPosition(targetX, targetY, targetZ);
					}
					else{                                                                         // 포거싱될 경우
						objectZoomCount ++ ;
						if (objectZoomCount > 10) {
							objectZoomCount = 10;
						}
						non_targetAngleY += 0.1f ;
						(*it)->setRotate(non_targetAngleX, non_targetAngleY, non_targetAngleZ);
						(*it)->setScale(1.0f,1.0f,1.0f);
						(*it)->setPosition((orbitHeight-temp_dif) * cos((- interval * i - 90) * MATH_PI / 180), (orbitWidth-temp_dif) * sin((- interval * i - 90) * MATH_PI / 180), 0.8f * objectZoomCount + -10.0f );
					}
					(*it)->draw();
				}
			}
		}
		else{


			int i = 0;
			float interval = (360 / ((float)objectLen));
			for(it = objectData.begin() ; it != objectData.end() ;i++, it++){

				(*it)->setRotate(0.0f, 0.0f, 0.0f);                                               // 겉절이들
				(*it)->setScale(1.5f,1.5f,1.5f);
				(*it)->setPosition(orbitHeight * cos((- interval * i + 90) * MATH_PI / 180), orbitWidth * sin((- interval * i + 90) * MATH_PI / 180), -6.0f );
				(*it)->draw();

				if(i == focusedObject){															  // 포커싱된것을 클릭햇을경우
					float temp_dif = 2.2f;
					(*it)->setRotate(0.0f, 0.0f, 0.0f);
					(*it)->setScale(1.0f,1.0f,1.0f);
					if(isObjectZoom){
						(*it)->setRotate(targetAngleX, targetAngleY, targetAngleZ);
						(*it)->setPosition(targetX, targetY, targetZ);
					}
					else{                                                                         // 포거싱될 경우
						objectZoomCount ++ ;
						if (objectZoomCount > 10) {
							objectZoomCount = 10;
						}
						non_targetAngleY += 0.1f ;
						(*it)->setRotate(non_targetAngleX, non_targetAngleY, non_targetAngleZ);
						(*it)->setScale(1.0f,1.0f,1.0f);
						(*it)->setPosition((orbitHeight-temp_dif) * cos((- interval * i - 90) * MATH_PI / 180), (orbitWidth-temp_dif) * sin((- interval * i - 90) * MATH_PI / 180), 0.8f * objectZoomCount + -10.0f );
					}
					(*it)->draw();
				}
			}




		}




		// 바닥을 그려준다.

	}
	glPopMatrix();
}
void DialLayout::getFloorTexture(GLuint m){
	this->dialTexture = m;
}
void DialLayout::drawDial(){
	glPushMatrix();
	{

		glTranslatef(0.0f,0.0f,-5.0f);
		//dial_RotateX = 90.0f;
		glRotatef(dial_RotateX,-1.0f,0.0f,0.0f);
		glRotatef(dial_RotateY,0.0f,-1.0f,0.0f);
		glRotatef(dial_RotateZ,0.0f,0.0f,-1.0f);




		glVertexPointer(3, GL_FLOAT, 0, DialVerts);
		glNormalPointer(GL_FLOAT, 0, DialNormals);
		glTexCoordPointer(2, GL_FLOAT, 0, DialTexCoords);

		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		{
			glFrontFace(GL_CCW);
			// draw data
			glBindTexture(GL_TEXTURE_2D,dialTexture);
			glDrawArrays(GL_TRIANGLES, 0, DialNumVerts);
		}
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	glPopMatrix();

}



