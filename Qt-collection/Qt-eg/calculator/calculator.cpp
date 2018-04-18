#include "calculator.h"
#include "ui_calculator.h"

#include <sstream>
#include <climits>
using namespace std;

Calculator::Calculator(QWidget *parent) :
    QWidget(parent),
    Result(0)
{
    ui.setupUi(this);
    str="";

    connect(ui.numButton0,&QPushButton::clicked,this,&Calculator::on_numButton0_clicked);
    connect(ui.numButton1,&QPushButton::clicked,this,&Calculator::on_numButton1_clicked);
    connect(ui.numButton2,&QPushButton::clicked,this,&Calculator::on_numButton2_clicked);
    connect(ui.numButton3,&QPushButton::clicked,this,&Calculator::on_numButton3_clicked);
    connect(ui.numButton4,&QPushButton::clicked,this,&Calculator::on_numButton4_clicked);
    connect(ui.numButton5,&QPushButton::clicked,this,&Calculator::on_numButton5_clicked);
    connect(ui.numButton6,&QPushButton::clicked,this,&Calculator::on_numButton6_clicked);
    connect(ui.numButton7,&QPushButton::clicked,this,&Calculator::on_numButton7_clicked);
    connect(ui.numButton8,&QPushButton::clicked,this,&Calculator::on_numButton8_clicked);
    connect(ui.numButton9,&QPushButton::clicked,this,&Calculator::on_numButton9_clicked);
    connect(ui.dotButton,&QPushButton::clicked,this,&Calculator::on_dotButton_clicked);

    connect(ui.leftPButton,&QPushButton::clicked,this,&Calculator::on_leftPButton_clicked);
    connect(ui.rightPButton,&QPushButton::clicked,this,&Calculator::on_rightPButton_clicked);

    connect(ui.plusButton,&QPushButton::clicked,this,&Calculator::on_plusButton_clicked);
    connect(ui.minusButton,&QPushButton::clicked,this,&Calculator::on_minusButton_clicked);
    connect(ui.timeButton,&QPushButton::clicked,this,&Calculator::on_timeButton_clicked);
    connect(ui.divideButton,&QPushButton::clicked,this,&Calculator::on_divideButton_clicked);

    connect(ui.ACButton,&QPushButton::clicked,this,&Calculator::on_ACButton_clicked);
    connect(ui.DELButton,&QPushButton::clicked,this,&Calculator::on_DELButton_clicked);

}

void Calculator::on_numButton1_clicked()
{
    event_after_clicked("1");
}

void Calculator::on_numButton2_clicked()
{
    event_after_clicked("2");
}

void Calculator::on_numButton3_clicked()
{
    event_after_clicked("3");
}

void Calculator::on_numButton4_clicked()
{
    event_after_clicked("4");
}

void Calculator::on_numButton5_clicked()
{
    event_after_clicked("5");
}

void Calculator::on_numButton6_clicked()
{
    event_after_clicked("6");
}

void Calculator::on_numButton7_clicked()
{
    event_after_clicked("7");
}

void Calculator::on_numButton8_clicked()
{
    event_after_clicked("8");
}

void Calculator::on_numButton9_clicked()
{
    event_after_clicked("9");
}

void Calculator::on_numButton0_clicked()
{
    event_after_clicked("0");
}

void Calculator::on_dotButton_clicked()
{
    event_after_clicked(".");
}

//-------

void Calculator::on_leftPButton_clicked()
{
    event_after_clicked("(");
}

void Calculator::on_rightPButton_clicked()
{
    event_after_clicked(")");
}

//-------

void Calculator::on_plusButton_clicked()
{
    event_after_clicked("+");
}

void Calculator::on_minusButton_clicked()
{
    event_after_clicked("-");
}

void Calculator::on_timeButton_clicked()
{
    event_after_clicked("x");
}

void Calculator::on_divideButton_clicked()
{
    event_after_clicked("/");
}

//-------

void Calculator::on_ACButton_clicked()
{
    str="";
    Result=0.0;

    ui.textedit->setText(QString::fromStdString("0"));
    ui.result->setText(QString::fromStdString("0"));
}

void Calculator::on_DELButton_clicked()
{
    if(str.size())
        str=str.substr(0,str.size()-1);

    Result = calString(str);
    ui.textedit->setText(QString::fromStdString(str));
    ui.result->setText(QString::fromStdString(to_string(Result)));
}

//-------
//-------
void Calculator::event_after_clicked(string button)
{
    str=parseString(button);
    string str2 = divideCalString(str);
    Result = calString(str2);

    ui.textedit->setText(QString::fromStdString(str));
    ui.result->setText(QString::fromStdString((Result==LONG_MAX)?"ERROR! DIVIDED BY ZERO!":to_string(Result)));
}

string Calculator::parseString(string& button)
{
    string temp;
    if(button=="0")
    {
        bool flag=false;
        int i=str.size()-1;
        while(i>=0&&symbol.find(string(1,str[i]))==symbol.end()&&str[i]!='('&&str[i]!=')')
            i--;
        string num=(i==str.size()-1)?"":str.substr(i+1);
        for(int i=0;i<num.size();i++)
            if(num[i]=='.')
            {
                flag=true;
                break;
            }
        if(flag)
            temp = str+button;
        else
            temp = (str.size()==0||str[0]=='0')?str:str+button;
    }
    else if(symbol.find(button)!=symbol.end())
    {
        if(str.size()==0&&button=="-")
            temp="-";
        else if(button==")"&&str.size()&&str[str.size()-1]=='(')
            temp = str;
        else if(str.size()&&((str[str.size()-1]-'0'>=0&&str[str.size()-1]-'9'<=0)||str[str.size()-1]==')'))
            temp=str+button;
    }

    else
        temp=str+button;

    return temp;
}

double Calculator::calString(string str)
{
    if(str.size()==0)
        return 0.0;
    int i=0;
    while(i<str.size()&&(str[i]-'0'>=0&&str[i]-'9'<=0||str[i]=='.'))
        i++;
    if(i==str.size())
        return stod(str);
    string front=str.substr(0,i);
    string sym = string(1,str[i]);
    string back = (i==str.size()-1)?"":str.substr(i+1);

    switch(str[i])
    {
    case '+':return calString(front) + calString(back);break;
    case '-':return calString(front) - calString(back);break;
    case 'x':return (back.size()==0)?calString(front):calString(front) * calString(back);break;
    case '/':return (back.size()==0)?calString(front):(back=="0")?LONG_MAX:calString(front) / calString(back);break;
    }
}

string Calculator::divideCalString(string str)
{
    int i=0;
    while(i<str.size()&&str[i]!='(')
        i++;

    if(i==str.size())
        return to_string(calString(str));

    int j=1,count=0;
    while(i+j<str.size())
    {
        if(str[i+j]=='(')
            count++;
        else if(str[i+j]==')')
        {
            if(count==0)
                break;
            else
                count--;
        }
        j++;
    }
    return str.substr(0,i) + divideCalString(str.substr(i+1,j)) + divideCalString((i+j>=str.size()-1)?"":str.substr(i+j+1));
}
