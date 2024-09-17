//-----------------------------------------------------------------------------
// シーンコントロールクラス
//-----------------------------------------------------------------------------
#include "SceneControll.h"

//-----------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------
SceneControll::SceneControll()
{
	// 処理なし
}

//-----------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------
SceneControll::~SceneControll()
{
	// 処理なし
}

//-----------------------------------------------------------------------------
// 生成
//-----------------------------------------------------------------------------
void SceneControll::Create()
{
	p_playerBase = new PlayerBase();
	p_playerBase->Create();

	p_objectBase = new ObjectBase();
	p_objectBase->Create();

	p_camera = new Camera();

	p_stage = new StageManager();

	p_uiBase = new UIBase();
	p_uiBase->Create();

	p_levelSelect = new LevelSelect();
}

//-----------------------------------------------------------------------------
// 削除
//-----------------------------------------------------------------------------
void SceneControll::Delete()
{
	p_playerBase->Delete();
	delete(p_playerBase);

	p_objectBase->Delete();
	delete(p_objectBase);

	delete(p_camera);

	delete(p_stage);

	p_uiBase->Delete();
	delete(p_uiBase);

	delete(p_levelSelect);
}

//-----------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------
void SceneControll::Init()
{
	m_nowScene = TITLE;

	p_playerBase->Init();

	p_objectBase->Init();

	p_stage->Init();

	p_uiBase->Init();

	p_levelSelect->Init();

	m_isChange = false;
}

//-----------------------------------------------------------------------------
// 更新（タイトル）
//-----------------------------------------------------------------------------
void SceneControll::UpdateTitle()
{
	p_uiBase->SetNowScene(m_nowScene);
	p_uiBase->Update();
}

//-----------------------------------------------------------------------------
// 更新（セレクト画面）
//-----------------------------------------------------------------------------
void SceneControll::UpdateSelect()
{
	p_levelSelect->Update();

	p_uiBase->SetNowScene(m_nowScene);
	p_uiBase->SetLevelNum(p_levelSelect->GetLevelNum());
}

//-----------------------------------------------------------------------------
// 更新（プレイ中）
//-----------------------------------------------------------------------------
void SceneControll::UpdatePlay()
{
	p_playerBase->SetFloorPosToPlayer(p_objectBase->GetFloorPos());
	p_playerBase->Update();

	p_camera->Update();

	p_objectBase->SetPlayerPosToCube(p_playerBase->GetPlayerPos());
	p_objectBase->Update();

	p_stage->Update();

	for (int i = 0; i < 9; i++)
	{
		p_uiBase->SetMiniMapInfo(i, p_objectBase->GetCubePos(i), p_playerBase->GetPlayerPos(),
			p_objectBase->GetCubeDirPos(), (p_objectBase->GetCubeIsSupport() && !p_objectBase->GetCubeIsClear()));
	}

	p_uiBase->SetNowScene(m_nowScene);
	p_uiBase->SetNowStageNum(p_stage->GetNowStageNum());
	p_uiBase->Update();
}

//-----------------------------------------------------------------------------
// 描画（タイトル）
//-----------------------------------------------------------------------------
void SceneControll::DrawTitle()
{
	p_uiBase->Draw();
}

//-----------------------------------------------------------------------------
// 描画（セレクト画面）
//-----------------------------------------------------------------------------
void SceneControll::DrawSelect()
{
	p_uiBase->Draw();
}

//-----------------------------------------------------------------------------
// 描画（プレイ中）
//-----------------------------------------------------------------------------
void SceneControll::DrawPlay()
{
	p_playerBase->Draw();

	p_objectBase->Draw();

	p_uiBase->Draw();

	p_stage->Draw();

}

// シーン切り替え処理
void SceneControll::ChangeScene()
{
	if (m_nowScene == TITLE)
	{
		playSound(BGM_TITLE);

		if (GetInput(START) == PUSHDOWN)
		{
			m_nowScene = SELECT;

			stopSound(BGM_TITLE);
			playSound(BGM_SELECT);
		}
	}
	else if (m_nowScene == SELECT)
	{
		if (GetInput(START) == PUSHDOWN)
		{
			if (p_levelSelect->GetLevelNum() == NORMAL)
			{
				p_stage->SetStageNum(4);
			}
			if (p_levelSelect->GetLevelNum() == HARD)
			{
				p_stage->SetStageNum(7);
			}
			if (p_levelSelect->GetLevelNum() == EXTRA)
			{
				p_stage->SetStageNum(10);
			}
			m_nowScene = PLAY;

			stopSound(BGM_SELECT);
			playSound(BGM_PLAY);
		}
	}
	else if (m_nowScene == PLAY)
	{
		if (p_objectBase->GetIsFloorRisingEnd())
		{
			p_playerBase->SetIsAbleMoveToPlayer(true);

			if (p_playerBase->GetPlayerIsGround())
			{
				p_objectBase->SetIsAbleShotToCube(true);
			}
			else
			{
				p_objectBase->SetIsAbleShotToCube(false);
			}
		}
		else
		{
			p_playerBase->SetIsAbleMoveToPlayer(false);

			p_objectBase->SetIsAbleShotToCube(false);
		}

		if (p_objectBase->GetCubeIsClear())
		{
			p_stage->SetIsNext(true);
			m_nowScene = NEXT;
		}
	}
	else if (m_nowScene == NEXT)
	{
		if (p_stage->GetIsChange())
		{
			p_playerBase->Init();
			p_objectBase->ChangeToNextStage(p_stage->GetNowStageNum());
			m_nowScene = PLAY;
		}
	}
}
