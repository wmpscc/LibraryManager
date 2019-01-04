#ifndef CGLOBAL_H
#define CGLOBAL_H
#include"bookdata.h"
#include <QString>
extern long reader_id;
extern BookDetailD *bd_head_s;
extern long book_id_s;
extern TrieBookDetail *trieNameRoot;
extern TrieBookDetail *triePressRoot;
extern TrieBookDetail *trieAuthorRoot;
extern int fibonacciSearch(BookDetailD *r[], int n, long iKey);
extern ReaderInfoD *readerIndoHead;
extern int stringLength(char *s);
extern char *stringConcat(char *a, char *b);
extern char *stringCopy(QString str);
extern int BinarySearch(ReaderInfoD *r[], int n, long iKey);
extern int BinarySearch_book(BookDetailD *r[], int n, long iKey);
#endif // CGLOBAL_H
