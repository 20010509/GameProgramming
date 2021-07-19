#include "CXEnemy.h"

void CXEnemy::Init(CModelX* model){
	CXCharacter::Init(model);
	//�����s��̐ݒ�
	mColSphereBody.mpMatrix = &mpCombinedMatrix[8];
	//��
	mColSphereHead.mpMatrix = &mpCombinedMatrix[11];
	//��
	mColSphereSword.mpMatrix = &mpCombinedMatrix[21];
}

void CXEnemy::Collision(CCollider *m, CCollider *o){
	//�����̃R���C�_�̃^�C�v�����̂Ƃ�
	if (m->mType == CCollider::ESPHERE){
		//����̃R���C�_�̃^�C�v�����̂Ƃ�
		if (o->mType == CCollider::ESPHERE){
			//����̃R���C�_�̐e���v���C���[�̂Ƃ�
			if (o->mpParent->mTag == EPLAYER){
				//����̃R���C�_�����̂Ƃ�
				if (o->mTag == CCollider::ESWORD){
					//�����Ƒ���̃R���C�_���Փ˂��Ă���Ƃ�
					if (CCollider::Collision(m, o)){
						//30�t���[�������ă_�E�����A�J��Ԃ��Ȃ�
						ChangeAnimation(11, false, 30);
					}
				}
			}
		}
	}
}
