#include <QApplication>
#include <QLabel>
#include <QHBoxLabel>
#include <QSlider>
#include <QSpinBox>

int main(int argc, char *argv[])
{
	QApplication app(argc,argv);

	QWidget* window=new QWidget;
	window->setWindowTitle("Enter your age:");
	
	QSpinbox* spinBox=new QSpinbox;
	QSlider *slider=new QSlider(QT::Horizontal);
	spinBox->setRange(1,130);
	slider->setRange(0,130);

	QObject::connect(spinBox,SIGNAL(valueChanged(int)),
					 slider,SLOT(setValue(int)));

	QObject::connect(slider,SIGNAL(valueChanged(int)),
					 spinBox,SLOT(setValue(int)));
	
	spinBox->setValue(35);
	

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(spinBox);
	layout->addWidget(slider);
	window->setLayout(layout);
	
	window->show();

    return app.exec();
}
