/*
* Created by Zeng Yinuo, 2021.09.04
* Edited by Zeng Yinuo, 2021.09.05
*/

#include "Random.h"

static constexpr const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

int32_t Osmmd::Random::RandomInteger(int32_t min, int32_t max, int seed)
{
    return std::mt19937(seed < 0 ? std::random_device()() : seed)() % (max + 1) + min;
}

std::string Osmmd::Random::RandomString(int length, int seed)
{
	std::string result;

	for (int i = 0; i < length; i++)
	{
		int index = RandomInteger(0, sizeof(charset) - 2, seed);
		char ch = charset[index];
		result.push_back(ch == '\0' ? '0' : ch);
	}

	return result;
}

Osmmd::DataType Osmmd::Random::RandomDataType(int seed)
{
	return static_cast<DataType>(RandomInteger(0, 1, seed));
}

Osmmd::IndexStrategy Osmmd::Random::RandomIndexStrategy(int seed)
{
	return static_cast<IndexStrategy>(RandomInteger(0, 1, seed));
}

Osmmd::Value Osmmd::Random::RandomValue(int seed)
{
	return RandomValue(RandomDataType(seed), seed);
}

Osmmd::Value Osmmd::Random::RandomValue(DataType type, int seed)
{
	switch (type)
	{
	case DataType::Integer:
		return Value::FromInteger(RandomInteger(seed));
	case DataType::Char:
		return Value::FromChar(RandomString(10, seed));
	}

	return Value();
}
