package swssm.auidt.view;

import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Vector;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import swssm.auidt.Constrants;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLSurfaceView;
import android.opengl.GLSurfaceView.Renderer;
import android.opengl.GLUtils;
import android.os.Handler;
import android.os.Message;
import android.view.MotionEvent;
import android.widget.DialLayout;
import android.widget.DockLayout;
import android.widget.RollLayout;
import android.widget.RotationLayout;
import android.widget.Toast;

public class AUIDTView extends GLSurfaceView implements Renderer {

	private Handler handler;
	private GL10 mGl;
	public int mWidth;
	public int mHeight;

	Context mContext;

	public enum LAYOUT {
		ROTATION, DOCK, DIAL, ROLL,
	};
	
	public enum SYSTEMTEXTURE {
		SCREENBACKGROUND, OBJECTDEFAULT, DOCKLAYOUT, DIALLAYOUT, MOUSEPARTICLE,
	};

	private Vector<RotationLayout> mRotaionLayout;
	private Vector<DockLayout> mDockLayout;
	private Vector<DialLayout> mDialLayout;
	private Vector<RollLayout> mRollLayout;

	// NATIVE �Լ�
	public static native void nativeCreated();
	public static native void nativeChanged(int w, int h);
	private static native void nativeUpdateGame();
	public static native void nativeOnTouchEvent(int x, int y, int touchFlag);
	public static native void nativeSetTextureData(int id, int[] pixels, int width, int height);
	public static native void nativeSetNumberOf();
	public static native void nativeCreateLayout(int layoutFlag, int left, int top, float ratio, int objSize);
	public static native void nativeCreateObject(int objFlag, int[] textureArr);
	public static native void nativeCreateCustomObject(int[] textureArr, int size, float[] verts, float[] normals, float[] coords);
	public static native void nativeSetCustomObject();
	public static native void nativeReset();
	private native void accessField();

	// =========================================== �¿��̰� ����� =====================================================

	private int isLogoDraw = 0;

	// id = 0 : Screen Background Image Texture
	// id = 1 : Object Default Image Texture
	// id = 2 : DockLayout Dock Image Texture
	// id = 3 : DialLayout Dial Image Texture
	// id = 4 : Mouse Particle Image Texture

	private ArrayList<Integer> system_texture_Data_ID = new ArrayList<Integer>();

	public static native void nativeSetSystemTextureData(int id, int textureID);

	public void setSystemTextureData(SYSTEMTEXTURE id, int textureId) {
		system_texture_Data_ID.set(id.ordinal(), textureId);
	}

	// 2�� �������� �ƴѰ�� ���� ����� 2�� �������� ã���ش�.
	public Bitmap setSuitableSize(Bitmap bmp) {
		int w = bmp.getWidth();
		int h = bmp.getHeight();
		int count_w = 0, count_h = 0;

		while (true) {
			count_w++;

			w /= 2;

			if (w == 1 || w == 0) {
				break;
			}
		}

		while (true) {
			count_h++;

			h /= 2;

			if (h == 1 || h == 0) {
				break;
			}
		}

		if (count_w > 10)
			count_w = 10;

		if (count_h > 10)
			count_h = 10;

		// Log.i("ImageSizeChange", bmp.getWidth() + "/" + bmp.getHeight() +
		// "->" + (int) Math.pow(2, count_w) + "/" + (int) Math.pow(2,
		// count_h));

		bmp = Bitmap.createScaledBitmap(bmp, (int) Math.pow(2, count_w), (int) Math.pow(2, count_h), true);

		return bmp;
	}

	// ===================================================================================================================

	// LIBRARY ȣ��
	static { System.loadLibrary("NDKLib"); }

	public AUIDTView(Context context) {
		super(context);
		this.setRenderer(this);
		this.requestFocus();
		this.setRenderMode(RENDERMODE_CONTINUOUSLY);
		this.setFocusableInTouchMode(true);

		nativeCreated();

		mContext = context;
 
		mRotaionLayout = new Vector<RotationLayout>();
		mDockLayout = new Vector<DockLayout>();
		mDialLayout = new Vector<DialLayout>();
		mRollLayout = new Vector<RollLayout>();

		handler = new Handler() {

			@Override
			public void handleMessage(Message msg) {

				Toast.makeText(getContext(), "Toast Success", Toast.LENGTH_SHORT).show();

				super.handleMessage(msg);
			}

		};
		
		system_texture_Data_ID.add(Constrants.auidt_system_default_background);
		system_texture_Data_ID.add(Constrants.auidt_system_default_docklayout1);
		system_texture_Data_ID.add(Constrants.auidt_system_default_docklayout1);
		system_texture_Data_ID.add(Constrants.auidt_system_default_wood);
		system_texture_Data_ID.add(Constrants.auidt_system_default_particle);
	}

