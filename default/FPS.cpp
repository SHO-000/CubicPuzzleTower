#include "FPS.h"

//---------------------
// �R���X�g���N�^
//---------------------
FPS::FPS()
{
	m_startTime = 0;
	m_count = 0;
	m_fps = 0;
}

//---------------------
// �f�X�g���N�^
//---------------------
FPS::~FPS()
{
	// �����Ȃ�
}

//---------------------
// �X�V
//---------------------
bool FPS::Update()
{
	// 1�t���[���ڂȂ玞�����擾
	if (m_count == 0)
	{
		m_startTime = GetNowCount();
	}

	// 60�t���[���ڂȂ畽�ς��v�Z����
	if (m_count == N)
	{
		int t = GetNowCount();
		m_fps = 1000.f / ((t - m_startTime) / (float)N);
		m_count = 0;
		m_startTime = t;
	}
	m_count++;
	return true;
}

//---------------------
// �ҋ@
//---------------------
void FPS::Wait()
{
	int tookTime = GetNowCount() - m_startTime;		// ������������
	int waitTime = m_count * 1000 / Fps - tookTime;	// �҂ׂ�����
	if (waitTime > 0)
	{
		Sleep(waitTime);	// �ҋ@
	}
}
