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

void printreddata(int data[], int n,int x, int y){
  int i;
  for(i = 1; i <= n; i++){
    if(i ==x || i == y){
    printf("\x1b[31m");
    printf("%d ", data[i]);
    printf("\x1b[0m");
    }else{
    printf("%d ", data[i]);
    }
  }
  printf("\n");
}

void printyellowdata(int data[], int n,int x){
  int i;
  for(i = 1; i <= n; i++){
    if(i ==x){
    printf("\x1b[33m");
    printf("%d ", data[i]);
    printf("\x1b[0m");
    }else{
    printf("%d ", data[i]);
    }
  }
  printf("\n");
}

void printbluedata(int data[], int n,int x){
  int i;
  for(i = 1; i <= n; i++){
    if(i ==x){
    printf("\x1b[34m");
    printf("%d ", data[i]);
    printf("\x1b[0m");
    }else{
    printf("%d ", data[i]);
    }
  }
  printf("\n");
}

void shellsort(int a[], int n){
    int i;
    int j;
    int h;
    int v;
    for(h=1;h <= n/9;h = 3*h+1);
        for(;h>0;h = h/3){
          printf("\x1b[31mhは%d\n\x1b[0m",h);
            for(i = h+1;i<=n;i++){
                v = a[i];
                j = i;
                int check = 0;
                printf("j=%d,  h =%d,  j-h=%d\n",j,h,j-h);
                printreddata(a,n,j,j-h);
                while(j>h && a[j-h]> v){
                  printf("j>hかつa[%d]>%d\n",j-h,v);
                    a[j] = a[j-h];
                    printyellowdata(a,n,j-h);
                    j = j - h;
                    check = check + 1;
                }
                a[j] = v;
                if(check > 0){
                printbluedata(a,n,j);
                }
            }
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
  printf("shellsortの解説\n");
  printf("チェックする所は\x1b[31m赤色\x1b[0m に\n");
   printf("取り出しているvが入る可能性の場所は\x1b[33m黄色\x1b[0mに\n");
   printf("vが入ったの場所は\x1b[34m青色\x1b[0mに\n");  
  printf("\n\n");

  printf("今回整列する配列は、\n");
  printdata(data, ndata);
  printf("\n\n");

  shellsort(data, ndata);

  printf("整列された配列は,\n");
  printdata(data, ndata);

  return 0;
}