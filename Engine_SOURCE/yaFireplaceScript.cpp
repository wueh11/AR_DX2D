#include "yaFireplaceScript.h"

#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaObject.h"

#include "yaPlayer.h"
#include "yaScene.h"
#include "yaSceneManager.h"
#include "yaRigidbody.h"

#include "yaInput.h"

namespace ya
{
	FireplaceScript::FireplaceScript()
		: Script()
	{
	}
	FireplaceScript::~FireplaceScript()
	{
	}
	void FireplaceScript::Initialize()
	{
	}

	void FireplaceScript::Update()
	{
	}

	void FireplaceScript::FixedUpdate()
	{
	}
	void FireplaceScript::Render()
	{
	}

	void FireplaceScript::OnCollisionEnter(Collider2D* collider)
	{
		GameObject* other = collider->GetOwner();
		Player* player = dynamic_cast<Player*>(other);

		if (player != nullptr)
		{
		}
	}

	void FireplaceScript::OnCollisionStay(Collider2D* collider)
	{
		
	}
	void FireplaceScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void FireplaceScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void FireplaceScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void FireplaceScript::OnTriggerExit(Collider2D* collider)
	{
	}
}