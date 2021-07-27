#include "CSceneGame.h"
//
#include "CCamera.h"
//
#include "CUtil.h"
//
#include "CRes.h"

#include "CKey.h"

#include "CMaterial.h"

#include "CCollisionManager.h"

CMatrix Matrix;

CSceneGame::~CSceneGame() {

}

void CSceneGame::Init() {
	//3Dモデルファイルの読み込み
	CRes::sModelX.Load(MODEL_FILE);
	//キャラクターにモデルを設定
	mPlayer.Init(&CRes::sModelX);

	//3Dモデルファイルの読み
	CRes::sKnight.Load("Knight\\knight_low.x");
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");			//1:移動
	CRes::sKnight.SeparateAnimationSet(0, 1530, 1830, "idle1");		//2:待機
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");			//3:ダミー
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");			//4:ダミー
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");			//5:ダミー
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");			//6:ダミー
	CRes::sKnight.SeparateAnimationSet(0, 440, 520, "attack1");		//7:Attack1
	CRes::sKnight.SeparateAnimationSet(0, 520, 615, "attack2");		//8:Attack1
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");			//9:ダミー
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");			//10:ダミー
	CRes::sKnight.SeparateAnimationSet(0, 1160, 1260, "death1");	//11:ダミー

	//敵の初期設定
	mEnemy.Init(&CRes::sKnight);
	//敵の配置
	mEnemy.mPosition = CVector(7.0f, 0.0f, 0.0f);
	mEnemy.mAnimationFrameSize = 1024;
	mEnemy.ChangeAnimation(2, true, 200);

	//テキストフォントの読み込みと設定
	mFont.LoadTexture("FontG.tga", 1, 4096 / 64);
}


void CSceneGame::Update() {
	//歩くアニメーションに切り替える

	//キャラクタークラスの更新
	mPlayer.Update();

	//敵の更新処理
	mEnemy.Update();

	//カメラのパラメータを作成する
	CVector e, c, u;//視点、注視点、上方向
	//視点を求める
	e = CVector(1.0f, 2.0f, 10.0f);
	//注視点を求める
	c = CVector();
	//上方向を求める
	u = CVector(0.0f, 1.0f, 0.0f);

	//カメラクラスの設定
	Camera.Set(e, c, u);
	Camera.Render();

	//X軸+回転
	if (CKey::Push('K')){
		Matrix = Matrix*CMatrix().RotateX(1);
	}
	//Y軸+回転
	if (CKey::Push('L')){
		Matrix = Matrix*CMatrix().RotateY(1);
	}
	//X軸-回転
	if (CKey::Push('I')){
		Matrix = Matrix*CMatrix().RotateX(-1);
	}
	//Y軸-回転
	if (CKey::Push('J')){
		Matrix = Matrix*CMatrix().RotateY(-1);
	}
	//行列設定
	glMultMatrixf(Matrix.mF);

	//モデル描画
	//CRes::sModelX.Render();
	mPlayer.Render();
	//コライダの描画
	CCollisionManager::Get()->Render();
	//敵描画
	mEnemy.Render();

	//衝突処理
	CCollisionManager::Get()->Collision();

	/*
	//テクスチャテスト
	CRes::sModelX.mMaterial[0]->mTexture.DrawImage(-5, 5, -5, 5, 0, 128, 128, 0);
	*/

	//2D描画開始
	CUtil::Start2D(0, 800, 0, 600);

	mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2Dの描画終了
	CUtil::End2D();

	return;
}

