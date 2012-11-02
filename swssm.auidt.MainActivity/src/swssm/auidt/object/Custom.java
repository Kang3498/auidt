package swssm.auidt.object;

import swssm.auidt.Constrants;
import android.content.Context;
import android.os.Handler;
import android.os.Message;

abstract public class Custom extends ObjLoader{

	public int[] mTexture;
	
	private Handler mFaceHandler = new Handler(){

		@Override
		public void handleMessage(Message msg) {
			// TODO Auto-generated method stub
			super.handleMessage(msg);
			
			//Log.e("< AUIDTViewLog >", "Custom handleMessage() In");
			SetOnFaceClickListener();
			//Log.e("< AUIDTViewLog >", "Custom handleMessage() Out");
		}		
	};
	
	public Custom(String filename, Context context) {
		super(filename, context);

		// TODO Auto-generated constructor stub
		mTexture = new int[1];
		SetFace(Constrants.auidt_system_default_custom);
	}
	
	// NDK���� ȣ���� �ϱ� ���� �Լ�
	public void SendFaceMessage() 
	{
		//Log.e("< AUIDTViewLog >", "Custom SendFaceMessage() In");
		mFaceHandler.sendEmptyMessage(0);
		//Log.e("< AUIDTViewLog >", "Custom SendFaceMessage() Out");
	}	
	
	// ��������ǿ�����Ʈ�� �ؽ�ó�� �����ϱ� ���� �Լ�
	public void SetFace(int textureID) { mTexture[0] = textureID; }

	// ��������ǿ�����Ʈ�� ���� Ŭ���̺�Ʈ ������ �Լ�
	abstract public void SetOnFaceClickListener();
}
