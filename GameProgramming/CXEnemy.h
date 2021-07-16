#ifndef CXENEMY_H
#define CXENEMY_H

#include "CXCharacter.h"
#include "CCollider.h"

class CXEnemy : public CXCharacter{
public:
	//コライダの宣言
	CCollider mColSphereBody;	//体
	CCollider mColSphereHand;	//頭
	CCollider mColSphereSword;	//剣

	//コライダの初期化
	CXEnemy()
		:mColSphereBody(this, nullptr, CVector(), 0.5f)
		, mColSphereHand(this, nullptr, CVector(0.0f, 5.0f, -3.0f), 0.5f)
		, mColSphereSword(this, nullptr, CVector(-10.0f, 10.0f, 50.0f), 0.3f)
	{
	}

	void Init(CModelX *model);

};

#endif