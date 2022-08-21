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
	void Initialize(Model* model, const Vector3& position);
	void Update();
	void Draw(const ViewProjection& viewProjection);
private:
	WorldTransform worldTransform_;//���[���h�ϊ��f�[�^
    
	Model* model_ = nullptr;//���f���̃|�C���^

	uint32_t textureHandle_ = 0u;//�e�N�X�`���n���h��
	
	VectorMove* vectorMove_ = nullptr;
};

