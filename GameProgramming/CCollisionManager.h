#ifndef CCOLLISIONMANAGER_H
#define CCOLLISIONMANAGER_H
//�Փˏ����͈͂�藣��Ă���R���C�_�͏Փˏ������Ȃ�
#define COLLISIONRANGE 30

#include "CTaskManager.h"
#include "CCollider.h"

class CCollisionManager : public CTaskManager
{
	//�}�l�[�W���N���X�̃C���X�^���X
	static CCollisionManager* mpInstance;
public:
	//�C���X�^���X�̎擾
	static CCollisionManager* Get();
	//�Փˏ���
	void Collision();

	void Collision(CCollider *c,int range);
};
#endif