#include "roster_manager.h"
QTlenRosterManager::QTlenRosterManager(QTlenRosterBox *rosterBox,  QTlenTrayIcon *icon)
{
	dontShowOfflines = false;
	this->rosterBox = rosterBox;
	sysIcon = icon;
	av_manager = new QTlenAvatarsManager();
	avMask = QPixmap(":/icons/icons/64x64/mask.png");
}

int QTlenRosterManager::getIndexOf(QString jid)
{
	for ( int n = 0; n < (int)rosterItems.count(); n++ )
		if( rosterItems[n].jid == jid )
			return n;
	return -1;
};

QString QTlenRosterManager::getJidOf(QTreeWidgetItem* item)
{
	for ( int n = 0; n < (int)addedItems.count(); n++ )
		if( addedItems[n].item == item )
			return addedItems[n].jid;
	return "-1";
};

QString QTlenRosterManager::getJidOf(QString name)
{
	for ( int n = 0; n < (int)rosterItems.count(); n++ )
		if( rosterItems[n].name == name )
			return rosterItems[n].jid;
	return "-1";
};

int QTlenRosterManager::getIndexOfGroup(QString group)
{
	for ( int n = 0; n < (int)addedGroups.count(); n++ )
		if( addedGroups[n].group == group )
			return n;
	return -1;
};

int QTlenRosterManager::getIndexOfAddedGroup(QString group)
{
	for ( int n = 0; n < (int)addedGroups.count(); n++ )
		if( addedGroups[n].group == group )
			return n;
	return -1;
};

QTreeWidgetItem* QTlenRosterManager::getItemOfGroup(QString group)
{
	int index = getIndexOfAddedGroup(group);
	if ( index != -1)
		return addedGroups[index].item;
};

QString QTlenRosterManager::getNameOf(QString jid)
{
	for ( int n = 0; n < (int)rosterItems.count(); n++ )
		if( rosterItems[n].jid == jid )
			return rosterItems[n].name;
	return jid;
};

QString QTlenRosterManager::getGroupOf(QString jid)
{
	for ( int n = 0; n < (int)rosterItems.count(); n++ )
		if( rosterItems[n].jid == jid )
			return rosterItems[n].group;
	return "Tlen";
};

void QTlenRosterManager::beginRoster()
{
	 rosterItems.clear();
};

void QTlenRosterManager::addItem(QString jid, QString group, QString name, QString subscription)
{
	if (subscription != "remove")
	{
		if (getIndexOf(jid) != -1)
		{
			int index = getIndexOf(jid);
			if (name.isEmpty())
				rosterItems[index].name = jid;
			else
				rosterItems[index].name = name;
			if (group.isEmpty())
				rosterItems[index].group = "Tlen";
			else
				rosterItems[index].group = group;
			rosterItems[index].subscription = subscription;
		}
		else
		{
			RosterItem i;
			i.jid = jid;
			if (name.isEmpty())
				i.name = jid;
			else
				i.name = name;
			i.subscription = subscription;
			i.desc = QString::null;
                        i.avatar_type = "-1";
                        i.avatar = QPixmap();
			i.presence = Offline;
			if (group.isEmpty())
				i.group = "Tlen";
			else
				i.group = group;
			rosterItems.append(i);
		}
	}
	else
		rosterItems.removeAt(getIndexOf(jid));
	showRoster();
};

