#include <QtGui>
#include "qtlenchatwindow.hpp"
#ifndef QTLENCHATCONTAINER_HPP
#define QTLENCHATCONTAINER_HPP

class QTlenChatContainer: public QMainWindow
{
    Q_OBJECT
    public:
        QTlenChatContainer(QWidget * parent = 0, Qt::WFlags f = 0 );
        ~QTlenChatContainer(){}
        QTlenChatWidget*        addChat();
        QStackedWidget          *stack;
        QTabBar                 *tabbar;
        QString                 title;
        QTimer                  *blinkTimer;
        void                    setTabText(QTlenChatWidget*, QString);
        void                    setTabColour(QTlenChatWidget*, QColor);
        void                    startBlinking();
    private:
        QSettings		*settings;
        //QTabBar                 *tabbar;
    private slots:
        void                    closeAndRemove(int tab);
        void                    tabChanged(int tab);
        void                    swapTitle();
    protected:
        void                    showEvent(QShowEvent *);
        void                    closeEvent(QCloseEvent *);
};

#endif // QTLENCHATCONTAINER_HPP
