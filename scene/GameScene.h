#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"
#include "Player.h"
#include "MyMath.h"
#include "Enemy.h"
#include"EnemyBullet.h"
#include"Collider.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void CheckAllCollisions();

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;
	uint32_t textureHandle_ = 0;//テクスチャハンドル
	Model* model_ = nullptr;//3Dモデル
	WorldTransform  worldTransform_;//ワールドトランスフォーム
	ViewProjection  viewProjection_;//ビュープロジェクション
	DebugCamera* debugCamera_ = nullptr;//デバックカメラ
	Collider* collider_ = nullptr;
	std::unique_ptr<Player>player_;//自キャラ
	std::unique_ptr<Enemy>enemy_;//敵キャラ
	std::unique_ptr<EnemyBullet>enemyBullet_;
	bool isDebugCameraActive_ = FALSE;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
