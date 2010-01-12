#include "qtlenrosteritem.hpp"

QTlenRosterItem::QTlenRosterItem(QString name, QTlenPresence type, QString desc, QString jid, QPixmap pxAvatar)
{
    this->name = name;
    this->desc = desc;
    this->jid = jid;
    this->avatar = pxAvatar;
    height = 68;
    switch (type)
        {
                case Online:
                        presence=QPixmap(QString::fromUtf8(":/icons/icons/16x16/online.png"));
                break;
                case Chatty:
                        presence=QPixmap(QString::fromUtf8(":/icons/icons/16x16/chatty.png"));
                break;
                case Away:
                        presence=QPixmap(QString::fromUtf8(":/icons/icons/16x16/away.png"));
                break;
                case XA:
                        presence=QPixmap(QString::fromUtf8(":/icons/icons/16x16/xa.png"));
                break;
                case DND:
                        presence=QPixmap(QString::fromUtf8(":/icons/icons/16x16/dnd.png"));
                break;
                case Offline:
                        presence=QPixmap(QString::fromUtf8(":/icons/icons/16x16/offline.png"));
                break;
        }
}

int QTlenRosterItem::paint(QPainter *painter, const QRect &rect, const QPalette &palette, bool checked) const
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    if (checked) painter->setBrush(QColor("#fff"));
    else
        painter->setBrush(palette.foreground());
    //name
    QRect nameRect;
    nameRect.setLeft(rect.left()+20);
    nameRect.setRight(rect.right()-68);
    nameRect.setTop(rect.top()+2);
    nameRect.setBottom(rect.bottom()-2);
    QRect *nameBR = new QRect;
    QFont nameFont;
    nameFont.setBold(true);
    nameFont.setPixelSize(14);
    painter->setFont(nameFont);
    painter->drawText(nameRect, (int)(Qt::AlignLeft | Qt::TextWordWrap), name, nameBR);
    //jid
    QRect jidRect;
    jidRect.setLeft(rect.left()+20);
    jidRect.setRight(rect.right()-68);
    jidRect.setTop(nameBR->bottom()+2);
    jidRect.setBottom(nameBR->bottom()+18);
    QRect *jidBR = new QRect;
    nameFont.setBold(false);
    painter->setFont(nameFont);
    painter->drawText(jidRect,  (int)(Qt::AlignLeft | Qt::TextWordWrap), jid,  jidBR);
    //desc
    QRect descRect;
    descRect.setLeft(rect.left()+20);
    descRect.setRight(rect.right()-68);
    descRect.setTop(jidBR->bottom()+2);
    descRect.setBottom(rect.bottom()-2);
    QRect *descBR = new QRect;
    QFont descFont;
    descFont.setPixelSize(10);
    descFont.setItalic(true);
    painter->setFont(descFont);
    painter->drawText(descRect, (int)(Qt::AlignLeft | Qt::TextWordWrap), desc, descBR);
    int textHeight = nameBR->height() + jidBR->height() + descBR->height()+8;
    int theight;
    if (textHeight > 68)
        theight = textHeight;
    else
        theight = 68;
    //setHeight(68);s
    painter->drawPixmap(rect.left()+2, rect.top()-8+rect.height()/2,16, 16, presence);
    painter->drawPixmap(rect.right()-66, rect.top()+2, 64, 64, avatar);
    painter->restore();
    return theight;
}

 QSize QTlenRosterItem::sizeHint(const QStyleOptionViewItem &option, QWidget* tree) const
 {
     QFont descFont;
     descFont.setPixelSize(10);
     descFont.setItalic(true);
     QFontMetrics fm(descFont);
     QRect rect = fm.boundingRect(0,0,tree->width()-88,160, (int)(Qt::AlignLeft | Qt::TextWordWrap), desc);
     int h = rect.height();
     qDebug(QByteArray::number(h));
     if ((h + 44) < 68)
         return QSize(160, 68);
     return QSize(160, h+44);
 }

 void QTlenRosterItem::setHeight(int h)
 {
     height = h;
 }
