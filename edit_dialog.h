#include "ui_user_edit.h"
#include <QWidget>
#include <QCloseEvent>

using namespace Ui;
class QTlenUserEdit: public QWidget	//nie potrzebujemy na razie takiej armaty, jak QMainWindow
{
	Q_OBJECT
	public:
		userEditWindow		ui;
                QTlenUserEdit(QWidget * parent = 0, QString jid = "", QString name = "", QString group = "Tlen", QStringList groups = QStringList(), Qt::WFlags f = 0 );
                ~QTlenUserEdit(){}
	private slots:
		void		saveInfo();
	signals:
		void		saveItem(QString, QString, QString);
};
