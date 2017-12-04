#pragma once
#include <string>
#include <iostream>
#define toDigit(c) (c-'0')

namespace sse
{
	void fillRightWith0s(std::string &str, size_t size)
	{
		for (size_t i = str.size(); i < size; i++)
		{
			str += '0';
		}
	}

	void fillLeftWith0s(std::string &str, size_t size)
	{
		std::string buff = str;
		str = "";
		for (size_t i = buff.size(); i < size; i++)
		{
			str += '0';
		}
		str += buff;
	}

	

	struct hugeFloat
	{
	public:
		hugeFloat(const std::string& val)
			: m_val(val.substr(0, val.find(".")))
			, m_decimal(val.substr(val.find(".") + 1, val.size()))
		{
		}

		hugeFloat operator+(hugeFloat val)
		{
			hugeFloat result(".");

			if (val.m_val.size() < this->m_val.size())
			{
				fillLeftWith0s(val.m_val, this->m_val.size());
			}
			else if (val.m_val.size() > this->m_val.size())
			{
				fillLeftWith0s(this->m_val, val.m_val.size());
			}

			if (val.m_decimal.size() < this->m_decimal.size())
			{
				fillRightWith0s(val.m_decimal, this->m_decimal.size());
			}
			else if (val.m_decimal.size() > this->m_decimal.size())
			{
				fillRightWith0s(this->m_decimal, val.m_decimal.size());
			}


			int reminder = 0;
			fillLeftWith0s(result.m_decimal, m_decimal.size());
			fillRightWith0s(result.m_val, m_val.size());

			for (int i = static_cast<int>(m_decimal.size()) - 1; i >= 0; i--)
			{
				std::string res = std::to_string(toDigit(this->m_decimal[i]) + toDigit(val.m_decimal[i]) + reminder);
				char resNum = res.back();
				if (res.size() == 1)
				{
					reminder = 0;
				}
				else
				{
					reminder = 1;
				}
				result.m_decimal[i] = resNum;
			}

			for (int i = static_cast<int>(m_val.size()) - 1; i >= 0; i--)
			{
				std::string res = std::to_string(toDigit(this->m_val[i]) + toDigit(val.m_val[i]) + reminder);
				char resNum = res.back();
				if (res.size() == 1)
				{
					reminder = 0;
				}
				else
				{
					reminder = 1;
				}
				result.m_val[i] = resNum;
			}

			return { result };
		}


		const std::string str()
		{
			return m_val + "." + m_decimal;
		}
		/*
			192.23
		   +232.2334
		   +23972.2

		    00192.2300
		   +00232.2334
		   +23972.2000
			23396.6634
		*/
		std::string m_val;
		std::string m_decimal;
	};
}