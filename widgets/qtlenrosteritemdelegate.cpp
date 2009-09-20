#include "qtlenrosteritemdelegate.hpp"

void QTlenRosterItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{
     if (qVariantCanConvert<QTlenRosterItem>(index.data())) {
         QTlenRosterItem rosterItem = qVariantValue<QTlenRosterItem>(index.data());
         bool checked = false;
         if (option.state & QStyle::State_Selected)
         {
             painter->fillRect(option.rect, option.palette.highlight());
             checked = true;
         }
         rosterItem.setHeight(rosterItem.paint(painter, option.rect, option.palette, checked));
     } else {
         QStyledItemDelegate::paint(painter, option, index);
     }
}

QSize QTlenRosterItemDelegate::sizeHint(const QStyleOptionViewItem &option,
                              const QModelIndex &index) const
{
     if (qVariantCanConvert<QTlenRosterItem>(index.data())) {
         QTlenRosterItem rosterItem = qVariantValue<QTlenRosterItem>(index.data());
         return rosterItem.sizeHint(option, tree);
     } else {
         return QStyledItemDelegate::sizeHint(option, index);
     }
}

