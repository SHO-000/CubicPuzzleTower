//-----------------------------------------------------------------------------
// UIコントロールクラス
//-----------------------------------------------------------------------------
#pragma once
#include "DxLib.h"
#include "Define.h"

class UIControll
{
public:
	UIControll();
	~UIControll();
	
	//---主要関数-------------------------------------------------------------------
	void Init();
	void UpdateTitle();
	void UpdatePlay();
	void DrawTitle();
	void DrawSelect();
	void DrawPlay();
	//-----------------------------------------------------------------------------

	//---Set関数---------------------------------------------------------------------
	void SetNowStageNum(int num) { m_nowStageNum = num; }
	void SetLevelNum(int num) { m_levelNum = num; }
	//-----------------------------------------------------------------------------

private:
	void BlinkGraph(float interval);		// 点滅処理

	//---変数群----------------------------------------------------------------------
	int m_graphTitle;
	int m_graphStart;
	int m_graphLevel[4];
	int m_graphBackGound;
	int m_graphSlime;
	int m_graphFloorNum[12];
	int m_graphManual;
	int m_graphTutorial[5];

	int m_alpha;
	int m_startTime;
	int m_levelNum;
	int m_nowStageNum;
	int m_tutorialNum;
	int m_tutCnt;

	bool m_isBlink;

	SCENE_TYPE m_nowScene;
	//-----------------------------------------------------------------------------
};

