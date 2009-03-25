#include "qtlenrosterbox.hpp"
QTlenRosterBox::QTlenRosterBox(QWidget * parent):QTreeWidget(parent)
{
	setRootIsDecorated(0);
	setHeaderHidden(1);
        setIndentation(0);
	settings = new QSettings(QDir::homePath() + "/.qtlen4/config", QSettings::IniFormat);
	offlinesVisible = settings->value("/roster/offlines_visible", false).toBool();
        setSortingEnabled(false);
        setAnimated(1);
}

void QTlenRosterBox::contextMenuEvent(QContextMenuEvent *event)
{
	QMenu *menu = new QMenu(this);
	if (itemAt(event->pos()) and itemAt(event->pos())->childCount() == 0)
	{
		QIcon icon1;
		QIcon icon2;
		QIcon icon3;
		QIcon icon4;
		QIcon icon5;
		icon1.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/help-about.png")), QIcon::Normal, QIcon::Off);
		icon2.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/meeting-attending.png")), QIcon::Normal, QIcon::Off);
		icon3.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/view-history.png")), QIcon::Normal, QIcon::Off);
		icon4.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/user-properties.png")), QIcon::Normal, QIcon::Off);
		icon5.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/list-remove-user.png")), QIcon::Normal, QIcon::Off);
		QAction *actionInfo	= new QAction(icon1, tr("Info"), menu);
		QAction *actionMessage	= new QAction(icon2, tr("Message"), menu);
		QAction *actionHistory	= new QAction(icon3, tr("History"), menu);
		QAction *actionEdit	= new QAction(icon4, tr("Edit"), menu);
		QAction *actionDelete	= new QAction(icon5, tr("Remove"), menu);
		menu -> addAction(actionInfo);
		menu -> addSeparator();
		menu -> addAction(actionMessage);
		menu -> addAction(actionHistory);
		menu -> addSeparator();
		menu -> addAction(actionEdit);
                connect(actionInfo,
                        SIGNAL(triggered()),
                        parentWidget()->parentWidget(),
                        SLOT(menuActionInfo()));
                connect(actionMessage,
                        SIGNAL(triggered()),
                        parentWidget()->parentWidget(),
                        SLOT(menuActionChat()));
                connect(actionHistory,
                        SIGNAL(triggered()),
                        parentWidget()->parentWidget(),
                        SLOT(menuActionHistory()));
                connect(actionEdit,
                        SIGNAL(triggered()),
                        parentWidget()->parentWidget(),
                        SLOT(menuActionEdit()));
                connect(actionDelete,
                        SIGNAL(triggered()),
                        parentWidget()->parentWidget(),
                        SLOT(menuActionDelete()));
		menu -> addAction(actionDelete);
		menu -> addSeparator();
	}
	QAction *actionAdd 		= new QAction(tr("Add contact"), menu);
	QAction *actionShowOfflines	= new QAction(tr("Show offlines"), menu);
	actionShowOfflines->setCheckable(true);
	actionShowOfflines->setChecked(offlinesVisible);
	menu -> addAction(actionAdd);
	menu -> addAction(actionShowOfflines);
        connect(actionAdd,
                SIGNAL(triggered()),
                parentWidget()->parentWidget(),
                SLOT(menuActionAdd()));
        connect(actionShowOfflines,
                SIGNAL(toggled(bool)),
                parentWidget()->parentWidget(),
                SLOT(menuActionShowOfflines(bool)));
        connect(actionShowOfflines,
                SIGNAL(toggled(bool)),
                this,
                SLOT(setOfflinesVisible(bool)));
	menu -> exec(event->globalPos());
}

void QTlenRosterBox::setOfflinesVisible(bool yesno)
{
	offlinesVisible = yesno;
}

QTreeWidgetItem* QTlenRosterBox::addRosterItem(QString name,
                                               QTlenPresence type,
                                               QString desc,
                                               QString jid,
					       QPixmap pxAvatar,
                                               QTreeWidgetItem* node)
{
        QTreeWidgetItem*    item   = new QTreeWidgetItem(node);
        QFrame*             frame = new QFrame(this);
        QHBoxLayout*        hLayout = new QHBoxLayout(frame);
        hLayout->setAlignment(Qt::AlignTop);
        QVBoxLayout*        vLayout = new QVBoxLayout();
        vLayout->setAlignment(Qt::AlignTop);
	QLabel*             statusIcon = new QLabel(frame);
        statusIcon->setFixedSize(16,16);
        switch (type)
        {
                case Online:
                        statusIcon->setPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/online.png")));
                break;
                case Chatty:
                        statusIcon->setPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/chatty.png")));
                break;
                case Away:
                        statusIcon->setPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/away.png")));
                break;
                case XA:
                        statusIcon->setPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/xa.png")));
                break;
                case DND:
                        statusIcon->setPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/dnd.png")));
                break;
                case Offline:
                        statusIcon->setPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/offline.png")));
                break;
        }

        hLayout->addWidget(statusIcon);
        hLayout->addLayout(vLayout);
        QLabel* nameLabel = new QLabel(name, frame);
        QFont nameFont;
        nameFont.setBold(true);
        nameLabel->setFont(nameFont);
        vLayout->addWidget(nameLabel);
	if (!desc.isEmpty() && settings->value("/roster/show_descriptions", false).toBool())
        {
            QLabel* descLabel = new QLabel(desc, frame);
            QFont descFont;
            descFont.setPointSize(7);
            descFont.setItalic(true);
            descLabel->setWordWrap(true);
            descLabel->setFont(descFont);
            vLayout->addWidget(descLabel);
	}
        //prowizorka
	if(settings->value("/roster/show_avatars", false).toBool())
	{
	    QLabel* avatar = new QLabel();
	    if(pxAvatar.isNull())
		avatar->setPixmap(QPixmap(QString::fromUtf8(":/icons/icons/64x64/default_av.png")));
	    else
		avatar->setPixmap(pxAvatar);
	    avatar->setAlignment(Qt::AlignRight);
	    hLayout->addWidget(avatar);
	}
        frame->setLayout(hLayout);
        setItemWidget(item, 0, frame);
	return item;
}

QTreeWidgetItem* QTlenRosterBox::addRosterNode(QString group)
{
        QTreeWidgetItem* node = new QTreeWidgetItem(this);
        QLabel *label = new QLabel(group, this);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(170, 170, 170, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        label->setAutoFillBackground(true);
        label->setPalette(palette);
        label->setBackgroundRole(QPalette::Window);
	QFont font;
        font.setPointSize(7);
        font.setBold(true);
        label->setFont(font);
        label->setFrameShape(QFrame::StyledPanel);
        label->setFrameShadow(QFrame::Raised);
        label->setAlignment(Qt::AlignCenter);
        setItemWidget(node, 0, label);
	setItemExpanded(node, true);
	return node;
}
