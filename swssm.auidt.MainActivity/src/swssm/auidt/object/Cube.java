package swssm.auidt.object;

import swssm.auidt.Constrants;
import android.os.Handler;
import android.os.Message;

abstract public class Cube{
	
	/**������**/
	
	public int[] mTexture;
	
	private Handler mFaceHandler = new Handler(){

		@Override
		public void handleMessage(Message msg) {
			// TODO Auto-generated method stub
			super.handleMessage(msg);
			
			//Log.e("< AUIDTViewLog >", "Cube handleMessage() In");
			switch (msg.what) {
			case 0: SetOnFaceClickListener(0); break;
			case 1:	SetOnFaceClickListener(1); break;
			case 2:	SetOnFaceClickListener(2); break;
			case 3:	SetOnFaceClickListener(3); break;
			case 4: SetOnFaceClickListener(4); break;
			case 5:	SetOnFaceClickListener(5); break;
			default: break;
			}
			//Log.e("< AUIDTViewLog >", "Cube handleMessage() Out");
		}		
	};
	
	public Cube() {
		mTexture = new int[6];
		SetFace(Constrants.auidt_system_default_cube_a,
				Constrants.auidt_system_default_cube_b,
				Constrants.auidt_system_default_cube_c,
				Constrants.auidt_system_default_cube_d,
				Constrants.auidt_system_default_cube_e,
				Constrants.auidt_system_default_cube_f);
	}
	
	// NDK���� ȣ���� �ϱ� ���� �Լ�
	public void SendFaceMessage(int faceID) 
	{
		//Log.e("< AUIDTViewLog >", "Cube SendFaceMessage() In");
		mFaceHandler.sendEmptyMessage(faceID);
		//Log.e("< AUIDTViewLog >", "Cube SendFaceMessage() Out");
	}
		
	// ť���� �� �鿡 �ؽ�ó�� �����ϱ� ���� �Լ�
	public void SetFace(int texture1ID, int texture2ID, int texture3ID,
						int texture4ID, int texture5ID, int texture6ID)
	{
		mTexture[0] = texture1ID; mTexture[1] = texture2ID;
		mTexture[2] = texture3ID; mTexture[3] = texture4ID;
		mTexture[4] = texture5ID; mTexture[5] = texture6ID;
	}

	// ť���� �� �鿡 ���� Ŭ���̺�Ʈ ������ �Լ�
	abstract public void SetOnFaceClickListener(int ID);
}
