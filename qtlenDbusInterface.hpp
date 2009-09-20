#include <QtDBus>

         class QTlenDBusAdaptor: public QDBusAbstractAdaptor
         {
             Q_OBJECT
             Q_CLASSINFO("D-Bus Interface", "org.kde.DBus.QTlen")
             Q_PROPERTY(QString caption READ caption WRITE setCaption)
             Q_PROPERTY(QString organizationName READ organizationName)
             Q_PROPERTY(QString organizationDomain READ organizationDomain)

         private:
             QApplication *app;

         public:
             MainApplicationAdaptor(QApplication *application)
                 : QDBusAbstractAdaptor(application), app(application)
             {
                 connect(application, SIGNAL(aboutToQuit()), SIGNAL(aboutToQuit()));
                 connect(application, SIGNAL(focusChanged(QWidget*, QWidget*)),
                         SLOT(focusChangedSlot(QWidget*, QWidget*)));
             }

             QString caption()
             {
                 if (app->hasMainWindow())
                     return app->mainWindow()->caption();
                 return QString(""); // must not return a null QString
             }

             void setCaption(const QString &newCaption)
             {
                 if (app->hasMainWindow())
                     app->mainWindow()->setCaption(newCaption);
             }

             QString organizationName()
             {
                 return app->organizationName();
             }

             QString organizationDomain()
             {
                 return app->organizationDomain();
             }

         public slots:
             Q_NOREPLY void quit()
             { app->quit(); }

             void reparseConfiguration()
             { app->reparseConfiguration(); }

             QString mainWindowObject()
             {
                 if (app->hasMainWindow())
                     return QString("/%1/mainwindow").arg(app->applicationName());
                 return QString();
             }

             void setSessionManagement(bool enable)
             {
                 if (enable)
                    app->enableSessionManagement();
                 else
                    app->disableSessionManagement();
             }

         private slots:
             void focusChangedSlot(QWidget *, QWidget *now)
             {
                 if (now == app->mainWindow())
                     emit mainWindowHasFocus();
             }

         signals:
             QString
             void aboutToQuit();
             void mainWindowHasFocus();
         };
