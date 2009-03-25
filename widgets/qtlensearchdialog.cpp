#include "qtlensearchdialog.hpp"

QTlenSearchDialog::QTlenSearchDialog(QWidget * parent, Qt::WFlags f):QWidget(parent, f)
{
    resize(472, 503);
    hLayout = new QHBoxLayout(this);
    splitter = new QSplitter(Qt::Horizontal, this);
    hLayout->addWidget(splitter);
    frame       = new QWidget(this);
    fLayout	= new QFormLayout(frame);
    label       = new QLabel(tr("First name"),	frame);
    label_2     = new QLabel(tr("Nick"),	frame);
    label_3     = new QLabel(tr("Last name"),	frame);
    label_4     = new QLabel(tr("E-mail"),      frame);
    label_5     = new QLabel(tr("School"),      frame);
    label_6     = new QLabel(tr("City"),	frame);
    label_7     = new QLabel(tr("Sex"),         frame);
    label_8     = new QLabel(tr("Year from"),   frame);
    label_9     = new QLabel(tr("to"),          frame);
    le_first    = new QLineEdit(frame);
    le_last     = new QLineEdit(frame);
    le_mail     = new QLineEdit(frame);
    le_nick     = new QLineEdit(frame);
    le_school   = new QLineEdit(frame);
    le_city     = new QLineEdit(frame);
    comboBox    = new QComboBox(frame);
    comboBox->insertItems(0, QStringList()
	<< tr("-- unbound --")
	<< tr("man")
	<< tr("woman"));
    sb_ageMin   = new QSpinBox(frame);
    sb_ageMin   ->setMaximum(150);
    sb_ageMax   = new QSpinBox(frame);
    sb_ageMax   ->setMaximum(150);
    pb_search   = new QPushButton(tr("Search"), frame);
    pb_clear    = new QPushButton(tr("Clear"), frame);
    cb_onlines  = new QCheckBox(tr("Only online users"),frame);

    fLayout ->addRow(label, le_first);
    fLayout ->addRow(label_3, le_last);
    fLayout ->addRow(label_4, le_mail);
    fLayout ->addRow(label_2, le_nick);
    fLayout ->addRow(label_5, le_school);
    fLayout ->addRow(label_6, le_city);
    fLayout ->addRow(label_7, comboBox);
    fLayout ->addRow(cb_onlines);
    fLayout ->addRow(label_8, sb_ageMin);
    fLayout ->addRow(label_9, sb_ageMax);
    frame_2 = new QWidget(this);
    vLayout = new QVBoxLayout(frame_2);
    buttonLayout = new QHBoxLayout();
    tw_output   = new QTlenSearchResultBox(this, this);
    vLayout->addWidget(tw_output);
    vLayout->addLayout(buttonLayout);
    buttonLayout->addWidget(pb_search);
    buttonLayout->addWidget(pb_clear);
    connect(tw_output,
	    SIGNAL(itemDoubleClicked(QListWidgetItem*)),
	    this,
	    SLOT(menuActionChat()));
    splitter   ->addWidget(frame);
    splitter   ->addWidget(frame_2);
    setWindowTitle(tr("Contact search"));


    connect(pb_search,
            SIGNAL(clicked()),
            this,
            SLOT(sendRequest()));
    connect(pb_clear,
            SIGNAL(clicked()),
            this,
            SLOT(clearForm()));
    searchingAllowed = true;
    itemCount = 0;
    	if (!testAttribute(Qt::WA_DeleteOnClose)) this->setAttribute(Qt::WA_DeleteOnClose, true);
}

void QTlenSearchDialog::appendItem(const QTlenUserInfo info)
{
    SearchResult r;
    r.item = tw_output->appendItem(info);
    r.jid = info.jid;
    searchResults.append(r);
    itemCount++;
}

void QTlenSearchDialog::clearForm()
{
        pb_search->setEnabled(true);
        le_first->setEnabled(true);
        le_last->setEnabled(true);
        le_nick->setEnabled(true);
        le_mail->setEnabled(true);
        le_school->setEnabled(true);
        le_city->setEnabled(true);
        comboBox->setEnabled(true);
        cb_onlines->setEnabled(true);
	for(int i = 0; i < searchResults.count(); i++)
	{
	    tw_output->itemWidget(searchResults[i].item, 0)->deleteLater();
	}
        tw_output->clear();
	searchResults.clear();
	itemCount = 0;
}

QTlenSearchDialog::~QTlenSearchDialog()
{
    	for(int i = 0; i < searchResults.count(); i++)
	{
	    tw_output->itemWidget(searchResults[i].item, 0)->deleteLater();
	}
	disconnect(tw_output);
	disconnect(pb_search);
	disconnect(pb_clear);
	qDebug("search window deleted");
}

void QTlenSearchDialog::beginInfo(bool notEmpty)
{
	if (!notEmpty)
                pb_search->setDisabled(true);
}

void QTlenSearchDialog::sendRequest()
{
	QTlenUserInfo info;
        info.first	= le_first->text();
        le_first->setDisabled(true);
        info.last	= le_last->text();
        le_last->setDisabled(true);
        info.nick	= le_nick->text();
        le_nick->setDisabled(true);
        info.email	= le_mail->text();
        le_mail->setDisabled(true);
        info.school	= le_school->text();
        le_school->setDisabled(true);
        info.city	= le_city->text();
        le_city->setDisabled(true);
        info.sex	= comboBox->currentIndex();
        comboBox->setDisabled(true);
        info.visible	= cb_onlines->isChecked();
        cb_onlines->setDisabled(true);
        info.years_from = sb_ageMin->value();
        info.years_to	= sb_ageMax->value();
	info.start	= itemCount;
	emit search(info);
}

void QTlenSearchDialog::menuActionChat()
{
    emit openChat(findJidOf(tw_output->currentItem()));
}

void QTlenSearchDialog::menuActionAdd()
{
    emit addContact(findJidOf(tw_output->currentItem()));
}

QString QTlenSearchDialog::findJidOf(const QTreeWidgetItem* item)
{
    for(int i =0; i<searchResults.count(); i++)
	if (searchResults[i].item == item)
	    return searchResults[i].jid;
    return "";
}
