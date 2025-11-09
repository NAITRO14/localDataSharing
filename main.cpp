#include "header.h"



int main()
{
	setlocale(LC_ALL, "ru");

	short choose;

	while (true)
	{
		cout << "Какая роль у машины?" << endl;
		enter_num(choose);

		switch (choose)
		{
		case 1:
		{
			if (!iAmHost())
			{
				return iAmHost();
			}

		}break;
		case 2:
		{
			if (!iAmClient())
			{
				return iAmClient();
			}
		}break;
		}
	}
	

	
	return 0;
}