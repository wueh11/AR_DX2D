#pragma once
#include "yaScript.h"
#include "yaRock.h"

namespace ya
{
	class TrapdoorScript : public Script
	{
	public:
		TrapdoorScript();
		virtual ~TrapdoorScript();

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
		void Open(bool open) { mbOpen = open; }

	private:
		void OpenTrapDoor();

	private:
		GameObject* mPlayerTrapdoor;

		bool mbOpen;
		bool mbCreateComplete;

		bool mbInTrapdoor;
		float mTimer;
	};
}