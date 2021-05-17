#ifndef CCOLLIDERLINE_H
#define CCOLLIDERLINE_H
#include "CCollider.h"
/*
�����R���C�_�̒�`
*/
class CColliderLine : public CCollider
{
public:
	CColliderLine(){}
	//�R���X�g���N�^(�����R���C�_)
	//CColliderLine(�e�A�e�s��A���_1�A���_2)
	CColliderLine(CCharacter *parent, CMatrix *matrix, const CVector &v0, const CVector &v1);
	//�����R���C�_�̐ݒ�
	//Set(�e�A�e�s��A���_1�A���_2)
	void Set(CCharacter *parent, CMatrix *matrix, const CVector &v0, const CVector &v1);
	//�`��
	void Render();
	void ChangePriority();
};

#endif