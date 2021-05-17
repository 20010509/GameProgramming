#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include"CVector.h"
#include"CModel.h"
#include"CCharacter.h"
#include"CPlayer.h"
#include"CColliderTriangle.h"
#include"CColliderMesh.h"

/*
�Q�[���̃V�[��
*/
class CSceneGame : public CScene {
public:
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();

	CVector mEye;

	//���f���N���X�̃C���X�^���X�쐬
	CModel mModel;

	CModel mBackGround; //�w�i���f��

	CPlayer mPlayer;

	//�O�p�R���C�_�̍쐬
	CColliderTriangle mColliderTriangle;
	CColliderTriangle mColliderTriangle2;

	//���f������R���C�_�쐬
	CColliderMesh mColliderMesh;

	CMatrix mBackGroundMatrix;
};

#endif
