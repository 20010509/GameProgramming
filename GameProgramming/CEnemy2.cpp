
#include "CEnemy2.h"
#include "CTaskManager.h"
#include "CCollisionManager.h"
#include "CEffect.h"
#include "CBullet.h"

#define OBJ "f16.obj" //���f���̃t�@�C��
#define MTL "f16.mtl" //���f���̃}�e���A���t�@�C��

#define HP 3 //�ϋv�l
#define VELOCITY 0.11f //���x

CModel CEnemy2::mModel; //���f���f�[�^�̍쐬

//�f�t�H���g�R���X�g���N�^
CEnemy2::CEnemy2()
:mCollider(this, &mMatrix, CVector(0.0f,0.0f,0.0f),0.4f)
, mColSearch(this, &mMatrix,CVector(0.0f,0.0f,100.0f),30.0f)
, mpPlayer(0)
, mHp(HP)
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
CEnemy2::CEnemy2(const CVector& position, const CVector& rotation, const CVector& scale)
:CEnemy2()
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

	//�ړI�n�_�̐ݒ�
	mPoint = mPosition + CVector(0.0f, 0.0f, 100.0f)*mMatrixRotate;
}

//�X�V����
void CEnemy2::Update(){
	//������(X��)�̃x�N�g�������߂�
	CVector vx = CVector(1.0f, 0.0f, 0.0f)*mMatrixRotate;
	//�����(Y��)�̃x�N�g�������߂�
	CVector vy = CVector(0.0f, 1.0f, 0.0f)*mMatrixRotate;
	//�O����(Z��)�̃x�N�g�������߂�
	CVector vz = CVector(0.0f, 0.0f, 1.0f)*mMatrixRotate;
	//�v���C���[�̃|�C���^��0�ȊO�̎�
	if (mpPlayer)
	{
		//�v���C���[�܂ł̃x�N�g�������߂�
		CVector vp = mpPlayer->mPosition - mPosition;
		float dx = vp.Dot(vx); //���x�N�g���Ƃ̓��ς����߂�
		float dy = vp.Dot(vy); //��x�N�g���Ƃ̓��ς����߂�
		float dz = vp.Dot(vz); //�O�x�N�g���Ƃ̓��ς����߂�
		//X���̃Y����2.0�ȉ�
		if (-2.0f < dx && dx < 2.0f)
		{
			//Y���̃Y����2.0�ȉ�
			if (-2.0f < dy && dy < 2.0f)
			{
				if (0.0f < dz){
					//�e�𔭎˂��܂�
					CBullet*bullet = new CBullet();
					bullet->Set(0.1f, 1.5f);
					bullet->mPosition = CVector(0.0f, 0.0f, 10.0f)*mMatrix;
					bullet->mRotation = mRotation;
					bullet->Update();
				}
			}
		}
	}

	//HP��0�ȉ��̎��@���j
	if (mHp <= 0)
	{
		mHp--;
		//15�t���[�����ɃG�t�F�N�g
		if (mHp % 15 == 0)
		{
			//�G�t�F�N�g����
			new CEffect(mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
		}
		//���~������
		mPosition.mY -= 0.03f;
		CTransform::Update();
		return;
	}

	//�ړI�n�_�܂ł̃x�N�g�������߂�
	CVector vp = mPoint - mPosition;
	float dx = vp.Dot(vx); //���x�N�g���Ƃ̓��ς����߂�
	float dy = vp.Dot(vy); //��x�N�g���Ƃ̓��ς����߂�
	float margin = 0.1f;
	//���E�����։�]
	if (dx > margin)
	{
		mRotation.mY += 1.0f; //���։�]
	}
	else if (dx < -margin)
	{
		mRotation.mY -= 1.0f; //�E�։�]
	}
	//�㉺�����։�]
	if (dy>margin)
	{
		mRotation.mX -= 1.0f; //��։�]
	}
	else if (dy < -margin)
	{
		mRotation.mX += 1.0f; //���։�]
	}
	//�ړ�����
	mPosition = mPosition + CVector(0.0f, 0.0f, VELOCITY)*mMatrixRotate;
	CTransform::Update(); //�s��X�V

	//���悻3�b���ɖڕW�n�_���X�V
	int r = rand() % 180; //rand()�h�����̗�����Ԃ��@//%180��180�Ŋ������]������߂�
	if (r == 0)
	{
		if (mpPlayer)
		{
			mPoint = mpPlayer->mPosition;
		}
		else
		{
			mPoint = mPoint*CMatrix().RotateY(45);
		}
	}

	mpPlayer = 0;
}

//�Փˏ���
//Collider(�R���C�_1�A�R���C�_2)
void CEnemy2::Collision(CCollider *m, CCollider *o){
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
					//�v���C���[�̃|�C���^�ݒ�
					mpPlayer = o->mpParent;
				}
			}
		}
		return;
	}
	//����̃R���C�_�_�C�u�̔���
	switch (o->mType)
	{
	case CCollider::ESPHERE: //���R���C�_�̎�
		//�R���C�_��m��o���Փ˂��Ă��邩�̔���
		if (CCollider::Collision(m, o)){
			//�G�t�F�N�g����
			new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			mHp--; //�q�b�g�|�C���g�̌��Z
		}
		break;
	case CCollider::ETRIANGLE: //�O�p�R���C�_�̎�
		CVector adjust; //�����l
		//�O�p�R���C�_�Ƌ��R���C�_�̏Փ˔���
		if (CCollider::CollisionTriangleSphere(o, m, &adjust))
		{
			//�Փ˂��Ȃ��ʒu�܂Ŗ߂�
			mPosition = mPosition + adjust;
			if (mHp <= 0)
			{
				mEnabled = false;
			}
		}
		break;
	}
}

void CEnemy2::TaskCollision()
{
	//�R���C�_�̗D��x�ύX
	mCollider.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);

	mColSearch.ChangePriority();
	CCollisionManager::Get()->Collision(&mColSearch, COLLISIONRANGE);
}