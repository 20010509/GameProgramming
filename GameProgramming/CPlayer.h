#ifndef CPLAYER_H
#define CPLAYER_H
//�L�����N�^�[�N���X�̃C���N���[�h
#include"CCharacter.h"
#include"CBullet.h"
#include"CColliderLine.h"
#include"CText.h"
/*
�v���C���[�N���X
�L�����N�^�N���X���p��
*/
class CPlayer :public CCharacter{
private:
	float mJumpPower;			//�W�����v��
	bool mJumpFlag;				//�W�����v���Ă��邩���f����

	int mSlidingCount;			//�X���C�f�B���O�̎�������
	bool mSlidingFlag;			//�X���C�f�B���O���Ă��邩���f����

	float mSideMoveSpeed;		//�ׂ̃��[���ֈړ�����Ƃ��̃X�s�[�h
	bool mSideMoveFlagL;		//�v���C���[�����[�����ړ����Ă��邩���f����(������)
	bool mSideMoveFlagR;		//�v���C���[�����[�����ړ����Ă��邩���f����(�E����)
	int mSideMoveCount;			//�ׂ̃��[���ֈړ����鎞��

	int mNowLane;				//�v���C���[���������Ă��郌�[��

	float mSurface;				//�߂荞�񂾕��߂��p

public:
	//�X�V����
	void Update();

	CColliderLine mLine; //�����R���C�_
	CColliderLine mLine2;
	CColliderLine mLine3;

	//�f�t�H���g�R���X�g���N�^
	CPlayer();

	//�Փˏ���
	void Collision(CCollider *m, CCollider *o);

	void TaskCollision();

	CText mText;

	void Render();

	CCollider mCollider; //�{�̗p�R���C�_

};
#endif