class CustomObject:public Object{
private:
public:
	CustomObject(int size, float *verts, float *normals, float *coords);
	void draw();
};

CustomObject::CustomObject(int size, float *verts, float *normals, float *coords){
	objectType = 3;

	customNumVerts = size;

	customVerts = verts;      //v
	customNormals = normals;    // vn
	customTexCoords = coords;  // vt
}

void CustomObject::draw(){
	glPushMatrix();
	{
		glTranslatef(X,Y,Z);
		
		glRotatef(rotateX,1.0f,0.0f,0.0f);
		glRotatef(rotateY,0.0f,1.0f,0.0f);
		glRotatef(rotateZ,0.0f,0.0f,1.0f);

		glScalef(scaleX, scaleY, scaleZ);
		
		glVertexPointer(3, GL_FLOAT, 0, customVerts);
		glNormalPointer(GL_FLOAT, 0, customNormals);
		glTexCoordPointer(2, GL_FLOAT, 0, customTexCoords);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY); 
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		{
			glFrontFace(GL_CW);

			//각면마다 텍스쳐 뿌려줌
			std::vector<GLuint>::iterator it_textureData;
			std::vector<int>::iterator it_texturePosition;

			int i=0;

			//텍스쳐뿌리기

			it_textureData = textureData.begin();	
			it_texturePosition = texturePosition.begin();
			
			glBindTexture(GL_TEXTURE_2D,(*it_textureData));
			
			glDrawArrays(GL_TRIANGLE_STRIP, 0, customNumVerts);

		}

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	glPopMatrix();
}