#include "yaStageManager.h"
#include "yaObject.h"

#include "yaItemManager.h"

#include "yaHeartFull.h"
#include "yaHeartHalf.h"
#include "yaSoulHeartFull.h"

#include "yaKey.h"
#include "yaCoin.h"
#include "yaBomb.h"
#include "yaPill.h"
#include "yaCard.h"
#include "yaActiveItem.h"
#include "yaTrinket.h"
#include "yaGaper.h"

namespace ya
{

	void StageManager::Initialize()
	{
		{
			Stage* stage1 = object::Instantiate<Stage>(eLayerType::Stage);
			Transform* stage1Tr = stage1->GetComponent<Transform>();
			mCurrentStage = stage1;

			

			mCurrentStage = stage1;*/
		}

	}

	Room* StageManager::CreateRoom(int x, int y)
	{
		Room* room = new Room(x, y);
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(eLayerType::Stage);
		layer.AddGameObject(room);
		room->Initialize();

		mCurrentStage->AddRoom(room, x, y);

		return room;
	}
}
