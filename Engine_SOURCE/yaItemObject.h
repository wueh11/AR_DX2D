#pragma once
#include "IsaacItems.h"
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
		{
			mEvent = new Events();
			mEvent->mEvents = e;
		}
		~ItemObject() {}

	public:
		std::wstring GetName() { return mName; }
		Events* GetEvent() { return mEvent; }
		void PlayEvent() { mEvent->mEvents(); }

	private:
		isaac::eItemType mItemType;
		UINT mType;
		std::wstring mName;
		Events* mEvent;
	};
};