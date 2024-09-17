//-----------------------------------------------------------------------------
// UIコントロールクラス
//-----------------------------------------------------------------------------
#include "UIControll.h"

//-----------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------
UIControll::UIControll()
{
	m_graphTitle = LoadGraph("data/title2.png");
	m_graphStart = LoadGraph("data/start.png");

	m_graphLevel[0] = LoadGraph("data/easy.png");
	m_graphLevel[1] = LoadGraph("data/normal.png");
	m_graphLevel[2] = LoadGraph("data/hard.png");
	m_graphLevel[3] = LoadGraph("data/extra.png");
	m_graphBackGound = LoadGraph("data/select.png");
	m_graphSlime = LoadGraph("data/slime.png");

	LoadDivGraph("data/floor.png", 12, 12, 1, 180, 120, m_graphFloorNum, TRUE);
	m_graphManual = LoadGraph("data/sousa.png");
	m_graphTutorial[0] = LoadGraph("data/tutorial1.png");
	m_graphTutorial[1] = LoadGraph("data/tutorial2.png");
	m_graphTutorial[2] = LoadGraph("data/tutorial3.png");
	m_graphTutorial[3] = LoadGraph("data/tutorial4.png");
	m_graphTutorial[4] = LoadGraph("data/tutorial5.png");
}

//-----------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------
UIControll::~UIControll()
{
	DeleteGraph(m_graphTitle);
	DeleteGraph(m_graphStart);
	for (int i = 0; i < 12; i++)
	{
		DeleteGraph(m_graphFloorNum[i]);
	}
	DeleteGraph(m_graphManual);
}

//-----------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------
void UIControll::Init()
{
	m_startTime = 0;
	m_alpha = 255;
	m_nowStageNum = 0;
	m_tutorialNum = 0;
	m_tutCnt = 0;

	m_isBlink = false;
}

//-----------------------------------------------------------------------------
// 更新（タイトル）
//-----------------------------------------------------------------------------
void UIControll::UpdateTitle()
{
	BlinkGraph(1);
}

//-----------------------------------------------------------------------------
// 更新（プレイ中）
//-----------------------------------------------------------------------------
void UIControll::UpdatePlay()
{
	if (m_tutCnt < 100)
	{
		m_tutCnt++;
	}
	else
	{
		m_alpha -= 5;
	}

	if (m_alpha == 0)
	{
		m_tutorialNum++;
		if (m_tutorialNum > 4)
		{
			m_tutorialNum = 0;
		}
		m_alpha = 255;
		m_tutCnt = 0;
	}
}

//-----------------------------------------------------------------------------
// 描画（タイトル）
//-----------------------------------------------------------------------------
void UIControll::DrawTitle()
{
	DrawGraph(0, 0, m_graphTitle, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
	DrawGraph(0, 0, m_graphStart, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void UIControll::DrawSelect()
{
	DrawGraph(0, 0, m_graphBackGound, TRUE);

	SetDrawBright(150, 150, 150);
	if (m_levelNum == EASY)
	{
		SetDrawBright(255, 255, 255);
	}
	DrawGraph(0, 0, m_graphLevel[0], TRUE);
	SetDrawBright(150, 150, 150);

	if (m_levelNum == NORMAL)
	{
		SetDrawBright(255, 255, 255);
	}
	DrawGraph(0, 0, m_graphLevel[1], TRUE);
	SetDrawBright(150, 150, 150);

	if (m_levelNum == HARD)
	{
		SetDrawBright(255, 255, 255);
	}
	DrawGraph(0, 0, m_graphLevel[2], TRUE);
	SetDrawBright(150, 150, 150);

	if (m_levelNum == EXTRA)
	{
		SetDrawBright(255, 255, 255);
	}
	DrawGraph(0, 0, m_graphLevel[3], TRUE);
	SetDrawBright(255, 255, 255);
}

//-----------------------------------------------------------------------------
// 描画（プレイ中）
//-----------------------------------------------------------------------------
void UIControll::DrawPlay()
{
	DrawGraph(SCREEN_W / 2 - 90, 100, m_graphFloorNum[m_nowStageNum - 1], TRUE);
	DrawGraph(0, 50, m_graphManual, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
	DrawGraph(0, 0, m_graphTutorial[m_tutorialNum], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

// 点滅処理（引数に指定した秒毎にalphaを変更して点滅させる）
void UIControll::BlinkGraph(float interval)
{
	if (!m_isBlink)
	{
		m_startTime = GetNowCount();
		m_isBlink = true;
	}

	if (m_isBlink && (GetNowCount() - m_startTime) / 1000 >= interval)
	{
		if (m_alpha == 0)
		{
			m_alpha = 255;
		}
		else
		{
			m_alpha = 0;
		}

		m_isBlink = false;
	}
}
