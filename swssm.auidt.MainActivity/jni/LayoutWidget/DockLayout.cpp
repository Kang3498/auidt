#include <GLES/gl.h>
#include <GLES/glext.h>



class DockLayout : public LayoutWidget{
private:
	Cube* floor;
	GLuint floorTexture;

	bool isInit;
	bool touchLock;
	int action;
	int actionCount;
	int objectLen;
	int count_ani;
	int rotationFlag;

	float targetX, targetY, targetZ;
	float targetX_ani, targetY_ani, targetZ_ani;
	float targetAngleX,targetAngleY,targetAngleZ;
	float targetScaleX_ani,targetScaleY_ani,targetScaleZ_ani;

	float non_targetX, non_targetY, non_targetZ;
	float non_targetAngleX, non_targetAngleY, non_targetAngleZ;

	int focusedObjectType, focusedObjectId, focusedObjectFace; 
	std::vector<int> order; // 값이 1인게 포커싱된거임
public:
	DockLayout();
	void getFloorTexture(GLuint m);
	void init();
	void update();
	void getEvent(int* event);
	void draw();
	void touch();
	float* jumpAni();

};
DockLayout::DockLayout(){
	layoutType = 1;
	Aspect_Ratio = 0.5f; // 위젯의 비율( 세로 / 가로 )
	actionCount=0;
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
	count_ani = 0;

	rotationFlag = 0;

	isInit = true;
	touchLock = false;

	action = 0;

	focusedObjectType=0;
	focusedObjectId=0; 
	focusedObjectFace=0;

	floor = new Cube();
	floor->setMode(1);
}
void DockLayout::init(){
	// 초기화 : 초기 위치, 각도 초기화
	LOG("[Drawing Start : Dock Layout]");

	std::vector<Object*>::iterator it;
	std::vector<int>::iterator it_order;

	objectLen = objectData.size();

	if(objectLen ==1){                                           //큐브가 하나인경우엔 그냥 중심에 둔다. 
		it=objectData.begin();

		(*it)->setRotate(0,0,0);
		(*it)->setScale(1.0f, 1.0f, 1.0f);
		order.push_back( 0 );
	}else{

		int i=0;

		for(it=objectData.begin() ; it != objectData.end() ; it++, i++ ){

			(*it)->setRotate(0,0,0);
			(*it)->setScale(1.0f, 1.0f, 1.0f);
			order.push_back( 0 );
		}
	}
}
void DockLayout::getFloorTexture(GLuint m){
	this->floorTexture = m;
}

