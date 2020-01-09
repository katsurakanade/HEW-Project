/*
		�G�t�F�N�g�p�[�e�B�N������
		���� �q�T
*/


#include <algorithm>
#include <vector>
#include "Effect.h"
#include "EffectGame.h"


//EffectGame�̃����o�ɐG��ׂ̕ϐ�
static EffectGame* peg;


Effect::Effect()
{
}

Effect::Effect(Effect* pEft)
{
	// �q�N���X�̃����o�ɐG��ׂ̑��� //
	peg = (EffectGame*)pEft;
	// �q�N���X�̃����o�ɐG��ׂ̑��� //
	aryNum = peg->MaxAryNum;     // �������g�̔z��ԍ��m��
	peg->MaxAryNum++;
}
Effect::~Effect()
{
	peg->MaxAryNum--;
	aryNum = -1;
}

//�Q�[�����[�v
void Effect::Init()
{
}
void Effect::Uninit()
{
}
void Effect::Update()
{
}
void Effect::Draw()
{
}



//// �G�t�F�N�g�֐��Q ////
// ���g������Delay_�����Ɠ���
// ���A�j���[�V�����I���O�ɓ����G�t�F�N�g�œ������O�̊֐����Ăяo���Ə�񂪏㏑�������(�O�̃A�j���[�V�����𒆒f���ĐV�����A�j���[�V�������Đ����n�߂�)

// �����ړ�(����,x,y)
void Effect::Move(float sec, float x, float y)
{

	if (FinishedFancNum < MyFancNum_Move && this->MoveSec == sec && this->MoveX == x && this->MoveY == y     // �܂��I�����ĂȂ��G�t�F�N�g�Đ�
		|| this->SleepNow && MyFancNum_Move == -1)     // Sleep������Ȃ� && ����Ŏ��s
	{
		if (DoOnce_Move)     // ���񏈗�
		{
			//IsUse = true;     // �g�p�t���O
			this->IsDraw = true;     // �`��t���O
			this->MoveSec = sec;     //�l�ێ�
			this->MoveX = x;     //�l�ێ�
			this->MoveY = y;     //�l�ێ�
			this->obj.SetDelayFlag(E_MOVE);     // Delay�t���O�𗧂Ă�
			LastFancNum++;     //�֐��̌��J�E���g
			MyFancNum_Move = LastFancNum;     // �����̊֐��̐�����ێ�
			DoOnce_Move = false;
		}

		if (this->obj.Delay_Move(this->MoveSec, this->MoveX, this->MoveY))     // �G�t�F�N�g�Đ�
		{
			// �I��������
			if (FinishedFancNum == -1)
			{
				FinishedFancNum = 1;
			}
			else
			{
				FinishedFancNum++;
			}
			//IsUse = false;     // �g�p�t���O
			DoOnce_Move = true;
			MyFancNum_Move = -1;

			/*
			if(DrawEnd(�f�t�H���g�l����))     //�`��I��
			{
				IsDraw = false;
			}
			*/

		}

	}// if (FinishedFancNum < MyFancNum_Move || this->SleepNow && MyFancNum_Move == -1)

}

// �Ȑ��ړ�(�����v���==true, �Ȑ��̌ʂ̑傫��(0.0f~10.0f���x), ����, x, y)
void Effect::Curve(bool cw, float curveSize, float sec, float x, float y)
{
	
	if (FinishedFancNum < MyFancNum_Curve && this->CurveCW == cw && this->CurveSize == curveSize && this->CurveSec == sec && this->CurveX == x && this->CurveY == y      // �܂��I�����ĂȂ� && �㏑������Ȃ��G�t�F�N�g�Đ�
		|| this->SleepNow && MyFancNum_Curve == -1)     // Sleep������Ȃ� && ����Ŏ��s
	{
		if (DoOnce_Curve)     // ���񏈗�
		{
			//IsUse = true;     // �g�p�t���O
			this->IsDraw = true;     // �`��t���O
			this->CurveCW = cw;
			this->CurveSize = curveSize;
			this->CurveSec = sec;
			this->CurveX = x;
			this->CurveY = y;
			this->VecA = { this->CurveX , this->CurveY };
			this->obj.SetDelayFlag(E_CURVE);     // Delay�t���O�𗧂Ă�
			LastFancNum++;     //�֐��̌��J�E���g
			MyFancNum_Curve = LastFancNum;     // �����̊֐��̐�����ێ�
			DoOnce_Curve = false;
		}
		
		// �G�t�F�N�g�Đ�
		if (this->obj.Delay_CurveMove(this->CurveCW, this->CurveSize, this->CurveSec, this->VecA, this->Rad))
		{     // �I��������
			if (FinishedFancNum == -1)
			{
				FinishedFancNum = 1;
			}
			else
			{
				FinishedFancNum++;
			}
			//IsUse = false;
			DoOnce_Curve = true;
			MyFancNum_Curve = -1;
		}

	}// if (FinishedFancNum < MyFancNum_Curve || this->SleepNow && MyFancNum_Curve == -1)

}

