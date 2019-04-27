#include "FieldObjectManager.h"
#include "Sound.h"

FieldObjectManager::FieldObjectManager()
{
	m_modelHandleFloor = MV1LoadModel("data/model/scaffold.mqo");	//��
	m_modelHandleFrame = MV1LoadModel("data/model/frame.mqo");		//�g
	m_modelHandleTower = MV1LoadModel("data/model/tower.x");		//�^���[
}


FieldObjectManager::~FieldObjectManager()
{
	MV1DeleteModel(m_modelHandleFloor);
	MV1DeleteModel(m_modelHandleFrame);
	MV1DeleteModel(m_modelHandleTower);
}

void FieldObjectManager::Init()
{
	m_floorPos = VGet(0.f, -150.f, 0.f);

	m_isRising = false;
	m_isEndRising = false;
}

void FieldObjectManager::Update()
{
	MoveFloor();
}

void FieldObjectManager::Draw()
{
	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(m_modelHandleFloor, m_floorPos);
	MV1SetPosition(m_modelHandleTower, VGet(0, 0, 0));
	MV1SetPosition(m_modelHandleFrame, VGet(0, 0, 0));

	// �R�c���f���̕`��
	MV1DrawModel(m_modelHandleFloor);
	MV1DrawModel(m_modelHandleTower);
	MV1DrawModel(m_modelHandleFrame);
}

void FieldObjectManager::MoveFloor()
{
	// ���������Ă���ԁA���ʉ��Đ�
	if (m_floorPos.y != 0)
	{
		playSound(SE_SCAF);
	}
	else
	{
		stopSound(SE_SCAF);
		resetSound(SE_SCAF);
	}

	if (m_floorPos.y >= 0 && !m_isRising)
	{
		m_floorPos.y = 0.f;
		m_isEndRising = true;
	}
	else
	{
		m_floorPos.y += 2.f;
		m_isEndRising = false;
	}
}
