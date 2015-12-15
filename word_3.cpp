#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#define HashSize 8000000
#define MaxSize 400000
using namespace std;

struct hash_node
{
	bool exist;
	int count;
	char word_3[7];
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
int max_list[MaxSize];

int main()
{
	for (int i = 0; i < HashSize; i++)
	{
		Hash[i].exist = false;
		Hash[i].count = 0;
	}
	ifstream data_file("H:\\data_51_100.txt", ios::in);
	if (!data_file)
		cout << "Fail to open the source file" << endl;
	clock_t start, end;
	start = clock();
	while (!data_file.eof())
	{
		char line[150];
		data_file.getline(line, 150);
		for (int i = 0; i<strlen(line) - 7; i++)
		{
			if (line[i] & 0x80)
			{
				char word_a[3];
				char word_b[3];
				char word_c[3];
				word_a[0] = line[i];
				word_a[1] = line[i + 1];
				word_a[2] = '\0';
				word_b[0] = line[i + 3];
				word_b[1] = line[i + 4];
				word_b[2] = '\0';
				word_c[0] = line[i + 6];
				word_c[1] = line[i + 7];
				word_c[2] = '\0';
				if (is_word(word_a) == true && is_word(word_b) == true && line[i + 2] == ' ' && is_word(word_c)==true && line[i+5]==' ')
				{
					char word_3[7];
					word_3[0] = word_a[0];
					word_3[1] = word_a[1];
					word_3[2] = word_b[0];
					word_3[3] = word_b[1];
					word_3[4] = word_c[0];
					word_3[5] = word_c[1];
					word_3[6] = '\0';
					int hash_code = ((word_3[0] + 256) % 10) * 100000 + ((word_3[1] + 256) % 10) * 10000 + ((word_3[2] + 256) % 10) * 1000 + ((word_3[3] + 256) % 10) * 100 + ((word_3[4] + 256) % 10) * 10 + (word_3[5] + 256) % 10 + ((word_3[0] - word_3[1] + word_3[2] - word_3[3] + word_3[4] - word_3[5]+1200) % 8) * 1000000;
					//cout << word_3<<" "<< hash_code << endl;
					//getchar();
					if (Hash[hash_code].exist == false)
					{
						Hash[hash_code].exist = true;
						Hash[hash_code].count = 1;
						strcpy(Hash[hash_code].word_3, word_3);
					}
					else
					{
						if (strcmp(Hash[hash_code].word_3, word_3) == 0)
						{
							Hash[hash_code].count++;
						}
						else
						{
							hash_code = (hash_code + 1) % HashSize;
							bool found = false;
							while (Hash[hash_code].exist == true)
							{
								if (strcmp(Hash[hash_code].word_3, word_3) == 0)
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
								strcpy(Hash[hash_code].word_3, word_3);
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
	cout << "Run time of Hash: " << (double)(end - start) / CLOCKS_PER_SEC << "S" << endl;
	data_file.close();
	ofstream word_3("D:\\word_3.txt", ios::out);
	if (!word_3)
	{
		cout << "fail to open the word_3.txt" << endl;
		return 0;
	}

	int max_count = 0;        //ÅÅÐò·¨1
	int max_length = 0;
	for (int i = 0; i < HashSize; i++)
	{
		if (Hash[i].exist == true)
		{
			if (Hash[i].count > max_count)
			{
				max_count = Hash[i].count;
				max_length = 1;
				max_list[max_length - 1] = i;
			}
			else if (Hash[i].count == max_count)
			{
				max_list[max_length] = i;
				max_length++;
			}
		}
	}
	while (max_count > 2)
	{
		for (int i = 0; i < max_length; i++)
		{
			//word_3 << Hash[max_list[i]].word_3 << " " << Hash[max_list[i]].count << " " << (int)Hash[max_list[i]].word_3[0] << " " << (int)Hash[max_list[i]].word_3[1] << " " << (int)Hash[max_list[i]].word_3[2] << " " << (int)Hash[max_list[i]].word_3[3] <<endl;
			word_3 << Hash[max_list[i]].word_3 << " " << Hash[max_list[i]].count << endl;
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
					max_list[max_length - 1] = i;
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
			word_3 << Hash[i].word_3 << " " << Hash[i].count << endl;
			Hash[i].exist = false;
		}
	}
	word_3.close();
	end = clock();
	cout << "Run time of all: " << (double)(end - start) / CLOCKS_PER_SEC << "S" << endl;
	return 0;
}