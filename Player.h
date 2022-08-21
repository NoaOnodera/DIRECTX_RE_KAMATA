#pragma once
#include "WorldTransform.h"
#include "DebugText.h"
#include "Input.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "TextureManager.h"
#include "VectorMove.h"
#include "MyMath.h"
#include "PlayerBullet.h"
#include <memory>
#include <list>
class Player
{
public:
	Player();//コンストラクター
	~Player();//デストラクター
	void Rotate();
	void Initialize(Model*model,uint32_t textureHandle);//初期化
	void Update();
	void Draw(ViewProjection&viewProjection);
	void Attack();
private:
	WorldTransform worldTransform_;//ワールド変換データ
	Model* model_ = nullptr;//モデル
	uint32_t textureHandle_ = 0u;//テクスチャハンドル
	Input* input_ = nullptr;//入力処理をするため
	DebugText* debugText_ = nullptr;//デバッグテキスト
	MyMath* myMath_ = nullptr;//自作の数学関数
	VectorMove* vectorMove_ = nullptr;//行列の計算
	//std::list<std::unique_ptr<PlayerBullet>>playerBullets_;//自弾のユニークポインター
	PlayerBullet* playerBullet_ = nullptr;//弾
};

