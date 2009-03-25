#ifndef INFO_EDIT_H
#define INFO_EDIT_H
#include "ui_info_edit.h"
#include "defines.h"

using namespace Ui;
class QTlenPubdirEdit: public QWidget
{
	Q_OBJECT
	public:
		myInfo			ui;
		QTlenPubdirEdit(QWidget * parent = 0, Qt::WFlags f = 0 );
		~QTlenPubdirEdit(){};
	private:
		QTlenUserInfo		info;
	signals:
		void			saveInfo(QTlenUserInfo);
	public slots:
		void			setInfo(QTlenUserInfo);
		void			saveInfo();
};
#endif