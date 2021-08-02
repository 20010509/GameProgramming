#ifndef CMODELX_H //インクルードガード
#define CMODELX_H

#define MODEL_FILE "ラグナ.x" //入力ファイル名

//領域開放をマクロ化
#define SAFE_DELETE_ARRAY(a){if(a)delete[]a;a=0;}

//配列サイズ取得をマクロ化
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

#include <vector>		//vectorクラスのインクルード(動的配列)
#include "CMatrix.h"	//マトリクスクラスのインクルード
#include "CVector.h"
#include "CMyShader.h"	//シェーダーのインクルード
#include "CVertexX.h"

class CModelX;	//CModelXクラスの宣言
class CMaterial;	//クラスの宣言

/*
CAnimationKey
アニメーションキークラス
*/
class CAnimationKey{
public:
	//時間
	float mTime;
	//行列
	CMatrix mMatrix;
};

/*
CAnimation
アニメーションクラス
*/
class CAnimation{
public:
	char *mpFrameName;	//フレーム
	int mFrameIndex;	//フレーム番号
	int mKeyNum;	//キー数(時間数)
	CAnimationKey *mpKey;	//キー配列

	CAnimation(CModelX *model);

	CAnimation(){}

	~CAnimation(){
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpKey);
	}
};

/*
CAnimationSet
アニメーションセット
*/
class CAnimationSet{
public:
	//アニメーションセット名
	char *mpName;

	CAnimationSet(CModelX *model);

	CAnimationSet(){}

	~CAnimationSet(){
		SAFE_DELETE_ARRAY(mpName);
		//アニメーション要素の削除
		for (int i = 0; i < mAnimation.size(); i++){
			delete mAnimation[i];
		}
	}

	//アニメーション
	std::vector<CAnimation*> mAnimation;

	float mTime;	//現在時間
	float mWeight;	//重み
	float mMaxTime;	//最大時間
};

/*
CSkinWeights
スキンウェイトクラス
*/
class CSkinWeights{
public:
	char *mpFrameName;	//フレーム名
	int mFrameIndex;	//フレーム番号
	int mIndexNum;		//頂点番号数
	int *mpIndex;		//頂点番号配列
	float *mpWeight;	//頂点ウェイト配列
	CMatrix mOffset;	//オフセットマトリックス

	CSkinWeights(CModelX *model);

	~CSkinWeights(){
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpIndex);
		SAFE_DELETE_ARRAY(mpWeight);
	}
};

//CMashクラスの定義
class CMesh{
public:
	int mVertexNum;		//頂点数
	CVector *mpVertex;	//頂点データ
	int mFaceNum;		//面数
	int *mpVertexIndex;	//面を構成する頂点番号
	int mNormalNum;		//法線数
	CVector *mpNormal;	//法線データ
	int mMaterialNum;	//マテリアル数
	int mMaterialIndexNum;	//マテリアル番号数(関数)
	int *mpMaterialIndex;	//マテリアル番号
	//テクスチャ座標データ
	float *mpTextureCoords;
	CVector *mpAnimateVertex;	//アニメーション用頂点
	CVector *mpAnimateNormal;	//アニメーション用法線
	std::vector<CMaterial*>mMaterial;	//マテリアルデータ
	//スキンウェイト
	std::vector<CSkinWeights*>mSkinWeights;

	//マテリアル毎の面数
	std::vector<int>mMaterialVertexCount;
	//頂点バッファ識別子
	GLuint mMyVertexBufferId;
	//頂点バッファの作成
	void CreateVertexBuffer();

