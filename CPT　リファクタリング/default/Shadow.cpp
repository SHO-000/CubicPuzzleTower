#include "Shadow.h"
#include "Title.h"
#include "Player.h"
#include "Scaffold.h"

Shadow::Shadow()
{
	modelHandle = MV1LoadModel("data/model/shadow.mqo");
}

Shadow::~Shadow()
{
	MV1DeleteModel(modelHandle);
}

void Shadow::Init()
{
	pos = VGet(0, 0.5f, 120);
	p_pos = VGet(0, 0.5f, 120);
	angle = 0.0f;
}

void Shadow::TitleUpdate(const Title & title)
{
	p_pos = title.GetPos();
	pos.x = p_pos.x;
	pos.y = 1.f;
	pos.z = p_pos.z;

	angle = title.GetAngle();

	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(modelHandle, pos);

	MV1SetScale(modelHandle, title.GetScale());
	// �RD���f���̉�]�p�ݒ�
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, angle / 180.0f * DX_PI_F, 0.0f));
}

void Shadow::Update(const Player& player, const Scaf& scaf)
{
	p_pos = player.GetPos();
	pos.x = p_pos.x;
	pos.z = p_pos.z;
	pos.y = scaf.GetPos().y + 0.5f;

	angle = player.GetAngle();

	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(modelHandle, pos);

	MV1SetScale(modelHandle, player.GetScale());
	// �RD���f���̉�]�p�ݒ�
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, angle / 180.0f * DX_PI_F, 0.0f));
}

void Shadow::Draw()
{
	MV1DrawModel(modelHandle);
}

