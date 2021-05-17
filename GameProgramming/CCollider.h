#ifndef CCOLLIDER_H
#define CCOLLIDER_H
//キャラクタクラスのインクルード
#include"CCharacter.h"
//トランスフォームクラスのインクルード
#include"CTransform.h"
/*
コライダクラス
衝突判定データ
*/
class CCollider : public CTransform,public CTask{
public:
	CCharacter *mpParent; //親
	CMatrix *mpMatrix; //親行列
	float mRadius; //半径
	//コンストラクタ
	//CCollider(親、親行列、位置、回転、拡縮、半径)
	CCollider(CCharacter *parent, CMatrix *matrix, CVector position, float radius);
	//デストラクタ
	~CCollider();
	//描画
	void Render();
	//衝突判定
	//Collision(コライダ、コライダ2)
	//return:true(衝突している)false(衝突していない)
	static bool Collision(CCollider *m, CCollider *o);

	enum EType{
		ESPHERE, //弾コライダ
		ETRIANGLE, //三角コライダ
		ELINE, //線分コライダ
	};
	EType mType; //コライダダイブ
	//頂点
	CVector mV[3];
	//デフォルトコンストラクタ
	CCollider();

	//CollisionTriangleLine(三角コライダ、線分コライダ、調整値)
	//return:true(衝突している)false(衝突していない)
	//調整値:衝突しない位置まで戻す値
	static bool CollisionTriangleLine(CCollider *triangle, CCollider *line, CVector *adjust);

	//CollisionTriangleSphere(三角コライダ、球コライダ、調整値)
	//retrun:true(衝突している)false(衝突していない)
	//調整値:衝突しない位置まで戻す値
	static bool CollisionTriangleSphere(CCollider *triangle, CCollider *sphere, CVector *adjust);

	void ChangePriority();

	enum ETag
	{
		EBODY,		//本体用
		ESEARCH,	//サーチ用
	};
	ETag mTag;	//コライダ識別
};
#endif