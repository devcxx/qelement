#ifndef EL_CARD_H
#define EL_CARD_H

#include "el_global.h"
#include <QAbstractButton>

EL_BEGIN_NAMESPACE

// Card 卡片
class EL_EXPORT Card : public QAbstractButton {
    Q_OBJECT
public:
    Card(const QIcon& icon, const QString& title, const QString& content, QWidget* parent = nullptr);

protected:
    QSize sizeHint() const Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent* event);
    void iconToGrayscale(QPixmap* pm);

private:
    QString _content;
};

EL_END_NAMESPACE

#endif // EL_CARD_H
