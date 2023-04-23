#pragma once
#include "Isaac.h"
#include "yaEngine.h"
#include <functional>

namespace ya
{
	class ItemObject
	{
	public:
		struct Events
		{
			struct Event
			{
				void operator=(std::function<void()> func)
				{
					mEvent = std::move(func);
				}
				void operator()()
				{
					if (mEvent)
						mEvent();
				}

				std::function<void()> mEvent;
			};

			Event mEvents;
		};

	public:
		ItemObject(isaac::eItemType itemType, UINT type, std::wstring name, std::function<void()> e)
			: mItemType(itemType)
			, mType(type)
			, mName(name)
			, mEvent(nullptr)
			, mGauge(0)
			, mCharge(0)
		{
			mEvent = new Events();
			mEvent->mEvents = e;
		}

		ItemObject(isaac::eItemType itemType, UINT type, std::wstring name, int gauge, std::function<void()> e)
			: mItemType(itemType)
			, mType(type)
			, mName(name)
			, mEvent(nullptr)
			, mGauge(gauge)
			, mCharge(0)
		{
			mEvent = new Events();
			mEvent->mEvents = e;
		}

		~ItemObject() {}

	public:
		std::wstring GetName() { return mName; }
		Events* GetEvent() { return mEvent; }
		void PlayEvent() { mEvent->mEvents(); }
		int GetGauge() { return mGauge; }
		int GetCharge() { return mCharge; }

		void AddCharge(int charge) 
		{ 
			mCharge += charge; 
			if (mGauge < mCharge)
				mCharge = mGauge;

			if (mCharge < 0)
				mCharge = 0;
		}

		void resetCharge() { mCharge = 0; }

	private:
		isaac::eItemType mItemType;
		UINT mType;
		std::wstring mName;
		Events* mEvent;
		
		int mGauge;
		int mCharge;
	};
};