#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <time.h>
using namespace std;

/*默认路径为D:\\data_51_100.txt，文件读取语句在第40行*/

struct hash_node                    
{
	bool exist;          //用来标记是否被输出
	int count;          //用来记录出现次数
	char word[3];   //用来存储汉字
};

bool is_word(char a[])                //判断是否为汉字
{
	if (a[0] & 0x80)                          //首位字符为负
	{
		unsigned short x= (a[0] + 256) * 256 + a[1] + 256;
		if (x >= 41279 && x < 43584)      //汉字编码范围
			return false;
		else
			return true;
	}
	else
		return false;
}

int main()
{
	hash_node hash[8000];           //哈希表用来存储输出信息
	for (int i = 0; i < 8000; i++)
	{
		hash[i].count = 0;
		hash[i].exist = false;
	}
	ifstream data_file("D:\\data_51_100.txt",ios::in);           //文件路径
	if (!data_file)
		cout << "Fail to open the source file" << endl;
	clock_t start, end;
	start = clock();
	while (!data_file.eof())
	{
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
				{                                                                                                           //只截取前两位word
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
