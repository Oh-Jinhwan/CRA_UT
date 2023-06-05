#include "pch.h"
#include "../CRA_UT/cal.cpp"
using namespace std;

void func()
{
	string s;
	s.resize(-1);
}

TEST(TestCaseName, TestName) {
	Cal cal;
	int ret = cal.GetSum(1, 2);

	EXPECT_LT(1, 2); // 1 < 2
	EXPECT_LE(1, 2); // 1 <= 2
	EXPECT_GT(2, 1); // 2 > 1
	EXPECT_GE(2, 1); // 2 >= 1
	EXPECT_NE(1, 10); // 1 != 10

	bool b = true;
	EXPECT_TRUE(b);
	EXPECT_FALSE(1 == 10);

	EXPECT_TRUE(3 == ret);
	EXPECT_EQ(3, ret);
	EXPECT_EQ(4, ret); // FAIL�̴��� �ϴ� �Ѿ
	ASSERT_EQ(4, ret); // FAIL�̸� ����
	EXPECT_EQ(3, ret); // ����ȵ�
}

TEST(TestCaseName, TestName2) {
	// �� �䱸����
	// ������ ������ ������ Excpetion�� ������
	EXPECT_THROW(func(), std::exception);
}

TEST(TestCaseName, TestName3) {
	// �޽��� ���
	EXPECT_EQ(7, 1 + 1) << "2�̾�� �Ѵ�.";
}

TEST(TestCaseName, TestName4) {
	FAIL(); // ������ FAIL
}

TEST(TestCaseName, DISABLED_TestName5) {
	// disable�� TC
	EXPECT_EQ(1, 1);
}

// Test Fixture (�׽�Ʈ �� �� �ִ� ��ġ)
// ���� : 1) Unit Test �ߺ� �ڵ� ���ſ�
// 2) �Ź� ���Ӱ� �ʱ�ȭ��
// 3) �׽�Ʈ �� �غ�� ���� �ڵ� ���డ��
// KFCFixture���� ���·� alt + insert : ReSharper generate (�������̵� �Լ� ���� ��)
class KFCFixture : public testing::Test
{
protected:
	void SetUp() override
	{
		printf("�׽�Ʈ �ϳ��� ���� �غ� �ڵ�\n");
	}
	void TearDown() override
	{
		printf("�׽�Ʈ �ϳ��� ���� ���� �� ���� �ڵ�\n");
	}

public :
	// ��ġ �ȿ��� chiar �� ����ִ�.
	// chiar�� �׽�Ʈ�� ���
	int chair = 0;

	void push_chair() // �׽�Ʈ �����ϴ� ���(��ư)
	{
		chair++;
		printf("�׽�Ʈ�� chair %d\n", chair);
		EXPECT_EQ(1, chair);
	}
};

TEST_F(KFCFixture, test1)
{
	// chair = 100; �̷��� �� �ٷ� �ֱ⵵ ����
	push_chair(); // �׽�Ʈ ����
}

TEST_F(KFCFixture, test2)
{
	// chair = 100; �̷��� �� �ٷ� �ֱ⵵ ����
	push_chair(); // �׽�Ʈ ����
}

// �Ʒ��� ���� �ߺ� �ڵ� ���� ����
class BBQFix : public testing::Test
{
public:
	Cal cal;

	int a = 1;
	//int a1(1);// fixture�ȿ����� 2�� ����� �Ұ�
	int a2{ 1 };

	void hap_test(int exp, int a, int b)
	{
		int ret = cal.GetSum(a, b);
		EXPECT_EQ(exp, ret);
	}
};

TEST_F(BBQFix, TestName1)
{
	int ret = cal.GetSum(1, 2);
	EXPECT_EQ(3, ret);
}

TEST_F(BBQFix, TestName2)
{
	// �Ź� Ŭ���� ���� ���ص� ��
	// �ߺ� �ڵ� ���� ����
	int ret = cal.GetSum(2, 3);
	EXPECT_EQ(5, ret);
}

TEST_F(BBQFix, TestName3)
{
	hap_test(30, 10, 20);
}

TEST_F(BBQFix, TestName4)
{
	hap_test(300, 100, 200);
}

class GlobalEnv : public testing::Environment
{
public:
	void SetUp() override
	{
		printf("��� test ���� �� ȣ��\n");
	}

	void TearDown() override
	{
		printf("��� test ���� �� ȣ��\n");
	}
};
int main(int argc, char* argv[])
{
	// Ȯ���Ϸ��� google test project�� �������� ��Ʈ�� ���� �� run�غ���
	testing::InitGoogleTest(&argc, argv);
	testing::AddGlobalTestEnvironment(new GlobalEnv);
	return RUN_ALL_TESTS();
}

class OddEvenChecker
{
public :
	vector<string> * checkOddEven(vector<int> arr)
	{
		vector<string> *resultArr = new vector<string>();
		int oddCnt = 0;
		int evenCnt = 0;
		for(const int n : arr)
		{
			if (n % 2 == 0)
			{
				evenCnt++;
				resultArr->push_back("O");
			}
			else
			{
				oddCnt++;
				resultArr->push_back("X");
			}
		}
		if (evenCnt == 0 || oddCnt == 0) return nullptr;
		return resultArr;
	}
};

class OddEvenChckerFixture : public testing::Test
{
public:
	OddEvenChecker oddEvenChcker;

	void OddEvenCheck(vector<int> actual, vector<string> *expect)
	{
		vector<string> *result = nullptr;
		result = oddEvenChcker.checkOddEven(actual);
		if(result == nullptr) EXPECT_TRUE(expect == nullptr);
		else EXPECT_TRUE(*result == *expect);
	}
};


TEST_F(OddEvenChckerFixture, TestName1)
{
	vector<int> act = { 1,2,3,0 };
	vector<string> exp = { "X","O","X","O" };
	OddEvenCheck(act, &exp);
}

TEST_F(OddEvenChckerFixture, TestName2)
{
	vector<int> act = { 1,1,1,1 };
	vector<string>* exp = nullptr;
	OddEvenCheck(act, exp);
}

TEST_F(OddEvenChckerFixture, TestName3)
{
	vector<int> act = { 2,2,2,2 };
	vector<string>* exp = nullptr;
	OddEvenCheck(act, exp);
}