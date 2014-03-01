#include <QtGui>
#include "finddialog.h"

FindDialog::FindDialog(QWidget *parent):QDialog(parent)
{
	label=new QLabel(tr("Find &what:"));
	lineEdit=new QLineEdit;
	label->setBuddy(lineEdit);

	caseCheckBox=new QCheckBox(tr("Search &backward"));

	findButton=new QPushButton(tr("&Find"));
	findButton->setDefault(true);
	findBuuton->setEnable(false);

	closeButton=new QPushButton(tr("Close"));
	
}
