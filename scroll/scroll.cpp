#include <qapplication.h>
#include <qpushbutton.h>
#include <qfont.h>
#include <q3scrollview.h>

class MyMainWindow:public Q3ScrollView
{
public:
	MyMainWindow();

private:
	QPushButton *b1;
};

MyMainWindow::MyMainWindow()
{
	this->setGeometry(100,100,200,100);
	b1=new QPushButton("this ia a button");

	b1->setGeometry(10,10,180,80);
	b1->setFont(QFont("Times",18,QFont::Bold));
	
	addChild(b1);
	
}

int main(int argc,char** argv)
{
	QApplication a(argc,argv);

	MyMainWindow win;
	
	// QScrollArea scroll;
	// scroll.setWidget(&win);

	// win.show();
	// scroll.show();
	win.show();
	a.exec();
	
	return 0;
}










