#pragma once
class OutputComparer
{
public:
	static void AreEqual(const std::vector<std::string>& expected, const std::vector<std::string>& actual);
	static void ActualStartsWith(const std::vector<std::string>& expected, const std::vector<std::string>& actual);
};

