

#include <iostream>
#include "clsDate.h"
#include "clsString.h"
#include "clsUtil.h"

int main()
{
	clsDate Date1;
	Date1.Print();



	clsString s1;
	cout << s1.CountCapitalLetters("AjjsyhGihjHHKmnhGjjKYF") << endl;
	clsUtil obj1;

	string arr[10];
	obj1.FillArrayWithRandomKeys(arr, 10, obj1.MixChars);
	int i = 0;
	while (i <= 9)
	{
		cout << arr[i] << endl;
		i++;
	}
	cout << endl;

	clsString String1;
	clsString String2("Mohammed");

	String1.Value = "Ali Ahmed";

	cout << "String1 = " << String1.Value << endl;
	cout << "String2 = " << String2.Value << endl;


	cout << "Number of words: " << String1.CountWords() << endl;

	cout << "Number of words: " << String1.CountWords("Fadi ahmed rateb omer") << endl;

	cout << "Number of words: " <<clsString::CountWords("Mohammed Saqer Abu-Hadhoud");





	return 0;

}
