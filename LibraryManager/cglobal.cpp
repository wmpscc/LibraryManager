#include"cglobal.h"
#include <QString>
#include <stdlib.h>
#define MAXSIZE  89
BookDetailD *bd_head_s;
long book_id_s = 0;
TrieBookDetail *trieNameRoot;
TrieBookDetail *triePressRoot;
TrieBookDetail *trieAuthorRoot;
ReaderInfoD *readerIndoHead;

long reader_id = 0;

// 斐波那契搜素
void fibonacci(int *f) {
    f[0] = 1;
    f[1] = 1;
    for (int i = 2; i < MAXSIZE; ++i) {
        f[i] = f[i - 2] + f[i - 1];
    }
}

int fibonacciSearch(BookDetailD *r[], int n, long iKey) {
    int i, k = 0;
    int low = 0, high = n - 1, mid = 0;
    int F[MAXSIZE];
    long *data = (long *)malloc(sizeof(long) * n);
    for(int j = 0; j < n; j++)
        data[j] = r[j]->bookID;

    fibonacci(F); // 计算斐波那契数列，存于数组F中备用
    while (high > F[k] - 1 && high > 1)  // 计算出n在斐波那契数列中对应的阶数
        ++k;

    for (i = n; i < F[k] - 1; ++i)     // 把数组补全
        data[i] = data[high];

    while (low <= high) {
        if (low == high) {
            if (data[low] == iKey)
                return low;
            else
                return -1;
        }
        mid = low + F[k - 1] - 1;   // 根据斐波那契数列进行黄金分割
        if (data[mid] > iKey) {
            high = mid - 1;
            k = k - 1;
        } else {
            if (data[mid] < iKey) {
                low = mid + 1;
                k = k - 2;
            } else {
                if (mid <= high)    // 如果为真则找到相应的位置
                    return mid;
                else
                    return -1;
            }
        }
    }
    return -1;
}

// 二分查找
int BinarySearch(ReaderInfoD *r[], int n, long iKey){
    int low = 0, high = n - 1;
    int mid;
    while(low <= high){
        mid = (low + high + 1) / 2;
        if(r[mid]->readerID <iKey)
            low = mid + 1;
        else if (r[mid]->readerID > iKey)
            high = mid - 1;
        else
            return mid;
    }
    return -1;
}

int BinarySearch_book(BookDetailD *r[], int n, long iKey){
    int low = 0, high = n - 1;
    int mid;
    while(low <= high){
        mid = (low + high + 1) / 2;
        if(r[mid]->bookID <iKey)
            low = mid + 1;
        else if (r[mid]->bookID > iKey)
            high = mid - 1;
        else
            return mid;
    }
    return -1;
}
// ****************字符串工具函数****************
int stringLength(char *s) {
    int i = 0;
    while (s[i++] != '\0');
    return i;
}

char *stringConcat(char *a, char *b) {
    char *c = (char *) malloc(stringLength(a) + stringLength(b) + 1);
    if (c == NULL)exit(1);
    char *head = c; // 首地址
    while (*a != '\0')
        *c++ = *a++;
    while ((*c++ = *b++) != '\0');
    return head;
}

// 深拷贝QString
char *stringCopy(QString str){
    char *copy = (char *)malloc(sizeof (char) * str.size());
    int i;
    QByteArray ba = str.toLocal8Bit();

    for(i = 0; i < ba.size(); ++i){
        copy[i] = ba.at(i);
    }
    copy[i] = '\0';
    return copy;
}
