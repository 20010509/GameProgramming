//�v���C���[�N���X�̃C���N���[�h
#include"CPlayer.h"
//�L�[���̓N���X�̃C���N���[�h
#include"CKey.h"
#include"CTaskManager.h"
#include"CCollisionManager.h"
#include "CUtil.h"

#define GRAVITY 0.03f			//�d��
#define JUMPPOWER 0.6f			//�W�����v��
#define RUNSPEED 0.8f			//�O���ֈړ�����X�s�[�h
#define SIDEMOVESPEED 0.375f	//�����[���ֈړ�����X�s�[�h
#define INITIALIZE 0			//�l��������
#define SIDEMOVECOUNT 12		//�ׂ̃��[���ֈړ����鎞��(�t���[��)
#define SLIDINGCOUNT 30			//�X���C�f�B���O�̎�������

CPlayer::CPlayer()
:mLine(this, &mMatrix, CVector(0.0f, 0.0f, -0.75f), CVector(0.0f, 0.0f, 0.75f))
,mLine2(this, &mMatrix, CVector(0.0f, 0.75f, 0.0f), CVector(0.0f, -0.75f, 0.0f))
,mLine3(this, &mMatrix, CVector(0.75f, 0.0f, 0.0f), CVector(-0.75f, 0.0f, 0.0f))
,mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f),1.5f)
, mJumpPower(INITIALIZE)
, mJumpFlag(false)
, mSlidingFlag(false)
, mSlidingCount(INITIALIZE)
, mSideMoveSpeed(INITIALIZE)
, mSideMoveFlagL(false)
, mSideMoveFlagR(false)
, mSideMoveCount(INITIALIZE)
, mNowLane(INITIALIZE)
, mSurface(INITIALIZE)
{
	//�e�N�X�`���t�@�C���̓ǂݍ���(1�s64��)
	mText.LoadTexture("FontWhite.tga", 1, 64);
	mTag = EPLAYER; //�^�O�ݒ�
}

//�X�V����
void CPlayer::Update(){
	//A�L�[���͂ō����[���ֈړ�
	if (CKey::Once('A') && mNowLane > -1&&mSideMoveFlagR==false){
		//Y���̉�]�l�𑝉�
		//mRotation.mY += 1;
		//mPosition.mX -= 5;
		mNowLane--;
		mSideMoveFlagL = true;
		mSideMoveSpeed = SIDEMOVESPEED;
	}
	if (mSideMoveFlagL == true){
		mSideMoveCount++;
		mPosition.mX -= mSideMoveSpeed;
		if (mSideMoveCount > SIDEMOVECOUNT){
			mSideMoveSpeed = INITIALIZE;
			mSideMoveCount = INITIALIZE;
			mSideMoveFlagL = false;
		}
	}
	//D�L�[���͂ŉE���[���ֈړ�
	if (CKey::Once('D') && mNowLane < 1&&mSideMoveFlagL==false){
		//Y���̉�]�l�𑝉�
		//mRotation.mY -= 1;
		//mPosition.mX += 5;
		mNowLane++;
		mSideMoveFlagR = true;
		mSideMoveSpeed = SIDEMOVESPEED;
	}
	if (mSideMoveFlagR == true){
		mSideMoveCount++;
		mPosition.mX += mSideMoveSpeed;
		if (mSideMoveCount > SIDEMOVECOUNT){
			mSideMoveSpeed = INITIALIZE;
			mSideMoveCount = INITIALIZE;
			mSideMoveFlagR = false;
		}
	}
	
	//S�L�[���͂ŃX���C�f�B���O
	if (CKey::Once('S') && mSlidingFlag == false){
		//Y���̉�]�l�𑝉�
		//mRotation.mX -= 1;
		mSlidingFlag = true;
		
	}
	if (mSlidingFlag == true){
		mSlidingCount++;
		mScale = CVector(1.5f, 0.75f, 1.5f); //�g��k��
		if (mSlidingCount > SLIDINGCOUNT){
			mSlidingFlag = false;
			mSlidingCount = INITIALIZE;
			mScale = CVector(1.5f, 1.5f, 1.5f); //�g��k��
		}
	}

	//W�L�[���͂ŃW�����v
	if (CKey::Once('W') && mJumpFlag == false){
		//Y���̉�]�l�𑝉�
		//mRotation.mX += 1;
		mJumpFlag = true;
		mJumpPower = JUMPPOWER;
	}
	mPosition.mY += mJumpPower;
	mJumpPower -= GRAVITY;

	if (mPosition.mY <= 0){
		mSurface = mPosition.mY*-1;
		mPosition.mY += mSurface;
		mJumpFlag = false;
		mJumpPower = INITIALIZE;
	}

	//�����őO���Ɉړ�
	mPosition.mZ -= RUNSPEED;

	/*if (CKey::Push(VK_UP)){
		mPosition.mZ -= 0.5;
	}
	if (CKey::Push(VK_DOWN)){
		mPosition.mZ += 0.5;
	}*/

	//����L�[���͂őO�i
	/*if (CKey::Push(VK_UP)){
		//Z��������1�i�񂾒l����]�ړ�������
		mPosition = CVector(0.0f, 0.0f, 1.0f)*mMatrix;
	}*/
	//�X�y�[�X�L�[���͂Œe����
	if (CKey::Push(VK_SPACE)){
		/*CBullet*bullet = new CBullet();
		bullet->Set(0.1f, 1.5f);
		bullet->mPosition = CVector(0.0f, 0.0f, 10.0f)*mMatrix;
		bullet->mRotation = mRotation;
		bullet->Update();*/
		//TaskManager.Add(bullet);
	}
	
	//CTransform�̍X�V
	CTransform::Update();
}

