#include "effect.h"

GameObject eft[15];


static GameObject eftt[6];//��
static GameObject ef[6];//��

int k;
int n;
int h;

void effEct::Init()
{
	//flag�ݒ�
	//��
	eft[0].SetDelayFlag(0);
	eft[1].SetDelayFlag(0);
	eft[2].SetDelayFlag(0);
	eft[3].SetDelayFlag(0);
	//���@�w
	eft[4].SetDelayFlag(1);
	eft[4].SetDelayFlag(2);

	//�t�B�[�A�{�[��
	eft[5].SetDelayFlag(0);
	eft[6].SetDelayFlag(0);
	eft[7].SetDelayFlag(0);
	eft[8].SetDelayFlag(0);





	


	
	//�ʐ^
	eft[0].LoadTexture(TexturePassDict[TEXTURE_INDEX_EFFECT]);
	eft[1].LoadTexture(TexturePassDict[TEXTURE_INDEX_EFFECT]);
	eft[2].LoadTexture(TexturePassDict[TEXTURE_INDEX_EFFECT]);
	eft[3].LoadTexture(TexturePassDict[TEXTURE_INDEX_EFFECT]);
	//���@�w
	eft[4].LoadTexture(TexturePassDict[TEXTURE_INDEX_MAHOU]);
	//�t�B�[�A�{�[��
	eft[5].LoadTexture(TexturePassDict[TEXTURE_INDEX_HUOYAN]);
	eft[6].LoadTexture(TexturePassDict[TEXTURE_INDEX_HUOYAN]);
	eft[7].LoadTexture(TexturePassDict[TEXTURE_INDEX_HUOYAN]);
	eft[8].LoadTexture(TexturePassDict[TEXTURE_INDEX_HUOYAN]);



	//�傫��
    //��
	eft[0].Object.Scale.x = 0.05;
	eft[0].Object.Scale.y = 0.05;

	eft[1].Object.Scale.x = 0.05;
	eft[1].Object.Scale.y = 0.05;

	eft[2].Object.Scale.x = 0.05;
	eft[2].Object.Scale.y = 0.05;

	eft[3].Object.Scale.x = 0.05;
	eft[3].Object.Scale.y = 0.05;
	//�t�B�[�A�{�[��-------------------------------------
	eft[5].Object.Scale.x = 0.1;
	eft[5].Object.Scale.y = 0.1;

	eft[6].Object.Scale.x = 0.1;
	eft[6].Object.Scale.y = 0.1;

	eft[7].Object.Scale.x = 0.1;
	eft[7].Object.Scale.y = 0.1;

	eft[8].Object.Scale.x = 0.1;
	eft[8].Object.Scale.y = 0.1;
	//���@�w-------------------------------------
	eft[4].Object.Scale.x = 0.1;
	eft[4].Object.Scale.y = 0.1;

	//�F
	//eft[0].Color.saturation = 1.0f;

	//�ʒu
	//��
	//�E��
	eft[0].Object.Pos.x = 500;
	eft[0].Object.Pos.y = 300;
	//�E��
    eft[1].Object.Pos.x = 500;
	eft[1].Object.Pos.y = 500;
	//����
	eft[2].Object.Pos.x = 300;
	eft[2].Object.Pos.y = 300;
	//����
	eft[3].Object.Pos.x = 300;
	eft[3].Object.Pos.y = 500;
	//���@�w----------------------------
	

	eft[4].Object.Pos.x = 400;
	eft[4].Object.Pos.y = 400;
	//�t�B�[�A�{�[��------------------------------
	//�E
	eft[5].Object.Pos.x = 500;
	eft[5].Object.Pos.y = 400;
	//��
	eft[6].Object.Pos.x = 300;
	eft[6].Object.Pos.y = 400;
	//��
	eft[7].Object.Pos.x = 400;
	eft[7].Object.Pos.y = 300;
	//��
	eft[8].Object.Pos.x = 400;
	eft[8].Object.Pos.y = 500;


}

void effEct::Update()
{
	//������
	float a = 0.0f;
	float b = 0.0f;

	effEct fuck;

	//�ړ�
	if (keyboard.IsTrigger(DIK_B))
	{
		k = true;		
	}
	if (k)
	{
		//�E��
		a = eft[0].Object.Pos.x;
		b = eft[0].Object.Pos.y;

		eft[0].Delay_Move(3, 5.0, 500.0f, 0.0f);//�E�ړ�
		if (a < 600)
		{			
			eft[0].Delay_Move(0, 5.0, 0.0f, -500.0f);			
		}

		//�E��
		a = eft[1].Object.Pos.x;
		b = eft[1].Object.Pos.y;
		
		eft[1].Delay_Move(3, 5.0, 500.0f, 0.0f);
		if (a < 600)
		{
			eft[1].Delay_Move(0, 5.0, 0.0f, 500.0f);
		}
		//����
		a = eft[2].Object.Pos.x;
		b = eft[2].Object.Pos.y;

		eft[2].Delay_Move(2, 5.0, -500.0f, 0.0f);

		if (a>200)
		{
			eft[2].Delay_Move(0, 5.0, 0.0f, -500.0f);
		}

		
		//����
		a = eft[3].Object.Pos.x;
		b = eft[3].Object.Pos.y;

		eft[3].Delay_Move(2, 5.0, -500.0f, 0.0f);
		if (a > 200)
		{
			eft[3].Delay_Move(0, 5.0, 0.0f, 500.0f);
		}
		
		fuck.IsDraw = true;
	}

	
	//�t�B�[�A�{�[��-------------------------------------------------
	//�ړ�
	if (keyboard.IsTrigger(DIK_N))
	{
		n = true;
	}
	if (n)
	{
		//�E
		eft[5].Delay_Move(3, 5.0, 500.0f, 0.0f);
		//��
		eft[6].Delay_Move(2, 5.0, -500.0f, 0.0f);
		//��
		eft[7].Delay_Move(0, 5.0, 0.0f, -500.0f);
		//��
		eft[8].Delay_Move(1, 5.0, 0.0f, 500.0f);




		fuck.IsDraw = true;


	}
	//���@�w------------------------------------------------

	if (keyboard.IsTrigger(DIK_M))
	{
		h = true;
	}
	if (h)
	{

		eft[4].Delay_Zoom(5.0, 2.0);
		eft[4].Delay_Rotate(5.0, 360);
		fuck.IsDraw = true;

	}
	




	//eft[0].Delay_Move(3, 3.0, 50.0f, 0.0f);
	//�g��
	//eft[0].Delay_Zoom(5.0f, 2.0);
	//��]
	//eft[0].Delay_Rotate(5.0, 360);
	//eft[0].Color.saturation -= 0.1f;	
}

void effEct::Draw()
{
	//����
	eft[0].Draw();
	eft[1].Draw();
	eft[2].Draw();
	eft[3].Draw();
	//���@�w
	eft[4].Draw();
	//�t�B�[�A�{�[��
	eft[5].Draw();
	eft[6].Draw();
	eft[7].Draw();
	eft[8].Draw();
	//




	


}

effEct::effEct()
{
}

effEct::~effEct()
{
}








