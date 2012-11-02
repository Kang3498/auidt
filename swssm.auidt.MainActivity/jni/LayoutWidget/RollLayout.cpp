#include <GLES/gl.h>
#include <GLES/glext.h>

class RollLayout : public LayoutWidget{

private:
	 float orbitWidth;
	 float  orbitHeight ;

	GLfloat Xangle, Yangle, Zangle;
	bool isfirstDrawing;
	bool isCube;
	int action;
	int actionCount;
	float degreeRotate_term;
	float degreeRotate_distance;
	float degreeRotate;
	float targetX, targetY, targetZ;
	float targetAngleX,targetAngleY,targetAngleZ;
	float targetAngleX_ani,targetAngleY_ani,targetAngleZ_ani;

	float non_targetAngleX, non_targetAngleY, non_targetAngleZ;

	int rotationFlag;

	bool touchLock;
	std::vector<float> degree;

	int focusedObjectType, focusedObjectId, focusedObjectFace; 
public:
	RollLayout();

	void getGesture(int i);
	void update();
	void draw();
	void getEvent(int* event);
	void angleNormalize();

	int getFocusedObjectData(float aX, float aY, float aZ);
	void touch();
};

RollLayout::RollLayout(){
	layoutType = 3;

	Aspect_Ratio = 1.5f; // ������ ����( ���� / ���� )

	orbitWidth = 2;
	orbitHeight = 4;

	isfirstDrawing = false;
	isCube = false;
	action = 0;
	actionCount = 0;
	degreeRotate = 0;
	degreeRotate_term =0;
	degreeRotate_distance =0;
	targetX = 0;
	targetY = 0;
	targetZ = 0;
	targetAngleX = 0;
	targetAngleY = 0;
	targetAngleZ = 0;
	non_targetAngleX = 0;
	non_targetAngleY = 0;
	non_targetAngleZ = 0;
	targetAngleX_ani = 0;
	targetAngleY_ani = 0;
	targetAngleZ_ani = 0;

	touchLock = false;

	rotationFlag = 0;

	focusedObjectType = 0; 
	focusedObjectId = 0;
	focusedObjectFace = 0;
}
void RollLayout::update(){
	objectLen = objectData.size();

	if (objectLen == 0)
	{
		return;
	}
	//���⿡ ��ġ �̺�Ʈ ����
	touchManager->touchLockstate(touchLock);
	this->getEvent(touchManager->getGesture_RollLayout());

	this->draw();
}

