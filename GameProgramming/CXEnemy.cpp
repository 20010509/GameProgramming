#include "CXEnemy.h"

void CXEnemy::Init(CModelX* model){
	CXCharacter::Init(model);
	//‡¬s—ñ‚Ìİ’è
	mColSphereBody.mpMatrix = &mpCombinedMatrix[8];
	//“ª
	mColSphereHand.mpMatrix = &mpCombinedMatrix[11];
	//Œ•
	mColSphereSword.mpMatrix = &mpCombinedMatrix[21];
}
