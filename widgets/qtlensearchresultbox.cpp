#include "qtlensearchresultbox.hpp"

QTlenSearchResultBox::QTlenSearchResultBox(QWidget * parent, QWidget * realParent):QTreeWidget(parent)
{
	setRootIsDecorated(0);
	this->realParent = realParent;
	setHeaderHidden(true);
}

void QTlenSearchResultBox::contextMenuEvent(QContextMenuEvent *event)
{
        QMenu *menu = new QMenu(this);
	if (itemAt(event->pos()))
        {
                QIcon icon1;
                icon1.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/meeting-attending.png")),
                                QIcon::Normal, QIcon::Off);
                QAction *actionMessage	= new QAction(icon1, QString::fromUtf8("Wiadomość"), menu);
                QAction *actionAdd	= new QAction(QString::fromUtf8("Dodaj"), menu);
                menu -> addAction(actionMessage);
                menu -> addAction(actionAdd);
                connect(this,
                        SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
                        realParent,
                        SLOT(menuActionChat()));
                connect(actionMessage,
                        SIGNAL(triggered()),
			realParent,
                        SLOT(menuActionChat()));
                connect(actionAdd,
                        SIGNAL(triggered()),
			realParent,
			SLOT(menuActionAdd()));
		menu -> exec(event->globalPos());
        }

}

QTreeWidgetItem* QTlenSearchResultBox::appendItem(const QTlenUserInfo info)
{
	QStringList sex;
	sex	<< ""
		<< tr("man")
		<< tr("woman");
	QStringList presence;
	presence<< ":/icons/icons/32x32/offline.png"
		<< ":/icons/icons/32x32/offline.png"
		<< ":/icons/icons/32x32/online.png"
		<< ":/icons/icons/32x32/xa.png"
		<< ":/icons/icons/32x32/away.png"
		<< ":/icons/icons/32x32/dnd.png"
		<< ":/icons/icons/32x32/chatty.png";
	QTreeWidgetItem* item = new QTreeWidgetItem(this);
	QFrame* itemFrame = new QFrame(this);
	QHBoxLayout* mainLayout = new QHBoxLayout();
	QVBoxLayout* infoLayout = new QVBoxLayout();
	QGridLayout* extInfoLayout = new QGridLayout();
	QString name("");
	if (!info.last.isEmpty())
	    name += info.last;
	if (!info.first.isEmpty())
	{
	    if(name.isEmpty())
		name += info.first;
	    else
		name += QString(", ") += info.first;
	}
	QLabel *lb_status = new QLabel(itemFrame);
	lb_status->setPixmap(QPixmap(presence[info.presence]));
	lb_status->setFixedSize(32, 32);
	mainLayout->addWidget(lb_status);
	mainLayout->addLayout(infoLayout);
	QLabel *lb_jid = new QLabel(info.jid, itemFrame);
	infoLayout->addWidget(lb_jid);
	mainLayout->setAlignment(Qt::AlignTop);
	if(!name.isEmpty())
	{
	    QLabel *lb_name = new QLabel(name, itemFrame);
	    infoLayout->addWidget(lb_name);
	}
	infoLayout->addLayout(extInfoLayout);
	if(!info.nick.isEmpty())
	{
	    QLabel *lb_nick = new QLabel(info.nick, itemFrame);
	    extInfoLayout->addWidget(lb_nick, 0, 0);
	}
	if(!info.email.isEmpty())
	{
	    QLabel *lb_mail = new QLabel(info.email, itemFrame);
	    extInfoLayout->addWidget(lb_mail, 0, 1);
	}
	if(!info.school.isEmpty())
	{
	    QLabel *lb_school = new QLabel(info.school, itemFrame);
	    extInfoLayout->addWidget(lb_school, 1, 0);
	}
	if(!info.city.isEmpty())
	{
	    QLabel *lb_city = new QLabel(info.city, itemFrame);
	    extInfoLayout->addWidget(lb_city, 1, 1);
	}
	if(!sex[info.sex].isEmpty())
	{
	    QLabel *lb_sex = new QLabel(sex[info.sex], itemFrame);
	    extInfoLayout->addWidget(lb_sex, 2, 0);
	}
	if(info.year !=0)
	{
	    QLabel *lb_year = new QLabel(QString::number(info.year), itemFrame);
	    extInfoLayout->addWidget(lb_year, 2, 1);
	}
	itemFrame->setLayout(mainLayout);
	setItemWidget(item, 0, itemFrame);
	this->addTopLevelItem(item);
	return item;
}
