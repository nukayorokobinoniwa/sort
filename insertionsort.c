#include <stdio.h>
#include <stdlib.h>

#define SIZE 10000 //dataの最大サイズの定義
#define LINELEN 20 //ファイルから1行を読み込むときの最大文字数

void printdata(int data[], int n){
  int i;
  for(i = 1; i <= n; i++){
    printf("%d ", data[i]);
  }
  printf("\n");
}

void swap(int *a, int *b){
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

void insertionsort(int a[], int n){
  int i, j;
  int v;
  a[0] = -100;
  printf("nは%d\n",n);
  for(i = 2; i <= n; i++){
    printf("%d番目の整列を開始する\n",i-1);
    v=a[i];
    j=i;
    while(a[j-1]>v){ 
        printf("vは%dで、jは%d,a[j-1]は%d。\n",v,j,a[j-1]);
        a[j] = a[j-1];
        j--;
        printdata(a, n);
    }
    a[j] = v;
    printf("最小値をもどす\n");
    printdata(a, n);
  }
}

int loaddata(char *filename, int data[]){
  FILE *fp;
  char line[LINELEN];
  int pos;

  fp = fopen(filename, "r");
  if(fp == NULL){
    fprintf(stderr, "Can't open file: %s\n", filename);
    exit(1);
  }

  pos = 1;
  while(fgets(line, sizeof(line), fp) != NULL){
    sscanf(line, "%d", &data[pos]);
    pos++;
  }

  fclose(fp);

  return pos-1;
}

int main(int ac, char **av){
  int ndata; //読み込んだデータの数
  int data[SIZE]; //読み込んだデータの数を示す整数

  if(ac != 2){
    fprintf(stderr, "Usage: %s <datafile>\n", av[0]);
    exit(1);
  }

  ndata = loaddata(av[1], data);

  printdata(data, ndata);

  insertionsort(data, ndata);

  printdata(data, ndata);

  return 0;
}