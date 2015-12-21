#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#define HashSize 1000000
#define MaxSize 100000
using namespace std;

/*默认路径为D:\\data_51_100.txt，文件读取语句在第46行*/

struct hash_node
{
	bool exist;                  //标记位
	int count;                   //记录出现次数
	char word_2[5];        //存储双字词
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
		if (x >= 41279 && x < 43584 )
			return false;
		else
			return true;
	}
	else
		return false;
}

hash_node Hash[HashSize];        //用于存储双字词
int max_list[MaxSize];                  //排序的的辅助数组，用于在每次遍历时记录下出现次数最多的元素下标

int main()
{
	for (int i = 0; i < HashSize; i++)
	{
		Hash[i].exist = false;
		Hash[i].count = 0;
	}
	ifstream data_file("D:\\data_51_100.txt", ios::in);           //文件路径
	if (!data_file)
		cout << "Fail to open the source file" << endl;
	clock_t start, end;
	start = clock();
	while (!data_file.eof())
	{
		char line[150];
		data_file.getline(line,150);
		for (int i = 0;i<strlen(line)-4; i++)
		{
			if (line[i] & 0x80)
			{
				char word_a[3];
				char word_b[3];
				word_a[0] = line[i];
				word_a[1] = line[i + 1];
				word_a[2] = '\0';
				word_b[0] = line[i + 3];
				word_b[1] = line[i + 4];
				word_b[2] = '\0';
				if (is_word(word_a) == true && is_word(word_b) == true && line[i+2]==' ')
				{
					int hash_code = ((word_a[0] - word_b[0] + 256)*(word_a[1] - word_b[1] + 256)
						*(word_b[1] - word_a[0] + 256)+233333) % HashSize;
					char word_2[5];
					word_2[0] = word_a[0];
					word_2[1] = word_a[1];
					word_2[2] = word_b[0];
					word_2[3] = word_b[1];
					word_2[4] = '\0';
					if (Hash[hash_code].exist == false)
					{
						Hash[hash_code].exist = true;
						Hash[hash_code].count = 1;
						strcpy(Hash[hash_code].word_2, word_2);
					}
					else
					{
						if (strcmp(Hash[hash_code].word_2, word_2) == 0)
						{
							Hash[hash_code].count++;
						}
						else
						{
							hash_code = (hash_code + 1) % HashSize;
							bool found = false;
							while (Hash[hash_code].exist == true)
							{
								if (strcmp(Hash[hash_code].word_2, word_2) == 0)
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
								strcpy(Hash[hash_code].word_2, word_2);
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
	ofstream word_2("D:\\word_2.txt", ios::out);
	if (!word_2)
	{
		cout << "fail to open the word_2.txt" << endl;
		return 0;
	}
	int max_count = 0;
	int max_length = 0;
	for (int i = 0; i < HashSize; i++)
	{
		if (Hash[i].exist == true)
		{ 
			if (Hash[i].count > max_count)
			{
				max_count = Hash[i].count;
				max_length = 1;
				max_list[max_length-1] = i;
			}
			else if (Hash[i].count == max_count)
			{
				max_list[max_length] = i;
				max_length ++;
			}
		}
	}
	while (max_count > 2)
	{
		for (int i = 0; i < max_length; i++)
		{
			word_2 << Hash[max_list[i]].word_2 << " " << Hash[max_list[i]].count << endl;
			Hash[max_list[i]].exist = false;
		}
		max_count = 0;
		max_length = 0;
		for (int i = 0; i < HashSize; i++)
		{
			if (Hash[i].exist == true)
			{
				if (Hash[i].count > max_count)
				{
					max_count = Hash[i].count;
					max_length = 1;
					max_list[max_length-1] = i;
				}
				else if (Hash[i].count == max_count)
				{
					max_list[max_length] = i;
					max_length++;
				}
			}
		}
	}
	for (int i = 0; i < HashSize; i++)
	{
		if (Hash[i].count == 2 && Hash[i].exist == true)
		{
			word_2 << Hash[i].word_2 << " " << Hash[i].count << endl;
			Hash[i].exist = false;
		}
	}
	word_2.close();
	end = clock();
	cout << "总时间 : " << (double)(end - start) / CLOCKS_PER_SEC << "S" << endl;
	return 0;
}