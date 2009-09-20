#include "settings_dialog.h"

QTlenConfigDialog::QTlenConfigDialog(QWidget * parent):QWidget(parent)
{
    if (objectName().isEmpty())
	setObjectName(QString::fromUtf8("configDialog"));
    resize(480, 264);
    horizontalLayout_2 = new QHBoxLayout(this);

    listWidget	    = new QListWidget(this);
    listWidget	    ->setFixedWidth(220);
    listWidget->setIconSize(QSize(64, 64));
    stackedWidget   = new QStackedWidget(this);

    new QListWidgetItem(listWidget);
    new QListWidgetItem(QIcon(QPixmap(":icons/icons/64x64/roster.png")), tr("Roster appearance"), listWidget);
    new QListWidgetItem(QIcon(QPixmap(":icons/icons/64x64/look.png")), tr("Chat appearance"), listWidget);
    new QListWidgetItem(QIcon(QPixmap(":icons/icons/64x64/network.png")), tr("Network"), listWidget);

    connection_page = new QWidget();
    roster_page	    = new QWidget();
    chats_page	    = new QWidget();
    network_page    = new QWidget();
    label		= new QLabel(tr("Login"), connection_page);
    le_login		= new QLineEdit(connection_page);
    label_2		= new QLabel(tr("Password"), connection_page);
    le_password		= new QLineEdit(connection_page);
    le_password		->setEchoMode(QLineEdit::Password);
    cb_autoConnect	= new QCheckBox(connection_page);
    label_3		= new QLabel(connection_page);
    cb_defaultState	= new QComboBox(connection_page);
    QIcon icon		= QIcon(QPixmap(QString::fromUtf8(":/icons/icons/16x16/online.png")));
    QIcon icon1		= QIcon(QPixmap(QString::fromUtf8(":/icons/icons/16x16/chatty.png")));
    QIcon icon2		= QIcon(QPixmap(QString::fromUtf8(":/icons/icons/16x16/away.png")));
    QIcon icon3		= QIcon(QPixmap(QString::fromUtf8(":/icons/icons/16x16/xa.png")));
    QIcon icon4		= QIcon(QPixmap(QString::fromUtf8(":/icons/icons/16x16/dnd.png")));
    QIcon icon5		= QIcon(QPixmap(QString::fromUtf8(":/icons/icons/16x16/invisible.png")));
    cb_defaultState->addItem(icon, QString::fromUtf8("Dostępny"));
    cb_defaultState->addItem(icon1, QString::fromUtf8("Porozmawiajmy"));
    cb_defaultState->addItem(icon2, QString::fromUtf8("Zaraz wracam"));
    cb_defaultState->addItem(icon3, QString::fromUtf8("Wracam później"));
    cb_defaultState->addItem(icon4, QString::fromUtf8("Zajęty"));
    cb_defaultState->addItem(icon5, QString::fromUtf8("Niewidoczny"));
    cb_defaultState->addItem(QString::fromUtf8("-- poprzedni --"));
    cb_defaultState->setEnabled(false);

    formLayout		= new QFormLayout(connection_page);
    formLayout		->setWidget(0, QFormLayout::LabelRole, label);
    formLayout		->setWidget(0, QFormLayout::FieldRole, le_login);
    formLayout		->setWidget(1, QFormLayout::LabelRole, label_2);
    formLayout		->setWidget(1, QFormLayout::FieldRole, le_password);
    formLayout		->setWidget(2, QFormLayout::FieldRole, cb_autoConnect);
    formLayout		->setWidget(3, QFormLayout::LabelRole, label_3);
    formLayout		->setWidget(3, QFormLayout::FieldRole, cb_defaultState);
    stackedWidget->addWidget(connection_page);
    horizontalLayout_2	->addWidget(listWidget);

    verticalLayout = new QVBoxLayout(roster_page);
    cb_showOfflines = new QCheckBox(tr("Show offline users"),roster_page);
    QIcon icon6;
    icon6.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/view-user-offline-kopete.png")), QIcon::Normal, QIcon::Off);
    cb_showOfflines->setIcon(icon6);

    verticalLayout->addWidget(cb_showOfflines);

    cb_showExtendedInfo = new QCheckBox(tr("Show extended info"), roster_page);

    verticalLayout->addWidget(cb_showExtendedInfo);

    cb_showAvatars = new QCheckBox(tr("Show contacts avatars"), roster_page);

    verticalLayout->addWidget(cb_showAvatars);

    cb_showDescriptions = new QCheckBox(tr("Show contacts descriptions"),roster_page);
    verticalLayout->addWidget(cb_showDescriptions);

    cb_showJidInRoster = new QCheckBox(tr("Show contacts IDs"),roster_page);

    verticalLayout->addWidget(cb_showJidInRoster);

    gb_expandPolicy = new QGroupBox(roster_page);
    verticalLayout_2 = new QVBoxLayout(gb_expandPolicy);
    rb_expandedState = new QRadioButton(gb_expandPolicy);

    verticalLayout_2->addWidget(rb_expandedState);

    rb_collapsedState = new QRadioButton(gb_expandPolicy);

    verticalLayout_2->addWidget(rb_collapsedState);

    rb_previousState = new QRadioButton(gb_expandPolicy);

    verticalLayout_2->addWidget(rb_previousState);


    verticalLayout->addWidget(gb_expandPolicy);

    stackedWidget->addWidget(roster_page);

    verticalLayout_4 = new QVBoxLayout(chats_page);
    scrollArea = new QScrollArea(chats_page);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setFrameShadow(QFrame::Plain);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidgetResizable(true);
    scrollAreaWidgetContents = new QWidget();
    scrollAreaWidgetContents->setGeometry(QRect(0, 0, 330, 261));
    verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents);
    verticalLayout_3->setMargin(0);
    groupBox = new QGroupBox(scrollAreaWidgetContents);
    formLayout_4 = new QFormLayout(groupBox);
    formLayout_4->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    label_5 = new QLabel(groupBox);

    formLayout_4->setWidget(0, QFormLayout::LabelRole, label_5);

    le_nick = new QLineEdit(groupBox);

    formLayout_4->setWidget(0, QFormLayout::FieldRole, le_nick);

    label_7 = new QLabel(groupBox);

    formLayout_4->setWidget(4, QFormLayout::LabelRole, label_7);

    label_6 = new QLabel(groupBox);

    formLayout_4->setWidget(3, QFormLayout::LabelRole, label_6);

    pb_myColor = new QPushButton(groupBox);

    formLayout_4->setWidget(3, QFormLayout::FieldRole, pb_myColor);

    pb_myBg = new QPushButton(groupBox);

    formLayout_4->setWidget(4, QFormLayout::FieldRole, pb_myBg);


    verticalLayout_3->addWidget(groupBox);

    groupBox_2 = new QGroupBox(scrollAreaWidgetContents);
    formLayout_5 = new QFormLayout(groupBox_2);
    label_8 = new QLabel(tr("Contact text color"),groupBox_2);

    formLayout_5->setWidget(1, QFormLayout::LabelRole, label_8);

    cb_useJID = new QCheckBox(tr("Use ID instead of contact name"),groupBox_2);

    formLayout_5->setWidget(0, QFormLayout::FieldRole, cb_useJID);

    pb_chatColor = new QPushButton(groupBox_2);

    formLayout_5->setWidget(1, QFormLayout::FieldRole, pb_chatColor);

    pb_chatBg = new QPushButton(groupBox_2);

    formLayout_5->setWidget(2, QFormLayout::FieldRole, pb_chatBg);

    label_9 = new QLabel(tr("Contact text background"),groupBox_2);

    formLayout_5->setWidget(2, QFormLayout::LabelRole, label_9);


    verticalLayout_3->addWidget(groupBox_2);

    scrollArea->setWidget(scrollAreaWidgetContents);

    verticalLayout_4->addWidget(scrollArea);

    stackedWidget->addWidget(chats_page);

    stackedWidget->addWidget(network_page);

    horizontalLayout_2->addWidget(stackedWidget);

    QObject::connect(listWidget, SIGNAL(currentRowChanged(int)), stackedWidget, SLOT(setCurrentIndex(int)));

	settings = new QSettings(QDir::homePath() + "/.qtlen4/config", QSettings::IniFormat);
	le_login->setText(settings->value("/connection/username", "").toString());
	le_password->setText(settings->value("/connection/password", "").toString());
	cb_autoConnect->setChecked(settings->value("/behaviour/autoconnect", false).toBool());
	le_nick->setText(settings->value("/preferences/nick", "").toString());
	cb_showJidInRoster->setChecked(settings->value("/roster/show_jid", false).toBool());
	cb_showOfflines->setChecked(settings->value("/roster/offlines_visible", false).toBool());
	cb_showAvatars->setChecked(settings->value("/roster/show_avatars", false).toBool());
	cb_showDescriptions->setChecked(settings->value("/roster/show_descriptions", false).toBool());
	cb_showExtendedInfo->setChecked(settings->value("/roster/show_ext_info", false).toBool());
	if(!settings->value("/roster/show_ext_info", false).toBool())
	{
	    cb_showJidInRoster->setEnabled(false);
	    cb_showAvatars->setEnabled(false);
	    cb_showDescriptions->setEnabled(false);
	}
	connect(pb_myColor,		SIGNAL(clicked()),	this,	SLOT(setMyColor()));
	connect(pb_myBg,		SIGNAL(clicked()),	this,	SLOT(setMyBg()));
	connect(pb_chatColor,	SIGNAL(clicked()),	this,	SLOT(setChatColor()));
	connect(pb_chatBg,		SIGNAL(clicked()),	this,	SLOT(setChatBg()));
	changed.user = false;
        changed.roster = false;
}