void CPlayer::Collision(CCollider *m, CCollider *o){
	//���g�̃R���C�_�^�C�v�̔���
	switch (m->mType){
	case CCollider::ELINE: //�����R���C�_
		//����̃R���C�_���O�p�R���C�_�̎�
		if (o->mType == CCollider::ETRIANGLE){
			CVector adjust; //�����p�x�N�g��
			//�O�p�`�Ɛ����̏Փ˔���
			CCollider::CollisionTriangleLine(o, m, &adjust);
			//�ʒu�̍X�V(mPosition+adjust)
			mPosition = mPosition - adjust*-1;
			//�s��̍X�V
			CTransform::Update();
		}
		break;
	}
}

//�Փˏ���
void CPlayer::TaskCollision()
{
	//�R���C�_�̗D��x�ύX
	mLine.ChangePriority();
	mLine2.ChangePriority();
	mLine3.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Get()->Collision(&mLine, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine2, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine3, COLLISIONRANGE);

	mCollider.ChangePriority();
}

void CPlayer::Render()
{
	//�e�̕`�揈��
	CCharacter::Render();

	//2D�̕`��J�n
	CUtil::Start2D(-400, 400, -300, 300);
	//�`��F�̐ݒ�(�ΐF�̔�����)
	glColor4f(0.0f, 1.0f, 0.0f, 0.4f);
	//������ҏW�G���A�̍쐬
	char buf[64];

	//Y���W�̕\��
	//������̐ݒ�
	sprintf(buf, "PY:%7.2f", mPosition.mY);
	//������̕`��
	mText.DrawString(buf, 100, 30, 8, 16);

	//X����]�l�̕\��
	//������̐ݒ�
	sprintf(buf, "RX:%7.2f", mRotation.mX);
	//������̕`��
	mText.DrawString(buf, 100, 0, 8, 16);

	sprintf(buf, "RY:%7.2f", mRotation.mY);
	mText.DrawString(buf, 100, -100, 8, 16);

	//2D�̕`��I��
	CUtil::End2D();
}