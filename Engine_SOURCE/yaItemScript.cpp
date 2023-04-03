#include "yaItemScript.h"

#include "yaItemScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "yaSpriteRenderer.h"
#include "yaObject.h"

#include "yaTear.h"
#include "yaBomb.h"
#include "yaPlayer.h"
#include "yaScene.h"
#include "yaSceneManager.h"

namespace ya
{
	ItemScript::ItemScript()
		: Script()
		, mTransform(nullptr)
		, mAnimator(nullptr)
		, mItemType(eItemType::None)
	{
	}
	ItemScript::~ItemScript()
	{
	}
	void ItemScript::Initialize()
	{
	}
	void ItemScript::Update()
	{
	}

	void ItemScript::FixedUpdate()
	{
	}
	void ItemScript::Render()
	{
	}

	void ItemScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void ItemScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void ItemScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void ItemScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void ItemScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void ItemScript::OnTriggerExit(Collider2D* collider)
	{
	}
}