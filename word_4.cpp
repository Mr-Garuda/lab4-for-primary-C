#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#define HashSize 50000000
#define MaxSize 400000
using namespace std;

/*默认路径为D:\\data_51_100.txt，文件读取语句在第47行*/

struct hash_node
{
	bool exist;
	int count;
	char word_4[9];
};

bool is_word(char a[])
{
	if (a[0] & 0x80)
	{
		unsigned short x;
		if (a[1] & 0x80)
			x = (a[0] + 256) * 256 + a[1] + 256;
		else
			x = (a[0] + 256) * 256 + a[1];
		if (x >= 41279 && x < 43584)
			return false;
		else
			return true;
	}
	else
		return false;
}

hash_node Hash[HashSize];
hash_node sort[3300000];
int max_list[MaxSize];

int main()
{
	for (int i = 0; i < HashSize; i++)
	{
		Hash[i].exist = false;
		Hash[i].count = 0;
	}
	ifstream data_file("D:\\data_51_100.txt", ios::in);         //文件路径
	if (!data_file)
		cout << "Fail to open the source file" << endl;
	clock_t start, end;
	start = clock();
	while (!data_file.eof())
	{
		char line[150];
		data_file.getline(line, 150);
		for (int i = 0; i<strlen(line) - 10; i++)
		{
			if (line[i] & 0x80)
			{
				char word_a[3];
				char word_b[3];
				char word_c[3];
				char word_d[3];
				word_a[0] = line[i];
				word_a[1] = line[i + 1];
				word_a[2] = '\0';
				word_b[0] = line[i + 3];
				word_b[1] = line[i + 4];
				word_b[2] = '\0';
				word_c[0] = line[i + 6];
				word_c[1] = line[i + 7];
				word_c[2] = '\0';
				word_d[0] = line[i + 9];
				word_d[1] = line[i + 10];
				word_d[2] = '\0';
				if (is_word(word_a) == true && is_word(word_b) == true && line[i + 2] == ' ' && is_word(word_c) == true && line[i + 5] == ' ' && is_word(word_d)==true &&line[i+8]==' ')
				{
					char word_4[9];
					word_4[0] = word_a[0];
					word_4[1] = word_a[1];
					word_4[2] = word_b[0];
					word_4[3] = word_b[1];
					word_4[4] = word_c[0];
					word_4[5] = word_c[1];
					word_4[6] = word_d[0];
					word_4[7] = word_d[1];
					word_4[8] = '\0';
					int hash_code = ((word_4[0] +word_4[1]+ 512) % 50) * 1000000 + ((word_4[2] + 256) % 10) * 100000 + ((word_4[3] + 256) % 10) * 10000 + ((word_4[4] + 256) % 10) * 1000 + ((word_4[5] + 256) % 10) * 100 + ((word_4[6] + 256) % 10) * 10 + (word_4[7] + 256) % 10;
					if (Hash[hash_code].exist == false)
					{
						Hash[hash_code].exist = true;
						Hash[hash_code].count = 1;
						strcpy(Hash[hash_code].word_4, word_4);
					}
					else
					{
						if (strcmp(Hash[hash_code].word_4, word_4) == 0)
						{
							Hash[hash_code].count++;
						}
						else
						{
							hash_code = (hash_code + 1) % HashSize;
							bool found = false;
							while (Hash[hash_code].exist == true)
							{
								if (strcmp(Hash[hash_code].word_4, word_4) == 0)
								{
									Hash[hash_code].count++;
									found = true;
									break;
								}
								else
									hash_code = (hash_code + 1) % HashSize;
							}
							if (found == false && Hash[hash_code].exist == false)
							{
								Hash[hash_code].exist = true;
								Hash[hash_code].count = 1;
								strcpy(Hash[hash_code].word_4, word_4);
							}
						}
					}
					i++;
				}
				i++;
			}
		}
	}
	end = clock();
	cout << "建表时间: " << (double)(end - start) / CLOCKS_PER_SEC << "S" << endl;
	data_file.close();
	ofstream word_4("D:\\word_4.txt", ios::out);
	if (!word_4)
	{
		cout << "fail to open the word_4.txt" << endl;
		return 0;
	}

	int sort_num = 0;
	for (int i = 0;i < HashSize; i++ )
	{
		if (Hash[i].count > 1)
		{
			sort[sort_num].count = Hash[i].count;
			sort[sort_num].exist = true;
			strcpy(sort[sort_num].word_4, Hash[i].word_4);
			sort_num++;
		}
	}
	//cout << "Qualify finfished" << endl;
	int max_count = 0;
	int max_length = 0;
	for (int i = 0; i < sort_num; i++)
	{
		if (sort[i].count > max_count)
		{
			max_count = sort[i].count;
			max_length = 1;
			max_list[max_length - 1] = i;
		}
		else if (sort[i].count == max_count)
		{
			max_list[max_length] = i;
			max_length++;
		}
	}
	while (max_count > 2)
	{
		for (int i = 0; i < max_length; i++)
		{
			word_4<< sort[max_list[i]].word_4 << " " << sort[max_list[i]].count << endl;
			sort[max_list[i]].exist = false;
		}
		max_count = 0;
		max_length = 0;
		for (int i = 0; i < sort_num; i++)
		{
			if (sort[i].exist == true)
			{
				if (sort[i].count > max_count)
				{
					max_count = sort[i].count;
					max_length = 1;
					max_list[max_length - 1] = i;
				}
				else if (sort[i].count == max_count)
				{
					max_list[max_length] = i;
					max_length++;
				}
			}
		}
	}
	word_4.close();
	end = clock();
	cout << "总时间: " << (double)(end - start) / CLOCKS_PER_SEC << "S" << endl;
	return 0;
}