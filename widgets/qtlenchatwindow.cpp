#include "qtlenchatwindow.hpp"

QTlenChatWindow::QTlenChatWindow(QWidget * parent, Qt::WFlags f):QMainWindow(parent, f)
{

        resize(343, 449); //TODO: zapamiętanie rozmiaru okna
	timer = new QTimer(this);
	timer->setInterval(30000);
	timer->setSingleShot(true);
        QIcon icon;
	QIcon icon2;
	icon.addPixmap(QPixmap(":/icons/icons/draw-freehand.png"), QIcon::Normal, QIcon::Off);
	icon2.addPixmap(QPixmap(":/icons/icons/help-about.png"), QIcon::Normal, QIcon::Off);
        actionTyping    = new QAction(icon, QString::fromUtf8(""),  this);
        actionTyping    ->setEnabled(false);
	actionInfo	= new QAction(icon2, QString::fromUtf8(""),  this);
        centralwidget   = new QWidget(this);

        verticalLayout  = new QVBoxLayout(centralwidget);
        verticalLayout  ->setSpacing(0);
        verticalLayout  ->setMargin(0);

	te_chatWindow   = new QTextBrowser(centralwidget);

	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(3);
	sizePolicy.setHeightForWidth(te_chatWindow->sizePolicy().hasHeightForWidth());
        te_chatWindow   ->setSizePolicy(sizePolicy);

        te_chatInput    = new QTlenTextEdit(centralwidget);

	QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
	sizePolicy1.setHorizontalStretch(0);
	sizePolicy1.setVerticalStretch(1);
	sizePolicy1.setHeightForWidth(te_chatInput->sizePolicy().hasHeightForWidth());
        te_chatInput    ->setSizePolicy(sizePolicy1);

        verticalLayout  ->addWidget(te_chatWindow);
        verticalLayout  ->addWidget(te_chatInput);

        setCentralWidget(centralwidget);

        toolBar         = new QToolBar(this);
        toolBar         ->setLayoutDirection(Qt::RightToLeft);
        toolBar         ->setMovable(false);
        toolBar         ->setAllowedAreas(Qt::TopToolBarArea);
        addToolBar(Qt::TopToolBarArea, toolBar);
        toolBar         ->addAction(actionTyping);
	toolBar		->addAction(actionInfo);

	connect(te_chatInput,
		SIGNAL(returnPressed()),
		this,
		SLOT(sendMessage()));
	connect(te_chatInput,
		SIGNAL(keyPressed()),
		this,
		SLOT(keyPressHandler()));
	connect(timer,
		SIGNAL(timeout()),
		this,
		SLOT(typingStopped()));
        settings        = new QSettings(QDir::homePath() + "/.qtlen4/config", QSettings::IniFormat);
        myColor         = settings->value("/preferences/sent/color", "#000000").toString();
        myBg            = settings->value("/preferences/sent/bground", "#ffffff").toString();
        chatColor       = settings->value("/preferences/received/color", "#000000").toString();
        chatBg          = settings->value("/preferences/received/bground", "#ffffff").toString();
        vertScroll      = te_chatWindow->verticalScrollBar();
	document = te_chatWindow->document();
	cursor = QTextCursor(document);
	if (!testAttribute(Qt::WA_DeleteOnClose)) this->setAttribute(Qt::WA_DeleteOnClose, true);
}

void QTlenChatWindow::setContactInfo(const QString jid, const QString name)
{
	this->jid=jid;
	this->nick=name;
	setWindowTitle(name);
}

void QTlenChatWindow::showMessage(const QString body,const  QDateTime stamp)
{
	cursor		    .movePosition(QTextCursor::End);
	QBrush		    background;
	background	    .setColor(QColor(chatBg));
	background	    .setStyle(Qt::SolidPattern);
	QBrush		    foreground;
	foreground	    .setColor(QColor(chatColor));
	foreground	    .setStyle(Qt::SolidPattern);
	QTextBlockFormat    blockFormat;
	QTextCharFormat	    charFormat;
	blockFormat	    .setBackground(background);
	charFormat	    .setForeground(foreground);
	blockFormat	    .setBottomMargin(2);
	cursor		    .insertBlock(blockFormat, charFormat);
	cursor		    .insertHtml(formatMessage(stamp, nick, body, chatColor));
	vertScroll	    ->setValue(vertScroll->maximum());
}

void QTlenChatWindow::closeEvent(QCloseEvent *event)
{
	timer->stop();
	timer->deleteLater();
	document->deleteLater();
	emit widgetClosed(jid);
	event->accept();
}

void QTlenChatWindow::keyPressHandler()
{
    if (!timer->isActive())
	emit typing(jid, true);
    timer->start();
}

void QTlenChatWindow::typingStopped()
{
    emit typing(jid, false);
}

void QTlenChatWindow::sendMessage()
{
    if(!te_chatInput->toPlainText().isEmpty())
    {
        emit message(jid, te_chatInput->toPlainText());
	cursor.movePosition(QTextCursor::End);
	QBrush background;
	background.setColor(QColor(myBg));
	background.setStyle(Qt::SolidPattern);
	QBrush foreground;
	foreground.setColor(QColor(myColor));
	foreground.setStyle(Qt::SolidPattern);
	QTextBlockFormat    blockFormat;
	QTextCharFormat	    charFormat;
	blockFormat	    .setBackground(background);
	charFormat	    .setForeground(foreground);
	blockFormat	    .setBottomMargin(2);
	cursor		    .insertBlock(blockFormat, charFormat);
	cursor.insertHtml(formatMessage(QDateTime::currentDateTime(), myNick, te_chatInput->toPlainText(), myColor));
	vertScroll->setValue(vertScroll->maximum());
        te_chatInput->clear();
	timer->stop();
    }
}

void QTlenChatWindow::setTyping(bool yesno)
{
        actionTyping->setEnabled(yesno);
}

void QTlenChatWindow::setMyInfo(const QString nick)
{
	myNick = nick;
}
QString QTlenChatWindow::formatMessage(const QDateTime time,const QString nick,QString body,const QString color)
{
	body = Qt::escape(body);
	body.replace("\n\r", "<br>");
	body.replace("\n", "<br>");
	body.replace("\r", "<br>");
	QString format("<div style=\"color: %1;\"><b>%2 %3</b><br>%4</div>");
	return format.arg(color, time.time().toString(), nick, body);
}

void QTlenChatWindow::showPreviousMessages(const QList<QTlenMessageStruct> list)
{
    if (!list.isEmpty())
    {
	for(int i = 0; i < list.size(); i++)
	{
	    cursor.movePosition(QTextCursor::End);
	    cursor.insertBlock();
	    QString currNick;
	    if (list[i].sent_by  == jid)
		currNick = nick;
	    else
		currNick = myNick;
	    cursor.insertHtml(formatMessage(list[i].dateTime, currNick, list[i].body, "#000"));
	    vertScroll->setValue(vertScroll->maximum());
	}
	cursor.insertHtml("<hr />");
    }
}

void QTlenChatWindow::showNotify(const QString text)
{
}
