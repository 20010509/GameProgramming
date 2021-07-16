#include "CSceneGame.h"
//
#include "CCamera.h"
//
#include "CUtil.h"
//
#include "CRes.h"

#include "CKey.h"

#include "CMaterial.h"

CMatrix Matrix;

CSceneGame::~CSceneGame() {

}

void CSceneGame::Init() {
	//3D���f���t�@�C���̓ǂݍ���
	CRes::sModelX.Load(MODEL_FILE);
	//�L�����N�^�[�Ƀ��f����ݒ�
	mPlayer.Init(&CRes::sModelX);

	//�G�̏����ݒ�
	mEnemy.Init(&CRes::sModelX);
	//�G�̔z�u
	mEnemy.mPosition = CVector(7.0f, 0.0f, 0.0f);
	//�e�L�X�g�t�H���g�̓ǂݍ��݂Ɛݒ�
	mFont.LoadTexture("FontG.tga", 1, 4096 / 64);
}


void CSceneGame::Update() {
	//�����A�j���[�V�����ɐ؂�ւ���

	//�L�����N�^�[�N���X�̍X�V
	mPlayer.Update();

	//�G�̍X�V����
	mEnemy.Update();

	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����
	//���_�����߂�
	e = CVector(1.0f, 2.0f, 10.0f);
	//�����_�����߂�
	c = CVector();
	//����������߂�
	u = CVector(0.0f, 1.0f, 0.0f);

	//�J�����N���X�̐ݒ�
	Camera.Set(e, c, u);
	Camera.Render();

	//X��+��]
	if (CKey::Push('K')){
		Matrix = Matrix*CMatrix().RotateX(1);
	}
	//Y��+��]
	if (CKey::Push('L')){
		Matrix = Matrix*CMatrix().RotateY(1);
	}
	//X��-��]
	if (CKey::Push('I')){
		Matrix = Matrix*CMatrix().RotateX(-1);
	}
	//Y��-��]
	if (CKey::Push('J')){
		Matrix = Matrix*CMatrix().RotateY(-1);
	}
	//�s��ݒ�
	glMultMatrixf(Matrix.mF);

	//���f���`��
	//CRes::sModelX.Render();
	mPlayer.Render();
	//�G�`��
	mEnemy.Render();
	/*
	//�e�N�X�`���e�X�g
	CRes::sModelX.mMaterial[0]->mTexture.DrawImage(-5, 5, -5, 5, 0, 128, 128, 0);
	*/

	//2D�`��J�n
	CUtil::Start2D(0, 800, 0, 600);

	mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2D�̕`��I��
	CUtil::End2D();

	return;
}

