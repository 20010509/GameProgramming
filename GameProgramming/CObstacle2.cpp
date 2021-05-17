#include "CObstacle2.h"
#include "CTaskManager.h"
#include "CCollisionManager.h"
#include "CEffect.h"
#include "CBullet.h"

#define OBJ "sirclepillar.obj" //���f���̃t�@�C��
#define MTL "sirclepillar.mtl" //���f���̃}�e���A���t�@�C��

CModel CObstacle2::mModel; //���f���f�[�^�̍쐬

//�f�t�H���g�R���X�g���N�^
CObstacle2::CObstacle2()
: mColSearch(this, &mMatrix, CVector(0.0f, 0.0f, -10.0f), 30.0f)
, mRotateFlag(false)
, mStopFlag(false)
, mRotateSpeed(0)
{
	//���f�����Ȃ����͓ǂݍ���
	if (mModel.mTriangles.size() == 0)
	{
		mModel.Load(OBJ, MTL);
	}
	//���f���̃|�C���^�ݒ�
	mpModel = &mModel;
	//mColSearch.mTag = CCollider::ESEARCH; //�^�O�ݒ�
}

//�R���X�g���N�^
//CEnemy(�ʒu�A��]�A�g�k)
CObstacle2::CObstacle2(const CVector& position, const CVector& rotation, const CVector& scale)
:CObstacle2()
{
	//�ʒu�A��]�A�g�k��ݒ肷��
	mPosition = position; //�ʒu�̐ݒ�
	mRotation = rotation; //��]�̐ݒ�
	mScale = scale; //�g�k�̐ݒ�
	CTransform::Update(); //�s��̐ݒ�
	//�D��x��1�ɕύX����
	mPriority = 1;
	CTaskManager::Get()->Remove(this); //�폜����
	CTaskManager::Get()->Add(this); //�ǉ�����

	mColliderMesh.Set(NULL, &mMatrix, mpModel);
}

//�X�V����
void CObstacle2::Update(){
	if (mRotateFlag == true && mStopFlag == false){
		mRotateSpeed += 0.2f;
		mPosition.mZ += mRotateSpeed;
		if (mPosition.mZ >= 90.0f){
			mStopFlag = true;
			mPosition.mZ = 90.0f;
		}
	}

	CTransform::Update();
}

//�Փˏ���
//Collider(�R���C�_1�A�R���C�_2)
void CObstacle2::Collision(CCollider *m, CCollider *o){
	//���肪�T�[�`�̎��͖߂�
	if (o->mTag == CCollider::ESEARCH)
	{
		return;
	}
	//�������T�[�`�p�̎�
	if (m->mTag == CCollider::ESEARCH)
	{
		//���肪���R���C�_�̎�
		if (o->mType == CCollider::ESPHERE)
		{
			//���肪�v���C���[�̎�
			if (o->mpParent->mTag == EPLAYER)
			{
				//�Փ˂��Ă���Ƃ�
				if (CCollider::Collision(m, o))
				{
					mRotateFlag = true;
				}
			}
		}
		return;
	}
}

void CObstacle2::TaskCollision()
{
	mColSearch.ChangePriority();
	CCollisionManager::Get()->Collision(&mColSearch, COLLISIONRANGE);
}