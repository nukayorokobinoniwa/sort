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

void selectionsort(int a[], int n){
  int i, j,minindex;
  printf("nは%d\n",n);
  for(i = 1; i < n; i++){
    minindex = i;
    printf("a[%d]の整列を開始する\n",i);
    for(j = i+1; j <=n ; j++){
      if(a[j] < a[minindex]){
        minindex = j;
        printf("a[%d]の%dを最小値に更新\n",j,a[j]);
      }
    }
    swap(&a[minindex], &a[i]);
    printdata(a, n);
    printf("a[%d]の整列が終わった\n",i);
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

  selectionsort(data, ndata);

  printdata(data, ndata);

  return 0;
}