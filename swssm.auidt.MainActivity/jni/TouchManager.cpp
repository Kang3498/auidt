#include <jni.h>
#include <math.h>

#define MATH_PI 3.14159265

class TouchManager{
private:
	int TARGET_LAYOUT;

	int screenW, screenH;
	int layoutX, layoutY, layoutW, layoutH;
	int oldX,oldY;
	int startX, startY;
	int touchX,touchY, touchFlag;
	int count;
	int touchMode;
	double distance;
	double velocity;
	float degree;
	float degree_old;
	float degree_distance;
	float degree_origin;
	float degree_current;
	bool touchLock;

	int commandStatus;
	int* actionResult;
	bool touchUP_Lock;

	int clickedObject;
	int clickedObject_Order;
	// ===  Dock Layout 에 관한거
	int objectLen;
public:
	TouchManager(int screenW, int screenH, int x,int y,int w,int h);
	void setTartgetLayout(int target);
	void getXY(int x, int y, int flag);
	int* getGesture_RotationLayout();
	int* getGesture_RollLayout();
	int* getGesture_DockLayout(int arg);
	bool isFocused();
	void stop();
	void pause();
	void touchLockstate(bool _touchLock);
	int getTouchmode();
	void setTouchmode(int t);
	void getClickedObject(int clickedObject_);
	void setOriginDegree(float degree);

	void process_RotationLayout(int x, int y, int flag);
	void process_DockLayout(int x, int y, int flag);
	void process_DialLayout(int x, int y, int flag);
	void process_RollLayout(int x, int y, int flag);
};


TouchManager::TouchManager(int screenW, int screenH , int LayoutX, int LayoutY, int LayoutW, int LayoutH){
	this->screenW = screenW;
	this->screenH = screenH;

	this->layoutX = LayoutX;
	this->layoutY = LayoutY;
	this->layoutW = LayoutW;
	this->layoutH = LayoutH;
	degree =0;
	degree_origin = 0;
	degree_old =0;
	degree_distance = 0;
	distance = 0;
	degree_current = 0;
	count = 0; 
	startX =-1;
	oldX = -1;
	startY =-1;
	oldY = -1;
	commandStatus=0;
	touchMode=0; 
	touchLock=false;

	actionResult = new int[2];
	actionResult[0] = 0; // 제스쳐 종류 
	actionResult[1] = 0; // 제스쳐 넘길 변수

	touchUP_Lock=false;
	touchFlag=0;
	TARGET_LAYOUT = 0;
	clickedObject_Order=0;
	objectLen=0;
}

void TouchManager::getClickedObject(int clickedObject_){
	clickedObject = clickedObject_;
}
void TouchManager::getXY(int x, int y, int flag){

	switch(TARGET_LAYOUT){
	case 0:              // Rotation Layout
		process_RotationLayout(x, y, flag);
		break;
	case 1:              // Dock Layout
		process_DockLayout(x, y, flag);
		break;
	case 2:              // Dial Layout
		process_DialLayout(x, y, flag);
		break;
	case 3:              // Roll Layout
		process_RollLayout(x, y, flag);
		break;
	}

}

bool TouchManager::isFocused(){
	if(layoutX <= touchX && touchX <= layoutX + layoutW && layoutY <= touchY && touchY <= layoutY + layoutH){
		return true;
	}else{
		return false;
	}
}

void TouchManager::setTartgetLayout(int target){
	TARGET_LAYOUT = target;                // targetlayout-> 0:Rotation 1:Dock 2:Dial 3:Roll
}

void TouchManager::touchLockstate(bool _touchLock){
	touchLock=_touchLock;
}


void TouchManager::stop(){
	actionResult[0] = 0;
	actionResult[1] = 0;
}

void TouchManager::pause(){
	actionResult[0] = 9;
	actionResult[1] = 9;
}


