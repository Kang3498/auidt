#include <jni.h>

#include <android/log.h>
#define LOG_TAG "JNI"
#define LOG(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

#include "Main.cpp"


#ifdef __cplusplus
extern "C" {
#endif
	Main *main;

	int isFirstDraw;

	JNIEnv*  ENV;
	jobject OBJ;
	jclass CLS;
	jmethodID mid;
	JNIEXPORT void JNICALL Java_swssm_auidt_view_AUIDTView_nativeCreated(JNIEnv*  env)
	{	
		isFirstDraw=0;
		//delete main;
		main = new Main();
		LOG("nativeCreated Complete");
	}
	JNIEXPORT void JNICALL Java_swssm_auidt_view_AUIDTView_nativeReset(JNIEnv*  env)
	{
		main->reset();
		isFirstDraw =0;
	}
	JNIEXPORT void JNICALL Java_swssm_auidt_view_AUIDTView_nativeChanged
		(JNIEnv* env, jobject obj, jint width, jint height)
	{
		main->onSurfaceChanged(width, height);
		LOG("nativeChanged Complete");
	}

	JNIEXPORT void JNICALL Java_swssm_auidt_view_AUIDTView_nativeUpdateGame
		(JNIEnv* env, jobject obj)
	{
		if(isFirstDraw ==0){

			isFirstDraw=1;
			main->Javacall_Initialize(ENV,OBJ,CLS);
			LOG("nativeUpdate Start");
		}

		main->updateLoop(); 
	}
	
	JNIEXPORT void JNICALL Java_swssm_auidt_view_AUIDTView_nativeOnTouchEvent
		(JNIEnv* env, jobject thiz, jint x, jint y, jint touchFlag)
	{
		main->onTouchEvent(x, y, touchFlag);
	}

	JNIEXPORT void JNICALL Java_swssm_auidt_view_AUIDTView_nativeSetTextureData
		(JNIEnv* env, jobject thiz, jint id ,jintArray arr, jint width, jint height)
	{
		jint *temp = env->GetIntArrayElements(arr, 0);
		char *data =(char*)temp;

		main->setTextureData(id, data, width, height);

		env->ReleaseIntArrayElements(arr, (jint*)data, JNI_ABORT);
	}

	JNIEXPORT void JNICALL Java_swssm_auidt_view_AUIDTView_accessField(JNIEnv* env, jobject obj)
	{

		OBJ = obj;
		ENV = env;

		CLS = env->GetObjectClass(OBJ);
		mid = env->GetMethodID(CLS,"toast","()V");
	
		LOG("accessField Complete");
	}

	JNIEXPORT void JNICALL Java_swssm_auidt_view_AUIDTView_nativeCreateLayout
		(JNIEnv* env, jobject thiz, jint objFlag,jint left, jint top, jfloat ratio, jint objSize)
	{
		main->layoutLoad(objFlag, left, top, ratio, objSize);
	}

	JNIEXPORT void JNICALL Java_swssm_auidt_view_AUIDTView_nativeCreateObject
		(JNIEnv* env, jobject thiz, jint objFlag, jintArray textureArr)
	{
		jint *temp = env->GetIntArrayElements(textureArr, 0);
		main->objectLoad(objFlag, temp);		
	}

	JNIEXPORT void JNICALL Java_swssm_auidt_view_AUIDTView_nativeDeleteLayout
		(JNIEnv* env, jobject thiz, jint pos)
	{
		main->layoutDelete(pos);
	}
	JNIEXPORT void JNICALL Java_swssm_auidt_view_AUIDTView_nativeDeleteObject
		(JNIEnv* env, jobject thiz, jint layoutpos, jint pos)
	{
		main->objectDelete(layoutpos, pos);
	}




	JNIEXPORT void JNICALL Java_swssm_auidt_view_AUIDTView_nativeSetSystemTextureData
		(JNIEnv* env, jobject thiz, jint id, jint textureId)
	{
		main->setSystemTextureData(id, textureId);

	}
	JNIEXPORT void JNICALL Java_swssm_auidt_view_AUIDTView_nativeCreateCustomObject
		(JNIEnv* env, jobject thiz, jintArray textureArr, 
		jint size, jfloatArray verts, jfloatArray normals, jfloatArray coords)
	{
		jint *temp = env->GetIntArrayElements(textureArr, 0);
		jfloat *temp1 = env->GetFloatArrayElements(verts, 0);
		jfloat *temp2 = env->GetFloatArrayElements(normals, 0);
		jfloat *temp3 = env->GetFloatArrayElements(coords, 0);

		main->customobjectLoad(temp, size, temp1, temp2, temp3);
	}

#ifdef __cplusplus
}
#endif

