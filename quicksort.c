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

void printdata2(int data[],int i, int n){
  for(; i <= n; i++){
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

int partition(int a[],int l,int r){
    printf("今回ソートする部分は");
    printdata2(a,l,r);
    int i,j;
    int v;
    v = a[l];
    i = l;
    j = r+1;
    do{
        do{
            i++;
        }while(a[i] < v);
        printf("小さいほうの異常値候補iは%d\n",a[i]);
        do{
            j--;
        }while(a[j] > v);
        printf("大きいほうの異常値候補jは%d\n",a[j]);
        if(i<j){
            printf("異常値だったため%dと%dを交換\n",a[i],a[j]);
            swap(&a[i],&a[j]);
            printdata2(a,l,r);
        }
    }while(j>i);
    printf("異常値ではなくなった\n");
    a[l] = a[j];
    a[j] = v;
    printdata2(a,l,r);
    printf("返すiは%d\n",j);
    return j;
}

void quicksort(int a[], int l, int r){
    printf("\n");
    printf("範囲%d~%dのクイックソート、対象は%d\n",l,r,a[l]);
  int i;
  if(l < r){
    i = partition(a,l,r);
    quicksort(a,l,i-1);
    quicksort(a,i+1,r);
  }else{
    printf("これは要素数1以下のため無視\n");
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
  int let = 1;

  printdata(data, ndata);

  quicksort(data,let,ndata);

  printdata(data, ndata);

  return 0;
}