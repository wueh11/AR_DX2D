#pragma once

namespace ya::isaac
{
	const UINT STAGE_SIZE = 2;
	const UINT STAGE_MAX_ROW = 8;
	const UINT STAGE_MAX_COLUMN = 8;

	// monster
	enum class eMonsterType
	{
		None,
		Fly,
		AttackFly,
		Pacer,
		Gaper,
		Horf,
		Globin,
		Host,
		End,
	};

	// item
	enum class eItemType
	{
		None,

		ActiveItem,
		PassiveItem,
		Trinket,
		Pill,
		Card,

		Coin,
		Bomb,
		Key,
		HeartHalf,
		HeartFull,
		SoulHeartFull,

		End,
	};

	//enum class eItemType
	//{
	//	None,
	//	Coin,
	//	Bomb,
	//	Key,
	//	HeartHalf,
	//	HeartFull,
	//	SoulHeartFull,
	//	Pill,
	//	Card,
	//};

	enum class eActiveItem
	{
		None,
		TheBible, ///비행효과
		TammysHead, //눈물 8방향
		YumHeart, //회복아이템
		End,
	};

	enum class ePassiveItem
	{
		None,
		CricketsHead, // 크리켓머리 공격력+0.5, 공격력배율x1.5
		GrowthHormones, // 성장호르몬 공격력+1 이동속도+0.2
		Lunch, //점심밥 최대체력+1 회복+1
		OuijaBoard, // 공격속도+0.4, 눈물 장애물관통

		CubeOfMeat, // 고기조각 패밀리어
	};

	enum class eTrinkets
	{
		None,
		FishHead, //피격당할시 푸른파리생김
		PinkyEye, // 10%확률로 중독 상태이상을 주는 눈물 발사
		End,
	};

	enum class ePills
	{
		None,
		HealthUp, // 체력1칸늘어남
		HealthDown, //체력1칸줄어듬
		RangeUp, //사거리 +2
		RangeDown, //사거리 -2
		TearsUp, // 공격속도 +0.35
		TearsDown, // 공격속도 -0.28
		SpeedUp, // 이동속도+0.15
		SpeedDown, // 이동속도 -0.12
		End,
	};

	enum class eCards
	{
		None,
		Taro,
		TheFool, // 현재층의 시작지점으로 텔레포트
		TheLovers, //빨간하트2개 생성
		Trump,
		Club2, // 현재폭탄 x2, 0개일때 +2
		Diamonds2, //동전x2
		Spades2, // 열쇠x2
		End,
	};

	/*struct ActiveItemInfo
	{
		std::wstring name;
		eActiveItem type;
		int maxGauge;

		ActiveItemInfo()
			: type(eActiveItem::None)
			, maxGauge(1)
		{}

		int GetMaxGauge() { return maxGauge; }
	};

	struct PillInfo
	{
		std::wstring name;
		ePills type;

		PillInfo()
			:type(ePills::None)
		{}
	};
	
	struct CardInfo
	{
		std::wstring name;
		eCards type;

		CardInfo()
			:type(eCards::None)
		{}
	};
		
	struct TrinketInfo
	{
		std::wstring name;
		eTrinkets type;

		TrinketInfo()
			:type(eTrinkets::None)
		{}
	};

	struct PassiveItemInfo
	{  
		std::wstring name;
		ePassiveItem type;
		
		PassiveItemInfo()
			:type(ePassiveItem::None)
		{}
	};*/

	enum class eStageType
	{
		None,
		Basement,
		End,
	};

	enum class eRoomType
	{
		None,
		Normal = 1,
		Treasure = 2,
		Shop,
		Selfsacrifice = 4,
		Secret = 8,
		Boss = 10,
		End,
	};
}