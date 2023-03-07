#pragma once
#include "..\Engine_SOURCE\yaGameObject.h"

namespace ya
{
	class DebugObject : public GameObject
	{
	public:
		DebugObject();
		~DebugObject();
		
		virtual void FixedUpdate();

	private:

	};

}
