#include "CEnemy.h"
#include "CEffect.h"
#include "CTaskManager.h"
#include "CCollisionManager.h"

//�R���X�g���N�^
//CEnemy(���f���A�ʒu�A��]�A�g�k)
CEnemy::CEnemy(CModel*model, CVector position, CVector rotation, CVector scale)
:mCollider1(this, &mMatrix, CVector(0.0f, 5.0f, 0.0f), 0.8f)
, mCollider2(this, &mMatrix, CVector(0.0f, 5.0f, 20.0f), 0.8f)
, mCollider3(this, &mMatrix, CVector(0.0f, 5.0f, -20.0f), 0.8f)
{
	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
	mpModel = model; //���f���̐ݒ�
	mPosition = position; //�ʒu�̐ݒ�
	mRotation = rotation; //��]�̐ݒ�
	mScale = scale; //�g�k�̐ݒ�

	//�D��x��1�ɕύX����
	mPriority = 1;
	CTaskManager::Get()->Remove(this); //�폜����
	CTaskManager::Get()->Add(this); //�ǉ�����
}

//�Փˏ���
//Collision(�R���C�_�A�R���C�_2)
void CEnemy::Collision(CCollider *m, CCollider *o){
	//���肪�T�[�`�̎��͖߂�
	if (o->mTag == CCollider::ESEARCH)
	{
		return;
	}
	//����̃R���C�_�_�C�u�̔���
	switch (o->mType)
	{
	case CCollider::ESPHERE: //���R���C�_�̎�
		//�R���C�_��m��y���Փ˂��Ă��邩�̔���
		if (CCollider::Collision(m, o)){
			//�G�t�F�N�g����
			new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			//�Փ˂��Ă���Ƃ��͖����ɂ���
			mEnabled=false;
		}
		break;
	case CCollider::ETRIANGLE: //�O�p�R���C�_�̎�
		CVector adjust; //�����l
		//�O�p�R���C�_�Ƌ��R���C�_�̏Փ˔���
		if (CCollider::CollisionTriangleSphere(o, m, &adjust))
		{
			//�Փ˂��Ȃ��ʒu�܂Ŗ߂�
			mPosition = mPosition + adjust;
		}
		break;
	}
}

//�X�V����
void CEnemy::Update(){
	//�s����X�V
	CTransform::Update();
	//�ʒu���X�V
	mPosition = CVector(0.0f, 0.0f, 0.9f)*mMatrix;
}

void CEnemy::TaskCollision()
{
	//�R���C�_�̗D��x�ύX
	mCollider1.ChangePriority();
	mCollider2.ChangePriority();
	mCollider3.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Get()->Collision(&mCollider1, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mCollider2, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mCollider3, COLLISIONRANGE);
}