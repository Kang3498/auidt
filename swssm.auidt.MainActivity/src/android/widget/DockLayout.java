package android.widget;

import android.content.Context;
import android.util.AttributeSet;

public class DockLayout extends Layout{
	
	public DockLayout(Context context) {
		super(context);
		init();
	}
	
	public DockLayout(Context context, AttributeSet attrs) {
		this(context, attrs, 0);
	}

	public DockLayout(Context context, AttributeSet attrs, int defStyle) {
		super(context, attrs, defStyle);
		init();
	}
	
	public void init(){
		mLeft = 0;
		mTop = 0;
		mSize = 1.0f;
	}
	
	public void SendLayout()
	{
		super.SendLayoutData(1, mLeft, mTop, mSize);
	}	
	
	@Override
	protected void onMeasure(int widthSpec, int heightSpec) {	
		super.onMeasure(widthSpec, heightSpec);
	}	
}
