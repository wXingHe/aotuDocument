#include <iostream>
#include <string>
#include <Document.h>
#include <io.h>
#include <vector>
#include <direct.h>
#include <windows.h>
using namespace std;

/**
 * ��ȡ�ļ�
 * @param string Ŀ¼·��
 * @param vector<vector<string>> �����ļ�����·�����ļ���������
 * @param string �ļ���׺
 * @return void
 */
void findFile(string, vector<vector<string>> &, string);

#define CHECK_LENGTH 10       //����Ƿ�Ϊutf8����ʱ�������ַ�����
int is_utf8_string(const char *);

/**
 * ��ȡ�ļ�����
 * @param string �ļ�·��
 * @return string �ַ�����
 */
int getFileCode(char *);

int main()
{
    SetConsoleTitle("�ĵ�ת���� v1.0");
    string suffix = "txt";
    cout << "������Ҫת�����ĵ���׺:��txt,php" << endl;
    cin >> suffix;

    int descriptionOnHead;
    cout << "�ĵ�ͷ���Ƿ����ĵ�˵����Ҫ����?\n�����������ͷ��˵��������;����������0" << endl;
    cin >> descriptionOnHead;
    descriptionOnHead = descriptionOnHead > 0 ? descriptionOnHead : 0;
    string path = "E:\\document\\document\\document";
    string dir = path+"\\result";
    mkdir(dir.data()); //��������ĵ�Ŀ¼

    //��ȡ�ļ�
    vector<vector<string>> files; //����ļ�����
    findFile(path,files,suffix);

    if(files.size() <= 0){
        cout << "��Ŀ¼���ļ�" << endl;
        return 0;
    }
    string content = "";
    string documentContent;
    int is_utf8 = 0;
    for(vector<vector<string>>::iterator it=files.begin();it!=files.end();it++){
            cout << "��ȡ�ļ�:" << (*it)[1] << " ";
            Document d((*it)[0],descriptionOnHead);
            d.check();
            content = "# "+(*it)[1]+"\n\n";

            //����ļ�����
            const char * str;
            str = d.titles[0].data();
            is_utf8 = is_utf8_string(str);

            //��ȡ�ĵ�����
            content += d.toMarkdown(is_utf8);

            //�ĵ�ת��utf8
            documentContent = is_utf8 ? content : d.GbkToUtf8(content.data());
            //documentContent = content;

            //д���ĵ�����
            ofstream file(dir + "\\" + (*it)[1] + ".md");
            if(!file){
                cout << "���ļ�,�ļ�������" << (*it)[0] << endl;
                continue;
            }
            file << documentContent << endl;
            file.close();//�ر��ļ�
            delete str;
            content = "";
    }

    return 0;

    //d.printTitles();
    //d.printMethodss();
    //d.printExplains();
    //return 0;
}

/**��ȡ�����ļ�*/
void findFile(string path, vector<vector<string>> &res, string spc = ""){
    if(spc != ""){
        spc = "." + spc;
    }
    vector<string> file(2);
    string p;
    long hFile = 0;                //�ļ����
    struct _finddata_t fileinfo;    //�ļ���Ϣ
    int subIndex;
    string name;
    if((hFile = _findfirst(p.assign(path).append("\\*" + spc).c_str(), &fileinfo)) != 0)
    {
        do
        {
            string path_s = p.assign(path).append("\\").append(fileinfo.name);
            name = fileinfo.name;
            subIndex = name.find(".");
            file[0] = path_s;
            file[1] =  name.substr(0,subIndex == -1 ? name.length() : subIndex);
            res.push_back(file);
        }
        while(_findnext(hFile, &fileinfo) != -1);
        _findclose(hFile);    //�ر��ļ�
    }
}


/**
 * ��ȡ�ļ�����
 * @param const char * �ַ�����ָ��
 * @return int �жϽ��
 */
int is_utf8_string(const char *utf)
    {
        int length = strlen(utf);
        int check_sub = 0;
        int i = 0;

        if ( length > CHECK_LENGTH )  //ֻȡǰ���ض����ȵ��ַ�����֤����
        {
            length = CHECK_LENGTH;
        }

        for ( ; i < length; i ++ )
        {
            if ( check_sub == 0 )
            {
                if ( (utf[i] >> 7) == 0 )         //0xxx xxxx
                {
                    continue;
                }
                else if ( (utf[i] & 0xE0) == 0xC0 ) //110x xxxx
                {
                    check_sub = 1;
                }
                else if ( (utf[i] & 0xF0) == 0xE0 ) //1110 xxxx
                {
                    check_sub = 2;
                }
                else if ( (utf[i] & 0xF8) == 0xF0 ) //1111 0xxx
                {
                    check_sub = 3;
                }
                else if ( (utf[i] & 0xFC) == 0xF8 ) //1111 10xx
                {
                    check_sub = 4;
                }
                else if ( (utf[i] & 0xFE) == 0xFC ) //1111 110x
                {
                    check_sub = 5;
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                if ( (utf[i] & 0xC0) != 0x80 )
                {
                    return 0;
                }
                check_sub --;
            }
        }
        return 1;
    }
