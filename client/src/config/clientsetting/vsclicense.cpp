#include "debug.hpp"
#include "config/clientsetting/vsclicense.h"
#include <fstream>
#include <iostream>
#include <QFileDialog>

VSCLicense::VSCLicense(ClientFactory &pFactory, QWidget *parent)
	: QWidget(parent), m_pFactory(pFactory)
{
	ui.setupUi(this);
	UpdateUI();
	connect( this->ui.pushButtonImport, SIGNAL( clicked() ), this, SLOT(SlotImportLic()));
	connect( this->ui.pushButtonDefault, SIGNAL( clicked() ), this, SLOT(SlotDefaultLic()));

}

void VSCLicense::UpdateUI()
{
	astring strLicense = "";
	astring strHostId = "";
	astring strExpire = "";
	char channel[256];
	int ch = 0;
	astring type = " ";
	m_pFactory.GetLicense(strLicense, strHostId, ch, type, strExpire);
	memset(channel, 0, 256);
	sprintf(channel, "%d", ch);
	ui.lic->setText(strLicense.c_str());
	ui.hostId->setText(strHostId.c_str());
	ui.channel->setText(channel);
	ui.type->setText(type.c_str());

	return;
}



void VSCLicense::SlotImportLic()
{
	
	QFileDialog *fileDialog = new QFileDialog(this); 
	fileDialog->setWindowTitle(tr("Select License")); 
	fileDialog->setNameFilter(tr("License(*.lic)")); 
	QIcon icon;
	icon.addFile(QStringLiteral(":/logo/resources/vscsmall.png"), QSize(), QIcon::Normal, QIcon::Off);
	fileDialog->setWindowIcon(icon);
	if(fileDialog->exec() == QDialog::Accepted) { 
		QString path = fileDialog->selectedFiles()[0]; 
		VDC_DEBUG( "%s  QFileDialog %s\n",__FUNCTION__, path.toStdString().c_str());
		
		ifstream b_file (path.toStdString().c_str());
		astring strLic;
		b_file>> strLic;
		
		std::string strLicense = strLic;
		m_pFactory.SetLicense(strLicense);
		
		UpdateUI();	
		b_file.close();
	} else 
	{ 
	
	}
	

	return;

}

void VSCLicense::SlotDefaultLic()
{
	std::string strLicense = "qETTpSZ/O4aGoLMNE+oXqXDCtBrIBOHtuvmSnr6clGqcHiMEaI+L1DDOHTR8l03WBE5sYvVenhRDh4WuTMI+ubErKFxJi3l5/pA6+H0FL2nX16issSbA0Pys2zZN4E2R2X9eO+wt2K2g0eomfZXkfwMwuWCFSIGQu84TXCscNS7ID/w2zeIpG8GQ8RY4m2D/QyLKdrRtCfkdYls43pxt9gTpuNgj3e6x3IReEflwgdW5WA9gYMhE6hByqu8iHYPLiL+y7wEn3nPKQmtnHake+x6755+LS4ZszcRjMBRU7Ozxd7rAnImrh6KX408tJc7Gy6C7yPyGxbJyGtOxlC190w==";
	m_pFactory.SetLicense(strLicense);
	UpdateUI();
	return;

}


