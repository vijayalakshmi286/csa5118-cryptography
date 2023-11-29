#include<stdio.h>
#include<string.h>
#include<ctype.h>
void vigenereEncrypt(char*plaintext,const char*key)
{
	int keylength=strlen(key);
	int i,textlength=strlen(plaintext);
	for(i=0;i<textlength;i++)
	{
		if(isalpha(plaintext[i]))
		{
		char keychar=key[i%keylength];
		int keyshift=isupper(keychar)?keychar-'A':keychar-'a';
		if(isupper(plaintext[i]))
		{
		plaintext[i]=(plaintext[i]-'A'+keyshift)%26+'A';
		}
		else
		{
			plaintext[i]=(plaintext[i]-'a'+keyshift)%26+'a';
			}	
		}
	}
}
void vigenereDecrypt(char*ciphertext,const char*key)
{
	int keylength=strlen(key);
	int i,textlength=strlen(ciphertext);
	for (i=0;i<textlength;i++)
	{
		if(isalpha(ciphertext[i]))
		{
			char keychar=key[i%keylength];
			int keyshift=isupper(keychar)?keychar-'A':keychar-'a';
			if(isupper(ciphertext[i]))
			{
				ciphertext[i]=(ciphertext[i]-'A'- keyshift+26)%26+'A';
			}
			else
			{
				ciphertext[i]=(ciphertext[i]-'a'-keyshift+26)%26+'a';
			}
		}
	}
}
int main()
{
	char plaintext[100];
	char key[100];
	printf("enter plaintext:");
	fgets(plaintext,sizeof(plaintext),stdin);
	plaintext[strcspn(plaintext,"\n")]='\0';
	printf("enter key:");
	fgets(key,sizeof(key),stdin);
	key[strcspn(key,"\n")]='\0';
	vigenereEncrypt(plaintext,key);
	printf("encrypted text:%s\n",plaintext);
	vigenereDecrypt(plaintext,key);
	printf("decrypted text:%s\n",plaintext);
	return 0;
}
