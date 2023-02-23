#pragma once
#include "yaComponent.h"
#include "yaScript.h"
#include "yaEntity.h"

namespace ya 
{
	class GameObject : public Entity
	{
	public:
		enum eState
		{
			Active,
			Paused, /// Update X, Render X
			Dead, /// �Ѱ��� ������ Update�� ���� �� ����
		};
		
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();

			eComponentType order = comp->GetType();

			if (order != eComponentType::Script)
			{
				mComponents[(UINT)order] = comp;
				mComponents[(UINT)order]->SetOwner(this);
			}
			else
			{
				mScripts.push_back(comp);
				comp->SetOwner(this);
			}

			return comp;
		}

		void AddComponent(Component* comp);

		template <typename T>
		T* GetComponent()
		{
			T* comp;
			for (auto c : mComponents)
			{
				comp = dynamic_cast<T*>(c);
				
				if (comp != nullptr)
					return comp;
			}

			return nullptr;
		}

		bool IsDead() { return (mState == eState::Dead); }
		void Pause() { mState = eState::Paused; }
		void Death() { mState = eState::Dead; }

		eState GetState() { return mState; }

	private:
		eState mState;
		std::vector<Component*> mComponents;
		std::vector<Component*> mScripts;
		
	};
}
