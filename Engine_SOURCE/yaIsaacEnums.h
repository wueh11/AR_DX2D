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
		TheBible, ///����ȿ��
		TammysHead, //���� 8����
		YumHeart, //ȸ��������
		End,
	};

	enum class ePassiveItem
	{
		None,
		CricketsHead, // ũ���ϸӸ� ���ݷ�+0.5, ���ݷ¹���x1.5
		GrowthHormones, // ����ȣ���� ���ݷ�+1 �̵��ӵ�+0.2
		Lunch, //���ɹ� �ִ�ü��+1 ȸ��+1
		OuijaBoard, // ���ݼӵ�+0.4, ���� ��ֹ�����

		CubeOfMeat, // ������� �йи���
	};

	enum class eTrinkets
	{
		None,
		FishHead, //�ǰݴ��ҽ� Ǫ���ĸ�����
		PinkyEye, // 10%Ȯ���� �ߵ� �����̻��� �ִ� ���� �߻�
		End,
	};

	enum class ePills
	{
		None,
		HealthUp, // ü��1ĭ�þ
		HealthDown, //ü��1ĭ�پ��
		RangeUp, //��Ÿ� +2
		RangeDown, //��Ÿ� -2
		TearsUp, // ���ݼӵ� +0.35
		TearsDown, // ���ݼӵ� -0.28
		SpeedUp, // �̵��ӵ�+0.15
		SpeedDown, // �̵��ӵ� -0.12
		End,
	};

	enum class eCards
	{
		None,
		Taro,
		TheFool, // �������� ������������ �ڷ���Ʈ
		TheLovers, //������Ʈ2�� ����
		Trump,
		Club2, // ������ź x2, 0���϶� +2
		Diamonds2, //����x2
		Spades2, // ����x2
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