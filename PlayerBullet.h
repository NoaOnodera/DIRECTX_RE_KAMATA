#pragma once
#include"Player.h"
#include "Model.h"
#include "Input.h" 
#include "WorldTransform.h"
#include "ViewProjection.h"
#include"TextureManager.h"
#include "VectorMove.h"
#include "MyMath.h"
class PlayerBullet
{
public:
	PlayerBullet();
	~PlayerBullet();
	void Initialize(Model* model, const Vector3& position,const Vector3& velocity);
	void Update();
	void OnCollision();
	Vector3 GetWorldPosition();
	Vector3 GetRadius();
	void Draw(const ViewProjection& viewProjection);
	bool IsDead() const { return isDead_; }
private:
	WorldTransform worldTransform_;//���[���h�ϊ��f�[�^
    
	Model* model_ = nullptr;//���f���̃|�C���^

	uint32_t textureHandle_ = 0u;//�e�N�X�`���n���h��
	
	Vector3 velocity_;//���x

	VectorMove* vectorMove_ = nullptr;

	static const int32_t kLifeTime = 60 * 5;//����

	int32_t deathTimer_ = kLifeTime;//�f�X�^�C�}�[

	bool isDead_ = FALSE;
};

