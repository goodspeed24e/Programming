If you're like us, you'd like to look at some Google Test sample code. The samples folder has a number of well-commented samples showing how to use a variety of Google Test features.

Sample #1 shows the basic steps of using Google Test to test C++ functions.
Sample #2 shows a more complex unit test for a class with multiple member functions.
Sample #3 uses a test fixture.
	- SetUp
	-TestBody -> TEST_F
Sample #4 puts shared testing logic in a base test fixture, and reuses it in derived fixtures.
Sample #5 teaches how to reuse a test fixture in multiple test cases by deriving sub-fixtures from it.
  - SetUp
  -TestBody ->TEST_F
  - TearDown
Sample #6 demonstrates type-parameterized tests.
  - using testing::Types
  -  TYPED_TEST_CASE(TestCaseName, TypeList);
  - TYPED_TEST(TestCaseName, TestName)  similar to  TEST_F
  - TYPED_TEST_CASE_P
  - TYPED_TEST_P(TestCaseName, TestName)
  - REGISTER_TYPED_TEST_CASE_P
Sample #7 teaches the basics of value-parameterized tests.
  - TEST_P
Sample #8 shows using Combine() in value-parameterized tests.
Sample #9 shows use of the listener API to modify Google Test's console output and the use of its reflection API to inspect test results.
Sample #10 shows use of the listener API to implement a primitive memory leak checker.