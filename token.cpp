#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <time.h>
using namespace std;

struct hash_node                    //hash rule : ASCII mod 8000
{
	bool exist;
	int count;
	char word[3];
};

bool is_word(char a[])
{
	if (a[0] & 0x80)
	{
		unsigned short x= (a[0] + 256) * 256 + a[1] + 256;
		if (x >= 41279 && x < 43584)
			return false;
		else
			return true;
	}
	else
		return false;
}

int main()
{
	hash_node hash[8000];
	for (int i = 0; i < 8000; i++)
	{
		hash[i].count = 0;
		hash[i].exist = false;
	}
	ifstream data_file("H:\\data_51_100.txt",ios::in);
	//ifstream data_file("H:\\test.txt", ios::in);
	if (!data_file)
		cout << "Fail to open the source file" << endl;
	clock_t start, end;
	start = clock();
	while (!data_file.eof())
	{
		/*string line;
		getline(data_file, line);
		istringstream ss(line);
		while (!ss.eof())
		{*/
		char line[150];
		data_file.getline(line, 150);
		for (int i = 0; line[i] != '\0'; i++)
		{
			if (line[i] & 0x80)
			{
				char word[3];
				word[0] = line[i];
				word[1] = line[i + 1];
				word[2] = '\0';
				char a[3];
				strcpy(a, word);
				if (a[1] > 0)
					a[1] = -a[1];
				if (is_word(word) == true)
				{                                                                 //只截取前两位word
					if (hash[((int)a[0])*((int)a[1]) % 8000].exist == false)
					{
						hash[((int)a[0])*((int)a[1]) % 8000].exist = true;
						hash[((int)a[0])*((int)a[1]) % 8000].count = 1;
						strcpy(hash[((int)a[0])*((int)a[1]) % 8000].word, word);
					}
					else
					{
						if (strcmp(hash[((int)a[0])*((int)a[1]) % 8000].word, word) == 0)
						{
							hash[((int)a[0])*((int)a[1]) % 8000].count++;
						}
						else
						{
							int index = (((int)a[0])*((int)a[1]) % 8000 + 1) % 8000;
							bool found = false;
							while (hash[index].exist == true)
							{
								if (strcmp(hash[index].word, word) == 0)
								{
									hash[index].count++;
									found = true;
									break;
								}
								else
									index = (index + 1) % 8000;
							}
							if (found == false && hash[index].exist == false)
							{
								hash[index].count = 1;
								hash[index].exist = true;
								strcpy(hash[index].word, word);
							}
						}
					}
				}
				i++;
			}
		}
	}
	end = clock();
	cout << "Run time: " << (double)(end - start) / CLOCKS_PER_SEC << "S" << endl;
	data_file.close();
	ofstream token("D:\\token.txt", ios::out);
	if (!token)
	{
		cout << "fail to open the token.txt" << endl;
		return 0;
	}
	int max_count = 0;
	for (int i = 0; i < 8000; i++)
	{
		if (hash[i].exist == true && hash[i].count > max_count)
			max_count = hash[i].count;
	}
	while (max_count != 0)
	{
		for (int i = 0; i < 8000; i++)
		{
			if (hash[i].count == max_count && hash[i].exist == true)
			{
				token << hash[i].word << " " << hash[i].count << endl;
				hash[i].exist = false;
			}
		}
		max_count = 0;
		for (int i = 0; i < 8000; i++)
		{
			if (hash[i].exist == true && hash[i].count > max_count)
				max_count = hash[i].count;
		}
	}
	return 0;
}
