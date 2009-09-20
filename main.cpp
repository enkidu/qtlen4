#include <QApplication>
#include "form1.h"
#include <QtCrypto>

int main(int argc, char *argv[])
{
    QCA::Initializer init;
        QApplication app(argc, argv);

	QString locale = QLocale::system().name();
	QTranslator translator;
	if(translator.load(QString("qtlen4_pl.qm"), "."))
	    qDebug("translation loaded");
	app.installTranslator(&translator);
	app.setQuitOnLastWindowClosed(false);
        QTlenManager manager;
        return app.exec();
}
