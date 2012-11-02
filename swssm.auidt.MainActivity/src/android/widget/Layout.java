package android.widget;

import java.util.Iterator;
import java.util.Vector;

import swssm.auidt.object.Circle;
import swssm.auidt.object.Cube;
import swssm.auidt.object.Custom;
import swssm.auidt.object.Flat;
import swssm.auidt.view.AUIDTView;
import android.content.Context;
import android.util.AttributeSet;

public class Layout extends ImageView {
	
	public int mLeft;
	public int mTop;
	public float mSize;

	public Vector<Object> mObjArray;	

	public Layout(Context context) {
		super(context);
		initRect();
	}

	public Layout(Context context, AttributeSet attrs) {
		this(context, attrs, 0);
	}

	public Layout(Context context, AttributeSet attrs, int defStyle) {		
		super(context, attrs, defStyle);
		initRect();
	}

	public void initRect() {		
		mObjArray = new Vector<Object>();
	}

	public void AddObject(Object obj) {		
		if (mObjArray.size() >= 5)
			return;

		if (obj instanceof Cube) {
			mObjArray.add((Cube) obj);
		} else if (obj instanceof Flat) {
			mObjArray.add((Flat) obj);
		} else if (obj instanceof Circle) {
			mObjArray.add((Circle) obj);
		} else if (obj instanceof Custom) {
			mObjArray.add((Custom) obj);
		}
	}

	public void SendFaceMessage(int object, int objectindex, int faceindex) {
		switch (object) {
		case 0:
			// Log.e("< AUIDTViewLog >", "Cube In");
			Cube cube = (Cube) mObjArray.get(objectindex);
			cube.SendFaceMessage(faceindex);
			// Log.e("< AUIDTViewLog >", "Cube Out");
			break;
		case 1:
			// Log.e("< AUIDTViewLog >", "Flat In");
			Flat flat = (Flat) mObjArray.get(objectindex);
			flat.SendFaceMessage();
			// Log.e("< AUIDTViewLog >", "Flat Out");
			break;
		case 2:
			// Log.e("< AUIDTViewLog >", "Circle In");
			Circle circle = (Circle) mObjArray.get(objectindex);
			circle.SendFaceMessage();
			// Log.e("< AUIDTViewLog >", "Circle Out");
			break;
		case 3:
			// Log.e("< AUIDTViewLog >", "Custom In");
			Custom custom = (Custom) mObjArray.get(objectindex);
			custom.SendFaceMessage();
			// Log.e("< AUIDTViewLog >", "Custom Out");
			break;
		default:
			break;
		}
	}

	public void SendLayoutData(int layout, int left, int top, float size) {
		// AUIDTView.nativeCreateLayout(layout,
		// 0,
		// 0,
		// 1.0f,
		// mObjArray.size());
		AUIDTView.nativeCreateLayout(layout, left, top, size,// rect.width()
																		// /
																		// this.getWidth(),
				mObjArray.size());

		Iterator<Object> objiter = mObjArray.iterator();
		while (objiter.hasNext()) {
			Object obj = (Object) objiter.next();
			// Cube
			if (obj instanceof Cube) {
				Cube cube = (Cube) obj;
				AUIDTView.nativeCreateObject(0, cube.mTexture);
			}
			// Flat
			else if (obj instanceof Flat) {
				Flat flat = (Flat) obj;
				AUIDTView.nativeCreateObject(1, flat.mTexture);
			}
			// Circle
			else if (obj instanceof Circle) {
				Circle circle = (Circle) obj;
				AUIDTView.nativeCreateObject(2, circle.mTexture);
			}
			// Custom
			else if (obj instanceof Custom) {
				Custom custom = (Custom) obj;
				custom.openObjFile();
				AUIDTView.nativeCreateCustomObject(custom.mTexture,
						custom.faceIndex, custom.mVertices, custom.mNormals,
						custom.mUv);
			}
		}
	}
	
	@Override
	protected void onMeasure(int widthSpec, int heightSpec) {	
		super.onMeasure(widthSpec, heightSpec);
	}
	
	@Override
	protected void onLayout(boolean changed, int l, int t, int r, int b) {	
		super.onLayout(changed, l, t, r, b);
	}
}
