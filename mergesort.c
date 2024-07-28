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

void printrdata(int data[],int i, int n){
  for(; i <= n; i++){
    printf("\x1b[31m%d \x1b[0m", data[i]);
  }
}

void printbdata(int data[], int i,int n){
  for(; i <= n; i++){
    printf("\x1b[34m%d \x1b[0m", data[i]);
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

void mergesort(int a[],int l, int r,int all){
    int i;
    int j;
    int k;
    int m;
    int b[r+1];
    if(l<r){
        m = (r+l)/2;
        printrdata(a,l,m);
        printbdata(a,m+1,r);
        mergesort(a,l,m,all);
        mergesort(a,m+1,r,all);
        for(i= m;i>=l;i--){
            b[i] = a[i];
        }
        i = l;
        for(j = m +1; j <= r; j++){
            b[r+m+1-j] = a[j];
        }
        j = r;
        printf("bは");
        printrdata(b,i,m);
        printbdata(b,m+1,j);
        for(k = l; k<= r; k++){
            printf("赤は%d,青は%d     ",b[i],b[j]);
            if(b[i] < b[j]){
                printf("よって赤側からとる\n");
                a[k] = b[i++];
            }else{
                if(b[i] ==b[j]){
                    printf("両者同じ\n");
                }else{
                printf("よって青側からとる\n");
                }
                a[k] = b[j--];
            }
        }
        printf("現在のaは");
        printdata(a,all);
        printf("\n");
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

  mergesort(data,let,ndata,ndata);

  printdata(data, ndata);

  return 0;
}