// �g��k��(����,�g�嗦)     ���g�嗦�̂Ƃ��낪��������
void Effect::Zoom(float sec, double scale)
{

	if (FinishedFancNum < MyFancNum_Zoom && this->ZoomSec == sec && this->ZoomScale == scale     // �܂��I�����ĂȂ��G�t�F�N�g�Đ�
		|| this->SleepNow && MyFancNum_Zoom == -1)     // Sleep������Ȃ� && ����Ŏ��s
	{
		if (DoOnce_Zoom)     // ���񏈗�
		{
			//IsUse = true;     // �g�p�t���O
			this->IsDraw = true;     // �`��t���O
			this->ZoomSec = sec;
			this->ZoomScale = scale;
			this->obj.SetDelayFlag(E_ZOOM);     // Delay�t���O�𗧂Ă�
			LastFancNum++;     //�֐��̌��J�E���g
			MyFancNum_Zoom = LastFancNum;     // �����̊֐��̐�����ێ�
			DoOnce_Zoom = false;
		}

		// �G�t�F�N�g�Đ�
		if (this->obj.Delay_Zoom(this->ZoomSec, this->ZoomScale))
		{     // �I��������
			if (FinishedFancNum == -1)
			{
				FinishedFancNum = 1;
			}
			else
			{
				FinishedFancNum++;
			}
			//IsUse = false;
			DoOnce_Zoom = true;
			MyFancNum_Zoom = -1;
		}

	}// if (FinishedFancNum < MyFancNum_Zoom || this->SleepNow && MyFancNum_Zoom == -1)

}

// ��](����,��]�p�x)     // ��]�p�x���}�C�i�X���肵�Ȃ�
void Effect::Rotate(float sec, double rotate)
{

	if (FinishedFancNum < MyFancNum_Rot && this->RotSec == sec && this->RotRotate == rotate     // �܂��I�����ĂȂ��G�t�F�N�g�Đ�
		|| this->SleepNow && MyFancNum_Rot == -1)     // Sleep������Ȃ� && ����Ŏ��s
	{
		if (DoOnce_Rot)     // ���񏈗�
		{
			//IsUse = true;     // �g�p�t���O
			this->IsDraw = true;     // �`��t���O
			this->RotSec = sec;
			this->RotRotate = rotate;
			this->obj.SetDelayFlag(E_ROT);     // Delay�t���O�𗧂Ă�
			LastFancNum++;     //�֐��̌��J�E���g
			MyFancNum_Rot = LastFancNum;     // �����̊֐��̐�����ێ�
			DoOnce_Rot = false;
		}

		// �G�t�F�N�g�Đ�
		if (this->obj.Delay_Rotate(this->RotSec, this->RotRotate))
		{     // �I��������
			if (FinishedFancNum == -1)
			{
				FinishedFancNum = 1;
			}
			else
			{
				FinishedFancNum++;
			}
			//IsUse = false;
			DoOnce_Rot = true;
			MyFancNum_Rot = -1;
		}

	}// if (FinishedFancNum < MyFancNum_Rot || this->SleepNow && MyFancNum_Rot == -1)

}

// �G�t�F�N�g�Đ��҂��֐� (�҂�����)
void Effect::Sleep(float sec)
{
	if (FinishedFancNum < MyFancNum_Sleep && this->SleepSec == sec     // �܂��I�����ĂȂ��G�t�F�N�g�Đ�
		|| MyFancNum_Sleep == -1)     // ����Ŏ��s
	{
		if (DoOnce_Sleep)     // ���񏈗�
		{
			this->SleepNow = false;
			this->lastSleepFlag = false;
			this->SleepSec = sec;
			LastFancNum++;     // �֐��̌��J�E���g
			MyFancNum_Sleep = LastFancNum;     // �����̊֐��̐�����ێ�
			DoOnce_Sleep = false;
		}


		this->SleepCnt += SECONDS;     // Sleep���Ԍv��

		if (this->SleepCnt >= this->SleepSec)     // Sleep�I������
		{
			this->SleepCnt = 0;
			this->SleepNow = true;
			if (FinishedFancNum == -1)
			{
				FinishedFancNum = 1;
			}
			else
			{
				FinishedFancNum++;
			}
			DoOnce_Sleep = true;
			MyFancNum_Sleep = -1;
		}

	}// if (FinishedFancNum < MyFancNum_Sleep || this->SleepNow && MyFancNum_Sleep == -1)

}


// �G�t�F�N�g�Đ��ŏI�҂��֐� (�҂�����)
void Effect::LastSleep(float sec)
{
	if (FinishedFancNum < MyFancNum_Sleep && this->SleepSec == sec     // �܂��I�����ĂȂ��G�t�F�N�g�Đ�
		|| MyFancNum_Sleep == -1)     // ����Ŏ��s
	{
		if (DoOnce_Sleep)     // ���񏈗�
		{
			this->SleepNow = false;
			this->SleepSec = sec;
			LastFancNum++;     // �֐��̌��J�E���g
			MyFancNum_Sleep = LastFancNum;     // �����̊֐��̐�����ێ�
			DoOnce_Sleep = false;
		}


		this->SleepCnt += SECONDS;     // Sleep���Ԍv��

		if (this->SleepCnt >= this->SleepSec)     // Sleep�I������
		{
			this->lastSleepFlag = true;
			if (FinishedFancNum == -1)
			{
				FinishedFancNum = 1;
			}
			else
			{
				FinishedFancNum++;
			}
		}

	}// if (FinishedFancNum < MyFancNum_Sleep || this->SleepNow && MyFancNum_Sleep == -1)

}




