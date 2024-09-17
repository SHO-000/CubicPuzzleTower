//-----------------------------------------------------------------------------
// UIベースクラス
//-----------------------------------------------------------------------------
#pragma once
#include "DxLib.h"
#include "Define.h"
#include "UIControll.h"
#include "MiniMapControll.h"

class UIBase
{
public:
	UIBase();		// コンストラクタ
	~UIBase();		// デストラクタ

	//---主要関数-------------------------------------------------------------------
	void Create();		// 生成
	void Delete();		// 削除
	void Init();		// 初期化
	void Update();		// 更新
	void Draw();		// 描画
	//-----------------------------------------------------------------------------

	//---Set関数---------------------------------------------------------------------
	void SetNowScene(SCENE_TYPE scene) { m_nowScene = scene; }
	void SetMiniMapInfo(int i, VECTOR cubePos, VECTOR playerPos, VECTOR dirPos, bool isSupport);
	void SetNowStageNum(int num) { p_uiControll->SetNowStageNum(num); }
	void SetLevelNum(int num) { p_uiControll->SetLevelNum(num); }
	//------------------------------------------------------------------------------

private:
	//---変数群----------------------------------------------------------------------
	UIControll *p_uiControll;
	MiniMapControll *p_miniMap;

	SCENE_TYPE m_nowScene;		// 現在のシーン
	//------------------------------------------------------------------------------
};

