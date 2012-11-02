package swssm.auidt.activity;

import java.util.Vector;

import swssm.auidt.view.AUIDTView;
import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Layout;
import android.widget.AbsoluteLayout.LayoutParams;

public class AUIDTActivity extends Activity {

	public AUIDTView mAUIDTView;
	private Vector<Integer> idArray;	
	public boolean init_5 = true;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		idArray = new Vector<Integer>();
		mAUIDTView = new AUIDTView(getApplicationContext());		
	}

	@Override
	public View findViewById(int id) {
		idArray.add(id);	
		return super.findViewById(id);
	}
	
	public void myman(View view) {
		for(int i = 0 ; i < idArray.size() ; i++){
			Layout tmp =  (Layout)super.findViewById(idArray.get(i));						
			LayoutParams tmp2 = (LayoutParams) tmp.getLayoutParams();			
			tmp.mLeft = tmp2.x;	
			tmp.mTop = tmp2.y;
			tmp.mSize = (float)((float)tmp.getWidth() / (float)800.0f);
			if(tmp.mSize > 1.0f)
				tmp.mSize = 1.0f;
			mAUIDTView.SetLayoutData(tmp);
		}		
		super.setContentView(view);
	}
	
	@Override
	public void onWindowFocusChanged(boolean hasFocus) {
		// TODO Auto-generated method stub
		super.onWindowFocusChanged(hasFocus);		
		if(hasFocus && init_5){
			init_5 = false;
			myman(mAUIDTView);
		}
	}
}
