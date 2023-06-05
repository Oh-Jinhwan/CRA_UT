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
	EXPECT_EQ(4, ret); // FAIL이더라도 일단 넘어감
	ASSERT_EQ(4, ret); // FAIL이면 멈춤
	EXPECT_EQ(3, ret); // 수행안됨
}

TEST(TestCaseName, TestName2) {
	// 고객 요구사항
	// 음수를 넣으면 적절한 Excpetion이 떠야함
	EXPECT_THROW(func(), std::exception);
}

TEST(TestCaseName, TestName3) {
	// 메시지 출력
	EXPECT_EQ(7, 1 + 1) << "2이어야 한다.";
}

TEST(TestCaseName, TestName4) {
	FAIL(); // 무조건 FAIL
}

TEST(TestCaseName, DISABLED_TestName5) {
	// disable된 TC
	EXPECT_EQ(1, 1);
}

// Test Fixture (테스트 할 수 있는 장치)
// 목적 : 1) Unit Test 중복 코드 제거용
// 2) 매번 새롭게 초기화됨
// 3) 테스트 전 준비와 정리 코드 수행가능
// KFCFixture누른 상태로 alt + insert : ReSharper generate (오버라이딩 함수 생성 등)
class KFCFixture : public testing::Test
{
protected:
	void SetUp() override
	{
		printf("테스트 하나에 대한 준비 코드\n");
	}
	void TearDown() override
	{
		printf("테스트 하나에 대한 종료 후 정리 코드\n");
	}

public :
	// 장치 안에는 chiar 가 들어있다.
	// chiar는 테스트할 대상
	int chair = 0;

	void push_chair() // 테스트 수행하는 기능(버튼)
	{
		chair++;
		printf("테스트중 chair %d\n", chair);
		EXPECT_EQ(1, chair);
	}
};

TEST_F(KFCFixture, test1)
{
	// chair = 100; 이렇게 값 바로 넣기도 가능
	push_chair(); // 테스트 수행
}

TEST_F(KFCFixture, test2)
{
	// chair = 100; 이렇게 값 바로 넣기도 가능
	push_chair(); // 테스트 수행
}

// 아래와 같이 중복 코드 제거 가능
class BBQFix : public testing::Test
{
public:
	Cal cal;

	int a = 1;
	//int a1(1);// fixture안에서는 2번 방법은 불가
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
	// 매번 클래스 생성 안해도 됨
	// 중복 코드 제거 가능
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
		printf("모든 test 시작 전 호출\n");
	}

	void TearDown() override
	{
		printf("모든 test 종료 후 호출\n");
	}
};
int main(int argc, char* argv[])
{
	// 확인하려면 google test project를 시작프로 젝트로 설정 후 run해보기
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