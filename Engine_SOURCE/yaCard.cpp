#include "yaCard.h"
#include "yaCardScript.h"
#include "yaTransform.h"

namespace ya
{
	Card::Card()
		: Pickup(eItemType::Card)
		, mCard(eCards::None)
	{
		AddComponent<CardScript>();
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
	void Card::SetCardType(eCards card)
	{
		mCard = card; 

		CardScript* cardScript = GetScript<CardScript>();
		cardScript->SetCard(card);
	}
}