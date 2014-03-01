#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
	QApplication app(argc,argv);
	QLabel *label =new QLabel("<font color=red>Hello Qt!!!</font>");
	label->show();
    return app.exec();
}
