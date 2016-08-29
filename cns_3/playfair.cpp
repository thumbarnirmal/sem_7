#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdio.h>

using namespace std;

void filter()
{
	char ch;
	FILE *f1,*f2;
	f1=fopen("plain.txt","r");
	f2=fopen("filtered.txt","w");
	while((ch=fgetc(f1))!=EOF)
	{
		if((ch>='A'&&ch<='Z'))
			fprintf(f2,"%c",ch);
		else if(ch>='a'&&ch<='z')
			fprintf(f2,"%c",ch-32);
	}
	fclose(f1);
	fclose(f2);
	return;
}

/*int filter2()
{
	char ch1, ch2;
	FILE *fin, *fout;
	fin = fopen("filtered.txt", "r");
	fout = fopen("filtered2.txt", "w");

	while(!feof(fin))
	{
		ch1 = fgetc(fin);
		if((ch2 = fgetc(fin)) != EOF && ch1 != ch2)
		{
			fprintf(fout, "%c%c", ch1,ch2);
		}
		else
		{
			fprintf(fout, "%c", ch1);
		}
	}

	fclose(fin);
	fclose(fout);
	return 0;
}*/

int encrypt_playfair(char key[])
{
	char playfair[5][5];
	int len = strlen(key), indexof[26][2];
	if(len > 0)					//Remove 'J' and duplicates from key
	{
		for(int i = 0;i < len;++i)		//Replace J with I
			if(key[i] == 'J')
				key[i] = 'I';
		int arr[26] = {0}, j = 0;
		char temp[100];
		for(int i = 0;i < len;++i)		//Remove duplicates
		{
			if(arr[key[i]-'A'] == 0)
			{
				temp[j++] = key[i];
				arr[key[i]-'A']++;
			}
		}
		temp[j] = '\0';
		len = j;
		for(int i = 0;i <= len;++i)		//Copy temp to key
			key[i] = temp[i];
		for(int i = 0;i < len;++i)		//Build playfair matrix (characters from key)
		{
			playfair[i/5][i%5] = key[i];
		}
		int i = len/5;
		j = len%5;
		for(int t = 0;t < 26;++t)		//Build playfair matrix (remaining characters)
		{
			if(arr[t] == 0 && t != 9)
				playfair[i][j++] = t + 'A';
			if(j == 5)
			{
				j = 0;
				i++;
			}
		}
		for(int i = 0;i < 5;++i)		//Build indexof array
		{
			for(int j = 0;j < 5;++j)
			{
				indexof[playfair[i][j]-'A'][0] = i;
				indexof[playfair[i][j]-'A'][1] = j;
				if(playfair[i][j] == 'I')
				{
					indexof[playfair[i][j]-'A'+1][0] = i;
					indexof[playfair[i][j]-'A'+1][1] = j;
				}
			}
		}
	}
	// cout << len << endl << key << endl;
	// for(int i = 0;i < 5;++i)
	// {
	// 	for(int j = 0;j < 5;++j)
	// 		cout << playfair[i][j] << " ";
	// 	cout << endl;
	// }
	// for(int i = 0;i < 26;++i)
	// {
	// 	cout << (char)(i+'A') << indexof[i][0] << " " << indexof[i][1] << endl;
	// }

	char ch1, ch2;
	int ch1i, ch1j, ch2i, ch2j;
	FILE *fin, *fout;
	fin = fopen("filtered.txt", "r");
	fout = fopen("cipher.txt", "w");

	cout << "Encrypted: " << endl;

	while((ch1 = fgetc(fin))!=EOF && (ch2 = fgetc(fin))!=EOF)
	{
		char temp;
		if(ch1 == ch2)
		{
			temp = ch2;
			ch2 = 'X';
		}
		ch1i = indexof[ch1-'A'][0];
		ch1j = indexof[ch1-'A'][1];
		ch2i = indexof[ch2-'A'][0];
		ch2j = indexof[ch2-'A'][1];
		if(ch1i == ch2i)	//Same row
		{
			fprintf(fout, "%c%c", playfair[ch1i][(ch1j+1)%5], playfair[ch2i][(ch2j+1)%5]);
			printf("%c%c", playfair[ch1i][(ch1j+1)%5], playfair[ch2i][(ch2j+1)%5]);
		}
		else if(ch1j == ch2j)	//Same column
		{
			fprintf(fout, "%c%c", playfair[(ch1i+1)%5][ch1j], playfair[(ch2i+1)%5][ch2j]);
			printf("%c%c", playfair[(ch1i+1)%5][ch1j], playfair[(ch2i+1)%5][ch2j]);
		}
		else	//Different row and column
		{
			fprintf(fout, "%c%c", playfair[ch1i][ch2j], playfair[ch2i][ch1j]);
			printf("%c%c", playfair[ch1i][ch2j], playfair[ch2i][ch1j]);
		}
		if(temp  == ch1 && ch2 == 'X' && !feof(fin))
		{
			ch2 = fgetc(fin);
			ch1i = indexof[ch1-'A'][0];
			ch1j = indexof[ch1-'A'][1];
			ch2i = indexof[ch2-'A'][0];
			ch2j = indexof[ch2-'A'][1];
			if(ch1i == ch2i)	//Same row
			{
				fprintf(fout, "%c%c", playfair[ch1i][(ch1j+1)%5], playfair[ch2i][(ch2j+1)%5]);
				printf("%c%c", playfair[ch1i][(ch1j+1)%5], playfair[ch2i][(ch2j+1)%5]);
			}
			else if(ch1j == ch2j)	//Same column
			{
				fprintf(fout, "%c%c", playfair[(ch1i+1)%5][ch1j], playfair[(ch2i+1)%5][ch2j]);
				printf("%c%c", playfair[(ch1i+1)%5][ch1j], playfair[(ch2i+1)%5][ch2j]);
			}
			else	//Different row and column
			{
				fprintf(fout, "%c%c", playfair[ch1i][ch2j], playfair[ch2i][ch1j]);
				printf("%c%c", playfair[ch1i][ch2j], playfair[ch2i][ch1j]);
			}
		}
	}

	fprintf(fout,"\n");
	printf("\n");
	fclose(fin);
	fclose(fout);
	return 0;
}

