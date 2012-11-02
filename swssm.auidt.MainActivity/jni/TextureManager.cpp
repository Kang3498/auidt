
class TextureManager{
private:
	JNIEnv* env;
	jobject obj;

	std::vector<GLuint> textureData;
	std::vector<int> textureId;

	std::vector<GLuint> System_TextureData_Id;
	std::vector<int> System_Texture_Id;
public:
	TextureManager();

	void getContext(JNIEnv* env, jobject obj);

	void addTexture(int id, char *data, int width, int height);
	void addTexture_System(int id, int textureId);

	GLuint getTextureData(int id);
	GLuint getTextureData_System(int id);
};

TextureManager::TextureManager(){

}
void TextureManager::getContext(JNIEnv* env, jobject obj){

}

void TextureManager::addTexture(int id, char *data, int width, int height){

	GLuint mTexture =0;
	int i;
	char *buf;

	buf = (char *)malloc((sizeof(char)*width*height)<<2);

	for (i = 0; i < width*height*4; i += 4)
	{

		buf[i]   = data[i+2];
		buf[i+1] = data[i+1];
		buf[i+2] = data[i];
		buf[i+3] = data[i+3];
		
	}

	glGenTextures(1, &mTexture);

	glBindTexture(GL_TEXTURE_2D, mTexture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)buf);

	free(buf);
	textureData.push_back(mTexture);
	textureId.push_back(id);
}

void TextureManager::addTexture_System(int id, int textureId){
	LOG("id : %d, t_id : %d", id , textureId);

	System_Texture_Id.push_back(id);

	System_TextureData_Id.push_back(this->getTextureData(textureId));

}

GLuint TextureManager::getTextureData(int id){
	std::vector<GLuint>::iterator it_textureData;
	std::vector<int>::iterator it_textureId;

	for (it_textureData = textureData.begin(), it_textureId = textureId.begin() ; it_textureData != textureData.end() ; it_textureData++,it_textureId++)
	{	
		if((*it_textureId) == id){
		
			return (*it_textureData);
		}
	}
	return 0;
}

GLuint TextureManager::getTextureData_System(int id){
	std::vector<GLuint>::iterator it_textureData;
	std::vector<int>::iterator it_textureId;

	for (it_textureData = System_TextureData_Id.begin(), it_textureId = System_Texture_Id.begin() ; it_textureData != System_TextureData_Id.end() ; it_textureId++, it_textureData++)
	{	
		if((*it_textureId) == id){
	
			return (*it_textureData);
		}
	}
	return 0;
}