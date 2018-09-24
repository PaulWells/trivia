#include "pch.h"
#include <vector>
#include <string>
#include "OutputComparer.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

/*static*/ void OutputComparer::AreEqual(const vector<string>& expected, const vector<string>& actual)
{
	Assert::AreEqual(expected.size(), actual.size());
	for (int i = 0; i < actual.size(); i++)
	{
		Assert::AreEqual(expected[i], actual[i]);
	}
}

/*static*/ void OutputComparer::ActualStartsWith(const vector<string>& expected, const vector<string>& actual)
{
	Assert::IsTrue(expected.size() <= actual.size());
	for (int i = 0; i < expected.size(); i++)
	{
		Assert::AreEqual(expected[i], actual[i]);
	}
}