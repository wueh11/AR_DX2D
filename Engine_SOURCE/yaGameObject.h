#pragma once
#include "yaComponent.h"
#include "yaScript.h"
#include "yaEntity.h"
#include "yaAnimator.h"

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

			eComponentType type = comp->GetType();

			if (type != eComponentType::Script)
			{
				mComponents[(UINT)type] = comp;
				mComponents[(UINT)type]->SetOwner(this);
			}
			else
			{
				mScripts.push_back(dynamic_cast<Script*>(comp));
				comp->SetOwner(this);
			}

			comp->Initialize();

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

		template <typename T>
		T* GetScript()
		{
			T* script;
			for (auto s : mScripts)
			{
				script = dynamic_cast<T*>(s);

				if (s != nullptr)
					return script;
			}
			
			return nullptr;
		}

		std::vector<Script*>& GetScripts() { return mScripts; }

		bool IsDead() { return (mState == eState::Dead); }

		void SetActive() 
		{ 
			mState = eState::Active;
			Collider2D* collider = GetComponent<Collider2D>();
			if (collider != nullptr)
				collider->Active(true);

			for (auto obj : mChildren)
				obj->SetActive();
		}

		void Pause()
		{
			mState = eState::Paused;
			Collider2D* collider = GetComponent<Collider2D>();
			if(collider != nullptr)
				collider->Active(false);

			for (auto obj : mChildren)
				obj->Pause();
		}

		void Death()
		{
			mState = eState::Dead;
			for (auto obj : mChildren)
				obj->Death();
		}

		eState GetState() { return mState; }

		bool IsDontDestroy() { return mbDontDestroy; }
		void DontDestroy(bool enable) { mbDontDestroy = enable; }

		void SetLayerType(eLayerType type) { mType = type; }
		eLayerType GetLayerType() { return mType; }

		GameObject* GetParent() { return mParent; }
		void SetParent(GameObject* obj) { mParent = obj; }

		std::vector<GameObject*> GetChildren() { return mChildren; }
		void AddChild(GameObject* child) { mChildren.push_back(child); }

	protected:
		std::vector<Component*> mComponents;

	private:
		eState mState;
		eLayerType mType;
		std::vector<Script*> mScripts;
		bool mbDontDestroy;

		GameObject* mParent;
		std::vector<GameObject*> mChildren;
	};
}
