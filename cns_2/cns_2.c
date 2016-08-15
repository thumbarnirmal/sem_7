#include<stdio.h>
#include<string.h>

void filter()
{
	char ch;
	FILE *f1,*f2;
	f1=fopen("text.txt","r");
	f2=fopen("text_filtered.txt","w");
	while((ch=fgetc(f1))!=EOF)
	{
		if((ch>='A'&&ch<='Z'))
			fprintf(f2,"%c",ch);
		else if(ch>='a'&&ch<='z')
			fprintf(f2,"%c",ch-32);
	}
	fclose(f1);
	fclose(f2);

	printf("\nPlain text Filtered\n");
}

int encrypt_vigenere(char key[])
{
	char ch;
	int i=0,len;
	len = strlen(key);
	while(key[i])
	{
		key[i]=toupper(key[i]);
		i++;
	}
	puts(key);
	i=0;
	FILE *f1,*f2;
	f1=fopen("text_filtered.txt","r");
	f2=fopen("text_encrypted.txt","w");
	while((ch=fgetc(f1))!=EOF)
	{
		ch=ch+key[i]-65;
		if(ch>90)
			ch=ch-26;
		fprintf(f2,"%c",ch);
		if(i==len-1)
			i=0;
		else
			i++;
	}
	fclose(f1);
	fclose(f2);
	printf("\nPlain text encrypted\n");
	return 0;
}

int decrypt_vigenere(char key[])
{
	char ch;
	int i=0,len;
	len = strlen(key);
	while(key[i])
	{
		key[i]=toupper(key[i]);
		i++;
	}
	i=0;
	FILE *f1,*f2;
	f1=fopen("text_encrypted.txt","r");
	f2=fopen("text_decrypted.txt","w");
	while((ch=fgetc(f1))!=EOF)
	{
		ch=ch-key[i]+65;
		if(ch<65)
			ch=ch+26;
		fprintf(f2,"%c",ch);
		if(i==len-1)
			i=0;
		else
			i++;
	}
	fclose(f1);
	fclose(f2);
	printf("\nCipher text decrypted\n");
	return 0;
}

int encrypt_columnar(char key[])
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

int decrypt_columnar(char key[])
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
	char key[100];
top:printf("\n------------------------------------------------------------\n");
	printf("1. Encrypt data - Columnar transposition.\n");
	printf("2. Decrypt data - Columnar transposition.\n");
	printf("3. Encrypt data - Vigenère.\n");
	printf("4. Decrypt data - Vigenère.\n");
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
			printf("Enter key for encryption(CAPS): ");
			scanf("%s",key);
			encrypt_columnar(key);
			goto top;
			break;
		case 2:
			printf("\nInput will be taken from 'cipher.txt'.\n");
			printf("Enter key for decryption(CAPS): ");
			scanf("%s",key);
			decrypt_columnar(key);
			goto top;
			break;
		case 3:
			printf("\nInput will be taken from 'plain.txt'.\n");
			printf("Enter key for encryption: ");
			scanf("%s",key);
			encrypt_vigenere(key);
			goto top;
			break;
		case 4:
			printf("\nInput will be taken from 'cipher.txt'.\n");
			printf("Enter key for decryption: ");
			scanf("%s",key);
			decrypt_vigenere(key);
			goto top;
			break;
		default:
			printf("Enter proper choice!\n");
			goto top;
			break;
	}
}