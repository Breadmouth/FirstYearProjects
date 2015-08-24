#include <iostream>
#include "BinDec.h"

using namespace std;

int main (int argc, char** argv)
{
	BinDec myNumber1;
	BinDec myNumber2;
	char input[16];

	cout << "Please enter a binary number: ";
	cin >> input; 
	myNumber1.FromBinary(input);
	cout << "The signed number in decimal is: " << myNumber1.ToDecimal(true) << endl;
	cout << "The unsigned number in decimal is: " << myNumber1.ToDecimal(false) << endl << endl;

	cout << "Please enter a decimal number: ";
	cin >> input;
	myNumber2.FromDecimal(input);
	cout << "The number in binary is: " << myNumber2.ToBinary(true) << endl << endl;

	cout << "Decimal operations" << endl << endl;

	cout << "Number 1 + Number 2 = " << (myNumber1 + myNumber2).ToDecimal(true) << endl;
	cout << "Number 1 - Number 2 = " << (myNumber1 - myNumber2).ToDecimal(true) << endl;
	cout << "Number 1 & Number 2 = " << (myNumber1 & myNumber2).ToDecimal(true) << endl;
	cout << "Number 1 | Number 2 = " << (myNumber1 | myNumber2).ToDecimal(true) << endl;
	cout << "Number 1 ^ Number 2 = " << (myNumber1 ^ myNumber2).ToDecimal(true) << endl;
	cout << "~Number 1 = " << (~myNumber1).ToDecimal(true) << endl;
	cout << "~Number 2 = " << (~myNumber2).ToDecimal(true) << endl;
	cout << "Please enter a decimal number: ";
	int myNumber3;
	cin >> myNumber3;
	cout << "Number 1 >> Number 3 = " << (myNumber1 >> myNumber3).ToDecimal(true) << endl;
	cout << "Number 1 << Number 3 = " << (myNumber1 << myNumber3).ToDecimal(true) << endl;
	cout << "Number 2 >> Number 3 = " << (myNumber1 >> myNumber3).ToDecimal(true) << endl;
	cout << "Number 2 << Number 3 = " << (myNumber1 << myNumber3).ToDecimal(true) << endl << endl;

	cout << "Binary operations" << endl << endl;

	cout << "Number 1 + Number 2 = " << (myNumber1 + myNumber2).ToBinary(true) << endl;
	cout << "Number 1 - Number 2 = " << (myNumber1 - myNumber2).ToBinary(true) << endl;
	cout << "Number 1 & Number 2 = " << (myNumber1 & myNumber2).ToBinary(true) << endl;
	cout << "Number 1 | Number 2 = " << (myNumber1 | myNumber2).ToBinary(true) << endl;
	cout << "Number 1 ^ Number 2 = " << (myNumber1 ^ myNumber2).ToBinary(true) << endl;
	cout << "~Number 1 = " << (~myNumber1).ToBinary(true) << endl;
	cout << "~Number 2 = " << (~myNumber2).ToBinary(true) << endl;
	cout << "Please enter a decimal number: ";
	cin >> myNumber3;
	cout << "Number 1 >> Number 3 = " << (myNumber1 >> myNumber3).ToBinary(true) << endl;
	cout << "Number 1 << Number 3 = " << (myNumber1 << myNumber3).ToBinary(true) << endl;
	cout << "Number 2 >> Number 3 = " << (myNumber1 >> myNumber3).ToBinary(true) << endl;
	cout << "Number 2 << Number 3 = " << (myNumber1 << myNumber3).ToBinary(true) << endl;

	system("pause");
	return 0;
}