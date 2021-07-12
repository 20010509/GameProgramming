#include "CXPlayer.h"
#include "CKey.h"

void CXPlayer::Update(){

	//UŒ‚
	if (CKey::Once(VK_SPACE)){
		ChangeAnimation(3, false, 30);
	}
	if (mAnimationIndex == 3 && mAnimationFrame >= mAnimationFrameSize){
		ChangeAnimation(4, false, 30);
	}
	if (mAnimationIndex == 4 && mAnimationFrame >= mAnimationFrameSize){
		ChangeAnimation(0, true, 60);
	}

	//ˆÚ“®
	if (mAnimationIndex != 3 && mAnimationIndex != 4){
		if (CKey::Push('A')){
			mRotation.mY += 2;
		}
		if (CKey::Push('D')){
			mRotation.mY -= 2;
		}
		if (CKey::Push('W')){
			ChangeAnimation(1, true, 60);
			mPosition += CVector(0.0f, 0.0f, 0.1f)*mMatrixRotate;
		}
		else{
			ChangeAnimation(0, true, 60);
		}
	}

	CXCharacter::Update();
}