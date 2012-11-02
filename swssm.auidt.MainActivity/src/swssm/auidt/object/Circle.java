package swssm.auidt.object;

import swssm.auidt.Constrants;
import android.os.Handler;
import android.os.Message;

abstract public class Circle{

	public int[] mTexture;
	
	private Handler mFaceHandler = new Handler(){

		@Override
		public void handleMessage(Message msg) {
			// TODO Auto-generated method stub
			super.handleMessage(msg);
			
			//Log.e("< AUIDTViewLog >", "Circle handleMessage() In");
			SetOnFaceClickListener();
			//Log.e("< AUIDTViewLog >", "Circle handleMessage() Out");
		}		
	};
	
	public Circle() {
		// TODO Auto-generated constructor stub
		mTexture = new int[1];
		SetFace(Constrants.auidt_system_default_sphere);
	}
	
	// NDK���� ȣ���� �ϱ� ���� �Լ�
	public void SendFaceMessage() 
	{
		//Log.e("< AUIDTViewLog >", "Circle SendFaceMessage() In");
		mFaceHandler.sendEmptyMessage(0);
		//Log.e("< AUIDTViewLog >", "Circle SendFaceMessage() In");
	}	
	
	// ���� �ؽ�ó�� �����ϱ� ���� �Լ�
	public void SetFace(int textureID) { mTexture[0] = textureID; }

	// ���� ���� Ŭ���̺�Ʈ ������ �Լ�
	abstract public void SetOnFaceClickListener();
}
