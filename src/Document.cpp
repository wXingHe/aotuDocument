#include "Document.h"

Document::Document(string file, int ignore = 0,int fileCounter = 1)
{
    fileNumber = fileCounter;
    ignoreBlock = ignore;
    int commentBlock = 0; //ע�Ϳ������
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
                    if(commentBlock > ignoreBlock){ //����ͷ����˵��ע�Ϳ�
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
 * ��ն���
 * @param queue q �ַ�������
 * @return void
 */
void Document::clearQueue(queue <char> &q){
    queue <char> empty;
    swap(empty,q);
}

/**
 * ��ӡ����
 * @param queue q �ַ�������
 * @return void
 */
void Document::printQueue(queue <char> q){
    if(q.empty()){
        cout << "error:�ն���" <<endl;
    }

    while(!q.empty()){
        cout << q.front();
        q.pop();
    }
}

/**
 * ��ʽ��ע��
 * @param queue q ע�͵��ַ�����
 * @return void
 */
void Document::formatComment(queue <char> q){
    string title = ""; //����
    bool titleStart = false; //���⿪ʼ
    bool titleEnd = false; //�������
    bool explain = false; //˵����ʼ
    queue <char> explainChar; //˵���ַ�����
    char currentCahr; //��ǰ�ַ�
    char prevChar; //��һ���ַ�

    vector<string> explainVector;
    vector <vector<string>> explainsVector;

    while(!q.empty()){
        currentCahr =  q.front();
        //��ȡ����(**֮��@֮ǰ)
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
        //��ȡÿ����(@~@,����@~/)
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
 * ��ʽ��˵��
 * @param queue q �ַ�������(����ʽ�����ַ�����)
 * @return void
 */
vector<string> Document::formatExplain(queue <char> q){
    vector<string> explain(4);
    vector<string>::iterator it;
    it = explain.begin();
    int counter = 0; //�ո������spaceCounter
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
 * ��ȡ����
 * @param queue q һ��stl�ı�׼����(ע�͵��ַ�����)
 * @return void
 */
void Document::getMethod(string str){
    if(str.length() == 0){
        cout << "��ȡ����ʱ�����˿յ��ַ���" << endl;
        return;
    }
    string method;
    method = (replace_all(str,"function ", ""));
    method = (replace_all(str,"public ", ""));
    method = (replace_all(str,"\n", ""));
    methods.push_back(method);
}

/**
 * �ַ����滻
 * @param queue q һ��stl�ı�׼����(ע�͵��ַ�����)
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
 * ��ӡ����
 */
void Document::printTitles(){
    if(titles.empty()){
        cout << "�ޱ�������" << endl;
        return ;
    }
    cout << "����: " << methods.size() <<  " ������";
    for(vector<string>::iterator it=titles.begin();it!=titles.end();it++)
        cout << "����:" << *it << " ";
}

/**
 * ��ӡ����
 */
void Document::printMethodss(){
    if(methods.empty()){
        cout << "�޷�������" << endl;
        return ;
    }
    cout << "����: " << methods.size() <<  " ������";
    for(vector<string>::iterator it=methods.begin();it!=methods.end();it++)
        cout << "����:" << *it << " ";
}

/**
 * ��ӡ˵��
 */
void Document::printExplains(){
    if(explains.empty()){
        cout << "��˵������" << endl;
        return ;
    }
    cout << "����: " << explains.size() <<  " ��˵��";
    vector<string>::iterator it;
    vector<vector<string>>::iterator iter;
    vector<vector<vector<string>>>::iterator explainIter;
    vector<string> explianTmp;
    vector<vector<string>> explainsTmp;
    int explainCounter = 0; //˵��������,���ڱ��˵������[1=>˵������,2=>��������,3=>��������,4=>��������]

    cout << " ˵������ : " << endl;
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
 * ����ĵ��ṹ
 */
void Document::check(){
    int titleSize = titles.size() - ignoreBlock;
    int methodSize = methods.size() - ignoreBlock;
    int explainSize = explains.size() - ignoreBlock;

    cout << "��������:" << titleSize << endl;
    cout << "��������:" << methodSize << endl;
    cout << "˵������:" << explainSize << endl;

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // ��ȡ��׼����豸���
    WORD wr;//������ɫ���ԣ���һλΪ����ɫ���ڶ�λΪǰ��ɫ
    if(titleSize == methodSize && titleSize == explainSize){
        wr = 0x0a;
        SetConsoleTextAttribute(hOut, wr);
        cout << "���ݽṹ����һ��:" << explainSize << endl;
    }else{
        wr = FOREGROUND_RED | FOREGROUND_INTENSITY;//��������ϵͳ�궨����ɫ����
        SetConsoleTextAttribute(hOut, wr);
        cout << "���ݽṹ������һ��:" << explainSize << endl;
    }

    wr = 0x0f;
    SetConsoleTextAttribute(hOut, wr); //�ָ��ڵװ���
}

/**
 * ����markdown��ʽ������
 */
string Document::toMarkdown(int is_utf8){
    string content = "";

    if(explains.empty()){
        cout << "��˵������" << endl;
        return "��˵������";
    }

    vector<string>::iterator it;
    vector<vector<string>>::iterator iter;
    vector<vector<vector<string>>>::iterator explainIter;
    vector<string> explianTmp;
    vector<vector<string>> explainsTmp;
    int explainCounter = 0; //˵��������,���ڱ��˵������[1=>˵������,2=>��������,3=>��������,4=>��������]
    int methodCounter = 0; //����������
    int a = fileNumber; //a=>�ļ���������������,b=>�ļ��������������ַ�����,c=>�ļ��������������ַ�������
    char b[2];
    string c;
    char itc[8];
    cout << " ˵������ : " << endl;
    string prepareString;
    for(explainIter = explains.begin(); explainIter != explains.end(); explainIter++)
    {
        sprintf(itc,"%d",methodCounter+1);
        sprintf(b,"%d",a);
        c = b;
        content.append("## " + c + ".").append(itc).append(titles[methodCounter]).append("\n\n");
        prepareString = "### ����: ";
        prepareString = is_utf8?  GbkToUtf8(prepareString.data()) : prepareString;
        content.append(prepareString+methods[methodCounter]+"\n\n");
        prepareString = "\t˵��:\n\n";
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
 * ��gbk�ַ�����utf8�ַ���
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