void QTlenConfigDialog::closeEvent(QCloseEvent *event)
{
	//zapisujemy i puszczamy sygnały ewentualnie
	if (le_login->text() != settings->value("/connection/username", "").toString())
                changed.user = true;
	settings->setValue("/connection/username", le_login->text());

	if (le_password->text() != settings->value("/connection/password", "").toString())
                changed.user = true;
	settings->setValue("/connection/password", le_password->text());

	settings->setValue("/behaviour/autoconnect", cb_autoConnect->isChecked());

	if (cb_showOfflines->isChecked() != settings->value("/roster/offlines_visible", false).toBool())
                changed.roster = true;
	settings->setValue("/roster/offlines_visible", cb_showOfflines->isChecked());

	if (cb_showJidInRoster->isChecked() != settings->value("/roster/show_jid", false).toBool())
                changed.roster = true;
	settings->setValue("/roster/show_jid", cb_showJidInRoster->isChecked());

	if (cb_showAvatars->isChecked() != settings->value("/roster/show_avatars", false).toBool())
		changed.roster = true;
	settings->setValue("/roster/show_avatars", cb_showAvatars->isChecked());

	if (cb_showDescriptions->isChecked() != settings->value("/roster/show_descriptions", false).toBool())
		changed.roster = true;
	settings->setValue("/roster/show_descriptions", cb_showDescriptions->isChecked());

	if (cb_showExtendedInfo->isChecked() != settings->value("/roster/show_ext_info", false).toBool())
                changed.roster = true;
	settings->setValue("/roster/show_ext_info", cb_showExtendedInfo->isChecked());

	settings->setValue("/preferences/nick", le_nick->text());
        emit configChanged(changed);
	event->accept();
}

void QTlenConfigDialog::setMyColor()
{
	QColor color = QColorDialog::getColor(QColor(settings->value("/preferences/sent/color", "#000000").toString()), this);
	if (color.isValid())
		settings->setValue("/preferences/sent/color", color.name());
}

void QTlenConfigDialog::setMyBg()
{
	QColor color = QColorDialog::getColor(QColor(settings->value("/preferences/sent/bground", "#ffffff").toString()), this);
	if (color.isValid())
		settings->setValue("/preferences/sent/bground", color.name());
}

void QTlenConfigDialog::setChatColor()
{
	QColor color = QColorDialog::getColor(QColor(settings->value("/preferences/received/color", "#000000").toString()), this);
	if (color.isValid())
		settings->setValue("/preferences/received/color", color.name());
}

void QTlenConfigDialog::setChatBg()
{
	QColor color = QColorDialog::getColor(QColor(settings->value("/preferences/received/bground", "#ffffff").toString()), this);
	if (color.isValid())
		settings->setValue("/preferences/received/bground", color.name());
}