int* TouchManager::getGesture_RotationLayout(){

	return actionResult;
}
int* TouchManager::getGesture_DockLayout(int arg){
	objectLen = arg;

	//LOG("touch %d,%d  , clickedObject : %d , touchMode: %d, touchLock: %d",actionResult[0],actionResult[1],clickedObject,touchMode,touchLock);

	return actionResult;
}
int* TouchManager::getGesture_RollLayout(){

	return actionResult;
}
int TouchManager::getTouchmode(){
	return touchMode;
}
void TouchManager::setTouchmode(int t){
	this->touchMode = t;
}
void TouchManager::setOriginDegree(float degree){
	degree_origin = degree;
}
void TouchManager::process_RotationLayout(int x, int y, int flag){
	touchFlag=flag;
	touchX = x;
	touchY = y;

	if(this->isFocused()){
		// x, y 값의 평준화

		int X = (touchX - layoutX) * ((float)layoutW / (float)screenW);
		int Y = (touchY - layoutY) * ((float)layoutH / (float)screenH);

		switch(touchFlag){
		case 0:                      // 다운

			touchUP_Lock=false;

			if(startX == -1 && startY == -1)	
			{
				startX = X;
				startY = Y;
			}

			oldX = X;
			oldY = Y;
			break;
		case 1:                      // 업
			if(!touchUP_Lock){
				touchUP_Lock = true;


				if(!touchLock){
					if(touchMode == 0){	                       // 일반모드

						if(startX < X && distance > 10){
							actionResult[0] = 1;
							actionResult[1] = 1;

						}else if(startX > X  && distance > 10){
							actionResult[0] = 1;
							actionResult[1] = 2;
						}else{
							touchMode = 2;
							actionResult[0] = 2;
							actionResult[1] = 1; //확대

							LOG("zoom in");
						}
					}else if(touchMode==2)                   // 확대모드
					{                 
						float distanceX = (X - startX) * (X - startX);
						float distanceY = (Y - startY) * (Y - startY);

						//if(distanceX < distanceY && startY < Y && distance > 5){

						//	actionResult[0] = 2;
						//	actionResult[1] = 2; //축소
						//	LOG("zoom out");

						//}else if(distanceX < distanceY && startY > Y && distance > 5){

						//	actionResult[0] = 2;
						//	actionResult[1] = 2; //축소
						//	LOG("zoom out");

						//}else 

						if(startX < X && distance > 5){
							actionResult[0] = 3;
							actionResult[1] = 1;
							LOG("zoom in : Left");

						}else if(startX > X  && distance > 5){
							actionResult[0] = 3;
							actionResult[1] = 2;
							LOG("zoom in : Right");

						}else if((layoutW / 3.0f)< X  && X < (layoutW / 3.0f) * 2){
							touchMode == 0;
							actionResult[0] = 3;
							actionResult[1] = 3;             //클릭

							LOG("Click Cube Face");

						}else{
							actionResult[0] = 2;
							actionResult[1] = 2; //축소
							LOG("zoom out");

						}
					}
				}
				startX = -1;
				startY = -1;

				//초기화
				oldX = X;
				oldY = Y;
				distance=0;
				count=0;	

			}
			break;
		case 2:                      // 무브
			break;
		}

		count++;

		distance += sqrt((X-oldX)*(X-oldX) + (Y-oldY)*(Y-oldY));
		velocity = distance / count;
		degree = (atan2(layoutH/2 - Y, X- (layoutW/2)) * 180 / MATH_PI);
		if(degree < 0)
			degree += 360;

		oldX = X;
		oldY = Y;
	}
}
void TouchManager::process_DockLayout(int x, int y, int flag){
	touchFlag=flag;
	touchX = x;
	touchY = y;


	if(this->isFocused()){
		// x, y 값의 평준화

	
		int X = (touchX - layoutX) * ((float)layoutW / (float)screenW);
		int Y = (touchY - layoutY) * ((float)layoutH / (float)screenH);

		float intersection = ((float)layoutW)/((float)objectLen);

		switch(touchFlag){
		case 0:                      // 다운
			touchUP_Lock=false;

			if(startX == -1 && startY == -1)	
			{
				startX = X;
				startY = Y;
			}

			oldX = X;
			oldY = Y;

			if(touchMode == 0){	
				actionResult[0] = 0;
				actionResult[1] = 0;
				for (int i = 0; i < objectLen  ; i++)
				{
					if(i * intersection <= X && X<= (i + 1) * intersection){ // 드래그 하면서 확대모드

						actionResult[0] = 1;
						actionResult[1] = i;
						clickedObject_Order = i;
					}
				}
			}
			break;

		case 2:                      // 무브
			if(touchMode == 0){	
				actionResult[0] = 0;
				actionResult[1] = 0;
				for (int i = 0; i < objectLen  ; i++)
				{
					if(i * intersection <= X && X<= (i + 1) * intersection){ // 드래그 하면서 확대모드

						actionResult[0] = 1;
						actionResult[1] = i;
						clickedObject_Order = i;
					}
				}
			}
			break;
		case 1:                      // 업
			actionResult[0] = 0;
			actionResult[1] = 0;

			if(!touchUP_Lock){
				touchUP_Lock = true;


				if(!touchLock){
					if(touchMode == 0){	                       // 일반모드

						if(clickedObject == 0){  // 큐브일때, 확대
							touchMode = 1;
							actionResult[0] = 2;
							actionResult[1] = 1;
							LOG("ZoomIN : Cube");
						}else{
							actionResult[0] = 4; // 클릭함
							actionResult[1] = 1;
							LOG("Click : except cube");
						}

						//touchMode = 2;
					}else if(touchMode == 1)                 
					{                 
						float distanceX = (X - startX) * (X - startX);
						float distanceY = (Y - startY) * (Y - startY);

						if(distanceX < distanceY && startY < Y && distance > 5){       // 축소
							touchMode = 0;
							actionResult[0] = 2;
							actionResult[1] = 2;
							LOG("ZoomOUT : Cube");

						}else if(distanceX < distanceY && startY > Y && distance > 5){    //축소
							touchMode = 0;
							actionResult[0] = 2;
							actionResult[1] = 2;
							LOG("ZoomOUT : Cube");
						}else if(startX < X && distance > 5){
							actionResult[0] = 3;
							actionResult[1] = 1;
							LOG("Right : Cube");
						}else if(startX > X  && distance > 5){
							actionResult[0] = 3;
							actionResult[1] = 2;
							LOG("Left : Cube");
						}else if(distance < 5){
							if(layoutW / 3 <= X && X<= layoutW / 3 * 2){
								touchMode = 0;
								actionResult[0] = 4; // 클릭함
								actionResult[1] = 1;
								LOG("Click : cube");
							}else{
								touchMode = 0;
								actionResult[0] = 2; // 클릭함
								actionResult[1] = 2;
								LOG("Click : Cancle");
							}
						}
					}
				}
				startX = -1;
				startY = -1;

				//초기화
				oldX = X;
				oldY = Y;
				distance=0;
				count=0;	

			}
			break;

		}

		count++;

		distance += sqrt((X-oldX)*(X-oldX) + (Y-oldY)*(Y-oldY));
		velocity = distance / count;
		degree = (atan2(layoutH/2 - Y, X- (layoutW/2)) * 180 / MATH_PI);
		if(degree < 0)
			degree += 360;

		oldX = X;
		oldY = Y;
	}
}
void TouchManager::process_DialLayout(int x, int y, int flag){
	touchFlag=flag;
	touchX = x;
	touchY = y;


	if(this->isFocused()){
		// x, y 값의 평준화

		int X = (touchX - layoutX) * ((float)layoutW / (float)screenW);
		int Y = (touchY - layoutY) * ((float)layoutH / (float)screenH);

		float intersection = ((float)layoutW)/((float)objectLen);

		degree = 360 - (float)(((int)(((atan2(layoutH/2 - (Y), (X)- (layoutW/2)) * 180 / MATH_PI))+720) - 90) % 360);

		switch(touchFlag){
		case 0:                      // 다운
			touchUP_Lock=false;

			if(startX == -1 && startY == -1)	
			{
				startX = X;
				startY = Y;
			}
			oldX = X;
			oldY = Y;

			if(touchMode == 0){
			degree_current = degree_origin;
			degree_old = degree;
			}

			break;

		case 2:                      // 무브


			if (touchMode == 0 ) {
				degree_current += (degree - degree_old);
				degree_old = degree;
				degree_current = ((int) degree_current + 720) % 360;
				actionResult[0] = 1;
				actionResult[1] = (int) (((int) degree_current + 720) % 360); //각도

			}
			break;
		case 1:                      // 업


			degree_origin = degree_current;
		
			actionResult[0] = 0;
			actionResult[1] = 0;

			if(!touchUP_Lock){
				touchUP_Lock = true;


				if(!touchLock){
					if(touchMode == 0){	                       // 일반모드
						
						if(distance < 10
								&& 0 <= X && X<= layoutW
								&& (layoutH / 3.0f)< Y  && Y < (layoutH / 3.0f) * 2){

							if (clickedObject == 0) {
								touchMode = 1;
								actionResult[0] = 2; // 클릭함
								actionResult[1] = 1;
							} else if (1 <= clickedObject && clickedObject <= 4) {
								LOG("Click : Except Cube");
								actionResult[0] = 4; // 클릭함
								actionResult[1] = 1;
							} else {
								//아무것두 아님
							}
						}
				

						
					}else if(touchMode == 1)                 
					{                 
						float distanceX = (X - startX) * (X - startX);
						float distanceY = (Y - startY) * (Y - startY);

					   if(startX < X && distance > 5){
							actionResult[0] = 3;
							actionResult[1] = 1;
							LOG("Right : Cube");
						}else if(startX > X  && distance > 5){
							actionResult[0] = 3;
							actionResult[1] = 2;
							LOG("Left : Cube");
						}else if(distance < 5){
							if(layoutW / 3 <= X && X<= layoutW / 3 * 2 && (layoutH / 3.0f)< Y  && Y < (layoutH / 3.0f) * 2){
								touchMode = 0;
								actionResult[0] = 4; // 클릭함
								actionResult[1] = 1;
								LOG("Click : cube");
							}else{
								touchMode = 0;
								actionResult[0] = 2; // 클릭함
								actionResult[1] = 2;
								LOG("Click : Cancle");
							}
						}
					}
				}
				startX = -1;
				startY = -1;

				//초기화
				oldX = X;
				oldY = Y;
				distance=0;
				count=0;	

			}
			break;

		}

		count++;


		distance += sqrt((X-oldX)*(X-oldX) + (Y-oldY)*(Y-oldY));
		velocity = distance / count;
		
		oldX = X;
		oldY = Y;

	}
}
void TouchManager::process_RollLayout(int x, int y, int flag){
	touchFlag=flag;
	touchX = x;
	touchY = y;

	if(this->isFocused()){
		// x, y 값의 평준화

		int X = (touchX - layoutX) * ((float)layoutW / (float)screenW);
		int Y = (touchY - layoutY) * ((float)layoutH / (float)screenH);

		switch(touchFlag){
		case 0:                      // 다운

			touchUP_Lock=false;

			if(startX == -1 && startY == -1)	
			{
				startX = X;
				startY = Y;
			}

			oldX = X;
			oldY = Y;
			break;
		case 1:                       // 업
			if(!touchUP_Lock){
				touchUP_Lock = true;


				if(!touchLock){
					if(touchMode == 0){	                       // 일반모드

						if(startY > Y && distance > 5){
							actionResult[0] = 1;
							actionResult[1] = 1;

						}else if(startY < Y  && distance > 5){
							actionResult[0] = 1;
							actionResult[1] = 2;
						}else{
							touchMode = 2;
							actionResult[0] = 2;
							actionResult[1] = 1; //확대

							LOG("zoom in");
						}
					}else if(touchMode==2)                   // 확대모드
					{                 
						float distanceX = (X - startX) * (X - startX);
						float distanceY = (Y - startY) * (Y - startY);


						//if(distanceX < distanceY && startY < Y && distance > 5){

						//	actionResult[0] = 2;
						//	actionResult[1] = 2; //축소
						//	LOG("zoom out");

						//}else if(distanceX < distanceY && startY > Y && distance > 5){

						//	actionResult[0] = 2;
						//	actionResult[1] = 2; //축소
						//	LOG("zoom out");

						//}else 

						if(startX < X && distance > 5){
							actionResult[0] = 3;
							actionResult[1] = 1;
							LOG("zoom in : Left");

						}else if(startX > X  && distance > 5){
							actionResult[0] = 3;
							actionResult[1] = 2;
							LOG("zoom in : Right");

						}else if((layoutW / 3.0f)< X  && X < (layoutW / 3.0f) * 2){
							actionResult[0] = 3;
							actionResult[1] = 3;             //클릭

							LOG("Click Cube Face");

						}else{
							actionResult[0] = 2;
							actionResult[1] = 2; //축소
							LOG("zoom out");

						}
					}
				}
				startX = -1;
				startY = -1;

				//초기화
				oldX = X;
				oldY = Y;
				distance=0;
				count=0;	

			}
			break;
		case 2:                      // 무브
			break;
		}

		count++;

		distance += sqrt((X-oldX)*(X-oldX) + (Y-oldY)*(Y-oldY));
		velocity = distance / count;
		degree = (atan2(layoutH/2 - Y, X- (layoutW/2)) * 180 / MATH_PI);
		if(degree < 0)
			degree += 360;

		oldX = X;
		oldY = Y;
	}
}
