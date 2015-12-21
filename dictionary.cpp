#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#define HashSize2 1000000                      //578115
using namespace std;

/*
ɸѡ����
1.���ִʳ��ִ�������15�ν���ʵ�
2.���ִʳ��ִ�������17����ʵ�
3.���ִʳ��ִ�������10����ʵ�
4.���ִ�ABC���ִ���������AB��BC���ִ�����75%������ABC��������AB��BC�������¹���:
		a.��AB��BC���ִ��������20%֮�ڣ���ȫ��ɾ��
		b.��AB��BC���ִ�������20%����ɾ�������ٵĶ��ִʣ���ӱȽϣ���ABC����С��AB������15%�����ټ���ABC
		c.��AB��BC�ѱ�ɸȥ����ɾȥ
5.���ִ�ABCD��Ϊ�������
		a.��AB��CD�ֱ�ƥ�䵽���дʵ��ж��ִʣ�����AB��CD�������¹���
						1.��AB��CD��ABCD���ִ��������20%���ڣ���ɾ����Ӧ���ִʣ�����ABCD
						2.��AB��CD��ABCD���ִ�������20%���򲻼���ABCD
		b.��ƥ�䵽ABC��BCD����������¹���
						1.��ABC��BCD��ABCD���ִ��������15%���ڣ������ABCD��ɾ���������ִ�
						2.��ABC��BCD��ABCD���ִ�������15%���򲻼���ABCD
6.�����ִʹ���
		a.���ġ� ��ͷ�Ĵ�ֻ����ɡ���ȷ�������ĸ硱������ʿ�������Ľ㡱��������Լ����ġ���β�Ĵ��ų�
		b.���ǡ���ͷ�Ĵ�ֻ�С��Ƿǡ��͡��Ƿ񡱳���
		c.���ִʽ�βֻ�������ʳ���
					    1.���ִʽ�β���ִ�ֻ����ɡ�֮x��������x������ʮx����"��x"��"ǰx"�����ų�

*/

struct hash_node_2
{
	//bool exist;
	int count;
	char word_2[5];
};


struct hash_node_4
{
	int count;                      //��¼���ִ���
	char word_4[9];           //�洢����
};

hash_node_2 hash2[HashSize2];
hash_node_4 dic[HashSize2];         //���Դ洢ͨ��ɸѡ�Ĵ���
hash_node_4 SortDic[5000000];  //���Դ洢ȥ����Ԫ�غ�Ĵʵ�����
int max_list[10000];                         //����ĸ������飬���ڴ洢ÿ�α����г��ִ�������Ԫ�ص��±�

bool is_num(char a[], int index)
{
	unsigned short value = ((unsigned char)a[index]) * 256 + (unsigned char)a[index + 1];
	switch (value)
	{
	case (unsigned short)'һ':return true;
	case (unsigned short)'��':return true;
	case (unsigned short)'��':return true;
	case (unsigned short)'��':return true;
	case (unsigned short)'��':return true;
	case (unsigned short)'��':return true;
	case (unsigned short)'��':return true;
	case (unsigned short)'��':return true;
	case (unsigned short)'��':return true;
	case (unsigned short)'ʮ':return true;
	default:return false;
	}
}

bool is_similar(int a, int b,double k)
{
	if (a == b)
		return true;
	else
	{
		if (a > b)
		{
			if (a*k <= b)
				return true;
			else
				return false;
		}
		else
		{
			if (b*k <= a)
				return true;
			else
				return false;
		}
	}
}

