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
		Pickup::Initialize();
	}
	void Card::Update()
	{
		Pickup::Update();
	}
	void Card::FixedUpdate()
	{
		Pickup::FixedUpdate();
	}
	void Card::Render()
	{
		Pickup::Render();
	}
	void Card::SetCardType(eCards card)
	{
		mCard = card; 

		CardScript* cardScript = GetScript<CardScript>();
		cardScript->SetCard(card);
	}
}