#pragma once


void EffectInit();
void EffectUpdate();
void EffectDraw();


// �܂��g�p�ł��Ȃ�
class Effect
{
	// �ϐ��錾
	GameObject obj;     // Draw()��
	GameData data;     // �X�e�[�g
	bool IsUse = false;     // �g�p�t���O
	bool IsDraw = false;     // �`��t���O (��{�I�ɃA�j���[�V�����I�����ɃG�t�F�N�g�͏����Ȃ����A�w�肷�鎖�ŃA�j���[�V�����I�����ɃG�t�F�N�g���������Ƃ��ł���)
	bool sleepnow = false;     //Sleep�t���O


	// �����o�֐�
	void SleepCount();     //sleep���ԃJ�E���g     Update()�ɓ����


public:
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	// �x��t���O�ݒ�(�C���f�b�N�X)     DoOnece
	void SetDelayFlag(int index);

	// �G�t�F�N�g�Đ��҂��֐�(�҂�����)
	void eftSleep(float sec);
	



};


// �^�C�g��_�G�t�F�N�g
class TitleEffect : public Effect
{

};


// �`���[�g���A��_�G�t�F�N�g
class TutorialEffect : public Effect
{

};


// �Q�[��_�G�t�F�N�g
class GameEffect : public Effect
{

};


// ���U���g_�G�t�F�N�g
class ResultEffect : public Effect
{

};



