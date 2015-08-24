#pragma once


//this class represents a dual binary and decimal format for a number
class BinDec
{
private:
	unsigned char m_values;
	char m_buffer[16];

public:
	BinDec();
	~BinDec();

	void FromDecimal(const char* value);
	void FromBinary(const char* value);

	const char* ToBinary(bool isSigned);
	const char* ToDecimal(bool isSigned);

	unsigned char GetRawValue()	const;

	void SetRawValue(unsigned char value);

	BinDec operator +(const BinDec& rhs);
	BinDec operator -(const BinDec& rhs);
	BinDec operator >>(const int rhs);
	BinDec operator <<(const int rhs);
	BinDec operator &(const BinDec& rhs);
	BinDec operator ^(const BinDec& rhs);
	BinDec operator ~();
	BinDec operator |(const BinDec& rhs);

};