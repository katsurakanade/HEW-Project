#pragma once
#include "GameObject.h"


class Effect
{
	// �G�t�F�N�g�֐��̕ϐ��ێ�
	bool DoOnce_Move = true;
	int MyFancNum_Move = -1;     //�������g�̊֐��̐�����ێ�
	bool IsMove = false;     //Move���s���t���O
	float MoveSec = 0.0f;
	float MoveX = 0.0f;
	float MoveY = 0.0f;

	bool DoOnce_Curve = true;
	bool DoOnce_Curve2 = true;
	int MyFancNum_Curve = -1;     // �������g�̊֐��̐�����ێ�
	bool IsCurve = false;     // Curve���s���t���O
	bool CurveCW = true;     // ���v��� (false:�����v���)
	float CurveSize = 0.0f;
	float CurveSec = 0.0f;
	float CurveX = 0.0f;
	float CurveY = 0.0f;
	D3DXVECTOR2 VecA = { 0.0f, 0.0f };     // �����W���ړ�����W(�������ɕύX�����)
	float Rad = 0;     // �ʂ�`�����W�A���̒l

	bool DoOnce_Zoom = true;
	int MyFancNum_Zoom = -1;     //�������g�̊֐��̐�����ێ�
	bool IsZoom = false;     //Zoom���s���t���O
	float ZoomSec = 0.0f;
	double ZoomScale = 0.0f;

	bool DoOnce_Rot = true;
	int MyFancNum_Rot = -1;     //�������g�̊֐��̐�����ێ�
	bool IsRot = false;     //Rotate���s���t���O
	float RotSec = 0.0f;
	double RotRotate = 0.0f;

	bool DoOnce_Sleep = true;
	int MyFancNum_Sleep = -1;     //�������g�̊֐��̐�����ێ�
	float SleepCnt = 0;     //Sleep���Ԍv��
	bool IsSleep = false;     //Sleep���s���t���O
	float SleepSec = 0.0f;


public:
	// Draw(), �G�t�F�N�g�֐���
	GameObject obj;
	int aryNum = -1;     // ���g�̔z��ԍ�
	//bool IsUse = false;     // �g�p�t���O     IsUseMaxAryNum�X�V���Ɏg��
	bool IsDraw = false;     // �`��t���O (��{�I�ɃA�j���[�V�����I�����ɃG�t�F�N�g�͏����Ȃ����A�w�肷�鎖�ŃA�j���[�V�����I�����ɃG�t�F�N�g���������Ƃ��ł���)
	// �G�t�F�N�g���s(�e�p�[�e�B�N��)���I�������֐��̐�
	int FinishedFancNum = -1;
	// �G�t�F�N�g�����s(�e�p�[�e�B�N��)����Ō�̊֐��̐�
	int LastFancNum = 0;
	//Sleep�t���O(false:Sleep�ȍ~�̊֐��̎��s���~�߂�)
	bool SleepNow = true;
	// �A�j���[�V�����I������t���O
	bool lastSleepFlag = true;


	// �C���f�b�N�X�ϐ�
	const int E_MOVE = 0;
	const int E_CURVE = 1;
	const int E_ZOOM = 2;
	const int E_ROT = 3;


	Effect();
	Effect(Effect* pEft);
	virtual ~Effect();

	//�Q�[�����[�v
	void Init();
	void Uninit();
	void Update();
	void Draw();


	//// �G�t�F�N�g�֐��Q ////
	// ���g������Delay_�����Ɠ���
	// ���A�j���[�V�����I���O�ɓ����G�t�F�N�g�œ������O�̊֐����Ăяo���Ə�񂪏㏑�������(�O�̃A�j���[�V�����𒆒f���ĐV�����A�j���[�V�������Đ����n�߂�)

	// �����ړ�(����,x,y)
	void Move(float sec, float x, float y);

	// �Ȑ��ړ�(���v���==true, �Ȑ��̌ʂ̑傫��(0.0f~10.0f���x), ����, x, y)
	void Curve(bool cw, float CurveSize, float sec, float x, float y);

	// �g��k��(����,�g�嗦)
	void Zoom(float sec, double scale);

	// ��](����,��]�p�x)
	void Rotate(float sec, double rotate);

	// �G�t�F�N�g�Đ��҂��֐� (�҂�����)
	void Sleep(float sec);

	// �G�t�F�N�g�Đ��ŏI�҂��֐� (�҂�����)
	void LastSleep(float sec);
	
};
