#ifndef CENEMY_H
#define CENEMY_H
//�L�����N���X�̃C���N���[�h
#include "CCharacter.h"
#include "CCollider.h"

/*
�G�l�~�[�N���X
�L�����N�^�N���X���p��
*/
class CEnemy : public CCharacter{
public:
	//�R���X�g���N�^
	//CEnemy(���f���A�ʒu�A��]�A�g�k)
	CEnemy(CModel*model, CVector position, CVector rotation, CVector scale);
	//�X�V����
	void Update();
	//�R���C�_
	CCollider mCollider1;
	CCollider mCollider2;
	CCollider mCollider3;

	//�Փˏ���
	//Collision(�R���C�_�A�R���C�_2)
	void Collision(CCollider *m, CCollider *o);

	void TaskCollision();

};
#endif