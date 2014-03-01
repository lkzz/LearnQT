#include <qapplication.h>
#include <qwidget.h>
#include <qpushbutton.h>

int main(int argc,char ** argv)
{
	QApplication app(argc,argv);

	QWidget mainwindow;
	mainwindow.setMaximumSize(200,100);
	mainwindow.setMinimumSize(200,100);

	QPushButton button("nihao",&mainwindow);
	button.setGeometry(20,20,160,60);

	QObject::connect(&button,SIGNAL(clicked()),&app,SLOT(quit()));
	mainwindow.show();
	return app.exec();

}










