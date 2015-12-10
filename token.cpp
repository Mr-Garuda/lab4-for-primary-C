#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

struct gather
{
	char word[2];
	int count;
	gather* next;
};


bool is_word(char a[])
{
	char *sign[] = { "¡°", "¡±", "£¬", "¡£", "£¡", "£¿", "¡¶", "¡·", "¡¤", "¡¢", "£¨", "£©", "¡­", "£º", "¡®", "¡¯", "£»", "/", "¡¾", "¡¿","¢Ù"};
	if (a[0] & 0x80)
	{
		for (int i = 0;i<21; i++)
			if (strcmp(a,sign[i])==0)
				return false;
		return true;
	}
	else
		return false;
}

int main()
{
	//ifstream data_file("H:\\data_51_100.txt",ios::in);
	ifstream data_file("H:\\test.txt", ios::in);
	if (!data_file)
		cout << "Fail to open the source file" << endl;
	gather *root=NULL;
	while (!data_file.eof())
	{
		char a[100];
		data_file >> a;
		if (is_word(a) == true)
		{
			gather *p = root;
			if (p == NULL)
			{
				root = new gather;
				root->count = 1;
				strcpy(root->word,a);
				root->next = NULL;
			}
			else
			{
				bool found = false;
				while (1)
				{
					if (strcmp(p->word, a) == 0)
					{
						p->count++;
						found = true;
					}
					if (p->next == NULL)
						break;
					else
						p = p->next;
				}
				if (found == false)
				{
					p->next = new gather;
					p = p->next;
					p->count = 1;
					strcpy(p->word, a);
					p->next = NULL;
				}
			}
		}
		/*gather *p = root;
		while (p != NULL)
		{
			cout << p->word << " " <<p->count<< endl;
			p = p->next;
		}
		getchar();*/
	}
	cout << "success1" << endl;
	data_file.close();
	ofstream token("D:\\token.txt",ios::out);
	if (!token)
	{
		cout << "fail to open the token.txt" << endl;
		return 0;
	}
	gather *p = root;
	while (p != NULL)
	{
		token << p->word << " " << p->count << endl;
		p = p->next;
	}
	cout << "success2" << endl;
	return 0;
}
