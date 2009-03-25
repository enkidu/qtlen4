#ifndef QTLENPUBLICCHATSWINDOW_HPP
#define QTLENPUBLICCHATSWINDOW_HPP

#include <QtGui>

class QTlenPublicChatsWindow : public QWidget
{
public:
    QTlenPublicChatsWindow(QWidget * parent = 0, Qt::WFlags f = 0 );
private:
    QTabWidget *tabWidget;
    QTreeWidget* mainPage;
};

#endif // QTLENPUBLICCHATSWINDOW_HPP

