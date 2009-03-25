#include <QtCore/QtCore>
#include <QTreeWidget>

#include "defines.h"
#include "widgets/qtlenrosterbox.hpp"
#include "systrayicon.h"
#include "avatarsmanager.hpp"
class RosterItem
{
	public:
		RosterItem() {}
		RosterItem(QString j, QString n, QString g, QString s)
                        : jid(j), name(n), group(g), subscription(s), presence(Offline), desc(QString::null), avatar(QPixmap()) {}
		RosterItem(const RosterItem& other)
		{
			jid		= other.jid;
			name		= other.name;
			group		= other.group;
			subscription	= other.subscription;
			desc		= other.desc;
			presence	= other.presence;
                        avatar_type     = other.avatar_type;
                        avatar          = other.avatar;
		}
		RosterItem& operator=(const RosterItem& other)
		{
			if (this == &other) return *this;
			jid		= other.jid;
			name		= other.name;
			group		= other.group;
			subscription	= other.subscription;
			desc		= other.desc;
			presence	= other.presence;
                        avatar_type     = other.avatar_type;
                        avatar          = other.avatar;
			return *this;
		}
		bool operator<(const RosterItem& other) const {
			if( name.compare( other.name , Qt::CaseInsensitive) < 0 )
				return true;
			else
				return false;
		}
		~RosterItem() {}
		
		QString		jid;
		QString		name;
		QString		group;
		QString		subscription;
		QTlenPresence	presence;
		QString 	desc;
                QString         avatar_type;
                QPixmap         avatar;
		
};
class QTlenRosterManager: public QObject
{
	Q_OBJECT
	public:
		QTlenRosterManager(QTlenRosterBox *roster, QTlenTrayIcon *icon);
                ~QTlenRosterManager(){}

		struct AddedItem
		{
			QString			jid;
			QTreeWidgetItem*	item;
		};
		struct AddedGroup
		{
			QString			group;
			QTreeWidgetItem*	item;
		};
		QString QSStatus(int type) 
		{
			QString status[]=
			{
				QString::fromUtf8("Dostępny"),
				QString::fromUtf8("Pogadajmy"),
				QString::fromUtf8("Zaraz wracam"),
				QString::fromUtf8("Wracam później"),
				QString::fromUtf8("Zajęty"),
				QString::fromUtf8("Niewidoczny"), //nie zobaczymy, ale nam się przyda
				QString::fromUtf8("Niedostępny")
			};
			return status[type];
                }
		int			getIndexOf(QString);	//returns index, arguments: field, text
		QString			getJidOf(QString);	//uses index to find JID
		QString			getNameOf(QString);	//uses index to find nick
		QString			getGroupOf(QString);
		QString			getJidOf(QTreeWidgetItem*);
		int			getIndexOfGroup(QString);
		int			getIndexOfAddedGroup(QString group);
		QTreeWidgetItem*	getItemOfGroup(QString group);
                QStringList             getGroupsList();
	private:
		QList<RosterItem>	rosterItems;
		QList<AddedItem>	addedItems;
                QStringList		groups;
		QList<AddedGroup>	addedGroups;
		bool			dontShowOfflines;
		QTlenRosterBox		*rosterBox;
		QTlenTrayIcon		*sysIcon;
                QTlenMailConfig         mailInfo;
                QString                 token;
                void                    appendGroup(QString);
                QTlenAvatarsManager     *av_manager;
		QPixmap			avMask;
	public slots:
		void			beginRoster();
		void			addItem(QString, QString, QString, QString);		//jid, group, name, subscription
		void			deleteItem(QTreeWidgetItem*);
			//jid, type, description, avatar_type, avatar_digest
		void			presenceFrom(QString, QTlenPresence, QString, QString, QString);
		void			showRoster();
		void			showOfflines(bool);
                void                    setMailFetchInfo(QTlenMailConfig);
                void                    setToken(QString);
		void			setAvatar(QString, QPixmap);
		void			saveMyAvatar(QImage);
	signals:
		void			avatarSaved();
		void			savingError();
};