	public void toast() {

		handler.sendEmptyMessage(0);
	}

	public void SetLayoutData(Object obj) {
		if (obj instanceof RotationLayout) { mRotaionLayout.add((RotationLayout)obj);}
		else if (obj instanceof DockLayout) { mDockLayout.add((DockLayout) obj); }
		else if (obj instanceof DialLayout) { mDialLayout.add((DialLayout) obj);	}
		else if (obj instanceof RollLayout) { mRollLayout.add((RollLayout) obj); }
	}

	public void SendTextureData() 
	{		
		for(int i=0; i<Constrants.class.getFields().length; ++i)
		{
			Bitmap bmp = BitmapFactory.decodeResource(mContext.getResources(), 0x7f020000 + i);

			bmp = setSuitableSize(bmp);

			int[] pixels = new int[bmp.getWidth() * bmp.getHeight()];
			bmp.getPixels(pixels, 0, bmp.getWidth(), 0, 0, bmp.getWidth(), bmp.getHeight());

			nativeSetTextureData(0x7f020000 + i, pixels, bmp.getWidth(), bmp.getHeight());			
		}

		for (int i = 0; i < system_texture_Data_ID.size(); i++) {
			nativeSetSystemTextureData(i, system_texture_Data_ID.get(i));
		}
	}

	public void SendLayout(LAYOUT layout) {

		switch (layout) {
		case ROTATION:
			Iterator<RotationLayout> rotationiter = mRotaionLayout.iterator();
			while (rotationiter.hasNext()) {
				RotationLayout rotation = (RotationLayout) rotationiter.next();
				rotation.SendLayout();
			}
			break;
		case DOCK:
			Iterator<DockLayout> dockiter = mDockLayout.iterator();
			while (dockiter.hasNext()) {
				DockLayout dock = (DockLayout) dockiter.next();
				dock.SendLayout();
			}
			break;
		case DIAL:
			Iterator<DialLayout> dialiter = mDialLayout.iterator();
			while (dialiter.hasNext()) {
				DialLayout dial = (DialLayout) dialiter.next();
				dial.SendLayout();
			}
			break;
		case ROLL:
			Iterator<RollLayout> rolliter = mRollLayout.iterator();
			while (rolliter.hasNext()) {
				RollLayout roll = (RollLayout) rolliter.next();
				roll.SendLayout();
			}
			break;
		default:
			break;
		}

	}
	
	public void DeleteRotationLayout()
	{
		mRotaionLayout.removeAllElements();
	}
	
	public void DeleteRotationLayout(RotationLayout layout)
	{
		mRotaionLayout.remove(layout);
	}
	
	public void DeleteDockLayout()
	{
		mDockLayout.removeAllElements();
	}
	
	public void DeleteDockLayout(DockLayout layout)
	{
		mDockLayout.remove(layout);
	}
	
	public void DeleteDialLayout()
	{
		mDialLayout.removeAllElements();
	}
	
	public void DeleteDialLayout(DialLayout layout)
	{
		mDialLayout.remove(layout);
	}
	
	public void DeleteRollLayout()
	{
		mRollLayout.removeAllElements();
	}
	
	public void DeleteRollLayout(RollLayout layout)
	{
		mRollLayout.remove(layout);
	}
	
	public void DeleteAllLayout()
	{		
		mRotaionLayout.removeAllElements();
		mDockLayout.removeAllElements();
		mDialLayout.removeAllElements();
		mRollLayout.removeAllElements();
		
		isLogoDraw = 2;
	}
	
	public void resetStart()
	{
		isLogoDraw = -1;
		nativeReset();
	}
	
	public void resetComplete()
	{
		isLogoDraw = 3;
	}

	FloatBuffer vertbuf;
	FloatBuffer textbuf;

