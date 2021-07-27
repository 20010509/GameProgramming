#ifndef CXENEMY_H
#define CXENEMY_H

#include "CXCharacter.h"
#include "CCollider.h"

class CXEnemy : public CXCharacter{
public:
	//コライダの宣言
	CCollider mColSphereBody;	//体
	CCollider mColSphereHead;	//頭
	CCollider mColSphereSword0;	//剣
	CCollider mColSphereSword1;	//剣
	CCollider mColSphereSword2;	//剣

	//コライダの初期化
	CXEnemy()
		:mColSphereBody(this, nullptr, CVector(0.5f,-1.0f,0.0f), 1.0f)
		, mColSphereHead(this, nullptr, CVector(0.0f, 1.0f, 0.0f), 1.5f)
		, mColSphereSword0(this, nullptr, CVector(0.7f, 3.5f, -0.2f), 0.5f)
		, mColSphereSword1(this, nullptr, CVector(0.5f, 2.5f, -0.2f), 0.5f)
		, mColSphereSword2(this, nullptr, CVector(0.3f, 1.5f, -0.2f), 0.5f)
	{

	}

	void Init(CModelX *model);

	//衝突処理
	void Collision(CCollider *m, CCollider *o);
};

#endif