#pragma once
#include "yaGameObject.h"
#include "IsaacItems.h"

using namespace ya::isaac;
namespace ya
{
	class Item : public GameObject
	{
	public:
		Item(eItemType itemType);
		virtual ~Item();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	};
}
