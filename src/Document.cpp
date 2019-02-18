#include "Document.h"

Document::Document(string file, int ignore = 0,int fileCounter = 1)
{
    fileNumber = fileCounter;
    ignoreBlock = ignore;
    int commentBlock = 0; //注释块计数器
    char ch;
    ifstream fin(file);
    queue <char> block;
    char prev;
    bool hasGetMethod = false;
    string methodString;
    while( fin.get(ch) ){
        switch(ch){
            case '/':
                if(block.empty()){
                    block.push(ch);
                    continue;
                }
                if(block.back() == '*'){
                    block.push(ch);
                    commentBlock ++;
                    //printQueue(block);
                    if(commentBlock > ignoreBlock){ //忽略头部的说明注释块
                        formatComment(block);
                        hasGetMethod = true;
                    }
                    clearQueue(block);
                }else{
                    clearQueue(block);
                }
                break;
            case '*':
                if(block.empty()){
                    continue;
                }
                prev = block.back();
                if(prev == '/' || prev == '*' || prev == ' '){
                    block.push(ch);
                }
                break;
            default :
                if(hasGetMethod == true){
                    if(ch != '{'){
                        methodString += ch;
                    }else{
                        getMethod(methodString);
                        methodString = "";
                        hasGetMethod = false;
                    }
                }
                if(block.empty()){
                    continue;
                }
                block.push(ch);
                break;
            }
    }

    fin.close();
}

/**
 * 清空队列
 * @param queue q 字符串队列
 * @return void
 */
void Document::clearQueue(queue <char> &q){
    queue <char> empty;
    swap(empty,q);
}

/**
 * 打印队列
 * @param queue q 字符串队列
 * @return void
 */
void Document::printQueue(queue <char> q){
    if(q.empty()){
        cout << "error:空队列" <<endl;
    }

    while(!q.empty()){
        cout << q.front();
        q.pop();
    }
}

/**
 * 格式化注释
 * @param queue q 注释的字符队列
 * @return void
 */
void Document::formatComment(queue <char> q){
    string title = ""; //标题
    bool titleStart = false; //标题开始
    bool titleEnd = false; //标题结束
    bool explain = false; //说明开始
    queue <char> explainChar; //说明字符队列
    char currentCahr; //当前字符
    char prevChar; //上一个字符

    vector<string> explainVector;
    vector <vector<string>> explainsVector;

    while(!q.empty()){
        currentCahr =  q.front();
        //提取标题(**之后@之前)
        if(currentCahr == '*' && prevChar == '*'){
            titleStart = true;
        }
        if(currentCahr == '@'){
            titleEnd = true;
            if(explain == false){
                explain = true;
            }else{
                explainVector = formatExplain(explainChar);
                explainsVector.push_back(explainVector);
                clearQueue(explainChar);
            }
        }
        if(titleStart == true && titleEnd == false){
            if(currentCahr != '*' && currentCahr != '\n'){
                title += currentCahr;
            }
        }
        //提取每个段(@~@,或者@~/)
        if(explain == true && currentCahr != '*' && currentCahr != '/'){
            explainChar.push(currentCahr);
        }
        prevChar = currentCahr;
        q.pop();
    }
    titles.push_back(title);
    explains.push_back(explainsVector);
}

/**
 * 格式化说明
 * @param queue q 字符串队列(待格式化的字符队列)
 * @return void
 */
vector<string> Document::formatExplain(queue <char> q){
    vector<string> explain(4);
    vector<string>::iterator it;
    it = explain.begin();
    int counter = 0; //空格计数器spaceCounter
    char ch;
    char prev;
    while(!q.empty()){
        ch = q.front();
         q.pop();
        if(ch == ' '){
            if(prev == ' '){
                continue;
            }
            counter ++;
        }

        if(counter < 4){
            *(it + counter) += ch;
        }
        prev = ch;
    }

    return explain;
}

/**
 * 提取方法
 * @param queue q 一个stl的标准队列(注释的字符队列)
 * @return void
 */
void Document::getMethod(string str){
    if(str.length() == 0){
        cout << "提取方法时输入了空的字符串" << endl;
        return;
    }
    string method;
    method = (replace_all(str,"function ", ""));
    method = (replace_all(str,"public ", ""));
    method = (replace_all(str,"\n", ""));
    methods.push_back(method);
}

/**
 * 字符串替换
 * @param queue q 一个stl的标准队列(注释的字符队列)
 * @return void
 */
string& Document::replace_all(string& str,const string& old_value,const string& new_value){
    while(true){
            string::size_type   pos(0);
            if((pos=str.find(old_value))!=string::npos)
                str.replace(pos,old_value.length(),new_value);
            else break;
    }
    return str;
}

/**
 * 打印标题
 */
void Document::printTitles(){
    if(titles.empty()){
        cout << "无标题内容" << endl;
        return ;
    }
    cout << "共有: " << methods.size() <<  " 个标题";
    for(vector<string>::iterator it=titles.begin();it!=titles.end();it++)
        cout << "标题:" << *it << " ";
}

