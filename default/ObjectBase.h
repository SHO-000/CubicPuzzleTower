#pragma once
#include "CubeControll.h"
#include "FieldObjectManager.h"

class ObjectBase
{
public:
	ObjectBase();
	~ObjectBase();

	//---��v�֐�-----------------------------------
	void Create();
	void Delete();
	void Init();
	void Update();
	void Draw();
	//---------------------------------------------
	
	//---Get�֐�-----------------------------------
	VECTOR GetCubePos(int i) { return p_cube->GetPos(i); }
	VECTOR GetCubeDirPos() { return p_cube->GetDirPos(); }
	VECTOR GetFloorPos() { return p_fieldObject->GetFloorPos(); }
	bool GetCubeIsSupport() { return p_cube->GetIsSupport(); }
	bool GetCubeIsClear() { return p_cube->GetIsClear(); }
	bool GetFloorIsEndRising() { return p_fieldObject->GetIsEndRising(); }
	//---------------------------------------------

	//---Set�֐�-----------------------------------
	void SetPlayerPosToCube(VECTOR v) { p_cube->SetPlayerPos(v); }
	void SetIsCanShotToCube(bool flag) { p_cube->SetIsCanShot(flag); }
	void SetFloorIsRising(bool flag) { p_fieldObject->SetIsRising(flag); }
	//---------------------------------------------
	
	void NextStage(int n);

private:
	CubeControll *p_cube;
	FieldObjectManager *p_fieldObject;

};

