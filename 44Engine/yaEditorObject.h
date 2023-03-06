#pragma once
#include "..\Engine_SOURCE\yaGameObject.h"

namespace ya
{
	class EditorObject : public GameObject
	{
	public:
		EditorObject();
		~EditorObject();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:

	};

}
