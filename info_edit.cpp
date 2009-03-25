#include "info_edit.h"

QTlenPubdirEdit::QTlenPubdirEdit(QWidget * parent, Qt::WFlags f):QWidget(parent, f)
{
	ui.setupUi(this);
	connect(ui.pb_save,	SIGNAL(clicked()),	this,	SLOT(saveInfo()));
};

void QTlenPubdirEdit::setInfo(QTlenUserInfo newInfo)
{
	info = newInfo;
	ui.le_first		-> setText(info.first);
	ui.le_last		-> setText(info.last);
	ui.le_nick		-> setText(info.nick);
	ui.le_mail		-> setText(info.email);
	ui.le_city		-> setText(info.city);
	ui.le_school		-> setText(info.school);
	ui.cb_job		-> setCurrentIndex(info.job);
	ui.cb_sex		-> setCurrentIndex(info.sex);
	ui.sb_year		-> setValue(info.year);
	ui.cb_lookingFor	-> setCurrentIndex(info.lookingFor);
	ui.cb_showMyStatus	-> setChecked(info.visible);
};

void QTlenPubdirEdit::saveInfo()
{
	info.first	= ui.le_first		-> text();
	info.last	= ui.le_last		-> text();
	info.nick	= ui.le_nick		-> text();
	info.email	= ui.le_mail		-> text();
	info.city	= ui.le_city		-> text();
	info.school	= ui.le_school		-> text();
	info.job	= ui.cb_job		-> currentIndex();
	info.sex	= ui.cb_sex		-> currentIndex();
	info.year	= ui.sb_year		-> value();
	info.lookingFor	= ui.cb_lookingFor	-> currentIndex();
	info.visible	= ui.cb_showMyStatus	-> isChecked();
	emit saveInfo(info);
	this->close();
};