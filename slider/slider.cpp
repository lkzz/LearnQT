#include <QApplication>
#include <QLabel>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>
#include <QPushButton>

int main(int argc, char *argv[])
{
	QApplication app(argc,argv);


	QPushButton *button=new QPushButton("Quit");
	QObject::connect(button,SIGNAL(clicked()),&app,SLOT(quit()));
	
	button->show();
	
	QWidget* window=new QWidget;
	window->setWindowTitle("Enter your age:");
	QSpinBox* spinBox=new QSpinBox;
	QSlider *slider=new QSlider();
	slider->setOrientation(Qt::Horizontal);
	spinBox->setRange(1,130);
	slider->setRange(0,130);

	QObject::connect(spinBox,SIGNAL(valueChanged(int)),
					 slider,SLOT(setValue(int)));

	QObject::connect(slider,SIGNAL(valueChanged(int)),
					 spinBox,SLOT(setValue(int)));
	
	spinBox->setValue(35);
	
	QHBoxLayout *layout=new QHBoxLayout;
	layout->addWidget(button);
	layout->addWidget(spinBox);
	layout->addWidget(slider);
	window->setLayout(layout);
	
	window->show();

    return app.exec();
}