	public void onDrawFrame(GL10 gl) {
		if (isLogoDraw == 0) {
			gl.glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
			gl.glClear(GL10.GL_COLOR_BUFFER_BIT | GL10.GL_DEPTH_BUFFER_BIT);
			// gl.glColor4f(1.0f, 1.0f, 0, 1.0f);
			gl.glMatrixMode(GL10.GL_MODELVIEW);
			gl.glLoadIdentity();

			float vert[] = { -1.0f, -1.0f, 0.0f,
					-1.0f, 1.0f, 0.0f, 
					1.0f, 1.0f, 0.0f,

			-1.0f, -1.0f, 0.0f, 
			1.0f, 1.0f, 0.0f, 
			1.0f, -1.0f, 0.0f, };

			float text[] = { 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,

			0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,

			};

			vertbuf = ArrayToBuffer(vert);
			textbuf = ArrayToBuffer(text);
			gl.glVertexPointer(3, GL10.GL_FLOAT, 0, vertbuf);
			gl.glTexCoordPointer(2, GL10.GL_FLOAT, 0, textbuf);

			gl.glDrawArrays(GL10.GL_TRIANGLES, 0, 6);

			isLogoDraw = 1; 

		} else if (isLogoDraw == 1) {

			SendTextureData();
			accessField();

			nativeChanged(mWidth, mHeight);

			isLogoDraw = 2;

		} else if (isLogoDraw == 2) {
			
			resetStart();
			SendLayout(LAYOUT.ROTATION);
			SendLayout(LAYOUT.DOCK);
			SendLayout(LAYOUT.DIAL);
			SendLayout(LAYOUT.ROLL);
			resetComplete();
			
		} else if (isLogoDraw == 3) {
			nativeUpdateGame();
		}

	}

	public FloatBuffer ArrayToBuffer(float[] ar) 
	{
		ByteBuffer bytebuf = ByteBuffer.allocateDirect(ar.length * 4);
		bytebuf.order(ByteOrder.nativeOrder());
		FloatBuffer buf = bytebuf.asFloatBuffer();
		buf.put(ar);
		buf.position(0);
		return buf;
	}

	public void onSurfaceChanged(GL10 gl, int width, int height) 
	{
		mGl = gl; mWidth = width; mHeight = height;
		gl.glViewport(0, 0, width, height);
	}

	public void onSurfaceCreated(GL10 gl, EGLConfig config) 
	{
		gl.glClearColor(0.2f, 0.2f, 0.2f, 1);
		gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);
		gl.glEnable(GL10.GL_DEPTH_TEST);
		gl.glEnable(GL10.GL_TEXTURE_2D);
		gl.glEnableClientState(GL10.GL_TEXTURE_COORD_ARRAY);
		
		InputStream stream = getResources().openRawResource(Constrants.auidt_system_default_logo);
		Bitmap bitmap = BitmapFactory.decodeStream(stream);
		try {
			stream.close();
		} catch (IOException e) {
			;
		}

		int[] textures = new int[1];
		gl.glGenTextures(1, textures, 0);
		gl.glBindTexture(GL10.GL_TEXTURE_2D, textures[0]);
		gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MIN_FILTER, GL10.GL_LINEAR);
		gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MAG_FILTER, GL10.GL_LINEAR);
		GLUtils.texImage2D(GL10.GL_TEXTURE_2D, 0, bitmap, 0);

		bitmap.recycle();
	}

	public void SendFaceMessage(int layout, int layoutindex, int object, int objectindex, int faceindex) 
	{
		switch (layout) {
		case 0:
			mRotaionLayout.elementAt(layoutindex).SendFaceMessage(object, objectindex, faceindex);
			break;
		case 1:
			mDockLayout.get(layoutindex).SendFaceMessage(object, objectindex, faceindex);
			break;
		case 2:
			mDialLayout.get(layoutindex).SendFaceMessage(object, objectindex, faceindex);
			break;
		case 3:
			mRollLayout.get(layoutindex).SendFaceMessage(object, objectindex, faceindex);
			break;
		default:
			break;
		}
	}

	@Override
	public boolean onTouchEvent(MotionEvent event) {	
		if(isLogoDraw == 3)
			nativeOnTouchEvent((int) event.getX(), (int) event.getY(), event.getAction());				
		return true;
	}
}
