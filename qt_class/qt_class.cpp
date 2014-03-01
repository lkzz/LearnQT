#include <qapplication.h>
#include <qwidget.h>
#include <qpushbutton.h>
#include <qfont.h>
#include <qlabel.h>
#include <qslider.h>
#include <qlcdnumber.h>

class myclass:public QWidget
{
public:
	myclass();

// private:
	QLabel *label;
	QPushButton *b1;
	QSlider *slider;
	QLCDNumber *lcd;
	QFont font;
signals:
	p_valueChanged(int);
};

// myclass::p_valueChanged(int value)
// {
	
// }

myclass::myclass()
{
	this->setMaximumSize(200,400);
	this->setMinimumSize(100,200);

	
	font=QFont("Times",18,QFont::Bold);
	
	b1=new QPushButton("quit",this);
	b1->setGeometry(20,300,130,30);
	b1->setFont(font);

	label=new QLabel(this);
	label->setFont(font);
	label->setGeometry(20,260,160,30);
	label->setText("this is label");

	lcd=new QLCDNumber(2,this);
	lcd->setGeometry(50,10,80,80);

	slider=new QSlider(this);
	slider->setGeometry(20,100,160,20);
	slider->setOrientation(Qt::Horizontal);
	slider->setRange(0, 99);
	slider->setValue(0);

	QObject::connect(slider,SIGNAL(valueChanged(int)),
			lcd,SLOT(display(int)));
	
}
QFont font("Times",18,QFont::Bold);

int main( int argc,char** argv)
	{
		QApplication a(argc,argv);
		myclass w;
		
		QObject::connect(w.b1,SIGNAL(clicked()),&a,SLOT(quit()));
		w.show();
		return a.exec();
	}
