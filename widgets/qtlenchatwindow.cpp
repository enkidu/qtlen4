    #include "qtlenchatwindow.hpp"
#include <QWebFrame>
QTlenChatWidget::QTlenChatWidget(QWidget * parent, Qt::WFlags f):QWidget(parent, f)
{
    settings        = new QSettings(QDir::homePath() + "/.qtlen4/config", QSettings::IniFormat);
	timer = new QTimer(this);
	timer->setInterval(30000);
	timer->setSingleShot(true);

        verticalLayout  = new QVBoxLayout(this);
        verticalLayout  ->setSpacing(0);
        verticalLayout  ->setMargin(0);

        te_chatWindow   = new QWebView(this);

	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(3);
	sizePolicy.setHeightForWidth(te_chatWindow->sizePolicy().hasHeightForWidth());
        te_chatWindow   ->setSizePolicy(sizePolicy);

        te_chatInput    = new QTlenTextEdit(this);

	QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
	sizePolicy1.setHorizontalStretch(0);
	sizePolicy1.setVerticalStretch(1);
	sizePolicy1.setHeightForWidth(te_chatInput->sizePolicy().hasHeightForWidth());
        te_chatInput    ->setSizePolicy(sizePolicy1);

        verticalLayout  ->addWidget(te_chatWindow);
        verticalLayout  ->addWidget(te_chatInput);

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
        /*connect(actionImage,
                SIGNAL(triggered()),
                this,
                SLOT(openImage()));*/
        myColor         = settings->value("/preferences/sent/color", "#000000").toString();
        myBg            = settings->value("/preferences/sent/bground", "#ffffff").toString();
        chatColor       = settings->value("/preferences/received/color", "#000000").toString();
        chatBg          = settings->value("/preferences/received/bground", "#ffffff").toString();
        document = new QTextDocument();
	cursor = QTextCursor(document);
        if (!testAttribute(Qt::WA_DeleteOnClose)) this->setAttribute(Qt::WA_DeleteOnClose, true);
        //te_chatInput->focusWidget();
}

void QTlenChatWidget::setContactInfo(const QString jid, const QString name)
{
	this->jid=jid;
	this->nick=name;
        //setWindowTitle(name);
        /*connect(actionInfo,
                SIGNAL(triggered()),
                this,
                SLOT(requestInfo()));*/
}

void QTlenChatWidget::showMessage(const QString body,const  QDateTime stamp)
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
        te_chatWindow->setHtml(document->toHtml());
        QWebFrame *frame = te_chatWindow->page()->currentFrame();
        frame->setScrollBarValue(Qt::Vertical,
                                 frame->scrollBarMaximum(Qt::Vertical));
}

void QTlenChatWidget::closeEvent(QCloseEvent *event)
{
	timer->stop();
	timer->deleteLater();
        document->deleteLater();
	emit widgetClosed(jid);
	event->accept();
}

void QTlenChatWidget::keyPressHandler()
{
    if (!timer->isActive())
        if (!te_chatInput->toPlainText().isEmpty())
        {
	emit typing(jid, true);
            timer->start();
        }
}

void QTlenChatWidget::typingStopped()
{
    emit typing(jid, false);
}

void QTlenChatWidget::requestInfo()
{
    emit infoRequest(jid);
}

void QTlenChatWidget::sendMessage()
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
        cursor.insertHtml(formatMessage(QDateTime::currentDateTime(),
                                        myNick,
                                        te_chatInput->toPlainText(),
                                        myColor));
        te_chatWindow->setHtml(document->toHtml());
        QWebFrame *frame = te_chatWindow->page()->currentFrame();
        frame->setScrollBarValue(Qt::Vertical,
                                 frame->scrollBarMaximum(Qt::Vertical));
        te_chatInput->clear();
	timer->stop();
    }
}

void QTlenChatWidget::setTyping(bool yesno)
{
        //actionTyping->setEnabled(yesno);
}

void QTlenChatWidget::openImage()
{
     QString fileName = QFileDialog::getOpenFileName(0, tr("Choose file"),
                                                 QDir::homePath(),
                                                 tr("Images (*.png *.xpm *.jpg *.gif)"));
     if(!fileName.isNull())
     {
        QImage image;
        if(image.load(fileName))
        {
            cursor.movePosition(QTextCursor::End);
            cursor.insertBlock();
            cursor.insertImage(image);
            emit sendImage(jid, fileName);
        }
    }
}

void QTlenChatWidget::setMyInfo(const QString nick)
{
	myNick = nick;
}
QString QTlenChatWidget::formatMessage(const QDateTime time,const QString nick,QString body,const QString color)
{
    QRegExp rx("(?#Protocol)(?:(?:ht|f)tp(?:s?)\\:\\/\\/|~/|/)?(?#Username:Password)(?:\\w+:\\w+@)?(?#Subdomains)(?:(?:[-\\w]+\\.)+(?#TopLevel Domains)(?:com|org|net|gov|mil|biz|info|mobi|name|aero|jobs|museum|travel|[a-z]{2}))(?#Port)(?::[\\d]{1,5})?(?#Directories)(?:(?:(?:/(?:[-\\w~!$+|.,=]|%[a-f\\d]{2})+)+|/)+|\\?|#)?(?#Query)(?:(?:\\?(?:[-\\w~!$+|.,*:]|%[a-f\\d{2}])+=(?:[-\\w~!$+|.,*:=]|%[a-f\\d]{2})*)(?:&(?:[-\\w~!$+|.,*:]|%[a-f\\d{2}])+=(?:[-\\w~!$+|.,*:=]|%[a-f\\d]{2})*)*)*(?#Anchor)(?:#(?:[-\\w~!$+|.,*:=]|%[a-f\\d]{2})*)?");
    rx.indexIn(body, 0);
	body = Qt::escape(body);
	body.replace("\n\r", "<br>");
	body.replace("\n", "<br>");
	body.replace("\r", "<br>");
        QString format("<div style=\"color: %1;\"><b>%2 %3</b><br>%4</div>");
	return format.arg(color, time.time().toString(), nick, body);
}

void QTlenChatWidget::showPreviousMessages(const QList<QTlenMessageStruct> list)
{
    cursor.movePosition(QTextCursor::Start);
    if (!list.isEmpty())
    {
	for(int i = 0; i < list.size(); i++)
	{
            //cursor.movePosition(QTextCursor::End);
	    cursor.insertBlock();
	    QString currNick;
	    if (list[i].sent_by  == jid)
		currNick = nick;
	    else
		currNick = myNick;
	    cursor.insertHtml(formatMessage(list[i].dateTime, currNick, list[i].body, "#000"));
	}
	cursor.insertHtml("<hr />");
    }
}

void QTlenChatWidget::showNotify(const QString text)
{
}

void QTlenChatWidget::showImage(QPixmap image)
{
    QString path = QDir::homePath() + "/.qtlen4/images/";
    QDir().mkdir(path);
    QImage img = image.toImage();
    QString filename = QString("%1-%2.png").arg(jid).arg(img.cacheKey());
    img.save(path + filename);
            cursor.movePosition(QTextCursor::End);
            cursor.insertBlock();
            cursor.insertHtml("<img src=\"" + path + filename +"\" />");
            te_chatWindow->setHtml(document->toHtml());
        QWebFrame *frame = te_chatWindow->page()->currentFrame();
        frame->setScrollBarValue(Qt::Vertical,
                                 frame->scrollBarMaximum(Qt::Vertical));}
