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

void printreddata3(int data[], int n,int x, int y){
  int i;
  for(i = 1; i <= n; i++){
    if(i ==x || i == y || i == y+1){
    printf("\x1b[31m");
    printf("%d ", data[i]);
    printf("\x1b[0m");
    }else{
    printf("%d ", data[i]);
    }
  }
  printf("\n");
}

void printbluedata(int data[], int n,int x, int y){
  int i;
  for(i = 1; i <= n; i++){
    if(i ==x || i == y){
    printf("\x1b[34m");
    printf("%d ", data[i]);
    printf("\x1b[0m");
    }else{
    printf("%d ", data[i]);
    }
  }
  printf("\n");
}

void printbluedata3(int data[], int n,int x, int y){
  int i;
  for(i = 1; i <= n; i++){
    if(i ==x || i == y || i == y+1){
    printf("\x1b[34m");
    printf("%d ", data[i]);
    printf("\x1b[0m");
    }else{
    printf("%d ", data[i]);
    }
  }
  printf("\n");
}

void swap(int *a, int *b){
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}


void pushdown(int a[], int first, int last){
    int parent = first;
    printf("今回チェックする親ノード番号は%d\n",parent);
    int child = 2*parent;
    int check3;
    while(child <= last){
        check3 = 0;
        if(child<last){
            check3 = 1;
            printreddata3(a,last,parent,child);
            printf("子の対抗候補と比べて大きいほうを選択したい！つまり%dvs%d\n",a[child],a[child+1]);
            if(a[child] < a[child+1]){
                check3 = 1;
                printf("今回は%dの勝利\n",a[child+1]);
                child ++;
            }else{
                check3 = 2;
                printf("今回は%dの勝利\n",a[child]);
            }
        }else{
            printreddata(a,last,parent,child);
            printf("子の対抗候補はそもそも存在しない\n");
        }
        printf("親ノードとのチェック\n");
        if(a[parent] >= a[child]){
            if(check3 == 0){
            printreddata(a,last,parent,child);
        }else if(check3 ==2){
            printreddata3(a,last,parent,child);
        }else{
            printreddata3(a,last,parent,child-1);
        }
            break;
        }
        swap(&a[parent],&a[child]);
        if(check3 == 0){
            printreddata(a,last,parent,child);
        }else if(check3 ==2){
            printreddata3(a,last,parent,child);
        }else{
            printreddata3(a,last,parent,child-1);
        }
        parent = child;
        child= 2*parent;
    }
    printf("\n");
}

void pushdown2(int a[], int first, int last){
    int parent = first;
    printf("今回チェックする親ノード番号は%d\n",parent);
    int child = 2*parent;
    int check3;
    while(child <= last){
        check3 = 0;
        if(child<last){
            check3 = 1;
            printbluedata3(a,last,parent,child);
            printf("子の対抗候補と比べて大きいほうを選択したい！つまり%dvs%d\n",a[child],a[child+1]);
            if(a[child] < a[child+1]){
                check3 = 1;
                printf("今回は%dの勝利\n",a[child+1]);
                child ++;
            }else{
                check3 = 2;
                printf("今回は%dの勝利\n",a[child]);
            }
        }else{
            printbluedata(a,last,parent,child);
            printf("子の対抗候補はそもそも存在しない\n");
        }
        printf("親ノードとのチェック\n");
        if(a[parent] >= a[child]){
            if(check3 == 0){
            printbluedata(a,last,parent,child);
        }else if(check3 ==2){
            printbluedata3(a,last,parent,child);
        }else{
            printbluedata3(a,last,parent,child-1);
        }
            break;
        }
        swap(&a[parent],&a[child]);
        if(check3 == 0){
            printbluedata(a,last,parent,child);
        }else if(check3 ==2){
            printbluedata3(a,last,parent,child);
        }else{
            printbluedata3(a,last,parent,child-1);
        }
        parent = child;
        child= 2*parent;
    }
    printf("\n");
}

void heapsort(int a[],int n){
    int i;
    for(i = n/2; i>=1;i--){
        pushdown(a,i,n);
    }
    printf("\n\n\n原型完成\n\n\n\n");
    for(i =n;i>=2;i--){
        swap(&a[1],&a[i]);
        printf("\x1b[33m%d\x1b[0mのソートは完了した\n",a[i]);
        pushdown2(a,1,i-1);
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

  heapsort(data,ndata);

  printdata(data, ndata);

  return 0;
}