	//コンストラクタ
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
		, mpTextureCoords(nullptr)
		, mMyVertexBufferId(0)
	{}
	//デストラクタ
	~CMesh(){
		SAFE_DELETE_ARRAY(mpVertex);
		SAFE_DELETE_ARRAY(mpVertexIndex);
		SAFE_DELETE_ARRAY(mpNormal);
		SAFE_DELETE_ARRAY(mpMaterialIndex);
		SAFE_DELETE_ARRAY(mpAnimateVertex);
		SAFE_DELETE_ARRAY(mpAnimateNormal);
		SAFE_DELETE_ARRAY(mpTextureCoords);
		//スキンウェイトの削除
		for (int i = 0; i < mSkinWeights.size(); i++){
			delete mSkinWeights[i];
		}
	}
	//読み込み処理
	void Init(CModelX *model);
	void Render();
	//頂点にアニメーション適用
	void AnimateVertex(CModelX *model);
	void AnimateVertex(CMatrix*);
};

//CModelXFrameクラスの定義
class CModelXFrame{
public:
	std::vector<CModelXFrame*> mChild;	//子フレームの配列
	CMatrix mTransformMatrix;	//変換行列
	char* mpName;		//フレーム名前
	int mIndex;			//フレーム番号

	CMatrix mCombinedMatrix; //合成行列
	//合成行列の作成
	void AnimateCombined(CMatrix* parent);
	//コンストラクタ
	CModelXFrame(CModelX* model);
	//デストラクタ
	~CModelXFrame(){
		//子フレームを全て開放する
		std::vector<CModelXFrame*>::iterator itr;
		for (itr = mChild.begin(); itr != mChild.end(); itr++){
			delete *itr;
		}
		//名前のエリアを開放する
		SAFE_DELETE_ARRAY(mpName);
	}
	CMesh mMesh;	//Meshデータ
	void Render();

	CModelXFrame()
		:mpName(nullptr)
		, mIndex(0){}	//コンストラクタ
};

/*
CModelX
Xファイル形式の3Dモデルデータをプログラムで認識する
*/
class CModelX{
public:
	char* mpPointer;	//読み込み位置
	char mToken[1024];	//取り出した単語の領域
	std::vector<CModelXFrame*>mFrame;	//フレームの配列
	//アニメーションセットの配列
	std::vector<CAnimationSet*>mAnimationSet;
	std::vector<CMaterial*>mMaterial;	//マテリアルの配列

	//シェーダー用スキンマトリックス
	CMatrix *mpSkinningMatrix;
	CMyShader mShader;	//シェーダーのインスタンス

	CModelX()
		:mpPointer(nullptr)
		, mpSkinningMatrix(nullptr)
	{}

	~CModelX(){
		if (mFrame.size() > 0)
		{
			delete mFrame[0];
		}
		for (int i = 0; i < mAnimationSet.size(); i++){
			delete mAnimationSet[i];
		}
		//マテリアルの解放
		for (int i = 0; i < mMaterial.size(); i++){
			delete mMaterial[i];
		}
		SAFE_DELETE_ARRAY(mpSkinningMatrix);
	}

	//ファイル読み込み
	void Load(char* file);
	//単語の取り出し
	void GetToken();
	//ノードの読み飛ばし
	void SkipNode();

	//浮動小数点データの取得
	float GetFloatToken();

	//整数データの取得
	int GetIntToken();

	void Render();

	//フレーム名に該当するフレームのアドレスを返す
	CModelXFrame* FindFrame(char* name);

	void AnimateFrame();

	//スキンウェイトのフレーム番号設定
	void SetSkinWeightFrameIndex();

	//頂点にアニメーションを適用
	void AnimateVertex();

	//マテリアルの検索
	CMaterial* FindMaterial(char* name);

	void AnimateVertex(CMatrix*);

	/*
	アニメーションを抜き出す
	idx:分割したいアニメーションセットの番号
	start:分割したいアニメーションの開始時間
	end:分割したいアニメーションの終了時間
	name:追加するアニメーションセットの名前
	*/
	void CModelX::SeparateAnimationSet(int idx, int start, int end, char *name);

	//シェーダーを使った描画
	void RenderShader(CMatrix *m);
};

#endif