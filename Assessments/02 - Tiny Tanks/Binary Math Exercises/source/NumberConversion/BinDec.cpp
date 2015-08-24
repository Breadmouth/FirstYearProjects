#include "BinDec.h"
#include <string>
#include <iostream>

BinDec::BinDec()
{
	m_values = 0;
}

BinDec::~BinDec()
{

}

void BinDec::FromDecimal(const char* value)
{
	m_values = atoi(value);
}

void BinDec::FromBinary(const char* value)
{
	unsigned char answer = 0;
	int columnValue = 1;
	for (int i = strlen(value) - 1; i >= 0; --i)
	{
		if (value[i] == '1')
		{
			answer += columnValue;
		}
		columnValue *= 2;
	}

	m_values = answer;
}

const char* BinDec::ToBinary(bool isSigned)
{
	unsigned char value;
	int j;
	if (isSigned)
	{
		if (m_values & 128)
		{
			value = ~m_values + 1;
			j = 1;
		}
		else
		{
			value = m_values;
			j = 0;
		}
	}
	else
	{
		value = m_values;
		j = 0;
	}

	for (int i = 128; i > 0; i >>= 1)
	{
		if (value & i)
		{
			m_buffer[j] = '1';
		}
		else
		{
			m_buffer[j] = '0';
		}
		j++;
	}

	if (isSigned)
	{
		m_buffer[0] = '-';
		m_buffer[9] = '\0';
	}
	else
		m_buffer[8] = '\0';
	return m_buffer;
}

const char* BinDec::ToDecimal(bool isSigned)
{
	sprintf_s(m_buffer, 15, "%i", m_values);

	if (isSigned)
	{
		if ((m_values & 128) != 0)
		{
			unsigned char value = ~m_values + 1;
			sprintf_s(m_buffer, 15, "-%i", value);
		}
	}

	return m_buffer;
}

unsigned char BinDec::GetRawValue()	const
{
	return m_values;
}

void BinDec::SetRawValue(unsigned char value)
{
	m_values = value;
}

BinDec BinDec::operator+ (const BinDec& rhs)
{
	BinDec result;
	result.SetRawValue(m_values + rhs.GetRawValue());
	return result;
}
BinDec BinDec::operator -(const BinDec& rhs)
{
	BinDec result;
	result.SetRawValue(m_values - rhs.GetRawValue());
	return result;
}
BinDec BinDec::operator >>(const int rhs)
{
	BinDec result;
	result.SetRawValue(m_values >> rhs);
	return result;
}
BinDec BinDec::operator <<(const int rhs)
{
	BinDec result;
	result.SetRawValue(m_values << rhs);
	return result;
}
BinDec BinDec::operator &(const BinDec& rhs)
{
	BinDec result;
	result.SetRawValue(m_values & rhs.GetRawValue());
	return result;
}
BinDec BinDec::operator ^(const BinDec& rhs)
{
	BinDec result;
	result.SetRawValue(m_values ^ rhs.GetRawValue());
	return result;
}
BinDec BinDec::operator ~()
{
	BinDec result;
	result.SetRawValue(~m_values);
	return result;
}
BinDec BinDec::operator |(const BinDec& rhs)
{
	BinDec result;
	result.SetRawValue(m_values | rhs.GetRawValue());
	return result;
}