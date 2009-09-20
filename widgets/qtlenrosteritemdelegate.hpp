#ifndef QTLENROSTERITEMDELEGATE_HPP
#define QTLENROSTERITEMDELEGATE_HPP
#include <QtGui>
#include "qtlenrosteritem.hpp"
class QTlenRosterItemDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    QTlenRosterItemDelegate(QWidget *parent = 0) : QStyledItemDelegate(parent) {tree = parent;}
    QWidget * tree;
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
        const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option,
        const QModelIndex &index) const;

};

#endif // QTLENROSTERITEMDELEGATE_HPP
