#ifndef EL_SELECT_H
#define EL_SELECT_H

#include "el_global.h"

#include <QComboBox>

EL_BEGIN_NAMESPACE

// Select 选择器
class Select : public QComboBox {
    Q_OBJECT
public:
    Select(QWidget* parent = nullptr);

protected:
    QSize sizeHint() const;
    void showPopup();
};

EL_END_NAMESPACE

#endif // EL_SELECT_H
