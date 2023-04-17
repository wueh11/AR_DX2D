#pragma once

namespace ya::isaac
{
	enum class eItemType
	{
		None,
		ActiveItem,
		PassiveItem,
		Pill,
		Card,
		End,
	};

	enum class ePickupType
	{
		None,
		Coin,
		Bomb,
		Key,
		HeartHalf,
		HeartFull,
		SoulHeartFull,
		Pill,
		Card,
	};

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
		TheFool, // �������� ������������ �ڷ���Ʈ
		TheLovers, //������Ʈ2�� ����

		Club2, // ������ź x2, 0���϶� +2
		Diamonds2, //����x2
		Spades2, // ����x2
		End,
	};

	/*struct PillInfo
	{
		std::wstring name;
		ePills type;

		PillInfo()
			:type(ePills::HealthUp)
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

	struct ActiveItemInfo
	{
		std::wstring name;
		eActiveItem type;
		int maxGauge;

		ActiveItemInfo()
			: type(eActiveItem::None)
			, maxGauge(1)
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
}