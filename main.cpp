#include "header.h"



int main()
{
	setlocale(LC_ALL, "ru");

	short choose = 0;

	while (true)
	{
		cout << "Какая роль у машины?" << endl;
		cout << "1|Хост\n2|Клиент" << endl;
		enter_num(choose);

		system("cls");
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