#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include "CXCharacter.h"
#include "CXPlayer.h"
#include "CXEnemy.h"

/*
ゲームのシーン
*/
class CSceneGame : public CScene {
public:

	~CSceneGame();
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();

	//キャラクタのインスタンス
	CXPlayer mPlayer;

	//敵のインスタンス
	CXEnemy mEnemy;
};

#endif
