#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include"TextureManager.h"
#include "VectorMove.h"
#include "DebugText.h"



class EnemyBullet
{
public:
	EnemyBullet();
	~EnemyBullet();
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);
	void Update();
	void Draw(const ViewProjection& viewProjection);
	bool IsDead() const { return isDead_; }
private:
	WorldTransform worldTransform_;	//���[���h�ϊ��f�[�^

	Model* model_ = nullptr;	//���f���̃|�C���^(�؂�Ă���)
	
	uint32_t textureHandle_ = 0u;//�e�N�X�`���n���h��
	
	Vector3 velocity_;//���x

	DebugText* debugText_ = nullptr;

	VectorMove* vectorMove_ = nullptr;
	
	static const int32_t eLifeTime = 60 * 5; //����<frm>

	int32_t deathTimer_ = eLifeTime;	//�f�X�^�C�}�[

	
	bool isDead_ = false;	//�f�X�t���O

};

