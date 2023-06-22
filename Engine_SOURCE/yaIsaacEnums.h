#pragma once

namespace ya::isaac
{
	const UINT STAGE_SIZE = 2;
	const UINT STAGE_MAX_ROW = 8;
	const UINT STAGE_MAX_COLUMN = 8;

	enum class eDirection
	{
		None,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		End,
	};

	// monster
	enum class eMonsterType
	{
		None,
		Fly,
		AttackFly,
		RageCreep,
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

		LittleBattery,

		ChestNormal,
		ChestSpike,
		ChestTreasure,
		ChestRock,

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
		Ambush = 3,
		Selfsacrifice = 4,
		Arcade = 5,
		devil = 6,
		holy = 7,
		Secret = 8,
		Boss = 10,
		Dark = 21,
		Shop,
		End,
	};

	struct Status
	{
		float attack;		//���ݷ�
		float attackSpeed;	// �����߻�ӵ�
		float tearSpeed;	// �����ӵ�
		float range;		// �����Ÿ�
		float speed;		// �̵��ӵ�
		float luck;

		Status()
			: attack(3.5f)
			, attackSpeed(2.73f)
			, tearSpeed(1.0f)
			, range(6.5f)
			, speed(1.0f)
			, luck(0.0f)
		{}

		Status(float fattack, float fattackSpeed, float ftearSpeed, float frange, float fspeed, float fluck)
			: attack(fattack)
			, attackSpeed(fattackSpeed)
			, tearSpeed(ftearSpeed)
			, range(frange)
			, speed(fspeed)
			, luck(fluck)
		{}
	};
}