#include<stdio.h>

int encrypt()
{
	char c, enc_c;
	int key;
	FILE *fin, *fout;
	fin = fopen("input.txt","r");
	fout = fopen("output.txt","w");

	printf("\n\nEnter key: ");
	scanf("%d", &key);
	
	while(!feof(fin))
	{
		c = fgetc(fin);
		if(c >= 'A' && c <= 'Z')
		{
			enc_c = ((c-'A'+key)%26)+'A';
			fprintf(fout,"%c",enc_c);
			printf("%c",enc_c);
		}
		else if(c >= 'a' && c <= 'z')
		{
			enc_c = ((c-'a'+key)%26)+'A';
			fprintf(fout,"%c",enc_c);
			printf("%c",enc_c);
		}
	}
	printf("\n\n");
	fprintf(fout,"\n");
	fclose(fin);
	fclose(fout);

	return 0;
}

int decrypt_bruteforce()
{
	char c, dec_c;
	int key, decrypted = 0, ch = 0;
	FILE *fin, *fout;

	printf("\n\n");

	for(key = 0; key < 26; key++)
	{
		fin = fopen("output.txt","r");
		fout = fopen("decrypted.txt","w");
		while(!feof(fin))
		{
			c = fgetc(fin);
			if(c >= 'A' && c <= 'Z')
			{
				dec_c = ((c-'A'-key+26)%26)+'A';
				fprintf(fout,"%c",dec_c);
				printf("%c",dec_c);
			}
			else if(c >= 'a' && c <= 'z')
			{
				dec_c = ((c-'a'-key+26)%26)+'A';
				fprintf(fout,"%c",dec_c);
				printf("%c",dec_c);
			}
		}
		printf("\n");
		fprintf(fout,"\n");
		fclose(fin);
		fclose(fout);
		printf("Is output decrypted?[Yes=1/No=0]: ");
		scanf("%d",&ch);
		if(ch == 1)
		{
			decrypted = 1;
			break;
		}
	}
	
	if(decrypted == 0)
		printf("Either input is not ceaser cipher or you didn't recognize the true output!!!\n");

	printf("\n");

	return 0;
}

int decrypt_freqanalysis()
{
	char c, dec_c;
	int key, decrypted = 0, ch = 0, freq[2][26], i, j, swap, freq_c;
	FILE *fin, *fout, *fref;

	printf("\n\n");

	for(i = 0;i < 26;++i)
	{
		freq[0][i] = i;
		freq[1][i] = 0;
	}

	fin = fopen("output.txt","r");
	while(!feof(fin))
	{
		c = fgetc(fin);
		if(c >= 'A' && c <= 'Z')
		{
			freq[1][c-'A']++;
		}
		else if(c >= 'a' && c <= 'z')
		{
			freq[1][c-'a']++;
		}
	}
	fclose(fin);

	for(i = 0; i < 25; i++)
	{
		for(j = 0 ; j < 25-i; j++)
		{
			if(freq[1][j] < freq[1][j+1])
			{
				swap = freq[0][j];
				freq[0][j] = freq[0][j+1];
				freq[0][j+1] = swap;
				swap = freq[1][j];
				freq[1][j] = freq[1][j+1];
				freq[1][j+1] = swap;
			}
		}
	}
	freq_c = freq[0][0];

	for(i = 0;i < 26;++i)
	{
		freq[0][i] = i;
		freq[1][i] = 0;
	}

	fref = fopen("reference.txt","r");
	while(!feof(fref))
	{
		c = fgetc(fref);
		if(c >= 'A' && c <= 'Z')
		{
			freq[1][c-'A']++;
		}
		else if(c >= 'a' && c <= 'z')
		{
			freq[1][c-'a']++;
		}
	}
	fclose(fref);

	for(i = 0; i < 25; i++)
	{
		for(j = 0 ; j < 25-i; j++)
		{
			if(freq[1][j] < freq[1][j+1])
			{
				swap = freq[0][j];
				freq[0][j] = freq[0][j+1];
				freq[0][j+1] = swap;
				swap = freq[1][j];
				freq[1][j] = freq[1][j+1];
				freq[1][j+1] = swap;
			}
		}
	}

	for(i = 0; i < 26; ++i)
	{
		key = freq_c - freq[0][i];
		fin = fopen("output.txt","r");
		fout = fopen("decrypted.txt","w");
		while(!feof(fin))
		{
			c = fgetc(fin);
			if(c >= 'A' && c <= 'Z')
			{
				dec_c = ((c-'A'-key+26)%26)+'A';
				fprintf(fout,"%c",dec_c);
				printf("%c",dec_c);
			}
			else if(c >= 'a' && c <= 'z')
			{
				dec_c = ((c-'a'-key+26)%26)+'A';
				fprintf(fout,"%c",dec_c);
				printf("%c",dec_c);
			}
		}
		printf("\n");
		fprintf(fout,"\n");
		fclose(fin);
		fclose(fout);
		printf("Is output decrypted?[Yes=1/No=0]: ");
		scanf("%d",&ch);
		if(ch == 1)
		{
			decrypted = 1;
			printf("\nKey : %d",key%26);
			break;
		}
	}
	
	if(decrypted == 0)
		printf("Either input is not ceaser cipher or you didn't recognize the true output!!!\n");

	printf("\n");

	return 0;
}

int main()
{
	int ch;
top:	printf("\n\n");
	printf("1. Encrypt data.\n");
	printf("2. Decrypt data using bruteforce.\n");
	printf("3. Decrypt data using frequency analysis.\n");
	printf("0. Exit\n");
	printf("Enter choice: ");
	scanf("%d", &ch);
	switch(ch)
	{
		case 0:
			return 0;
			break;
		case 1:
			encrypt();
			goto top;
			break;
		case 2:
			decrypt_bruteforce();
			goto top;
			break;
		case 3:
			decrypt_freqanalysis();
			goto top;
			break;
		default:
			printf("Enter proper choice!\n");
			goto top;
			break;
	}
}



















