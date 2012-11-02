package swssm.auidt.object;

import swssm.auidt.Constrants;
import android.os.Handler;
import android.os.Message;

abstract public class Flat{

	public int[] mTexture;
	
	private Handler mFaceHandler = new Handler(){

		@Override
		public void handleMessage(Message msg) {
			// TODO Auto-generated method stub
			super.handleMessage(msg);
			
			//Log.e("< AUIDTViewLog >", "Flat handleMessage() In");
			SetOnFaceClickListener();
			//Log.e("< AUIDTViewLog >", "Flat handleMessage() Out");
		}		
	};
	
	public Flat() {
		mTexture = new int[1];
		SetFace(Constrants.auidt_system_default_flat);
	}
	
	// NDK���� ȣ���� �ϱ� ���� �Լ�
	public void SendFaceMessage()
	{
		//Log.e("< AUIDTViewLog >", "Flat SendFaceMessage() In");
		mFaceHandler.sendEmptyMessage(0);
		//Log.e("< AUIDTViewLog >", "Flat SendFaceMessage() Out");
	}	
	
	// �鿡 �ؽ�ó�� �����ϱ� ���� �Լ�
	public void SetFace(int textureID) { mTexture[0] = textureID; }

	// �鿡 ���� Ŭ���̺�Ʈ ������ �Լ�
	abstract public void SetOnFaceClickListener();
}
