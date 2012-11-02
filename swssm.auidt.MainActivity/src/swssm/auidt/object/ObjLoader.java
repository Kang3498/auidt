package swssm.auidt.object;

import java.io.BufferedReader;

import java.io.DataInputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.nio.ShortBuffer;
import java.util.ArrayList;
import java.util.List;

import android.content.Context;

public class ObjLoader {

	public List<String> LINes;
	public float[] verticesX;
	public float[] verticesY;
	public float[] verticesZ;
	public float[] normalsX;
	public float[] normalsY;
	public float[] normalsZ;
	public float[] uvX;
	public float[] uvY;

	public float[] mVertices;
	public float[] mNormals;
	public float[] mUv;

	public int numVertices = 0;
	public int numNormals = 0;
	public int numUV = 0;
	public int numFaces = 0;

	short[] facesVerts;
	short[] facesNormals;
	short[] facesUV;
	int vertexIndex = 0;
	int normalIndex = 0;
	int uvIndex = 0;
	public int faceIndex = 0;
	ShortBuffer index;
	ShortBuffer mnormal;
	ShortBuffer text;
	FloatBuffer vertex;
	FloatBuffer normal;
	FloatBuffer texcoords;
	int textureId = -1;
	int ilength;

	boolean DEBUG = true;

	String mFilename;
	Context mContext;

	boolean isOpened = false;

	public ObjLoader(String filename, Context context) {

		mFilename = filename;
		mContext = context;

	}

	public void openObjFile() {
		if (!isOpened) {
			isOpened = true;

		} else {
			return;
		}
		
		//Log.e("<ObjLoader>", "openObjFile Out");

		LINes = openFile(mFilename, mContext); // opens the file
        
        verticesX = new float[LINes.size()];
        verticesY = new float[LINes.size()];
        verticesZ = new float[LINes.size()];
        normalsX = new float[LINes.size()];
        normalsY = new float[LINes.size()];
        normalsZ = new float[LINes.size()];
        uvX = new float[LINes.size()];
        uvY = new float[LINes.size()];
        
        facesVerts = new short[LINes.size() * 3];
        facesNormals = new short[LINes.size() * 3];
        facesUV = new short[LINes.size() * 3];

        for (int i = 0; i < LINes.size(); i++) {
            String line = LINes.get(i);
            if (line.startsWith("v ")) {
                String[] tokens = line.split("[ ]+");
                verticesX[vertexIndex] = Float.parseFloat(tokens[1]);
                verticesY[vertexIndex] = Float.parseFloat(tokens[2]);
                verticesZ[vertexIndex] = Float.parseFloat(tokens[3]);
                vertexIndex++;
                numVertices++;
                continue;
            }

            if (line.startsWith("vn ")) {
                String[] tokens = line.split("[ ]+");
                normalsX[normalIndex] = Float.parseFloat(tokens[1]);
                normalsY[normalIndex] = Float.parseFloat(tokens[2]);
                normalsZ[normalIndex] = Float.parseFloat(tokens[3]);
                normalIndex++;
                numNormals++;
                continue;
            }

            if (line.startsWith("vt")) {
                String[] tokens = line.split("[ ]+");
                uvX[uvIndex] = Float.parseFloat(tokens[1]);
                uvY[uvIndex] = Float.parseFloat(tokens[2]);
                uvIndex++;
                numUV++;
                continue;
            }  

            if (line.startsWith("f ")) {
                String[] tokens = line.split("[ ]+");
 
                String[] parts1 = tokens[1].split("/");
                facesVerts[faceIndex] = getIndexs(parts1[0], numVertices);
                if (parts1.length > 2)
                    facesNormals[faceIndex] = getIndexs(parts1[2], numNormals);
                if (parts1.length > 1)
                    facesUV[faceIndex] = getIndexs(parts1[1], numUV);                
                faceIndex++;

                String[] parts2 = tokens[2].split("/");
                facesVerts[faceIndex] = getIndexs(parts2[0], numVertices);
                if (parts2.length > 2)
                    facesNormals[faceIndex] = getIndexs(parts2[2], numNormals);
                if (parts2.length > 1)
                    facesUV[faceIndex] = getIndexs(parts2[1], numUV);
                faceIndex++;
 
                String[] parts3 = tokens[3].split("/");
                facesVerts[faceIndex] = getIndexs(parts3[0], numVertices);
                if (parts3.length > 2)
                    facesNormals[faceIndex] = getIndexs(parts3[2], numNormals);
                if (parts3.length > 1)
                    facesUV[faceIndex] = getIndexs(parts3[1], numUV);
                faceIndex++;
                numFaces++;
                
                if(tokens.length >= 5)
                {
                    facesVerts[faceIndex] = getIndexs(parts1[0], numVertices);
                    if (parts1.length > 2)
                        facesNormals[faceIndex] = getIndexs(parts1[2], numNormals);
                    if (parts1.length > 1)
                        facesUV[faceIndex] = getIndexs(parts1[1], numUV);                
                    faceIndex++;
                    
                	String[] parts4 = tokens[4].split("/");
                    facesVerts[faceIndex] = getIndexs(parts4[0], numVertices);
                    if (parts4.length > 2)
                        facesNormals[faceIndex] = getIndexs(parts4[2], numNormals);
                    if (parts4.length > 1)
                        facesUV[faceIndex] = getIndexs(parts4[1], numUV);
                    faceIndex++;                	
                    
                    facesVerts[faceIndex] = getIndexs(parts3[0], numVertices);
                    if (parts3.length > 2)
                        facesNormals[faceIndex] = getIndexs(parts3[2], numNormals);
                    if (parts3.length > 1)
                        facesUV[faceIndex] = getIndexs(parts3[1], numUV);
                    faceIndex++;
                    numFaces++;
                }
                continue;
            }
        }
        
        AverageScale();
        Obj2Opengl();
        
        //Log.e("<ObjLoader>", "openObjFile Out");
	}
	
