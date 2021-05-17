#include "CSceneGame.h"
//OpenGL
#include"glut.h"
#include"CTriangle.h"
#include"CKey.h"
#include"CModel.h"
#include"CMatrix.h"
#include"CTransform.h"
#include"CTaskManager.h"
#include"CEnemy.h"
#include"CEnemy2.h"
#include"CCollisionManager.h"
#include"CBillBoard.h"
#include"CCamera.h"

#include"CObstacle.h"
#include"CObstacle2.h"

//CS���f��
CModel mModelIC5;

CModel mObstacle1;

void CSceneGame::Init() {
	mEye = CVector(1.0f, 2.0f, 3.0f);
	//���f���t�@�C���f�[�^�̓���
	mModel.Load("sphere.obj", "sphere.mtl");

	mBackGround.Load("sky.obj", "sky.mtl");

	CMatrix matrix;
	matrix.Print();

	mBackGroundMatrix.Translate(0.0f, 0.0f, -500.0f);

	mPlayer.mpModel = &mModel;
	mPlayer.mScale = CVector(1.5f, 1.5f, 1.5f); //�g��k��
	mPlayer.mPosition = CVector(3.0f, 0.0f, -3.0f)*mBackGroundMatrix; //�ʒu���W
	mPlayer.mRotation = CVector(0.0f, 180.0f, 0.0f); //��]

	//CS���f���̓ǂݍ���
	mModelIC5.Load("c5.obj", "c5.mtl");

	//�G�@�̃C���X�^���X�쐬
	/*
	new CEnemy(&mModelIC5, CVector(0.0f, 10.0f, -100.0f)*mBackGroundMatrix, CVector(), CVector(0.1f, 0.1f, 0.1f));
	new CEnemy(&mModelIC5, CVector(30.0f, 10.0f, -130.0f)*mBackGroundMatrix, CVector(), CVector(0.1f, 0.1f, 0.1f));

	new CEnemy2(CVector(-5.0f, 1.0f, -10.0f)*mBackGroundMatrix, CVector(), CVector(0.1f, 0.1f, 0.1f));
	new CEnemy2(CVector(5.0f, 1.0f, -10.0f)*mBackGroundMatrix, CVector(), CVector(0.1f, 0.1f, 0.1f));
	*/

	new CObstacle(CVector(3.0f, -3.0f, -80.0f)*mBackGroundMatrix, CVector(), CVector(1.0f, 1.0f, 1.0f));
	new CObstacle2(CVector(3.0f, -3.0f, -150.0f)*mBackGroundMatrix, CVector(), CVector(1.0f, 1.0f, 1.0f));

	//�r���{�[�h�̍쐬
	new CBillBoard(CVector(-6.0f, 3.0f, -10.0f), 1.0f, 1.0f);

	//�O�p�R���C�_�̊m�F
	mColliderTriangle.Set(NULL, NULL, CVector(-50.0f, 0.0f, -50.0f), CVector(-50.0f, 0.0f, 50.0f), CVector(50.0f, 0.0f, -50.0f));
	mColliderTriangle2.Set(NULL, NULL, CVector(50.0f, 0.0f, -50.0f), CVector(-50.0f, 0.0f, 50.0f), CVector(50.0f, 0.0f, 50.0f));

	//�w�i���f������O�p�R���C�_�𐶐�
	//�e�C���X�^���X�Ɛe�s��͂Ȃ�
	mColliderMesh.Set(NULL, &mBackGroundMatrix, &mBackGround);
}

void CSceneGame::Update() {
	//�^�X�N�}�l�[�W���̍X�V
	CTaskManager::Get()->Update();
	//�R���W�����}�l�[�W���̏Փˏ���
	//CCollisionManager::Get()->Collision();
	CTaskManager::Get()->TaskCollision();

	//���_1,���_2,���_3,�@���f�[�^�̍쐬
	CVector v0, v1, v2, n;

	//�@����������Őݒ肷��
	n.mX = 0.0f; n.mY = 1.0f; n.mZ = 0.0f;
	//���_1�̍��W��ݒ肷��
	v0.mX = 0.0f; v0.mY = 0.0f; v0.mZ = 0.5f;
	//���_2�̍��W��ݒ肷��
	v1.mX = 1.0f; v1.mY = 0.0f; v1.mZ = 0.0f;
	//���_3�̍��W��ݒ肷��
	v2.mX = 0.0f; v2.mY = 0.0f; v2.mZ = -0.5f;

	//���_�̈ړ�
	if (CKey::Push('J'))
	{
		mEye.mX -= 0.1f;
	}
	if (CKey::Push('L'))
	{
		mEye.mX += 0.1;
	}
	if (CKey::Push('I'))
	{
		mEye.mZ -= 0.1f;
	}
	if (CKey::Push('K'))
	{
		mEye.mZ += 0.1;
	}
	if (CKey::Push('O'))
	{
		mEye.mY += 0.1;
	}
	if (CKey::Push('M'))
	{
		mEye.mY -= 0.1;
	}
	
	//�J�����̃p�����[�^���쐬����
	CVector e, c, u; //���_�A�����_�A�����
	//���_�����߂�
	e = CVector(0.0f, 3.0f, -5.0f)*mPlayer.mMatrix;
	//�����_�����߂�
	c = mPlayer.mPosition;
	//����������߂�
	u = CVector(0, 1, 0)*mPlayer.mMatrixRotate;
	//�J�����̐ݒ�
	//glLookAt(e.mX,e.mY,e.mZ,c.mX,c.mY,c.mZ,u.mX,u.mY,u.mZ)
	//�J�����N���X�̐ݒ�
	Camera.Set(e, c, u);
	Camera.Render();
	
	mBackGround.Render(mBackGroundMatrix);
	
	//�^�X�N���X�g�̍폜
	CTaskManager::Get()->Delete();
	//�^�X�N�}�l�[�W���̕`��
	CTaskManager::Get()->Render();

	CCollisionManager::Get()->Render();
}
