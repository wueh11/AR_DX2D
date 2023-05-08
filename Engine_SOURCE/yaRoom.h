#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Room : public GameObject
	{
	public:
		Room(int x, int y);
		virtual ~Room();
	
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		void AddRoomObject(GameObject* roomObj, int x = -1, int y = -1);

		void Active(bool active) { mbActive = active; }
		bool IsActive() { return mbActive; }

		void SetRoomPos(Vector2 roomPos);

		Vector2 GetRoomPos() { return mRoomPos; }

	private:
		bool mbActive;	// player�� �濡 ���� ��� true
		bool mbClear;	// player�� ���� ���͸� ��� óġ���� ��� true
		bool mbLock;	// ���谡 �ʿ��� ��(����, ������), player�� ���� ���� ����� ������ ��� false

		int mMonsterCount;	// �濡 ���� ���� ��

		GameObject* mGrid[7][13];	// ���� �����ϴ� gameobject. ��ĭ�ϰ�� nullptr

		Vector2 mRoomPos;
	};
}