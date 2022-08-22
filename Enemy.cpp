#include "Enemy.h"
#include <cassert>
#include "Player.h"
#include "VectorMove.h"

Enemy::Enemy() {

}

Enemy::~Enemy() {

}

void Enemy::Initialize(Model* model, uint32_t texureHandle) {
	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
	//NULL�|�C���^�`�F�b�N
	assert(model);
	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	this->model_ = model;

	textureHandle_ = TextureManager::Load("player_shade.jpg");

	debugText_ = DebugText::GetInstance();
	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();

	vectorMove_ = new VectorMove();

	myMath_ = new MyMath();
	//�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = { 0,2,30 };
	worldTransform_.scale_ = { 1,1,1 };
}

void Enemy::LeaveMove() {
	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0,0,0 };

	//�L�����N�^�[�̈ړ�����
	const float kCharacterSpeed = 0.1f;

	move = { -kCharacterSpeed,-kCharacterSpeed,0 };

	worldTransform_.translation_ += move;

	vectorMove_->MyUpdate(worldTransform_);

	//�s��X�V
	//�s��̓]��
	worldTransform_.TransferMatrix();
}

void Enemy::ApprochMove() {

	enemyBullets_.remove_if([](std::unique_ptr<EnemyBullet>& EnemyBullet) {
		return EnemyBullet->IsDead();
		});
	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0,0,0 };

	//�L�����N�^�[�̈ړ�����
	const float kCharacterSpeed = 0.1f;

	move = { 0,0,-kCharacterSpeed };

	worldTransform_.translation_ += move;

	vectorMove_->MyUpdate(worldTransform_);

	eFireTime--;//���˃^�C�}�[�J�E���g�_�E��

	if (eFireTime == 0) {
		Fire();//�e�𔭎�

		eFireTime = kFireInterval;//���˃^�C�}�[��������
	}

	for (std::unique_ptr<EnemyBullet>& EnemyBullet : enemyBullets_) {
		if (EnemyBullet) {
			EnemyBullet->Update();
		}
	}


	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
	//�s��X�V
	//�s��̓]��
	worldTransform_.TransferMatrix();
}

void Enemy::Move() {
	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0,0,0 };

	//�L�����N�^�[�̈ړ�����
	const float kCharacterSpeed = 0.1f;

	move = { 0,0,-kCharacterSpeed };

	worldTransform_.translation_ += move;

	vectorMove_->MyUpdate(worldTransform_);

	//�s��X�V
	//�s��̓]��
	worldTransform_.TransferMatrix();
}



void Enemy::Update() {
	switch (phase_) {
	case Phase::Approch:
	default:
		//�K��̈ʒu�ɓ��B�����痣�E
		ApprochMove();
		break;
	case Phase::Leave:
		LeaveMove();
		break;
	}
	for (std::unique_ptr<EnemyBullet>& EnemyBullet : enemyBullets_) {
		EnemyBullet->Update();
	}
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	for (std::unique_ptr<EnemyBullet>& EnemyBullet : enemyBullets_) {
		if (EnemyBullet) {
			EnemyBullet->Draw(viewProjection);
		}
	}
}

Vector3 Enemy::GetWorldPosition()
{
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;

}

void Enemy::Fire()
{
	assert(player_);
	//�e�̑��x
	const float eBulletSpeed = 0.01f;
	Vector3 playerVec = player_->GetWorldPosition();
	Vector3 enemyVec = GetWorldPosition();
	Vector3 Difference = playerVec;
	Difference -= enemyVec;
	Vector3 normalize(Difference);
	Difference *= eBulletSpeed;
	Vector3 velocity(Difference);

	//�e�𐶐����A������
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	//�e��o�^����
	enemyBullets_.push_back(std::move(newBullet));
}