	private float xSum, ySum, zSum;
	private float xMin, yMin, zMin;
	private float xMax, yMax, zMax;
	private float xCen, yCen, zCen;
	private float xDiff, yDiff, zDiff;
	private float scaleFac;
	
	private void AverageScale()
	{
		xSum = 0; ySum = 0; zSum = 0;
		
		for(int i=0; i<numVertices; ++i)
		{
			xSum += verticesX[i];
			ySum += verticesY[i];
			zSum += verticesZ[i];
			
			if(i==0)
			{
				 xMin = verticesX[i];
				 xMax = verticesX[i];
				 yMin = verticesY[i];
				 yMax = verticesY[i];
				 zMin = verticesZ[i];
				 zMax = verticesZ[i];
			}
			else
			{
				if(verticesX[i] < xMin)	xMin = verticesX[i];
				else if(verticesX[i] > xMax) xMax = verticesX[i];
				
				if(verticesY[i] < yMin)	yMin = verticesY[i];
				else if(verticesY[i] > yMax) yMax = verticesY[i];
				
				if(verticesZ[i] < zMin)	zMin = verticesZ[i];
				else if(verticesZ[i] > zMax) zMax = verticesZ[i];
			}			
		}
		
		xCen = xSum / numVertices;
		yCen = ySum / numVertices;
		zCen = zSum / numVertices;
		
		xDiff = xMax - xMin;
		yDiff = yMax - yMin;
		zDiff = zMax - zMin;
		
		if((xDiff >= yDiff) && (xDiff >= zDiff)) scaleFac = xDiff;
		else if((yDiff >= xDiff) && (yDiff >= zDiff)) scaleFac = yDiff;
		else scaleFac = zDiff;
		
		scaleFac = 1.0f / scaleFac;
	}

	private void Obj2Opengl() {
		 
		int count = 0, count2 = 0;
		mVertices = new float[faceIndex * 3];
		mNormals = new float[faceIndex * 3];
		mUv = new float[faceIndex * 2];
		  
		for(int i=0; i<faceIndex; ++i)
        {
        	mVertices[count] = (verticesX[facesVerts[i]] - xCen) * scaleFac;
        	mNormals[count] = normalsX[facesNormals[i]];
        	mUv[count2] = uvX[facesUV[i]];
        	++count; count2++;
        	
        	mVertices[count] = (verticesY[facesVerts[i]] - yCen) * scaleFac;
        	mNormals[count] = normalsY[facesNormals[i]];
        	mUv[count2] = 1 - uvY[facesUV[i]];
        	++count; count2++;
        	
        	mVertices[count] = (verticesZ[facesVerts[i]] - zCen) * scaleFac;
        	mNormals[count] = normalsZ[facesNormals[i]];
        	++count;
        }
	}

	private List<String> openFile(String filename, Context context) {

		//Log.e("<ObjLoader>", "openFile In");

		InputStream instream = null;

		List<String> LINes = new ArrayList<String>();

		try {
			instream = context.getAssets().open(filename);

			DataInputStream in = new DataInputStream(instream);
			BufferedReader br = new BufferedReader(new InputStreamReader(in));
			String strLINE;

			while ((strLINE = br.readLine()) != null) {
				LINes.add(strLINE);
			}

			br.close();
			in.close();
			instream.close();

		} catch (Exception e) {
			e.toString();
		}

		//Log.e("<ObjLoader>", "openFile Out");

		return LINes;
	}

	ShortBuffer createsBuffer(short[] indices) {

		ShortBuffer sbuffer;
		ByteBuffer ibb = ByteBuffer.allocateDirect(indices.length * 2);
		ibb.order(ByteOrder.nativeOrder());
		sbuffer = ibb.asShortBuffer();
		sbuffer.put(indices);
		sbuffer.position(0);
		return sbuffer;

	}

	FloatBuffer createfBuffer(float[] indices) {

		FloatBuffer fbuffer;
		ByteBuffer ibb = ByteBuffer.allocateDirect(indices.length * 4);
		ibb.order(ByteOrder.nativeOrder());
		fbuffer = ibb.asFloatBuffer();
		fbuffer.put(indices);
		fbuffer.position(0);
		return fbuffer;

	}

	short getIndexs(String index, int size) {
		short idx = Short.parseShort(index);
		if (idx < 0)
			return (short) (size + idx);
		else
			return (short) (idx - 1);
	}

	int getIndex(String index, int size) {
		int idx = Integer.parseInt(index);
		if (idx < 0)
			return size + idx;
		else
			return idx - 1;
	}
}