/**
 * 打印方法
 */
void Document::printMethodss(){
    if(methods.empty()){
        cout << "无方法内容" << endl;
        return ;
    }
    cout << "共有: " << methods.size() <<  " 个方法";
    for(vector<string>::iterator it=methods.begin();it!=methods.end();it++)
        cout << "方法:" << *it << " ";
}

/**
 * 打印说明
 */
void Document::printExplains(){
    if(explains.empty()){
        cout << "无说明内容" << endl;
        return ;
    }
    cout << "共有: " << explains.size() <<  " 个说明";
    vector<string>::iterator it;
    vector<vector<string>>::iterator iter;
    vector<vector<vector<string>>>::iterator explainIter;
    vector<string> explianTmp;
    vector<vector<string>> explainsTmp;
    int explainCounter = 0; //说明计数器,用于辨别说明类型[1=>说明类型,2=>参数类型,3=>参数名称,4=>参数描述]

    cout << " 说明如下 : " << endl;
    for(explainIter = explains.begin(); explainIter != explains.end(); explainIter++)
    {
        cout << "************************************************************************" <<endl;
        explainsTmp = *explainIter;
        for(iter = explainsTmp.begin(); iter != explainsTmp.end(); iter++)
        {
            explianTmp = *iter;
            for(it = explianTmp.begin(); it != explianTmp.end(); it++) {
                explainCounter ++;
                cout << explainCounter << " : " << *it << " ";
            }
            explainCounter = 0;
        }

    }

}

/**
 * 检查文档结构
 */
void Document::check(){
    int titleSize = titles.size() - ignoreBlock;
    int methodSize = methods.size() - ignoreBlock;
    int explainSize = explains.size() - ignoreBlock;

    cout << "标题数量:" << titleSize << endl;
    cout << "方法数量:" << methodSize << endl;
    cout << "说明数量:" << explainSize << endl;

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出设备句柄
    WORD wr;//定义颜色属性；第一位为背景色，第二位为前景色
    if(titleSize == methodSize && titleSize == explainSize){
        wr = 0x0a;
        SetConsoleTextAttribute(hOut, wr);
        cout << "内容结构数量一致:" << explainSize << endl;
    }else{
        wr = FOREGROUND_RED | FOREGROUND_INTENSITY;//方法二用系统宏定义颜色属性
        SetConsoleTextAttribute(hOut, wr);
        cout << "内容结构数量不一致:" << explainSize << endl;
    }

    wr = 0x0f;
    SetConsoleTextAttribute(hOut, wr); //恢复黑底白字
}

/**
 * 返回markdown格式的内容
 */
string Document::toMarkdown(int is_utf8){
    string content = "";

    if(explains.empty()){
        cout << "无说明内容" << endl;
        return "无说明内容";
    }

    vector<string>::iterator it;
    vector<vector<string>>::iterator iter;
    vector<vector<vector<string>>>::iterator explainIter;
    vector<string> explianTmp;
    vector<vector<string>> explainsTmp;
    int explainCounter = 0; //说明计数器,用于辨别说明类型[1=>说明类型,2=>参数类型,3=>参数名称,4=>参数描述]
    int methodCounter = 0; //方法计数器
    int a = fileNumber; //a=>文件数量计数器类型,b=>文件数量计数器的字符类型,c=>文件数量计数器的字符串类型
    char b[2];
    string c;
    char itc[8];
    cout << " 说明如下 : " << endl;
    string prepareString;
    for(explainIter = explains.begin(); explainIter != explains.end(); explainIter++)
    {
        sprintf(itc,"%d",methodCounter+1);
        sprintf(b,"%d",a);
        c = b;
        content.append("## " + c + ".").append(itc).append(titles[methodCounter]).append("\n\n");
        prepareString = "### 函数: ";
        prepareString = is_utf8?  GbkToUtf8(prepareString.data()) : prepareString;
        content.append(prepareString+methods[methodCounter]+"\n\n");
        prepareString = "\t说明:\n\n";
        prepareString = is_utf8?  GbkToUtf8(prepareString.data()) : prepareString;
        content.append(prepareString);
        explainsTmp = *explainIter;
        for(iter = explainsTmp.begin(); iter != explainsTmp.end(); iter++)
        {
            content.append("\t* ");
            explianTmp = *iter;
            for(it = explianTmp.begin(); it != explianTmp.end(); it++) {
                explainCounter ++;
                content.append(" " + *it);
                //cout << explainCounter << " : " << *it << " ";
            }
            explainCounter = 0;
            content.append("\n");
        }
        methodCounter ++;
    }
    return content;
}

/**
 * 将gbk字符数组utf8字符串
 */
string Document::GbkToUtf8(const char *src_str){
	int len = MultiByteToWideChar(CP_ACP, 0, src_str, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, src_str, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	string strTemp = str;
	if (wstr) delete[] wstr;
	if (str) delete[] str;
	return strTemp;
}

Document::~Document()
{
    //dtor
}
