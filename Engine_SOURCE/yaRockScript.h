#pragma once
#include "yaWallScript.h"
#include "yaRock.h"

namespace ya
{
	class RockScript : public WallScript
	{
	public:
		RockScript();
		virtual ~RockScript();

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
		void SetRockType(Rock::eRockType type);
	};
}