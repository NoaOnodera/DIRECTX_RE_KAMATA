#pragma once
#include "GameScene.h"
#include "WorldTransform.h"
#include "Model.h"
#include "Input.h" 
#include "WorldTransform.h"
#include "ViewProjection.h"
#include"TextureManager.h"
#include "VectorMove.h"
#include "MyMath.h"
class Player
{
public:
	Player();//コンストラクター
	~Player();//デストラクター
	void Initialize(Model*model,uint32_t textureHandle);//初期化
	void Update();
	void Draw(ViewProjection&viewProjection);
private:
	WorldTransform worldTransform_;//ワールド変換データ
	Model* model_ = nullptr;//モデル
	uint32_t textureHandle_ = 0u;//テクスチャハンドル
	Input* input_ = nullptr;//入力処理をするため
	DebugText* debugText_ = nullptr;//デバッグテキスト
	MyMath* myMath_ = nullptr;//自作の数学関数
	VectorMove* vectorMove_ = nullptr;//行列の計算
};

