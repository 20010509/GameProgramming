#include "CObstacle.h"
#include "CTaskManager.h"
#include "CCollisionManager.h"
#include "CEffect.h"
#include "CBullet.h"

#define OBJ "needle.obj" //���f���̃t�@�C��
#define MTL "needle.mtl" //���f���̃}�e���A���t�@�C��

CModel CObstacle::mModel; //���f���f�[�^�̍쐬

//�f�t�H���g�R���X�g���N�^
CObstacle::CObstacle()
: mColSearch(this, &mMatrix, CVector(0.0f, 0.0f, -10.0f), 30.0f)
, mRiseFlag(false)
, mStopFlag(false)
, mRiseSpeed(0)
{
	//���f�����Ȃ����͓ǂݍ���
	if (mModel.mTriangles.size() == 0)
	{
		mModel.Load(OBJ, MTL);
	}
	//���f���̃|�C���^�ݒ�
	mpModel = &mModel;
	mColSearch.mTag = CCollider::ESEARCH; //�^�O�ݒ�
}

//�R���X�g���N�^
//CEnemy(�ʒu�A��]�A�g�k)
CObstacle::CObstacle(const CVector& position, const CVector& rotation, const CVector& scale)
:CObstacle()
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
void CObstacle::Update(){
	if (mRiseFlag == true&&mStopFlag==false){
		mRiseSpeed += 0.2f;
		mPosition.mY += mRiseSpeed;
		if (mPosition.mY >= -1.0f){
			mStopFlag = true;
			mPosition.mY = -1.0f;
		}
	}

	CTransform::Update();
}

//�Փˏ���
//Collider(�R���C�_1�A�R���C�_2)
void CObstacle::Collision(CCollider *m, CCollider *o){
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
					mRiseFlag = true;
				}
			}
		}
		return;
	}
}

void CObstacle::TaskCollision()
{
	mColSearch.ChangePriority();
	CCollisionManager::Get()->Collision(&mColSearch, COLLISIONRANGE);
}