#pragma once
#include <math.h>
#include "DxLib.h"

class FPS
{
public:
	FPS();
	~FPS();

	bool Update();
	void Wait();
private:
	int m_startTime;			// ����J�n����
	int m_count;				// �J�E���^
	float m_fps;				// fps
	static const int N = 60;	// ���ς��Ƃ�T���v����
	static const int Fps = 60;	// �ݒ肷��FPS
};

