#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include "CXCharacter.h"
#include "CXPlayer.h"
#include "CXEnemy.h"

/*
�Q�[���̃V�[��
*/
class CSceneGame : public CScene {
public:

	~CSceneGame();
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();

	//�L�����N�^�̃C���X�^���X
	CXPlayer mPlayer;

	//�G�̃C���X�^���X
	CXEnemy mEnemy;
};

#endif
