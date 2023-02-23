#pragma once
#include "yaEntity.h"
#include "yaMath.h"

using namespace ya::enums;
namespace ya
{
	class GameObject;
	class Component : public Entity
	{
	public:
		Component(eComponentType type);
		virtual ~Component();

		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() = 0;

		UINT GetOrder() { return (UINT)mType; }
		eComponentType GetType() { return mType; }

		GameObject* GetOwner() { return mOwner; }
		void SetOwner(GameObject* owner) { mOwner = owner; }

	private:
		const eComponentType mType;
		GameObject* mOwner;
	};
}

