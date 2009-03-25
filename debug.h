#include "ui_debug.h"
#include <QWidget>
#include <QCloseEvent>

using namespace Ui;
class QTlenDebugWindow: public QWidget	//nie potrzebujemy na razie takiej armaty, jak QMainWindow
{
	Q_OBJECT
	public:
		debugWindow		ui;
		QTlenDebugWindow(QWidget * parent = 0, Qt::WFlags f = 0 );
                ~QTlenDebugWindow(){}
	public slots:
		void		showXml(QByteArray xml);
		void		sendXML();
	signals:
		void		XMLsend(QString);
	protected:
		void		closeEvent(QCloseEvent *event);
};