int main()
{
	for (int i = 0; i < HashSize2; i++)
	{
		hash2[i].count = 0;
	}
	clock_t start, end;
	start = clock();
	ifstream word_2_file("D:\\word_2.txt", ios::in);       //��ȡword_2.txt
	if (!word_2_file)
		cout << "Fail to open the word_2.txt" << endl;
	int line_num = 0;
	while (!word_2_file.eof())
	{
		char line[12];
		word_2_file.getline(line, 12);
		if (word_2_file.fail())
			break;
		line_num++;
		char word_2[5];
		word_2[0] = line[0];
		word_2[1] = line[1];
		word_2[2] = line[2];
		word_2[3] = line[3];
		word_2[4] = '\0';
		int count = 0;

		int k = 5;
		while (line[k] != '\0')
		{
			count = line[k] - '0' + count * 10;
			k++;
		}
		if (count < 16)                     //�������ƣ����ִʳ��ִ���С��16����ѭ��
			break;
		int hash_code = ((word_2[0] - word_2[2] + 256)*(word_2[1] - word_2[3] + 256)*(word_2[3] - word_2[0] + 256) + 233333) % HashSize2;
		if (hash2[hash_code].count == 0)
		{
			hash2[hash_code].count = count;
			strcpy(hash2[hash_code].word_2, word_2);
		}
		else
		{
			if (strcmp(hash2[hash_code].word_2, word_2) == 0)
			{
				cout << line_num << "    repeats" << endl;
			}
			else
			{
				hash_code = (hash_code + 1) % HashSize2;
				bool found = false;
				while (hash2[hash_code].count > 0)
				{
					if (strcmp(hash2[hash_code].word_2, word_2) == 0)
					{
						cout << line_num << " repeats" << endl;
						found = true;
					}
					else
						hash_code = (hash_code + 1) % HashSize2;
				}
				if (found == false && hash2[hash_code].count == 0)
				{
					strcpy(hash2[hash_code].word_2, word_2);
					hash2[hash_code].count = count;
				}
			}
		}
	}
	cout << "word_2.txt has been read" << endl;
	word_2_file.close();


	/*�����ֱ���*/
	char word_de[3] = "��";
	char word_shi[3] = "��";

	for (int i = 0; i < HashSize2; i++)
	{
		if (hash2[i].count <= 15)
			continue;
		if (hash2[i].word_2[0] == word_de[0] && hash2[i].word_2[1] == word_de[1])          //���ġ���ͷ
		{
			char word_shi1[3] = "ʿ";
			char word_que[3] = "ȷ";
			char word_ge[3] = "��";
			char word_jie[3] = "��";
			if (hash2[i].word_2[2] == word_shi1[0] && hash2[i].word_2[3] == word_shi1[1])
			{
				dic[i].count = hash2[i].count;
				strcpy(dic[i].word_4, hash2[i].word_2);
			}
			else if (hash2[i].word_2[2] == word_que[0] && hash2[i].word_2[3] == word_que[1])
			{
				dic[i].count = hash2[i].count;
				strcpy(dic[i].word_4, hash2[i].word_2);
			}
			else if (hash2[i].word_2[2] == word_ge[0] && hash2[i].word_2[3] == word_ge[1])
			{
				dic[i].count = hash2[i].count;
				strcpy(dic[i].word_4, hash2[i].word_2);
			}
			else if (hash2[i].word_2[2] == word_jie[0] && hash2[i].word_2[3] == word_jie[1])
			{
				dic[i].count = hash2[i].count;
				strcpy(dic[i].word_4, hash2[i].word_2);
			}
			else
				continue;
		}
		else if (hash2[i].word_2[2] == word_de[0] && hash2[i].word_2[3] == word_de[1]) //���ġ���β
			continue;
		else if (hash2[i].word_2[0] == word_shi[0] && hash2[i].word_2[1] == word_shi[1])         //�ǿ�ͷ
		{
			char word_fei[3] = "��";
			char word_fou[3] = "��";
			if (hash2[i].word_2[2] == word_fei[0] && hash2[i].word_2[3] == word_fei[1])
			{
				dic[i].count = hash2[i].count;
				strcpy(dic[i].word_4, hash2[i].word_2);
			}
			else if (hash2[i].word_2[2] == word_fou[0] && hash2[i].word_2[3] == word_fou[1])
			{
				dic[i].count = hash2[i].count;
				strcpy(dic[i].word_4, hash2[i].word_2);
			}
			else
				continue;
		}
		else if (is_num(hash2[i].word_2, 2))        //���ֽ�β
		{
			unsigned short zhi = (unsigned short)'֮';
			unsigned short zhou = (unsigned short)'��';
			unsigned short shi = (unsigned short)'ʮ';
			unsigned short di = (unsigned short)'��';
			unsigned short qian = (unsigned short)'ǰ';
			unsigned short data = ((unsigned short)hash2[i].word_2[0]) * 256 + (unsigned short)hash2[i].word_2[1];
			if (data == zhi || data == zhou || data == shi || data == di || data == qian)
			{
				dic[i].count = hash2[i].count;
				strcpy(dic[i].word_4, hash2[i].word_2);
			}
			else
				continue;
		}
		else                                //�����ͨ��ɸѡ����ʵ�
		{
			dic[i].count = hash2[i].count;
			strcpy(dic[i].word_4, hash2[i].word_2);
		}
	}



	ifstream word_3_file("D:\\word_3.txt", ios::in);           //��ȡword_3.txt
	if (!word_3_file)
		cout << "Fail to open the word_3.txt" << endl;
	line_num = 0;
	while (!word_3_file.eof())
	{
		char line[13];
		word_3_file.getline(line, 13);
		if (word_3_file.fail())
			break;
		line_num++;
		char word_3[7];
		word_3[0] = line[0];
		word_3[1] = line[1];
		word_3[2] = line[2];
		word_3[3] = line[3];
		word_3[4] = line[4];
		word_3[5] = line[5];
		word_3[6] = '\0';
		int count = 0;

		int k = 7;
		while (line[k] != '\0')
		{
			count = line[k] - '0' + count * 10;
			k++;
		}
		if (count < 18)                           //�������ƣ����ִʳ��ִ���С��18����ѭ��
			break;
		char ab[5];
		ab[0] = word_3[0];
		ab[1] = word_3[1];
		ab[2] = word_3[2];
		ab[3] = word_3[3];
		ab[4] = '\0';
		char bc[5];
		bc[0] = word_3[2];
		bc[1] = word_3[3];
		bc[2] = word_3[4];
		bc[3] = word_3[5];
		bc[4] = '\0';
		int ab_pos = ((ab[0] - ab[2] + 256)*(ab[1] - ab[3] + 256)*(ab[3] - ab[0] + 256) + 233333) % HashSize2;
		int bc_pos = ((bc[0] - bc[2] + 256)*(bc[1] - bc[3] + 256)*(bc[3] - bc[0] + 256) + 233333) % HashSize2;
		bool ab_found = false;
		bool bc_found = false;
		while (dic[ab_pos].count > 0)
		{
			if (strcmp(dic[ab_pos].word_4, ab) == 0)
			{
				if (dic[ab_pos].count > 0)
					ab_found = true;
				break;
			}
			else
			{
				ab_pos = (ab_pos + 1) % HashSize2;
			}
		}
		while (dic[bc_pos].count > 0)
		{
			if (strcmp(dic[bc_pos].word_4, bc) == 0)
			{
				if (dic[bc_pos].count > 0)
					bc_found = true;
				break;
			}
			else
			{
				bc_pos = (bc_pos + 1) % HashSize2;
			}
		}
		if (ab_found == true && bc_found == true)
		{
			if (count > 0.75*dic[ab_pos].count || count > 0.75*dic[bc_pos].count)
			{
				if (is_similar(dic[ab_pos].count, dic[bc_pos].count, 0.75))            //AB��BC���������ȫ��ɾȥ
				{
					dic[ab_pos].count = 0;
					dic[bc_pos].count = 0;
					dic[ab_pos].count = count;
					strcpy(dic[ab_pos].word_4, word_3);
				}
				else                                                                                               //��������Զ��ɾȥС���Ǹ�
				{
					if (dic[ab_pos].count < dic[bc_pos].count)
					{
						if (count < dic[bc_pos].count*0.2)
						{
							dic[ab_pos].count = 0;
						}
						else
						{
							dic[ab_pos].count = count;
							strcpy(dic[ab_pos].word_4, word_3);
						}
					}
					else
					{
						if (count < dic[ab_pos].count*0.2)
						{
							dic[bc_pos].count = 0;
						}
						else
						{
							dic[bc_pos].count = count;
							strcpy(dic[bc_pos].word_4, word_3);
						}
					}
				}
			}
			else
				continue;
		}
		else if (ab_found == false && bc_found == false)
		{
			continue;
		}
		else
		{
			if (ab_found == true)
			{
				if (count > 0.75*dic[ab_pos].count)
				{
					dic[ab_pos].count = count;
					strcpy(dic[ab_pos].word_4, word_3);
				}
				else
					continue;
			}
			else
			{
				if (count > 0.75*dic[bc_pos].count)
				{
					dic[bc_pos].count = count;
					strcpy(dic[bc_pos].word_4, word_3);
				}
			}
		}
	}
	cout << "word_3.txt has been read" << endl;
	word_3_file.close();

	ifstream word_4_file("D:\\word_4.txt", ios::in);           //��ȡword_4.txt
	if (!word_4_file)
		cout << "Fail to open the word_4.txt" << endl;
	line_num = 0;
	while (!word_4_file.eof())
	{
		char line[14];
		word_4_file.getline(line, 14);
		if (word_4_file.fail())
		{
			cout << "break" << endl;
			break;
		}
		line_num++;
		char word_4[9];
		word_4[0] = line[0];
		word_4[1] = line[1];
		word_4[2] = line[2];
		word_4[3] = line[3];
		word_4[4] = line[4];
		word_4[5] = line[5];
		word_4[6] = line[6];
		word_4[7] = line[7];
		word_4[8] = '\0';
		int count = 0;
		int k = 9;
		while (line[k] != '\0')
		{
			count = line[k] - '0' + count * 10;
			k++;
		}
		if (count < 11)                           //�������ƣ����ִʳ��ִ���С��11����ѭ��
			break;
	//	cout << line_num << endl;
		char abc[7];                                 //����ƥ��
		strncpy(abc, word_4, 6);
		abc[6] = '\0';
		char bcd[7];
		strncpy(bcd, &word_4[2], 6);
		bcd[6] = '\0';
		bool abc_found = false;
		bool bcd_found = false;
		int abc_pos = ((abc[0] - abc[2] + 256)*(abc[1] - abc[3] + 256)*(abc[3] - abc[0] + 256) + 233333) % HashSize2;
		int bcd_pos = ((bcd[0] - bcd[2] + 256)*(bcd[1] - bcd[3] + 256)*(bcd[3] - bcd[0] + 256) + 233333) % HashSize2;
		int i = 0;
		while (i<500)
		{
			if (strcmp(dic[abc_pos].word_4, abc) == 0)
			{
				if (dic[abc_pos].count > 0)
					abc_found = true;
				break;
			}
			else
			{
				i++;
				abc_pos = (abc_pos + 1) % HashSize2;
			}
		}
		if (abc_found == false)
		{
			i = 0;
			abc_pos = ((abc[2] - abc[4] + 256)*(abc[3] - abc[5] + 256)*(abc[5] - abc[2] + 256) + 233333) % HashSize2;
			while (i < 500)
			{
				if (strcmp(dic[abc_pos].word_4, abc) == 0)
				{
					if (dic[abc_pos].count > 0)
						abc_found = true;
					break;
				}
				else
				{
					i++;
					abc_pos = (abc_pos + 1) % HashSize2;
				}
			}
		}
		i = 0;
		while (i<500)
		{
			if (strcmp(dic[bcd_pos].word_4, bcd) == 0)
			{
				if (dic[bcd_pos].count > 0)
					bcd_found = true;
				break;
			}
			else
			{
				i++;
				bcd_pos = (bcd_pos + 1) % HashSize2;
			}
		}
		if (bcd_found == false)
		{
			i = 0;
			bcd_pos = ((bcd[2] - bcd[4] + 256)*(bcd[3] - bcd[5] + 256)*(bcd[5] - bcd[2] + 256) + 233333) % HashSize2;
			while (i<500)
			{
				if (strcmp(dic[bcd_pos].word_4, bcd) == 0)
				{
					if (dic[bcd_pos].count > 0)
						bcd_found = true;
					break;
				}
				else
				{
					i++;
					bcd_pos = (bcd_pos + 1) % HashSize2;
				}
			}
		}
		bool insert = false;
		if (abc_found == true)
		{
			if (dic[abc_pos].count*0.85<=count)
			{
				dic[abc_pos].count = count;
				strcpy(dic[abc_pos].word_4,word_4);
				insert = true;
			}
		}
		if (bcd_found == true)
		{
		//	cout << "Find" << bcd << endl;
			if (dic[bcd_pos].count*0.85 <= count)
			{
				if (insert == true)                     //ABCD�Ѳ���
				{
					dic[bcd_pos].count = 0;
				}
				else
				{
			//		cout << "Add word_4 :" << word_4 << endl;
					dic[bcd_pos].count = count;
					strcpy(dic[bcd_pos].word_4, word_4);
					insert = true;
				}
			}
		}
	}
	cout << "word_4.txt has been read" << endl;

	int sort_num = 0;                                                   //����+����
	for (int i = 0; i < HashSize2; i++)
	{
		if (dic[i].count > 0)
		{
			SortDic[sort_num].count = dic[i].count;
			strcpy(SortDic[sort_num].word_4, dic[i].word_4);
			sort_num++;
		}
	}
	end = clock();
	cout << "����ʱ��: " << (double)(end - start) / CLOCKS_PER_SEC << "S" << endl;
	int num_2 = 0;
	int num_3 = 0;
	int num_4 = 0;

	ofstream dic_file("D:\\dictionary.txt", ios::out);
	if (!dic_file)
		cout << "Fail to open dictionary.txt" << endl;
	int max_count = 0;
	int max_length = 0;
	for (int i = 0; i < sort_num; i++)
	{
		if (SortDic[i].count > max_count)
		{
			max_count = SortDic[i].count;
			max_length = 1;
			max_list[max_length - 1] = i;
		}
		else if (SortDic[i].count == max_count)
		{
			max_list[max_length] = i;
			max_length++;
		}
	}
	while (max_count > 15)
	{
		for (int i = 0; i < max_length; i++)
		{
			if (strlen(SortDic[max_list[i]].word_4) == 4)
				num_2++;
			else if (strlen(SortDic[max_list[i]].word_4) == 6)
				num_3++;
			else
				num_4++;
			dic_file << SortDic[max_list[i]].word_4 << "\t" << SortDic[max_list[i]].count << endl;
		}
		int last_max = max_count;
		max_count = 0;
		max_length = 0;
		for (int i = 0; i < sort_num; i++)
		{
			if (SortDic[i].count < last_max)
			{
				if (SortDic[i].count > max_count)
				{
					max_count = SortDic[i].count;
					max_length = 1;
					max_list[max_length - 1] = i;
				}
				else if (SortDic[i].count == max_count)
				{
					max_list[max_length] = i;
					max_length++;
				}
			}
		}
	}
	dic_file.close();
	cout << "���ִʸ�����" << num_2 << endl;
	cout << "���ִʸ�����" << num_3 << endl;
	cout << "���ִʸ�����" << num_4 << endl;
	end = clock();
	cout << "��ʱ��: " << (double)(end - start) / CLOCKS_PER_SEC << "S" << endl;
}