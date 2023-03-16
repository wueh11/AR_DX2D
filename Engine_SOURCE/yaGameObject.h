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
			Dead, /// 한곳에 모으고 Update가 끝난 후 삭제
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
				mScripts.push_back(dynamic_cast<Script*>(comp));
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

		template <typename T>
		std::vector<T*> GetComponents()
		{
			std::vector<T*> components = {};
			T* comp;
			for (auto c : mComponents)
			{
				comp = dynamic_cast<T*>(c);

				if (comp != nullptr)
					components.push_back(comp);
			}

			return components;
		}

		std::vector<Script*>& GetScripts() { return mScripts; }

		bool IsDead() { return (mState == eState::Dead); }
		void Pause() { mState = eState::Paused; }
		void Death() { mState = eState::Dead; }

		eState GetState() { return mState; }

		bool IsDontDestroy() { return mbDontDestroy; }
		void DontDestroy(bool enable) { mbDontDestroy = enable; }

		void SetLayerType(eLayerType type) { mType = type; }
		eLayerType GetLayerType() { return mType; }

	protected:
		std::vector<Component*> mComponents;

	private:
		eState mState;
		eLayerType mType;
		std::vector<Script*> mScripts;
		bool mbDontDestroy;
	};
}
