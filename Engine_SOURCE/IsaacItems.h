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

	struct Pill
	{
		std::wstring name;
		ePills type;

		Pill()
			:type(ePills::HealthUp)
		{}
	};
	
	struct Card
	{
		std::wstring name;
		eCards type;

		Card()
			:type(eCards::None)
		{}
	};
		
	struct Trinket
	{
		std::wstring name;
		eTrinkets type;

		Trinket()
			:type(eTrinkets::None)
		{}
	};

	struct ActiveItem
	{
		std::wstring name;
		eActiveItem type;
		int maxGauge;

		ActiveItem()
			: type(eActiveItem::None)
		{}
	};

	struct PassiveItem
	{
		std::wstring name;
		ePassiveItem type;
		
		PassiveItem()
			:type(ePassiveItem::None)
		{}
	};
}