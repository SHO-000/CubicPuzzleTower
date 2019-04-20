#include "Map.h"
#include "Player.h"


Map::Map()
{
	modelHandle_stage = MV1LoadModel("data/model/stage.mqo");	//�X�e�[�W�p�̃f�J���{�b�N�X
	modelHandle_frame = MV1LoadModel("data/model/frame.mqo");	//�g
	modelHandle_tower = MV1LoadModel("data/model/tower.x");	//�^���[
}


Map::~Map()
{
	// ���f���̃A�����[�h.
	MV1DeleteModel(modelHandle_stage);
	MV1DeleteModel(modelHandle_frame);
	MV1DeleteModel(modelHandle_tower);
}

void Map::Update()
{

}

void Map::Draw()
{
	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(modelHandle_stage, VGet(0, 0, 0));
	MV1SetPosition(modelHandle_frame, VGet(0, 0, 0));
	MV1SetPosition(modelHandle_tower, VGet(0, 0, 0));
	// �R�c���f���̕`��
	//MV1DrawModel(modelHandle_stage);
	MV1DrawModel(modelHandle_frame);
	MV1DrawModel(modelHandle_tower);
}