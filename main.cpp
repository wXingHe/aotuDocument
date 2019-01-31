#include <iostream>
#include <string>
#include <Document.h>
#include <io.h>
#include <vector>
#include <direct.h>
#include <windows.h>
using namespace std;

/**
 * 获取文件
 * @param string 目录路径
 * @param vector<vector<string>> 包含文件完整路径和文件名的数组
 * @param string 文件后缀
 * @return void
 */
void findFile(string, vector<vector<string>> &, string);

#define CHECK_LENGTH 10       //检查是否为utf8编码时所检查的字符长度
int is_utf8_string(const char *);

/**
 * 获取文件编码
 * @param string 文件路径
 * @return string 字符编码
 */
int getFileCode(char *);

int main()
{
    SetConsoleTitle("文档转换器 v1.0");
    string suffix = "txt";
    cout << "请输入要转换的文档后缀:如txt,php" << endl;
    cin >> suffix;

    int descriptionOnHead;
    cout << "文档头部是否有文档说明需要忽略?\n若有请输入该头部说明的数量;若无请输入0" << endl;
    cin >> descriptionOnHead;
    descriptionOnHead = descriptionOnHead > 0 ? descriptionOnHead : 0;
    string path = "E:\\document\\document\\document";
    string dir = path+"\\result";
    mkdir(dir.data()); //创建存放文档目录

    //获取文件
    vector<vector<string>> files; //存放文件数组
    findFile(path,files,suffix);

    if(files.size() <= 0){
        cout << "该目录无文件" << endl;
        return 0;
    }
    string content = "";
    string documentContent;
    int is_utf8 = 0;
    for(vector<vector<string>>::iterator it=files.begin();it!=files.end();it++){
            cout << "获取文件:" << (*it)[1] << " ";
            Document d((*it)[0],descriptionOnHead);
            d.check();
            content = "# "+(*it)[1]+"\n\n";

            //检测文件编码
            const char * str;
            str = d.titles[0].data();
            is_utf8 = is_utf8_string(str);

            //获取文档内容
            content += d.toMarkdown(is_utf8);

            //文档转换utf8
            documentContent = is_utf8 ? content : d.GbkToUtf8(content.data());
            //documentContent = content;

            //写入文档内容
            ofstream file(dir + "\\" + (*it)[1] + ".md");
            if(!file){
                cout << "打开文件,文件不存在" << (*it)[0] << endl;
                continue;
            }
            file << documentContent << endl;
            file.close();//关闭文件
            delete str;
            content = "";
    }

    return 0;

    //d.printTitles();
    //d.printMethodss();
    //d.printExplains();
    //return 0;
}

/**获取遍历文件*/
void findFile(string path, vector<vector<string>> &res, string spc = ""){
    if(spc != ""){
        spc = "." + spc;
    }
    vector<string> file(2);
    string p;
    long hFile = 0;                //文件句柄
    struct _finddata_t fileinfo;    //文件信息
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
        _findclose(hFile);    //关闭文件
    }
}


/**
 * 获取文件编码
 * @param const char * 字符数组指针
 * @return int 判断结果
 */
int is_utf8_string(const char *utf)
    {
        int length = strlen(utf);
        int check_sub = 0;
        int i = 0;

        if ( length > CHECK_LENGTH )  //只取前面特定长度的字符来验证即可
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
