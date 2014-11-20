/* qtPro.cpp程序：简单的Qt程序，包含标签Label，按钮Button，滑动条Slider和LCD计数器LCDNumber*/
#include <qapplication.h>//每个Qt程序都必须包含的头文件
#include <qpushbutton.h>//pushbutton控件的头文件
#include <qslider.h>//滑动条控件的头文件
#include <qlcdnumber.h>//LCD计数器的头文件
#include <qfont.h>//字体设置的头文件
#include <qlabel.h>//标签控件的头文件
#include <qvbox.h>//垂直布局头文件
class MyWidget : public QVBox// MyWidget类中的控件说垂直排列的，这里说类的声明
{
public:
    MyWidget( QWidget *parent=0, const char *name=0 );
};
MyWidget::MyWidget( QWidget *parent, const char *name )
        : QVBox( parent, name )
{
		//新建标签对象，显示hello world文字内容，对象名为label；字体的样式为Times，大小为20，并且加粗；文字位置在屏幕的上方，居中
    QLabel *label = new QLabel("Hello World!",this,"label");
label->setFont(QFont("Times",20,QFont::Bold));
label->setAlignment( AlignTop| AlignCenter );
//新建LCD计数器对象，显示3位数，对象名为lcd；设置计数器的背景色为红色
    QLCDNumber *lcd  = new QLCDNumber( 3, this, "lcd" );
lcd->setBackgroundColor(red);
//新建滑动条对象，水平放置，对象名为slider，滑动范围在-49～50之间，初始值为0，把滑动条的“值改变”信号和LCD计数器的“显示”槽联系起来
    QSlider * slider = new QSlider( Horizontal, this, "slider" );
    slider->setRange( -49, 50);
    slider->setValue( 0 );
connect( slider, SIGNAL(valueChanged(int)), lcd, SLOT(display(int)) );
//新建按钮对象，按钮上文本为Quit，对象名为quit，设置文本字体样式为Times，10pt大小，粗体；把按钮的clicked信号和系统退出槽联系起来
    QPushButton *quit = new QPushButton( "Quit", this, "quit" );
    quit->setFont( QFont( "Times", 10, QFont::Bold ) );
    connect( quit, SIGNAL(clicked()), qApp, SLOT(quit()) );
}
int main( int argc, char **argv )
{
    QApplication a( argc, argv );
    MyWidget w;
    a.setMainWidget( &w );//加载窗体
    w.show();//显示
    return a.exec();
}