#pragma once

namespace ya::isaac
{
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
		TheBible, ///����ȿ��
		TammysHead, //���� 8����
		YumHeart, //ȸ��������
	};

	enum class ePassiveItem
	{
		CricketsHead, // ũ���ϸӸ� ���ݷ�+0.5, ���ݷ¹���x1.5
		GrowthHormones, // ����ȣ���� ���ݷ�+1 �̵��ӵ�+0.2
		Lunch, //���ɹ� �ִ�ü��+1 ȸ��+1
		OuijaBoard, // ���ݼӵ�+0.4, ���� ��ֹ�����

		CubeOfMeat, // ������� �йи���
	};

	enum class eTrinkets
	{
		FishHead, //�ǰݴ��ҽ� Ǫ���ĸ�����
		PinkyEye, // 10%Ȯ���� �ߵ� �����̻��� �ִ� ���� �߻�
	};

	enum class ePill
	{
		HealthUp, // ü��1ĭ�þ
		HealthDown, //ü��1ĭ�پ��
		RangeUp, //��Ÿ� +2
		RangeDown, //��Ÿ� -2
		TearsUp, // ���ݼӵ� +0.35
		TearsDown, // ���ݼӵ� -0.28
		SpeedUp, // �̵��ӵ�+0.15
		SpeedDown, // �̵��ӵ� -0.12
	};

	enum class eCard
	{
		TheFool, // �������� ������������ �ڷ���Ʈ
		TheLovers, //������Ʈ2�� ����

		Club2, // ������ź x2, 0���϶� +2
		Diamonds2, //����x2
		Spades2, // ����x2
	};
}