#include "yaAudioManager.h"

#include "yaObject.h"
#include "yaPlayer.h"

#include "yaPill.h"
#include "yaCard.h"
#include "yaTrinket.h"
#include "yaActiveItem.h"
#include "yaPassiveItem.h"
#include "yaHeartFull.h"
#include "yaStageScene.h"

#include "yaRigidbody.h"
#include "yaAudioClip.h"
#include "yaResources.h"

namespace ya
{
	void AudioManager::Initialize()
	{
		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\hurt_grunt.wav");
			Resources::Insert<AudioClip>(L"audio_hurt", clip);
		}
		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\tear block.wav");
			Resources::Insert<AudioClip>(L"tear block", clip);
		}
		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\tear fire 4.wav");
			Resources::Insert<AudioClip>(L"tear fire 4", clip);
		}
		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\tear fire 5.wav");
			Resources::Insert<AudioClip>(L"tear fire 5", clip);
		}
		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\power up1.wav");
			Resources::Insert<AudioClip>(L"power_up", clip);
		}
		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\thumbs up.wav");
			Resources::Insert<AudioClip>(L"thumbs up", clip);
		}
		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\thumbs down.wav");
			Resources::Insert<AudioClip>(L"thumbs down", clip);
		}

		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\vamp.wav");
			Resources::Insert<AudioClip>(L"vamp", clip);
		}


		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\chest drop 1.wav");
			Resources::Insert<AudioClip>(L"chest drop 1", clip);
		}
		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\chest open 1.wav");
			Resources::Insert<AudioClip>(L"chest_open", clip);
		}
		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\unlock.wav");
			Resources::Insert<AudioClip>(L"unlock", clip);
		}

		{ // monstro
			{
				std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
				clip->Load(L"..\\Resources\\Issac\\sfx\\boss spit blob barf 1.wav");
				Resources::Insert<AudioClip>(L"boss_spit_blob_barf", clip);
			}
			{
				std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
				clip->Load(L"..\\Resources\\Issac\\sfx\\forest boss stomp.wav");
				Resources::Insert<AudioClip>(L"forest boss stomp", clip);
			}
		}

		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\door heavy close.wav");
			Resources::Insert<AudioClip>(L"door heavy close", clip);
		}
		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\door heavy open.wav");
			Resources::Insert<AudioClip>(L"door heavy open", clip);
		}
		
		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\holy!.wav");
			Resources::Insert<AudioClip>(L"holy!", clip);
		}
		
		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\key drop 2.wav");
			Resources::Insert<AudioClip>(L"key drop 2", clip);
		}
		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\key pickup guantlet 4.wav");
			Resources::Insert<AudioClip>(L"key pickup guantlet 4", clip);
		}

		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\penny drop 1.wav");
			Resources::Insert<AudioClip>(L"penny drop 1", clip);
		}
		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\penny pickup 1.wav");
			Resources::Insert<AudioClip>(L"penny pickup 1", clip);
		}

		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\power up1.wav");
			Resources::Insert<AudioClip>(L"power up1", clip);
		}
		
		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\battery charge.wav");
			Resources::Insert<AudioClip>(L"battery charge", clip);
		}
		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\castleportcullis.wav");
			Resources::Insert<AudioClip>(L"castleportcullis", clip);
		}
		
		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\meat feet slow.wav");
			Resources::Insert<AudioClip>(L"meat feet slow", clip);
		}
		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\meat head shoot.wav");
			Resources::Insert<AudioClip>(L"meat head shoot", clip);
		}
		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\shakey kid roar.wav");
			Resources::Insert<AudioClip>(L"shakey kid roar", clip);
		}
		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\spider coughs.wav");
			Resources::Insert<AudioClip>(L"spider coughs", clip);
		}
		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\spider spit roar 0.wav");
			Resources::Insert<AudioClip>(L"spider spit roar 0", clip);
		}

		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\boss explosions 0.wav");
			Resources::Insert<AudioClip>(L"boss explosions 0", clip);
		}
		
		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\plop.wav");
			Resources::Insert<AudioClip>(L"plop", clip);
		}
		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\boss 2 bubbles.wav");
			Resources::Insert<AudioClip>(L"boss 2 bubbles", clip);
		}

		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\maggot enter ground .wav");
			Resources::Insert<AudioClip>(L"maggot enter ground ", clip);
		}
		
		{
			std::shared_ptr<AudioClip> clip = std::make_shared<AudioClip>();
			clip->Load(L"..\\Resources\\Issac\\sfx\\.wav");
			Resources::Insert<AudioClip>(L"", clip);
		}


	}
}