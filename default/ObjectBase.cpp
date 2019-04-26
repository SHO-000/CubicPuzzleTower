#include "ObjectBase.h"

ObjectBase::ObjectBase()
{
}


ObjectBase::~ObjectBase()
{
}

void ObjectBase::Create()
{
	p_cube = new CubeControll();
	p_fieldObject = new FieldObjectControll();
}

void ObjectBase::Delete()
{
	delete(p_cube);
	delete(p_fieldObject);
}

void ObjectBase::Init()
{
	p_cube->Init();
	p_fieldObject->Init();
}

void ObjectBase::Update()
{
	p_cube->Update();
	p_fieldObject->Update();
}

void ObjectBase::Draw()
{
	p_cube->Draw();
	p_fieldObject->Draw();
}

void ObjectBase::NextStage(int n)
{
	p_cube->ChangeNextPos(n);
	p_fieldObject->Init();
}
