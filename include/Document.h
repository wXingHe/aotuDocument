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
        string file; //�ļ���
        vector <string> titles; //��������
        int fileNumber;
    protected:
        int ignoreBlock; //��Ҫ���Ե�ע�Ϳ�(��ͷ����ʼ)

        vector <string> methods; //��������
        vector <vector<vector<string>>>  explains; //˵������

    public:
        Document(string,int,int);
        void clearQueue(queue <char> &); //��ն���
        void printQueue(queue <char>); //��ӡ����
        string& replace_all(string& ,const string& ,const string& ); //�滻�ַ���
        void printTitles();
        void printMethodss();
        void printExplains();
        void check();
        string toMarkdown(int);
        string GbkToUtf8(const char *);
        virtual ~Document();

    protected:
        void formatComment(queue <char>); //��ʽ��ע��
        vector <string> formatExplain(queue <char>); //��ʽ��˵��
        void getMethod(string); //��ȡ������

    private:
};

#endif // DOCUMENT_H
