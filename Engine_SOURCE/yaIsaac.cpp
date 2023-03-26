#include "yaIsaac.h"
#include "yaMeshRenderer.h"
#include "yaMaterial.h"
#include "yaMesh.h"
#include "yaResources.h"
#include "yaPlayerScript.h"
#include "yaTransform.h"

namespace ya
{
	Isaac::Isaac()
		: GameObject()
		, mMr(nullptr)
	{
		SetName(L"Isaac");
	}

	Isaac::~Isaac()
	{
	}

	void Isaac::Initialize()
	{
		GameObject::Initialize();
	}

	void Isaac::Update()
	{
		GameObject::Update();
	}

	void Isaac::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Isaac::Render()
	{
		GameObject::Render();
	}
}