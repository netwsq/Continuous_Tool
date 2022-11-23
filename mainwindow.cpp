#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QClipboard>
#include <windows.h>
#include <QRegularExpressionValidator>
#include <thread>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui -> setupUi(this);
    ui -> lineEdit_2 -> setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]+$")));//强制次数框只能输入数字
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);//置顶窗口
    setWindowOpacity(0.8);
    ui -> checkBox -> setChecked(1);//设置checkbox为选中状态
    ui -> radioButton_2 ->setChecked(1);


}

MainWindow::~MainWindow()
{
    delete ui;
}
bool CON=1;
bool c=0;
int num;
void mouse(){
    while(c==1){
            if(GetAsyncKeyState(VK_MENU)&&CON==1){
                mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );
                Sleep(2);
            }if(GetAsyncKeyState(VK_MENU)&&CON==0){
                mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0 );
                Sleep(2);
            }if(GetAsyncKeyState(VK_RSHIFT)){
                break;
            }
        }

}
void mouse_2(){
    int x=0;
    if(CON==1)
    {
        while(x<2)
        {
            if(GetAsyncKeyState(VK_LBUTTON))
            {
                x++;
            }
        }
    }else{
        while(x<2)
        {
            if(GetAsyncKeyState(VK_RBUTTON))
            {
                x++;
            }
        }
    }
    for(int i=0;i<num;i++)
    {
        if(CON==1){
            mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );
            Sleep(2);
        }else{
            mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0 );
            Sleep(2);
        }

    }
}
void keyboard(){
    int m=0;
    while(m<2)
    {
        if(GetAsyncKeyState(VK_LBUTTON))
        {
            m++;
        }
    }
    Sleep(500);
    for(int n=0;n<num;n++)
    {
        keybd_event(VK_CONTROL,0,0,0);
        Sleep(1);
        keybd_event('V',0,0,0);
        keybd_event('V',0,KEYEVENTF_KEYUP,0);
        Sleep(1);
        keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP,0);
        Sleep(1);
        keybd_event(VK_RETURN,0,0,0);
        keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP,0);
        Sleep(1);

    }
}
void MainWindow::on_pushButton_clicked()
{
     QString text = ui->lineEdit->text();//获取内容框数据
     QClipboard *clipboard = QApplication::clipboard();
     clipboard->setText(text);//复制数据
     QString text1 = ui->lineEdit_2->text();
     num=text1.toInt();//获取次数框内数字
     std::thread myobj(keyboard);
     myobj.detach();
     ui -> lineEdit -> setText("");
     ui -> lineEdit_2-> setText("");
//使输入框初始化


}


void MainWindow::on_checkBox_clicked(bool checked)
{

    if (checked == 1)
    {
      setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
      show();//置顶窗口

    }
    else
    {
      setWindowFlags(windowFlags() & ~Qt::WindowStaysOnTopHint);
      show();//取消置顶窗口

    }
}


void MainWindow::on_pushButton_2_clicked()
{
    QString input = ui->lineEdit_2->text();
    if(input.isEmpty()){
        if(c==0){
            c=1;
            ui->pushButton_2->setText("关闭");
        }else{
            c=0;
            ui->pushButton_2->setText("连点");
        }
        std::thread myobj(mouse);
        myobj.detach();
    }else{
    num=input.toInt();
    std::thread myobj(mouse_2);
    myobj.detach();
    Sleep(100);

    ui -> lineEdit_2-> setText("");
    }
}


void MainWindow::on_radioButton_2_clicked(bool checked)
{
    if(checked==1){
        CON=1;
    }
}


void MainWindow::on_radioButton_clicked(bool checked)
{
    if(checked==1){
        CON=0;
    }

}

