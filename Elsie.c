#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#define SIZE 70
const int M = 6;
const int N = 6;

//Finding the row in which character of plaintext appears in key
int findPositionofRow(char plainchar,char key[][N])
{
  for(int i=0;i<6;i++)
  {
    for(int j=0;j<6;j++)
    {
      if(plainchar == key[i][j])
      {
        return i;
      }
    }
  }
}

//Finding the column in which character of plaintext appears in key
int findPositionofColumn(char plainchar,char key[][N])
{
  for(int i=0;i<6;i++)
  {
    for(int j=0;j<6;j++)
    {
      if(plainchar == key[i][j])
      {
        return j;
      }
    }
  }
}

//Performing Encryption using Elsie Four Cipher
void getCipherText(char finalPlainMessage[],char stateMatrix[][N],char p[])
{
  int r = 0,c = 0,x = 0,y = 0,i=0,j=0;
  char cipherText[strlen(finalPlainMessage)];
  printf("\nThe Received Plaintext Including Nonce and Signature is\n");
  puts(finalPlainMessage);
  for(int h=0; h < strlen(finalPlainMessage); h++)
  {
        r = findPositionofRow(finalPlainMessage[h],stateMatrix);
        c = findPositionofColumn(finalPlainMessage[h],stateMatrix);
        x = (r+(stateMatrix[i][j]/6))%6;
        y = (c+(stateMatrix[i][j]%6))%6;
        cipherText[h] = stateMatrix[x][y];

        char temp = stateMatrix[r][0];
        for(int k=0;k<5;k++)
        {
          stateMatrix[r][k] = stateMatrix[r][k+1];
        }
          stateMatrix[r][5] = temp;
          //c = (c+1)%6;
        char temp1 = stateMatrix[0][y];
        for(int k=0;k<5;k++)
        {
          stateMatrix[k][y] = stateMatrix[k+1][y];
        }
          stateMatrix[5][y] = temp1;

          i = (i+(c/6))%6;
          j = (j+(c%6))%6;

          for(int i = 0 ; i<6 ; i++)
          {
            //printf("Iteration %d",i);
            //printf("\n");
            for(int j = 0 ; j<6 ; j++)
            {
              printf("%c\t",stateMatrix[i][j]);
            }
            printf("\n");
          }
          printf("*********************************\n");
    }
    for(int i=0;i<6;i++)
    {
      cipherText[i] = p[i];
    }
    cipherText[strlen(finalPlainMessage)] = '\0';
    printf("Obtained CipherText is\n");
    puts(cipherText);
}

//Initializing the Initial State
void stateMatrix(char key[],char finalPlainMessage[],char p[])
{
  int i,j;
  char stateMatrix[6][6];
  for(int k=0;k<36;k++)
  {
    stateMatrix[k/6][k%6] = key[k];
  }
getCipherText(finalPlainMessage,stateMatrix,p);
}

    int intN(int n) { return rand() % n; }
//To Generate Random Nonce

char *randomString(int len) {
      const char alphabet[] = "abcdefghijklmnopqrstuvwxyz#_23456789";
        char *nonce = malloc((len + 1) * sizeof(char));
        int i;
        for (i = 0; i < len; i++) {
          nonce[i] = alphabet[intN(strlen(alphabet))];
        }
        nonce[len] = '\0';
        return nonce;
      }

int main()
{
char plaintext[20], z=0;
char finalMessage[SIZE];
char *p;
char signature[] = "#its_me";
char key[] = "hxo_tp#a3jdnmq2glf75kw469eyrzbvci8us";
printf("\nEnter the plainText\n");
gets(plaintext);

  srand(6);
  p = randomString(6);
  strcpy(finalMessage,p);
  strcat(finalMessage,plaintext);
  strcat(finalMessage,signature);
  stateMatrix(key,finalMessage,p);

return 0;
}
