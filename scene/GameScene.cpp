#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "Player.h"
#include "MyMath.h"
#include"EnemyBullet.h"
#include"AxisIndicator.h"
#include"Collider.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete modelSkydome_;
	delete skydome_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	textureHandle_ = TextureManager::Load("mario.jpg");
	model_ = Model::Create();
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);
	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
	collider_ = new Collider;
	worldTransform_.Initialize();//ワールドトランスフォームの初期化
	viewProjection_.Initialize();//ビュープロジェクションの初期化
	viewProjection_.eye = { 0,0,-50 };
	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_);
	player_ = std::make_unique<Player>();
	enemy_ = std::make_unique<Enemy>();
	enemy_->SetPlayer(player_.get());
	player_->Initialize(model_,textureHandle_);
	enemy_->Initialize(model_, textureHandle_);
}

void GameScene::Update() {
	debugCamera_->Update();//デバッグカメラの更新
	
	player_->Update();//自キャラの更新
	enemy_->Update();//敵キャラの更新
	skydome_->Update();
	debugText_->SetPos(50, 70);
	debugText_->Printf("eye:(%f,%f,%f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	skydome_->Draw(viewProjection_);
	player_->Draw(viewProjection_);//自キャラの描画
	enemy_->Draw(viewProjection_);//敵キャラの描画
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
void GameScene::CheckAllCollisions()
{
	//判定対象AとBの座標
	Vector3 p_Pos,e_Pos,pb_Pos,eb_Pos;

	Vector3 p_radius, e_radius, pb_radius, eb_radius;

	//自弾リストの取得
	const std::list<std::unique_ptr<PlayerBullet>>& playerBullets_ = player_->GetBullets();
	//敵弾リストの取得
	const std::list<std::unique_ptr<EnemyBullet>>& enemyBullets_ = enemy_->GetBullets();
#pragma 自キャラと敵弾の当たり判定
	//自キャラの座標
	p_Pos = player_->GetWorldPosition();
	
	//自キャラの半径
	p_radius = player_->GetRadius();


	//自キャラと敵弾全てのあたり判定
	for (const std::unique_ptr<EnemyBullet>& EnemyBullet : enemyBullets_) {


		//敵弾の座標
		e_Pos = EnemyBullet->GetWorldPosition();
		e_radius = EnemyBullet->GetRadius();

	
		
			//球と球の交差判定
			if(collider_->OnBulletCollision(p_Pos.x,p_Pos.y,p_Pos.z,p_radius.x,e_Pos.x,e_Pos.y,e_Pos.z,e_radius.x) == true) {
				//自キャラの衝突時コールバックを呼び出す
				player_->OnCollision();
				//敵弾の衝突時コールバックを呼び出す
				EnemyBullet->OnCollision();
			}
	}
#pragma endregion

#pragma 自弾と敵キャラのあたり判定
	

	
	e_Pos = enemy_->GetWorldPosition();
	e_radius =enemy_->GetRadius();

	for (const std::unique_ptr<PlayerBullet>& PlayerBullet : playerBullets_) {

		//自キャラの座標
		pb_Pos = PlayerBullet->GetWorldPosition();

		//自キャラの半径
		pb_radius = PlayerBullet->GetRadius();
		


		//球と球の交差判定
		if (collider_->OnBulletCollision(pb_Pos.x, pb_Pos.y, pb_Pos.z, pb_radius.x, e_Pos.x, e_Pos.y, e_Pos.z, e_radius.x) == true) {
			
			enemy_->OnCollision();
			
			PlayerBullet->OnCollision();
		}
	}


#pragma endregion

#pragma 自弾と敵弾のあたり判定
	for (const std::unique_ptr<PlayerBullet>& PlayerBullet : playerBullets_) {
		for (const std::unique_ptr<EnemyBullet>& EnemyBullet : enemyBullets_) {


			//敵弾の座標
			eb_Pos = EnemyBullet->GetWorldPosition();
			eb_radius = EnemyBullet->GetRadius();

			//自キャラの座標
			pb_Pos = PlayerBullet->GetWorldPosition();

			//自キャラの半径
			pb_radius = PlayerBullet->GetRadius();

			//球と球の交差判定
			if (collider_->OnBulletCollision(pb_Pos.x, pb_Pos.y, pb_Pos.z, pb_radius.x, eb_Pos.x, eb_Pos.y, eb_Pos.z, eb_radius.x) == true) {
				EnemyBullet->OnCollision();
				//敵弾の衝突時コールバックを呼び出す
				PlayerBullet->OnCollision();
			}
		}
	}

#pragma endregion
	
	
}


