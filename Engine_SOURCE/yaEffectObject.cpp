#include "yaEffectObject.h"
#include "yaIsaacEnums.h"

#include "yaIsaacObject.h"
#include "yaRigidbody.h"

namespace ya
{
	EffectObject::EffectObject()
		: GameObject()
		, mEffectObjectOwner(nullptr)
	{
		SetName(L"EffectObject");

		Rigidbody* rigidbody = AddComponent<Rigidbody>();
	}
	EffectObject::~EffectObject()
	{
	}
	void EffectObject::Initialize()
	{
		GameObject::Initialize();
	}
	void EffectObject::Update()
	{
		GameObject::Update();
	}
	void EffectObject::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void EffectObject::Render()
	{
		GameObject::Render();
	}
}