#include <QApplication>
#include "form1.h"

int main(int argc, char *argv[])
{
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