void RollLayout::getEvent(int* event){

	if(!touchLock){
		switch(event[0]){
		case 0:
			break;
		case 1:
			action = event[1];       // 1: �������� ���� 2: ���������� ����
			break;
		case 2: 
			action = 2 + event[1];   // 3: Ȯ��, 4: ���
			break;
		case 3:
			action = 4 + event[1];   // 5: Ȯ�뿡�� ���� 6: Ȯ�뿡�� ������ 7: Ȯ���� �� Ŭ��
			break;

		}
	}
	objectLen = objectData.size();


	std::vector<Object*>::iterator it;
	std::vector<float>::iterator it_degree;
	if(!isfirstDrawing){
		// ó�� �׸��� ���ۿ��� �۵�
		LOG("[Drawing Start : Rotation Layout]");

		if(objectLen ==1){ //ť�갡 �ϳ��ΰ�쿣 �׳� �߽ɿ� �д�. 
			it=objectData.begin();
			(*it)->setRotate(0,0,0);
			(*it)->setPosition(0,0,-2);
			(*it)->setScale(1.0f,1.0f,1.0f);
			degree.push_back( -90 );
		}else{

			int i=0;
			for(it=objectData.begin() ; it != objectData.end() ; it++, i++ ){

				float temp = (-90 + 360 / (objectLen) % 360 * i) % 360; // �ʱ� ������ ������
				degree.push_back( temp );

				(*it)->setRotate(0,0,0);
				(*it)->setScale(1.0f,1.0f,1.0f);
			}
		}
		isfirstDrawing=true;
	}

	switch(action){
	case 0: 
		actionCount = 0;
		degreeRotate = 0;
		break;

	case 1: // �������� ���� 

		if(objectLen != 1){
			if(actionCount == 0){
				degreeRotate_distance =(int)( (int)360 / (objectLen));
				degreeRotate_term = 360.0f / ((float)objectLen) / 10.0f;

				//LOG("c : %d , degreeRotate_distance1 : %f , degreeRotate_term : %f",actionCount , degreeRotate_distance,degreeRotate_term);
			}
			else if(actionCount == 10){					
				// ��� ���� �ٽ� ����ȭ��Ų��.
				std::vector<float>::iterator it_degree_temp;
				float term_temp = 360.0f / (float)objectLen;


				for(it_degree_temp = degree.begin(); it_degree_temp != degree.end() ; it_degree_temp++){
					float term_temp1;
					for(int k=0; k < objectLen; k++){
						term_temp1 = term_temp * k + 270;
						if(term_temp1 > 360){
							term_temp1 -= 360;
						}
						else if(term_temp1 < 0){
							term_temp1 += 360;
						}

						if(term_temp1 - 1 < (*it_degree_temp) && (*it_degree_temp) < term_temp1  + 1)
						{
							(*it_degree_temp) = term_temp1;
							//LOG("it_degree_temp : %f, term_temp1: %f",(*it_degree_temp),term_temp1);
						}

					}
				}

				degreeRotate = degreeRotate_distance;
				LOG("c : %d , degreeRotate_distance3 : %f",actionCount , degreeRotate_distance);
				touchLock=false;
				actionCount=0;
				action=0;
				touchManager->stop();
				break;
			}

			degreeRotate_distance -= degreeRotate_term;
			degreeRotate = degreeRotate_term;
			actionCount++;

		}
		break;

	case 2: // ���������� ����

		if(objectLen != 1){
			if(actionCount == 0){
				degreeRotate_distance = -(int)( (int)360 / (objectLen));
				degreeRotate_term = -360.0f / ((float)objectLen) / 10.0f;

				//LOG("c : %d , degreeRotate_distance1 : %f , degreeRotate_term : %f",actionCount , degreeRotate_distance,degreeRotate_term);
			}
			else if(actionCount == 10){					
				// ��� ���� �ٽ� ����ȭ��Ų��.
				std::vector<float>::iterator it_degree_temp;
				float term_temp = 360.0f / (float)objectLen;


				for(it_degree_temp = degree.begin(); it_degree_temp != degree.end() ; it_degree_temp++){
					float term_temp1;
					for(int k=0; k < objectLen; k++){
						term_temp1 = term_temp * k + 270;
						if(term_temp1 > 360){
							term_temp1 -= 360;
						}
						else if(term_temp1 < 0){
							term_temp1 += 360;
						}

						if(term_temp1 - 1 < (*it_degree_temp) && (*it_degree_temp) < term_temp1  + 1)
						{
							(*it_degree_temp) = term_temp1;
							//LOG("it_degree_temp : %f, term_temp1: %f",(*it_degree_temp),term_temp1);
						}

					}
				}

				degreeRotate = degreeRotate_distance;
				LOG("c : %d , degreeRotate_distance3 : %f",actionCount , degreeRotate_distance);
				touchLock=false;
				actionCount=0;
				action=0;
				touchManager->stop();
				break;
			}

			degreeRotate_distance -= degreeRotate_term;
			degreeRotate = degreeRotate_term;
			actionCount++;
		}
		break;

	case 3: // Ȯ���ϱ�


		if(actionCount == 10){               	// �ൿ ����
			this->angleNormalize(); 
			targetAngleX = 0;
			targetAngleY = 0;
			targetAngleZ = 0;
			touchLock=false;
			actionCount=0;
			action=0;
			rotationFlag=0;
			touchManager->stop();
			break;
		}else if(actionCount==0){     // �ൿ ���� ��
			this->angleNormalize(); 


			targetAngleX_ani = (0 - targetAngleX) /10;
			targetAngleY_ani = (0 - targetAngleY) /10;
			targetAngleZ_ani = (0 - targetAngleZ) /10;


		}
		touchLock=true;

		targetAngleX += targetAngleX_ani;
		targetAngleY += targetAngleY_ani; 
		targetAngleZ += targetAngleZ_ani; 

		targetZ +=0.07f;
		actionCount++;

		break;

	case 4: // ����ϱ�
		this->angleNormalize(); 
		if(actionCount == 10){                 // �ൿ ����
			this->angleNormalize(); 
			targetAngleX_ani = non_targetAngleX;
			targetAngleY_ani = non_targetAngleY;
			targetAngleZ_ani = non_targetAngleZ;
			touchLock=false;
			actionCount=0;
			action=0;
			targetZ=0;
			touchManager->setTouchmode(0);
			touchManager->stop();
			break;
		}else if(actionCount==0){     // �ൿ ���� ��

			targetAngleX_ani = (non_targetAngleX - targetAngleX) /10;
			targetAngleY_ani = (non_targetAngleY - targetAngleY) /10;
			targetAngleZ_ani = (non_targetAngleZ - targetAngleZ) /10;
		}
		targetAngleX += targetAngleX_ani;
		targetAngleY += targetAngleY_ani; 
		targetAngleZ += targetAngleZ_ani; 

		touchLock=true;
		targetZ -=0.07f;
		actionCount++;
		break;


	case 5: // Ȯ���� �� �������� ������
		if(!isCube)  //ť���϶��� ������
			break;

		this->angleNormalize(); 
		if(actionCount == 10){                 // �ൿ ����
			rotationFlag = (rotationFlag + 1 + 12) % 6;

			touchLock=false;
			actionCount=0;
			action=0;
			touchManager->stop();

			//LOG("targetAngleX: %f, targetAngleY: %f, targetAngleZ: %f",targetAngleX, targetAngleY, targetAngleZ);

			break;
		}
		touchLock=true;

		// A : (   0,   0,   0)
		// B : (  90,   0,   0)
		// C : (   0, 180,   0)
		// D : ( 270,  90,   0)
		// E : ( 180, 270, 180)
		// F : (   0,  90,   0)

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

	case 6: // Ȯ���� �� ���������� ������


		if(!isCube)  //ť���϶��� ������
			break;

		this->angleNormalize(); 
		if(actionCount == 10){                 // �ൿ ����
			rotationFlag = (rotationFlag - 1 + 12) % 6;

			touchLock=false;
			actionCount=0;
			action=0;
			touchManager->stop();

			//LOG("targetAngleX: %f, targetAngleY: %f, targetAngleZ: %f",targetAngleX, targetAngleY, targetAngleZ);
			break;
		}

		touchLock=true;

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
	case 7: // Ȯ���� �� Ŭ��

		this->angleNormalize(); 
		if(actionCount == 10){                 // �ൿ ����
			
			this->angleNormalize(); 
			targetAngleX_ani = non_targetAngleX;
			targetAngleY_ani = non_targetAngleY;
			targetAngleZ_ani = non_targetAngleZ;
			touchLock=false;
			actionCount=0;
			action=0;
			targetZ=0;
			touchManager->setTouchmode(0);
			touchManager->stop();
			break;
		}else if(actionCount==0){     // �ൿ ���� ��
			this->touch();
			targetAngleX_ani = (non_targetAngleX - targetAngleX) /10;
			targetAngleY_ani = (non_targetAngleY - targetAngleY) /10;
			targetAngleZ_ani = (non_targetAngleZ - targetAngleZ) /10;
		}
		targetAngleX += targetAngleX_ani;
		targetAngleY += targetAngleY_ani; 
		targetAngleZ += targetAngleZ_ani; 

		touchLock=true;
		targetZ -=0.07f;
		actionCount++;
		break;
		break;

	}

}
int RollLayout::getFocusedObjectData(float aX, float aY, float aZ){

	// A : (   0,   0,   0)
	// B : (  90,   0,   0)
	// C : (   0, 180,   0)
	// D : ( 270,  90,   0)
	// E : ( 180, 270, 180)
	// F : (   0,  90,   0)

	aX = ((int)aX + 720) % 360;
	aY = ((int)aY + 720) % 360;
	aZ = ((int)aZ + 720) % 360;

	if(aX ==   0 && aY == 0 && aZ == 0) return 0;
	else if(aX ==  90 && aY ==   0 && aZ ==   0) return 1;
	else if(aX ==   0 && aY == 180 && aZ ==   0) return 2;
	else if(aX == 270 && aY ==  90 && aZ ==   0) return 3;
	else if(aX == 180 && aY == 270 && aZ == 180) return 4;
	else if(aX ==   0 && aY ==  90 && aZ ==   0) return 5;
	else return -1;

}
void RollLayout::touch(){
	LOG("TOUCHED layoutType: %d, layoutID: %d, focusedObjectType: %d, focusedObjectId: %d, focusedObjectFace: %d", layoutType, layoutID, focusedObjectType, focusedObjectId, focusedObjectFace);
	javaCallManager->call(layoutType, layoutID, focusedObjectType, focusedObjectId, focusedObjectFace);

}
void RollLayout::draw(){

	glViewport(x, ScreenH - y - LayoutH, LayoutW, LayoutH); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glFrustumf(-1.0f, 1.0f, -1.0f * Aspect_Ratio, 1.0f * Aspect_Ratio, 1.0f, 20.0f);   

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	//this->drawLayoutLine();   // ���̾ƿ� ���� �� �׸���



	std::vector<Object*>::iterator it;
	std::vector<float>::iterator it_degree;

	if(objectLen == 1){


		it=objectData.begin();
		it_degree = degree.begin();

		focusedObjectType = (*it)->getObjectType();
		focusedObjectId = (*it)->getObjectId();
		if(focusedObjectType == 0){
			isCube = true;          //ť���� ��� <- ȸ���� �����ϰ� ��
			focusedObjectFace = this->getFocusedObjectData(targetAngleX, targetAngleY, targetAngleZ);
		}
		else{
			isCube = false;
			focusedObjectFace = 0;
		}

		(*it_degree) = 270;
		(*it)->setRotate(targetAngleX, targetAngleY, targetAngleZ);
		(*it)->setScale(1.0f,1.0f,1.0f);
		(*it)->setPosition(0.0f, orbitHeight * cos((*it_degree) * MATH_PI / 180), -4.5 - orbitWidth * sin((*it_degree) * MATH_PI / 180) + targetZ);


		(*it)->draw();

	}else{

		non_targetAngleX +=0.1f;
		non_targetAngleY = non_targetAngleX;

		for(it = objectData.begin(), it_degree = degree.begin() ; it != objectData.end() ; it++,it_degree++ ){

			// ���� ���� �⺻���� ��ġ�� �ѷ��ش�.
			(*it_degree)+=degreeRotate;
		
			if((*it_degree) > 360)
				(*it_degree) -= 360;
			else if((*it_degree) < 0)
				(*it_degree) += 360;

			if(((int)(*it_degree)) == 270){ // ��� �ִ� �� ĳġ

				focusedObjectType = (*it)->getObjectType();
				focusedObjectId = (*it)->getObjectId();
				if(focusedObjectType == 0){
					isCube = true;          //ť���� ��� <- ȸ���� �����ϰ� ��
					focusedObjectFace = this->getFocusedObjectData(targetAngleX, targetAngleY, targetAngleZ);
				}
				else{
					isCube = false;
					focusedObjectFace = 0;
				}


				if(touchManager->getTouchmode() == 2){  // ��� ���� ���õǾ� �ִٸ� (Ȯ����)

					(*it)->setRotate(targetAngleX, targetAngleY, targetAngleZ);
				}else{                                  // ��� ���� ������ �ȵǾ� �ִٸ�   -> �ٸ� �͵麸�� �� ���� ����.
					targetAngleX +=0.1f;
					targetAngleY = targetAngleX;

					(*it)->setRotate(non_targetAngleX, non_targetAngleY , non_targetAngleZ);
				}

				(*it)->setPosition(0.0f, orbitHeight * cos((*it_degree) * MATH_PI / 180), -4.5 - orbitWidth * sin((*it_degree) * MATH_PI / 180) + targetZ);

			}else{                         // ������ ���

				if(touchManager->getTouchmode() != 2){

				}else{

				}
				(*it)->setRotate(non_targetAngleX, non_targetAngleY , non_targetAngleZ);
				(*it)->setPosition(0.0f, orbitHeight * cos((*it_degree) * MATH_PI / 180), -4.5 - orbitWidth * sin((*it_degree) * MATH_PI / 180) - targetZ);

			}
			(*it)->setScale(1.0f,1.0f,1.0f);
			(*it)->draw();
		}
	}

	//this->angleNormalize();         // ���� ����ȭ
}

void RollLayout::angleNormalize(){ 
	// ������ 0~359 ���̷� ������ ����� �ش�

	targetAngleX = (((int)(targetAngleX * 1000) + 720000) % 360000) / 1000;
	targetAngleY = (((int)(targetAngleY * 1000) + 720000) % 360000) / 1000;
	targetAngleZ = (((int)(targetAngleZ * 1000) + 720000) % 360000) / 1000;

	targetAngleX_ani = (((int)(targetAngleX_ani * 1000) + 720000) % 360000) / 1000;
	targetAngleY_ani = (((int)(targetAngleY_ani * 1000) + 720000) % 360000) / 1000;
	targetAngleZ_ani = (((int)(targetAngleZ_ani * 1000) + 720000) % 360000) / 1000;

	non_targetAngleX = (((int)(non_targetAngleX * 100000) + 72000000) % 36000000) / 100000;
	non_targetAngleY = (((int)(non_targetAngleY * 100000) + 72000000) % 36000000) / 100000;
	non_targetAngleZ = (((int)(non_targetAngleZ * 100000) + 72000000) % 36000000) / 100000;


}

void RollLayout::getGesture(int token){
	switch(token){
	case 0:
		break;
	}
}