#ifndef CMODELX_H //�C���N���[�h�K�[�h
#define CMODELX_H

#define MODEL_FILE "sample.blend.x" //���̓t�@�C����

//�̈�J�����}�N����
#define SAFE_DELETE_ARRAY(a){if(a)delete[]a;a=0;}

//�z��T�C�Y�擾���}�N����
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

#include <vector>		//vector�N���X�̃C���N���[�h(���I�z��)
#include "CMatrix.h"	//�}�g���N�X�N���X�̃C���N���[�h
#include "CVector.h"

class CModelX;	//CModelX�N���X�̐錾
class CMaterial;	//�N���X�̐錾

/*
CAnimationKey
�A�j���[�V�����L�[�N���X
*/
class CAnimationKey{
public:
	//����
	float mTime;
	//�s��
	CMatrix mMatrix;
};

/*
CAnimation
�A�j���[�V�����N���X
*/
class CAnimation{
public:
	char *mpFrameName;	//�t���[��
	int mFrameIndex;	//�t���[���ԍ�
	int mKeyNum;	//�L�[��(���Ԑ�)
	CAnimationKey *mpKey;	//�L�[�z��

	CAnimation(CModelX *model);

	~CAnimation(){
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpKey);
	}
};

/*
CAnimationSet
�A�j���[�V�����Z�b�g
*/
class CAnimationSet{
public:
	//�A�j���[�V�����Z�b�g��
	char *mpName;

	CAnimationSet(CModelX *model);

	~CAnimationSet(){
		SAFE_DELETE_ARRAY(mpName);
		//�A�j���[�V�����v�f�̍폜
		for (int i = 0; i < mAnimation.size(); i++){
			delete mAnimation[i];
		}
	}

	//�A�j���[�V����
	std::vector<CAnimation*> mAnimation;

	float mTime;	//���ݎ���
	float mWeight;	//�d��
	float mMaxTime;	//�ő厞��
};

/*
CSkinWeights
�X�L���E�F�C�g�N���X
*/
class CSkinWeights{
public:
	char *mpFrameName;	//�t���[����
	int mFrameIndex;	//�t���[���ԍ�
	int mIndexNum;		//���_�ԍ���
	int *mpIndex;		//���_�ԍ��z��
	float *mpWeight;	//���_�E�F�C�g�z��
	CMatrix mOffset;	//�I�t�Z�b�g�}�g���b�N�X

	CSkinWeights(CModelX *model);

	~CSkinWeights(){
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpIndex);
		SAFE_DELETE_ARRAY(mpWeight);
	}
};

//CMash�N���X�̒�`
class CMesh{
public:
	int mVertexNum;		//���_��
	CVector *mpVertex;	//���_�f�[�^
	int mFaceNum;		//�ʐ�
	int *mpVertexIndex;	//�ʂ��\�����钸�_�ԍ�
	int mNormalNum;		//�@����
	CVector *mpNormal;	//�@���f�[�^
	int mMaterialNum;	//�}�e���A����
	int mMaterialIndexNum;	//�}�e���A���ԍ���(�֐�)
	int *mpMaterialIndex;	//�}�e���A���ԍ�
	CVector *mpAnimateVertex;	//�A�j���[�V�����p���_
	CVector *mpAnimateNormal;	//�A�j���[�V�����p�@��
	std::vector<CMaterial*>mMaterial;	//�}�e���A���f�[�^
	//�X�L���E�F�C�g
	std::vector<CSkinWeights*>mSkinWeights;
	//�R���X�g���N�^
	CMesh()
		:mVertexNum(0)
		, mpVertex(nullptr)
		, mFaceNum(0)
		, mpVertexIndex(nullptr)
		, mNormalNum(0)
		, mpNormal(nullptr)
		, mMaterialNum(0)
		, mMaterialIndexNum(0)
		, mpMaterialIndex(nullptr)
		, mpAnimateVertex(nullptr)
		, mpAnimateNormal(nullptr)
	{}
	//�f�X�g���N�^
	~CMesh(){
		SAFE_DELETE_ARRAY(mpVertex);
		SAFE_DELETE_ARRAY(mpVertexIndex);
		SAFE_DELETE_ARRAY(mpNormal);
		SAFE_DELETE_ARRAY(mpMaterialIndex);
		SAFE_DELETE_ARRAY(mpAnimateVertex);
		SAFE_DELETE_ARRAY(mpAnimateNormal);
		//�X�L���E�F�C�g�̍폜
		for (int i = 0; i < mSkinWeights.size(); i++){
			delete mSkinWeights[i];
		}
	}
	//�ǂݍ��ݏ���
	void Init(CModelX *model);
	void Render();
	//���_�ɃA�j���[�V�����K�p
	void AnimateVertex(CModelX *model);
};

//CModelXFrame�N���X�̒�`
class CModelXFrame{
public:
	std::vector<CModelXFrame*> mChild;	//�q�t���[���̔z��
	CMatrix mTransformMatrix;	//�ϊ��s��
	char* mpName;		//�t���[�����O
	int mIndex;			//�t���[���ԍ�

	CMatrix mCombinedMatrix; //�����s��
	//�����s��̍쐬
	void AnimateCombined(CMatrix* parent);
	//�R���X�g���N�^
	CModelXFrame(CModelX* model);
	//�f�X�g���N�^
	~CModelXFrame(){
		//�q�t���[����S�ĊJ������
		std::vector<CModelXFrame*>::iterator itr;
		for (itr = mChild.begin(); itr != mChild.end(); itr++){
			delete *itr;
		}
		//���O�̃G���A���J������
		SAFE_DELETE_ARRAY(mpName);
	}
	CMesh mMesh;	//Mesh�f�[�^
	void Render();
};

/*
CModelX
X�t�@�C���`����3D���f���f�[�^���v���O�����ŔF������
*/
class CModelX{
public:
	char* mpPointer;	//�ǂݍ��݈ʒu
	char mToken[1024];	//���o�����P��̗̈�
	std::vector<CModelXFrame*>mFrame;	//�t���[���̔z��
	//�A�j���[�V�����Z�b�g�̔z��
	std::vector<CAnimationSet*>mAnimationSet;


	CModelX()
		:mpPointer(nullptr)
	{}

	~CModelX(){
		if (mFrame.size() > 0)
		{
			delete mFrame[0];
		}
		for (int i = 0; i < mAnimationSet.size(); i++){
			delete mAnimationSet[i];
		}
	}

	//�t�@�C���ǂݍ���
	void Load(char* file);
	//�P��̎��o��
	void GetToken();
	//�m�[�h�̓ǂݔ�΂�
	void SkipNode();

	//���������_�f�[�^�̎擾
	float GetFloatToken();

	//�����f�[�^�̎擾
	int GetIntToken();

	void Render();

	//�t���[�����ɊY������t���[���̃A�h���X��Ԃ�
	CModelXFrame* FindFrame(char* name);

	void AnimateFrame();

	//�X�L���E�F�C�g�̃t���[���ԍ��ݒ�
	void SetSkinWeightFrameIndex();

	//���_�ɃA�j���[�V������K�p
	void AnimateVertex();

};

#endif