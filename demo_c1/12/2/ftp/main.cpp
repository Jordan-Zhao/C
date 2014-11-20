#include <qapplication.h>
//这一行包含了QApplication类的定义,在每一个使用Qt的应用程序中
//都必须使用一个QApplication对象
#include <qnetwork.h>
//使用qInitNetworkProtocols()所要用到的头文件
#include <qsplitter.h>
//使用mainSplitter()所要用到的头文件
#include "ftpmainwindow.h"
//前面所定义的FTP主窗体头文件
int main( int argc, char **argv )
{
    QApplication a( argc, argv );
     //a是这个程序的QApplication。它在这里被创建并且处理这些命令行变量
      //（比如在X窗口下的-display）。请注意，所有被Qt识别的命令行参数都会从argv中被移除
      //（并且argc也因此而减少）。
    qInitNetworkProtocols();
     //使用这个函数来调用Qt自身定义的网络协议类，该类中定义了像FTP和HTTP网络协议的一些方法
    FtpMainWindow m;//定义FtpMainWindow的一个对象m
    a.setMainWidget( &m );//a被选为这个应用程序的主窗口部件。
    m.setCaption(  "MyFtp-client" );//设置主窗口标题栏显示内容为:MyFtp-client
    QValueList<int> sizes;//QValueList类是一个提供双向链表的基于值的模板类
    sizes << 300 << 70 << 300;
    m.mainSplitter()->setSizes( sizes );
    m.resize( 800, 600 );
     //设置FtpClient窗体大小为100像素宽，30像素高，在Qt中resize()属于槽的定义
    m.show();
     //当创建一个窗口部件的时候，它是不可见的。必须调用show()来使它变为可见的。
    return a.exec();
     //这里就是main()把控制转交给Qt，并且当应用程序退出的时候exec()就会返回
}
