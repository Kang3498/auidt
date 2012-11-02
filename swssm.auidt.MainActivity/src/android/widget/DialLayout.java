package android.widget;

import android.content.Context;
import android.util.AttributeSet;

public class DialLayout extends Layout{
	
	public DialLayout(Context context) {
		super(context);
		init();
	}
	
	public DialLayout(Context context, AttributeSet attrs) {
		this(context, attrs, 0);
	}

	public DialLayout(Context context, AttributeSet attrs, int defStyle) {
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
		super.SendLayoutData(2, mLeft, mTop, mSize);
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
