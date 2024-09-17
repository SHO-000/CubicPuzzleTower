//-----------------------------------------------------------------------------
// レベルセレクトクラス
//-----------------------------------------------------------------------------
#include "LevelSelect.h"
#include "Define.h"
#include "Sound.h"
#include "InputInfo.h"

//---------------------
// コンストラクタ
//---------------------
LevelSelect::LevelSelect()
{
	// 処理なし
}

//---------------------
// デストラクタ
//---------------------
LevelSelect::~LevelSelect()
{
	// 処理なし
}

//---------------------
// 初期化
//---------------------
void LevelSelect::Init()
{
	m_levelNum = EASY;
}

//---------------------
// 更新
//---------------------
void LevelSelect::Update()
{
	if (GetInput(RIGHT) == PUSHDOWN)
	{
		playSound(SE_CURSOR);
		if (m_levelNum == EXTRA)
			m_levelNum = EASY;
		else
			m_levelNum++;
	}
	else if (GetInput(LEFT) == PUSHDOWN)
	{
		playSound(SE_CURSOR);
		if (m_levelNum == EASY)
			m_levelNum = EXTRA;
		else
			m_levelNum--;
	}
}
