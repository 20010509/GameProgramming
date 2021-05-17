#ifndef CENEMY2_H
#define CENEMY2_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter.h"
//�R���C�_�N���X�̃C���N���[�h
#include "CCollider.h"
/*
�G�l�~�[�N���X
�L�����N�^�N���X���p��
*/
class CEnemy2 : public CCharacter{
public:
	//���f���f�[�^
	static CModel mModel;
	//�R���C�_
	CCollider mCollider;
	//�R���X�g���N�^
	CEnemy2();
	//CEnemy(�ʒu�A��]�A�g��)
	CEnemy2(const CVector& position, const CVector& rotation, const CVector& scale);
	//�X�V����
	void Update();
	//�Փˏ���
	//Collider(�R���C�_1,�R���C�_2)
	void Collision(CCollider *m, CCollider *o);
	void TaskCollision();
	CCollider mColSearch; //�T�[�`�p�R���C�_
	CCharacter *mpPlayer; //�v���C���[�̃|�C���^
	int mHp; //�q�b�g�|�C���g
	CVector mPoint; //�ڕW�n�_
};
#endif