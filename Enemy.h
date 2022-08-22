#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "DebugText.h"
#include "Input.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "TextureManager.h"
#include "VectorMove.h"
#include "MyMath.h"
#include "EnemyBullet.h"
#include <memory>
#include <list>

class Player;//�v���C���[�̑O���錾

enum class Phase {
	Approch,//�ڋ߂���
	Leave,//���E����
};

class Enemy
{
public:
	Enemy();
	~Enemy();
	void Initialize(Model* model, uint32_t textureHandle);
	void Move();
	void Update();
	void Draw(const ViewProjection& viewProjection);
	void ApprochMove();
	void LeaveMove();
	void Fire();
	void SetPlayer(Player* player) { player_ = player; }
	void OnCollision();
	Vector3 GetWorldPosition();
	Vector3 GetRadius();
    static const int kFireInterval = 60;//���ˊ��o
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return enemyBullets_; }
private:
	WorldTransform worldTransform_;//���[���h�ϊ��f�[�^

	Model* model_ = nullptr;//���f��

	uint32_t textureHandle_ = 0u;//�e�N�X�`���n���h��

	DebugText* debugText_ = nullptr;//�f�o�b�O�e�L�X�g

	MyMath* myMath_ = nullptr;//���w�֐�

	int32_t eFireTime = 60;

	VectorMove* vectorMove_ = nullptr;
    //�t�F�[�Y
	Phase phase_ = Phase::Approch;

	Player* player_ = nullptr;

	std::list<std::unique_ptr<EnemyBullet>>enemyBullets_;

	EnemyBullet* enemyBullet_ = nullptr;
};

