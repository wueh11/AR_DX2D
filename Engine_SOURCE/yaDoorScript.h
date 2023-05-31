#pragma once
#include "yaWallScript.h"
#include "yaDoor.h"

namespace ya
{
	class DoorScript : public WallScript
	{
	public:
		DoorScript();
		virtual ~DoorScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		virtual void OnTriggerEnter(Collider2D* collider) override;
		virtual void OnTriggerStay(Collider2D* collider) override;
		virtual void OnTriggerExit(Collider2D* collider) override;

	public:
		void SetDoorDirection(Door::eDirection dir);
		void SetDoorType(isaac::eRoomType doorType);

		void SetOpen(bool open);
		void SetDamaged(bool damaged);
		void SetLock(bool lock);

		void playDeco(isaac::eRoomType doorType);

	private:
		std::shared_ptr<Material> mMaterial;

		GameObject* mDoorBackground;
		GameObject* mDoorFrame;
		GameObject* mDoorLeft;
		GameObject* mDoorRight;
		GameObject* mDoorDeco;

	};
}
