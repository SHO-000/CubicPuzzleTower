#pragma once
#include "DxLib.h"

class FieldObjectManager
{
public:
	FieldObjectManager();
	~FieldObjectManager();

	//---��v�֐�-----------------------------------
	void Init();
	void Update();
	void Draw();
	//---------------------------------------------

	//---Get�֐�-----------------------------------
	VECTOR GetFloorPos() { return m_floorPos; }
	bool GetIsEndRising() { return m_isEndRising; }
	//---------------------------------------------

	//---Set�֐�-----------------------------------
	void SetIsRising(bool flag) { m_isRising = flag; }
	//---------------------------------------------
private:
	void MoveFloor();

	int m_modelHandleFloor;
	int m_modelHandleTower;
	int m_modelHandleFrame;

	VECTOR m_floorPos;

	bool m_isRising;
	bool m_isEndRising;
};