int decrypt_playfair(char key[])
{
	char playfair[5][5];
	int len = strlen(key), indexof[26][2];
	if(len > 0)					//Remove 'J' and duplicates from key
	{
		for(int i = 0;i < len;++i)		//Replace J with I
			if(key[i] == 'J')
				key[i] = 'I';
		int arr[26] = {0}, j = 0;
		char temp[100];
		for(int i = 0;i < len;++i)		//Remove duplicates
		{
			if(arr[key[i]-'A'] == 0)
			{
				temp[j++] = key[i];
				arr[key[i]-'A']++;
			}
		}
		temp[j] = '\0';
		len = j;
		for(int i = 0;i <= len;++i)		//Copy temp to key
			key[i] = temp[i];
		for(int i = 0;i < len;++i)		//Build playfair matrix (characters from key)
		{
			playfair[i/5][i%5] = key[i];
		}
		int i = len/5;
		j = len%5;
		for(int t = 0;t < 26;++t)		//Build playfair matrix (remaining characters)
		{
			if(arr[t] == 0 && t != 9)
				playfair[i][j++] = t + 'A';
			if(j == 5)
			{
				j = 0;
				i++;
			}
		}
		for(int i = 0;i < 5;++i)		//Build indexof array
		{
			for(int j = 0;j < 5;++j)
			{
				indexof[playfair[i][j]-'A'][0] = i;
				indexof[playfair[i][j]-'A'][1] = j;
				if(playfair[i][j] == 'I')
				{
					indexof[playfair[i][j]-'A'+1][0] = i;
					indexof[playfair[i][j]-'A'+1][1] = j;
				}
			}
		}
	}
	// cout << len << endl << key << endl;
	// for(int i = 0;i < 5;++i)
	// {
	// 	for(int j = 0;j < 5;++j)
	// 		cout << playfair[i][j] << " ";
	// 	cout << endl;
	// }
	// for(int i = 0;i < 26;++i)
	// {
	// 	cout << (char)(i+'A') << indexof[i][0] << " " << indexof[i][1] << endl;
	// }

	char ch1, ch2;
	int ch1i, ch1j, ch2i, ch2j;
	FILE *fin, *fout;
	fin = fopen("cipher.txt", "r");
	fout = fopen("decrypted.txt", "w");

	cout << "Decrypted: " << endl;

	while((ch1 = fgetc(fin))!=EOF && (ch2 = fgetc(fin))!=EOF)
	{
		char temp;
		if(ch1 == ch2)
		{
			temp = ch2;
			ch2 = 'X';
		}
		ch1i = indexof[ch1-'A'][0];
		ch1j = indexof[ch1-'A'][1];
		ch2i = indexof[ch2-'A'][0];
		ch2j = indexof[ch2-'A'][1];
		if(ch1i == ch2i)	//Same row
		{
			fprintf(fout, "%c%c", playfair[ch1i][(ch1j-1)%5], playfair[ch2i][(ch2j-1)%5]);
			printf("%c%c", playfair[ch1i][(ch1j-1)%5], playfair[ch2i][(ch2j-1)%5]);
		}
		else if(ch1j == ch2j)	//Same column
		{
			fprintf(fout, "%c%c", playfair[(ch1i-1)%5][ch1j], playfair[(ch2i-1)%5][ch2j]);
			printf("%c%c", playfair[(ch1i-1)%5][ch1j], playfair[(ch2i-1)%5][ch2j]);
		}
		else	//Different row and column
		{
			fprintf(fout, "%c%c", playfair[ch1i][ch2j], playfair[ch2i][ch1j]);
			printf("%c%c", playfair[ch1i][ch2j], playfair[ch2i][ch1j]);
		}
		if(temp  == ch1 && ch2 == 'X' && !feof(fin))
		{
			ch2 = fgetc(fin);
			ch1i = indexof[ch1-'A'][0];
			ch1j = indexof[ch1-'A'][1];
			ch2i = indexof[ch2-'A'][0];
			ch2j = indexof[ch2-'A'][1];
			if(ch1i == ch2i)	//Same row
			{
				fprintf(fout, "%c%c", playfair[ch1i][(ch1j-1)%5], playfair[ch2i][(ch2j-1)%5]);
				printf("%c%c", playfair[ch1i][(ch1j-1)%5], playfair[ch2i][(ch2j-1)%5]);
			}
			else if(ch1j == ch2j)	//Same column
			{
				fprintf(fout, "%c%c", playfair[(ch1i-1)%5][ch1j], playfair[(ch2i-1)%5][ch2j]);
				printf("%c%c", playfair[(ch1i-1)%5][ch1j], playfair[(ch2i-1)%5][ch2j]);
			}
			else	//Different row and column
			{
				fprintf(fout, "%c%c", playfair[ch1i][ch2j], playfair[ch2i][ch1j]);
				printf("%c%c", playfair[ch1i][ch2j], playfair[ch2i][ch1j]);
			}
		}
	}

	fprintf(fout,"\n");
	printf("\n");
	fclose(fin);
	fclose(fout);
	return 0;
}

int main()
{
	int ch;
	char key[100];
	filter();
top:cout << "\n------------------------------------------------------------\n";
	cout << "1. Encrypt data - Playfair.\n";
	cout << "2. Decrypt data - Playfair.\n";
	cout << "0. Exit\n";
	cout << "Enter choice: ";
	cin >> ch;
	switch(ch)
	{
		case 0:
			cout << "\n------------------------------------------------------------\n";
			return 0;
			break;
		case 1:
			cout << "\nInput will be taken from 'plain.txt'.\n";
			cout << "Enter key for encryption(CAPS): ";
			cin >> key;
			encrypt_playfair(key);
			goto top;
			break;
		case 2:
			cout << "\nInput will be taken from 'cipher.txt'.\n";
			cout << "Enter key for decryption(CAPS): ";
			cin >> key;
			decrypt_playfair(key);
			goto top;
			break;
		default:
			cout << "Enter proper choice!\n";
			goto top;
			break;
	}
}