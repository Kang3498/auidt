
#include <jni.h>


class JavaCallManager{
private:
	JNIEnv* env;
	jobject obj;
	jclass cls;

public:
	JavaCallManager();
	void getContext(JNIEnv* env, jobject obj, jclass cls);
	void call(int layout, int layoutindex,int object, int objectindex,int faceindex);
	
};

JavaCallManager::JavaCallManager(){

}

void JavaCallManager::getContext(JNIEnv* env, jobject obj, jclass cls){
	this->env = env;
	this->obj = obj;
	this->cls = cls;
}

void JavaCallManager::call(int layout, int layoutindex,int object, int objectindex,int faceindex){

	jmethodID mid = env->GetMethodID(cls, "SendFaceMessage","(IIIII)V");
	//jobject jObj = env->NewObject(cls, mid, layout, layoutindex, object, objectindex, faceindex );

	env->CallVoidMethod(obj, mid ,layout, layoutindex, object, objectindex, faceindex );

	LOG("JavaCall Sent");
}