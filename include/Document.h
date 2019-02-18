#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <string>
#include <fstream>
#include <queue>
#include <vector>
#include <iostream>
#include <iterator>
#include <array>
#include <windows.h>

using namespace std;

class Document
{
    public:
        string file; //文件名
        vector <string> titles; //标题数组
        int fileNumber;
    protected:
        int ignoreBlock; //需要忽略的注释块(从头部开始)

        vector <string> methods; //方法数组
        vector <vector<vector<string>>>  explains; //说明数组

    public:
        Document(string,int,int);
        void clearQueue(queue <char> &); //清空队列
        void printQueue(queue <char>); //打印队列
        string& replace_all(string& ,const string& ,const string& ); //替换字符串
        void printTitles();
        void printMethodss();
        void printExplains();
        void check();
        string toMarkdown(int);
        string GbkToUtf8(const char *);
        virtual ~Document();

    protected:
        void formatComment(queue <char>); //格式化注释
        vector <string> formatExplain(queue <char>); //格式化说明
        void getMethod(string); //提取方法名

    private:
};

#endif // DOCUMENT_H
