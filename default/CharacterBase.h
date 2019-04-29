#pragma once
#include "DxLib.h"
#include "PlayerControll.h"

class CharacterBase
{
public:
	CharacterBase();
	~CharacterBase();

	//---��v�֐�-----------------------------------
	void Create();
	void Delete();
	void Init();
	void Update();
	void Draw();
	//---------------------------------------------

	//---Get�֐�-----------------------------------
	VECTOR GetPlayerPos() { return p_player->GetPos(); }
	bool GetPlayerIsGround() { return p_player->GetIsGround(); }
	//---------------------------------------------
	
	//---Set�֐�-----------------------------------
	void SetFloorPosToPlayer(VECTOR v) { p_player->SetFloorPos(v); }
	void SetIsCanMoveToPlayer(bool flag) { p_player->SetIsCanMove(flag); }
	//---------------------------------------------

private:
	PlayerControll *p_player;

};