void QTlenRosterManager::presenceFrom(QString jid,
				      QTlenPresence type,
				      QString description,
				      QString av_type,
				      QString digest)
{	
	if (getIndexOf(jid) != -1)
	{
		int index = getIndexOf(jid);
                rosterItems[index].presence     = type;
                rosterItems[index].desc         = description;
                rosterItems[index].avatar_type  = av_type;
                //TODO: fetch avatars
		if (av_type != "-1")
		{
		    QString nick = jid;
		    nick.chop(8);
		    QTlenAvatarsFetcher *fetcher = new QTlenAvatarsFetcher();
		    //token nick digest
		    connect(fetcher,
			    SIGNAL(gotAvatar(QString,QPixmap)),
			    this,
			    SLOT(setAvatar(QString, QPixmap)));
		    rosterItems[index].avatar = fetcher->getAvatar(av_manager, mailInfo, token, nick, digest);
		}
		sysIcon->showMessage(QString::fromUtf8("Zmiana statusu"), rosterItems[index].name + " ma teraz status " + QSStatus(type));
	}
	else
	{
		RosterItem i;
		i.jid = jid;
		i.name = jid;
		if (description.isEmpty())
			i.desc = "";
		else
			i.desc = description;
		i.subscription = "both";
		i.presence = type;
		i.group = "Tlen";
		rosterItems.append(i);
	}
	showRoster();
};

void QTlenRosterManager::showRoster()
{
	for(int i = 0; i < addedItems.count(); i++)
	{
	    rosterBox->itemWidget(addedItems[i].item, 0)->deleteLater();
	}
	rosterBox->clear();
	qSort( rosterItems.begin(), rosterItems.end() );
	addedItems.clear();
	addedGroups.clear();
	AddedItem i;
	QTreeWidgetItem *node;
	for ( int n = 0; n < (int)rosterItems.count(); n++ )
	{
            appendGroup(rosterItems[n].group);
		if (!dontShowOfflines || rosterItems[n].presence != Offline)
		{
                        int group_index = getIndexOfGroup(rosterItems[n].group);
                        if(group_index != -1)
                                node = addedGroups[group_index].item;
			else
			{
				node = rosterBox->addRosterNode(rosterItems[n].group);
				AddedGroup g;
				g.item = node;
				g.group = rosterItems[n].group;
				addedGroups.append(g);
			}
			QPixmap tmpAvatar = QPixmap(rosterItems[n].avatar);
			tmpAvatar.setAlphaChannel(avMask);
			i.item = rosterBox->addRosterItem(rosterItems[n].name,
							  rosterItems[n].presence,
							  rosterItems[n].desc,
							  rosterItems[n].jid,
							  tmpAvatar,
							  node);
			i.jid = rosterItems[n].jid;
			addedItems.append(i);
		}
        }
}

void QTlenRosterManager::showOfflines(bool yesno)
{
	dontShowOfflines = !yesno;
	showRoster();
}

void QTlenRosterManager::deleteItem(QTreeWidgetItem* item)
{
	if (getJidOf(item) != "-1")
	{
		rosterItems.removeAt(getIndexOf(getJidOf(item)));
		showRoster();
	}
};

void QTlenRosterManager::appendGroup(QString group)
{
        bool found = false;
        for ( int n = 0; n < (int)groups.count(); n++ )
                if( groups[n] == group )
                        found = true;
        if(!found)
            groups << group;
}

QStringList QTlenRosterManager::getGroupsList()
{
        return groups;
}

void QTlenRosterManager::setMailFetchInfo(QTlenMailConfig config)
{
    mailInfo=config;
}
void QTlenRosterManager::setToken(QString tokenString)
{
    token = tokenString;
}

void QTlenRosterManager::setAvatar(QString jid, QPixmap avatar)
{
    int index = getIndexOf(jid);
	if (index != -1)
	{
	    rosterItems[index].avatar = avatar;
	    this->showRoster();
	    qDebug("Got avatar " + jid.toAscii());
	}
}

void QTlenRosterManager::saveMyAvatar(QImage image)
{
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    image.save(QDir::homePath() + "/.qtlen4/avatar.png", "PNG");
    QTlenAvatarSaver *saver = new QTlenAvatarSaver();
    connect(saver,
	    SIGNAL(saved()),
	    this,
	    SIGNAL(avatarSaved()));
    connect(saver,
	    SIGNAL(error()),
	    this,
	    SIGNAL(savingError()));
    saver->start();
    saver->saveAvatar(mailInfo, ba, token, 0);
}
