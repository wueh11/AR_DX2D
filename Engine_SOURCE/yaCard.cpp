#include "yaCard.h"
#include "yaCardScript.h"
#include "yaTransform.h"

namespace ya
{
	Card::Card(eCards type)
		: Pickup(ePickupType::Card)
		, mCard(type)
	{
		CardScript* cardScript = AddComponent<CardScript>();
		cardScript->SetCard(type);
	}

	Card::~Card()
	{
	}
	void Card::Initialize()
	{
		GameObject::Initialize();
	}
	void Card::Update()
	{
		GameObject::Update();
	}
	void Card::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Card::Render()
	{
		GameObject::Render();
	}
}