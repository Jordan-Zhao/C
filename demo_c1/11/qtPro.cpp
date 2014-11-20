/* qtPro.cpp���򣺼򵥵�Qt���򣬰�����ǩLabel����ťButton��������Slider��LCD������LCDNumber*/
#include <qapplication.h>//ÿ��Qt���򶼱��������ͷ�ļ�
#include <qpushbutton.h>//pushbutton�ؼ���ͷ�ļ�
#include <qslider.h>//�������ؼ���ͷ�ļ�
#include <qlcdnumber.h>//LCD��������ͷ�ļ�
#include <qfont.h>//�������õ�ͷ�ļ�
#include <qlabel.h>//��ǩ�ؼ���ͷ�ļ�
#include <qvbox.h>//��ֱ����ͷ�ļ�
class MyWidget : public QVBox// MyWidget���еĿؼ�˵��ֱ���еģ�����˵�������
{
public:
    MyWidget( QWidget *parent=0, const char *name=0 );
};
MyWidget::MyWidget( QWidget *parent, const char *name )
        : QVBox( parent, name )
{
		//�½���ǩ������ʾhello world�������ݣ�������Ϊlabel���������ʽΪTimes����СΪ20�����ҼӴ֣�����λ������Ļ���Ϸ�������
    QLabel *label = new QLabel("Hello World!",this,"label");
label->setFont(QFont("Times",20,QFont::Bold));
label->setAlignment( AlignTop| AlignCenter );
//�½�LCD������������ʾ3λ����������Ϊlcd�����ü������ı���ɫΪ��ɫ
    QLCDNumber *lcd  = new QLCDNumber( 3, this, "lcd" );
lcd->setBackgroundColor(red);
//�½�����������ˮƽ���ã�������Ϊslider��������Χ��-49��50֮�䣬��ʼֵΪ0���ѻ������ġ�ֵ�ı䡱�źź�LCD�������ġ���ʾ������ϵ����
    QSlider * slider = new QSlider( Horizontal, this, "slider" );
    slider->setRange( -49, 50);
    slider->setValue( 0 );
connect( slider, SIGNAL(valueChanged(int)), lcd, SLOT(display(int)) );
//�½���ť���󣬰�ť���ı�ΪQuit��������Ϊquit�������ı�������ʽΪTimes��10pt��С�����壻�Ѱ�ť��clicked�źź�ϵͳ�˳�����ϵ����
    QPushButton *quit = new QPushButton( "Quit", this, "quit" );
    quit->setFont( QFont( "Times", 10, QFont::Bold ) );
    connect( quit, SIGNAL(clicked()), qApp, SLOT(quit()) );
}
int main( int argc, char **argv )
{
    QApplication a( argc, argv );
    MyWidget w;
    a.setMainWidget( &w );//���ش���
    w.show();//��ʾ
    return a.exec();
}