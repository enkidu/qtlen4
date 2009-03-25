#include "edit_dialog.h"

QTlenUserEdit::QTlenUserEdit(QWidget * parent, QString jid, QString name, QString group, QStringList groups, Qt::WFlags f):QWidget(parent, f)
{
	ui.setupUi(this);
	connect(ui.buttonBox,	SIGNAL(rejected()),	this,	SLOT(close()));
	connect(ui.buttonBox,	SIGNAL(accepted()),	this,	SLOT(saveInfo()));
        ui.cb_group->addItems(groups);
        ui.cb_group->setDuplicatesEnabled(0);
	if (jid != "")
	{
		setWindowTitle("Edycja kontaktu");
		ui.le_jid->setEnabled(0);
		ui.le_jid->setText(jid.mid(0, jid.length()-8));
		ui.le_nick->setText(name);
		ui.cb_group->setEditText(group);
	}
	else
		setWindowTitle(tr("Adding contact"));
}

void QTlenUserEdit::saveInfo()
{
	emit saveItem(ui.le_jid->text(), ui.le_nick->text(), ui.cb_group->currentText());
	this->close();
}
