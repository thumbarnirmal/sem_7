#include<stdio.h>
#include<string.h>

int encrypt(char key[])
{
	int key_length = strlen(key), plaintxt_length = 0, i, j;
	char c;
	FILE *fin, *fout;
	fin = fopen("plain.txt","r");
	fout = fopen("cipher.txt","w");
	
	while(!feof(fin))
	{
		c = fgetc(fin);
		if(c >= 'A' && c <= 'Z')
		{
			plaintxt_length++;
		}
		else if(c >= 'a' && c <= 'z')
		{
			plaintxt_length++;
		}
	}
	
	int nrows = (plaintxt_length/(float)key_length == (int)(plaintxt_length/key_length))?(plaintxt_length/key_length):(plaintxt_length/key_length + 1);
	char mat[nrows][key_length];
	
	fseek(fin,0,SEEK_SET);
	i = 0;j = 0;
	while(!feof(fin))
	{
		c = fgetc(fin);
		if(c >= 'A' && c <= 'Z')
		{
			mat[i][j++] = c;
			if(j >= key_length) {i++;j=0;}
		}
		else if(c >= 'a' && c <= 'z')
		{
			mat[i][j++] = c - 'a' + 'A';
			if(j >= key_length) {i++;j=0;}
		}
	}
	while(j != key_length) {mat[i][j++] = 'X';}
	
/*	for(i = 0;i < nrows;i++)					//To be commented later!!!
	{
		for(j = 0;j < key_length;j++)
		{
			printf("%c",mat[i][j]);
		}
		printf("\n");
	}*/

	int jumbleOrder[key_length], orderNo = 1;

	for(j = (int)'A';j <= (int)'Z';++j)
	{
		for(i = 0;i < key_length;++i)
		{
			if((int)key[i] == j)
				jumbleOrder[i] = orderNo++;
		}
	}
	
/*	for(j = 0;j < key_length;j++)				//To be commented later!!!
	{
		printf("%d",jumbleOrder[j]);
	}*/
	printf("\n");

	printf("Encrypted text:\n");
	for(orderNo = 1;orderNo <= key_length;++orderNo)
	{
		for(j = 0;j < key_length;++j)
		{
			if(jumbleOrder[j] == orderNo)
			{
				for(i = 0;i < nrows;++i)
				{
					fprintf(fout, "%c", mat[i][j]);
					printf("%c", mat[i][j]);
				}
				fprintf(fout, " ");
				printf(" ");
				break;
			}
		}
	}

//	printf("\n%d\t%d\t%d\n",plaintxt_length,key_length,nrows);
	fprintf(fout,"\n");
	printf("\n");
	fclose(fin);
	fclose(fout);

	return 0;
}

int decrypt(char key[])
{
	int key_length = strlen(key), ciphertxt_length = 0, i, j;
	char c;
	FILE *fin, *fout;
	fin = fopen("cipher.txt","r");
	fout = fopen("decrypted.txt","w");
	
	while(!feof(fin))
	{
		c = fgetc(fin);
		if(c >= 'A' && c <= 'Z')
		{
			ciphertxt_length++;
		}
		else if(c >= 'a' && c <= 'z')
		{
			ciphertxt_length++;
		}
	}
	
	int nrows = ciphertxt_length/key_length;
	char mat[nrows][key_length], decrypted[nrows][key_length];
	
	fseek(fin,0,SEEK_SET);
	i = 0;j = 0;
	while(!feof(fin))
	{
		c = fgetc(fin);
		if(c >= 'A' && c <= 'Z')
		{
			mat[i++][j] = c;
			if(i >= nrows) {j++;i=0;}
		}
		else if(c >= 'a' && c <= 'z')
		{
			mat[i++][j] = c - 'a' + 'A';
			if(i >= nrows) {j++;i=0;}
		}
	}
	
/*	for(i = 0;i < nrows;i++)					//To be commented later!!!
	{
		for(j = 0;j < key_length;j++)
		{
			printf("%c",mat[i][j]);
		}
		printf("\n");
	}*/

	int jumbleOrder[key_length], orderNo = 1;

	for(j = (int)'A';j <= (int)'Z';++j)
	{
		for(i = 0;i < key_length;++i)
		{
			if((int)key[i] == j)
				jumbleOrder[i] = orderNo++;
		}
	}
	
/*	for(j = 0;j < key_length;j++)				//To be commented later!!!
	{
		printf("%d",jumbleOrder[j]);
	}*/
	printf("\n");

	for(orderNo = 1;orderNo <= key_length;++orderNo)
	{
		for(j = 0;j < key_length;++j)
		{
			if(jumbleOrder[j] == orderNo)
			{
				for(i = 0;i < nrows;++i)
				{
					decrypted[i][j] = mat[i][orderNo-1];
				}
				break;
			}
		}
	}

	printf("Decrypted text:\n");
	for(i = 0;i < nrows;++i)
	{
		for(j = 0;j < key_length;++j)
		{
			fprintf(fout, "%c", decrypted[i][j]);
			printf("%c", decrypted[i][j]);
		}
	}

//	printf("\n%d\t%d\t%d\n",plaintxt_length,key_length,nrows);
	fprintf(fout,"\n");
	printf("\n");
	fclose(fin);
	fclose(fout);

	return 0;
}

int main()
{
	int ch;
	char key[27];
top:printf("\n------------------------------------------------------------\n");
	printf("1. Encrypt data.\n");
	printf("2. Decrypt data.\n");
	printf("0. Exit\n");
	printf("Enter choice: ");
	scanf("%d", &ch);
	switch(ch)
	{
		case 0:
			printf("\n------------------------------------------------------------\n");
			return 0;
			break;
		case 1:
			printf("\nInput will be taken from 'plain.txt'.\n");
			printf("Enter key for encryption: ");
			scanf("%s",key);
			encrypt(key);
			goto top;
			break;
		case 2:
			printf("\nInput will be taken from 'cipher.txt'.\n");
			printf("Enter key for decryption: ");
			scanf("%s",key);
			decrypt(key);
			goto top;
			break;
		default:
			printf("Enter proper choice!\n");
			goto top;
			break;
	}
}