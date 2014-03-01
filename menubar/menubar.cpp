#include <qapplication.h>
#include <qpushbutton.h>
#include <qfont.h>
#include <qpopupmenu.h>
#include <qmenubar.h>

class MyMainWindow:public QWidget
{
public:
	MyMainWindow();
private:
	QPopupMenu *file;
	QMenuBar *menubar;
};

MyMainWindow::MyMainWindow()
{
	this->setGeometry(100,100,300,300);
	file=new QPopupMenu();
	file->insertItem("quit",qApp,SLOT(quit()));


	menubar=new QMenuBar(this);
	menubar->insertItem("file",file);
}

int main(int argc,char**argv)
{
	QApplication app(argc,argv);
	MyMainWindow w;
	w.show();
	return app.exec();
}