void DockLayout::update(){
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
	this->draw();                                    // 4
}
void DockLayout::getEvent(int* event){
	// 1. 터치결과 넘겨 받음
	// 2. 적용
	std::vector<Object*>::iterator it;
	std::vector<int>::iterator it_order =  order.begin();
	float *temp;
	int focusTEMP=0;
	float interval = (6 / ((float)objectLen - 1.0f));
	// 1. 터치결과 넘겨 받음
	if(!touchLock){
		switch(event[0]){
		case 0:
			for (int i=0; i<objectLen ; i++, it_order++)
			{
				(*it_order) = 0; 
			}
			break;
		case 1:
			// 1. 누른채로 드래그
			for (int i=0; i<objectLen ; i++, it_order++)
			{
				if(i == event[1]){
					(*it_order) = 1;

				}
				else{
					(*it_order) = 0; 
				}
			}
			break;
		case 2: 
			break;
		}
	}

	action = 10 * event[0] + event[1];  
	// 2. 적용
	/*LOG("action : %d", action);*/
	switch(action){
	case 0:
		targetAngleX=0;
		targetAngleY=0;
		targetAngleZ=0;
		break;
	case 21:  // 확대


		for (int i=0; i<objectLen ; i++, it_order++)
		{
			if((*it_order)==1){
				(*it_order) = 2;
				focusTEMP =i;
				break;
			}
		}
		if(actionCount == 0){


			targetX_ani = (-3.0f + interval * focusTEMP) * (-1.0f) / 10.0f;
			targetY_ani =  0.0f;
			targetZ_ani =  0.2f;

			targetX = (-3.0f + interval * focusTEMP);
			targetY = 0.0f;
			targetZ = -4.3f;
		}else if(actionCount == 10){
			focusedObjectFace = 0;
			rotationFlag=0;
			targetAngleX=0;
			targetAngleY=0;
			targetAngleZ=0;
			touchManager->pause();
			actionCount=0;
			break;

		}
		actionCount++;

		targetX += targetX_ani;
		targetY += targetY_ani;
		targetZ += targetZ_ani;

		//LOG("%f,%f,%f, || %f, %f, %f",targetX, targetY, targetZ, targetX_ani, targetY_ani, targetZ_ani);


		break;
	case 22:  // 축소

		if(actionCount == 0){

		}else if(actionCount == 10){
			touchManager->stop();
			actionCount=0;
			break;
		}
		actionCount++;

		targetX -= targetX_ani;
		targetY -= targetY_ani;
		targetZ -= targetZ_ani;


		break;
	case 31:  // 오른회전
		if(actionCount == 10){                 // 행동 종료
			rotationFlag = (rotationFlag - 1 + 12) % 6;
			focusedObjectFace = rotationFlag;
			actionCount=0;
			touchManager->pause();

			//LOG("targetAngleX: %f, targetAngleY: %f, targetAngleZ: %f",targetAngleX, targetAngleY, targetAngleZ);

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
		if(actionCount == 10){                 // 행동 종료
			rotationFlag = (rotationFlag + 1 + 12) % 6;
			focusedObjectFace = rotationFlag;
			actionCount=0;
			touchManager->pause();

			//LOG("targetAngleX: %f, targetAngleY: %f, targetAngleZ: %f",targetAngleX, targetAngleY, targetAngleZ);

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
	case 41:  // 클릭	


		if(actionCount == 0){
	
			this->touch();
		}else if(actionCount == 10){
			for (int i=0; i<objectLen ; i++, it_order++)
			{
				(*it_order) = 0; 
			}
			touchManager->stop();
			actionCount=0;
			break;
		}
		actionCount++;

		targetX -= targetX_ani;
		targetY -= targetY_ani;
		targetZ -= targetZ_ani;

		break;

	case 99: 
		targetX =  0.0f;
		targetY =  0.0f;
		targetZ = -2.0f;
		break;
	}
}

void DockLayout::touch(){
	LOG("TOUCHED layoutType: %d, layoutID: %d, focusedObjectType: %d, focusedObjectId: %d, focusedObjectFace: %d", layoutType, layoutID, focusedObjectType, focusedObjectId, focusedObjectFace);
	javaCallManager->call(layoutType, layoutID, focusedObjectType, focusedObjectId, focusedObjectFace);

}
void DockLayout::draw(){

	glPushMatrix();
	{
		glViewport(x, ScreenH - y - LayoutH, LayoutW, LayoutH); 
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glFrustumf(-1.0f, 1.0f, -1.0f * Aspect_Ratio, 1.0f * Aspect_Ratio, 1.0f, 20.0f);   

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


		//this->drawLayoutLine();   // 레이아웃 범위 선 그리기


		// 바닥을 그려준다.
		floor->setTexture(0,floorTexture);		
		floor->setPosition(0.0f, -0.7, -4.3);
		floor->setScale(7.0f, 0.2f, 1.5f);
		floor->setRotate(0.0f,0.0f,0.0f);
		floor->draw();





		std::vector<Object*>::iterator it;
		std::vector<int>::iterator it_order;


		if(objectLen == 1){		
			it = objectData.begin();
			(*it)->setPosition( 0.0f, 0.0f, -5.0f);
			(*it)->setScale(1.0f,1.0f,1.0f);
			(*it)->setRotate(0.0f, non_targetAngleY, 0.0f);

			(*it)->draw();

		}else{
			int i = 0;
			float interval = (6 / ((float)objectLen - 1.0f));
			for(it = objectData.begin(), it_order = order.begin() ; it != objectData.end() ;i++, it++,it_order++ ){
				(*it)->setRotate(10.0f,0,0);

				if((*it_order) == 0){                            // 선택되지 않은 것
					(*it)->setScale(1.0f, 1.0f, 1.0f);
					(*it)->setPosition( -3.0f + interval * i, 0.0f, -4.3f);
					
					non_targetAngleY+=0.1f;
					
					if((*it)->getObjectType() == 0 || (*it)->getObjectType() == 2 || (*it)->getObjectType() == 3)
						(*it)->setRotate(0.0f, non_targetAngleY, 0.0f);
					else if((*it)->getObjectType() == 1)
						(*it)->setRotate(0.0f, 0.0f, non_targetAngleY);
				}
				else if((*it_order) == 1){                       // 선택된 것
					focusedObjectType = (*it)->getObjectType();
					focusedObjectId = (*it)->getObjectId();

					touchManager->getClickedObject(	(*it)->getObjectType());
					float* temp = this->jumpAni();
					(*it)->setScale(temp[3], temp[4], temp[5]);
					(*it)->setPosition( -3.0f + interval * i, temp[1], -4.3f);
					if((*it)->getObjectType() == 0)
						(*it)->setRotate(0.0f, 0, 0.0f);
					else
						(*it)->setRotate(0, 0, 0);

				}else if((*it_order) == 2){
	

					touchManager->getClickedObject(	(*it)->getObjectType());
					(*it)->setScale(1.0f, 1.0f, 1.0f);
					(*it)->setPosition( targetX, targetY, targetZ);
					(*it)->setRotate(targetAngleX, targetAngleY, targetAngleZ);
					//LOG(" target %f,%f,%f,",targetX, targetY, targetZ);
				}

				(*it)->draw();
			}
		}
	}
	glPopMatrix();
}

float* DockLayout::jumpAni(){
	float* result = new float[6];
	//0.3 , 1.5;

	if(count_ani == 0){
		targetScaleX_ani = 1.02f;
		targetScaleY_ani = 1.02f;
		targetScaleZ_ani = 1.02f;

		non_targetX = 0.006f;
		non_targetY = 0.006f;
		non_targetZ = 0.006f;
	}else if(count_ani < 25){
		targetScaleX_ani += 0.02f;
		targetScaleY_ani += 0.02f;
		targetScaleZ_ani += 0.02f;

		non_targetX += 0.006f;
		non_targetY += 0.006f;
		non_targetZ += 0.006f;

	}else {
		targetScaleX_ani -= 0.02f;
		targetScaleY_ani -= 0.02f;
		targetScaleZ_ani -= 0.02f;

		non_targetX -= 0.006f;
		non_targetY -= 0.006f;
		non_targetZ -= 0.006f;
	}


	result[0] = non_targetX;
	result[1] = non_targetY ;
	result[2] = non_targetZ ;
	result[3] = targetScaleX_ani;
	result[4] =	targetScaleY_ani;
	result[5] =	targetScaleZ_ani;


	if(count_ani == 50)
		count_ani=0;
	else 
		count_ani++;

	return result;
}