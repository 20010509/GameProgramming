#include "CXEnemy.h"

void CXEnemy::Init(CModelX* model){
	CXCharacter::Init(model);
	//合成行列の設定
	mColSphereBody.mpMatrix = &mpCombinedMatrix[1];
	//頭
	mColSphereHead.mpMatrix = &mpCombinedMatrix[1];
	//剣
	mColSphereSword0.mpMatrix = &mpCombinedMatrix[26];
	mColSphereSword1.mpMatrix = &mpCombinedMatrix[26];
	mColSphereSword2.mpMatrix = &mpCombinedMatrix[26];
}

void CXEnemy::Collision(CCollider *m, CCollider *o){
	//自分のコライダのタイプが球のとき
	if (m->mType == CCollider::ESPHERE){
		//相手のコライダのタイプが球のとき
		if (o->mType == CCollider::ESPHERE){
			//相手のコライダの親がプレイヤーのとき
			if (o->mpParent->mTag == EPLAYER){
				//相手のコライダが剣のとき
				if (o->mTag == CCollider::ESWORD){
					//自分と相手のコライダが衝突しているとき
					if (CCollider::Collision(m, o)){
						//30フレームかけてダウンし、繰り返しなし
						ChangeAnimation(11, false, 30);
					}
				}
			}
		}
	}
}
