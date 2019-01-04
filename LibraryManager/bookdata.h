#ifndef BOOKDATA_H
#define BOOKDATA_H

const int SUBTRIE = 26; // 26叉树
const int NAMESIZE = 30;
typedef struct BookDetaild {
    long bookID;
    char *bookName;
    char *authorName;
    char *accessNumber;
    int currStorage = 0;
    int totalStorage = 0;
    char *pressName;
    long pressDate = 0;
    int pagesNumber = 0;
    char *standardCode;
    struct BookDetaild *next;
} BookDetailD;

typedef struct trieNode{
    int nCount = 0;
    bool isnData = true;
    BookDetailD *data;
    struct trieNode *nextTree[30];

} TrieBookDetail;

typedef struct boRecord{
    struct boRecord *next;
    BookDetailD *bookDetail;
    long lendDate = -1; // 借书日期
    long rebackDate = -1;   // 还书日期

} BorrowRecord;

typedef struct readinfo{
    long readerID;  // 读者卡ID
    char *readerName;   // 姓名
    char *readerRole;   // 角色
    long phoneNum;  // 手机号
    long createDate;    // 账号创建时间
    int allowBookNum;   // 允许借书数量
    int hasLentBookNum; // 已借数量
    BorrowRecord *borrowRecord; // 借书记录
    struct readinfo *next;
} ReaderInfoD;






#endif // BOOKDATA_H
