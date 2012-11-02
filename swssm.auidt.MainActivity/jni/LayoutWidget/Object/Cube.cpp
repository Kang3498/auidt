class Cube:public Object{
private:
	int mode;
public:
	Cube();
	void setMode(int m);

	void draw();
	void drawLayoutAccessory();   //���̾ƿ��� ���� �ʼ������� �׷���� �� ť����� �����.
};

Cube::Cube(){
	objectType = 0;
	mode = 0;
}

void Cube::setMode(int m){
	mode = m;
}

void Cube::draw(){
	if(mode == 1){
		drawLayoutAccessory();
		return;
	}

	glPushMatrix();
	{		
		glTranslatef(X,Y,Z);

		glRotatef(rotateX,1.0f,0.0f,0.0f);
		glRotatef(rotateY,0.0f,1.0f,0.0f);
		glRotatef(rotateZ,0.0f,0.0f,1.0f);	

		glScalef(scaleX, scaleY, scaleZ);

		glVertexPointer(3, GL_FLOAT, 0, CubeVerts);
		glNormalPointer(GL_FLOAT, 0, CubeNormals);
		glTexCoordPointer(2, GL_FLOAT, 0, CubeTexCoords);

		// draw data
	
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		//glEnableClientState(GL_COLOR_ARRAY); 
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		{
			glFrontFace(GL_CW);

			//���鸶�� �ؽ��� �ѷ���
			std::vector<GLuint>::iterator it_textureData;
			std::vector<int>::iterator it_texturePosition;

			int i=0;

			//�ؽ��ĻѸ���
			for (it_textureData = textureData.begin(), it_texturePosition = texturePosition.begin() ; it_textureData != textureData.end() ; it_textureData++,it_texturePosition++, i++)
			{			
				glBindTexture(GL_TEXTURE_2D,(*it_textureData));
				glDrawArrays(GL_TRIANGLE_STRIP, (*it_texturePosition) * 6, CubeNumVerts/6);

			}
			

		}
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		//glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	}
	glPopMatrix();
}


void Cube::drawLayoutAccessory(){

	glPushMatrix();
	{

		glTranslatef(X,Y,Z);

		glRotatef(rotateX,1.0f,0.0f,0.0f);
		glRotatef(rotateY,0.0f,1.0f,0.0f);
		glRotatef(rotateZ,0.0f,0.0f,1.0f);

		glScalef(scaleX, scaleY, scaleZ);
		
		glVertexPointer(3, GL_FLOAT, 0, CubeVerts);
		glNormalPointer(GL_FLOAT, 0, CubeNormals);
		glTexCoordPointer(2, GL_FLOAT, 0, CubeTexCoords);

		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		{
			glFrontFace(GL_CW);


			//�ؽ��ĻѸ���
			std::vector<GLuint>::iterator it_textureData =  textureData.begin();

			glBindTexture(GL_TEXTURE_2D,(*it_textureData));
			glDrawArrays(GL_TRIANGLE_STRIP, 0, CubeNumVerts);

		}
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	glPopMatrix();
}
