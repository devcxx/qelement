#ifndef INPUTNUMBER_H
#define INPUTNUMBER_H

#include "el_global.h"
#include <QLineEdit>

class QPushButton;

EL_BEGIN_NAMESPACE

// InputNumber 计数器
class EL_EXPORT InputNumber : public QLineEdit {
    Q_OBJECT
public:
    explicit InputNumber(int min, int max, QWidget* parent = nullptr);

protected:
    void resizeEvent(QResizeEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

signals:

private:
    QPushButton* _minusBtn;
    QPushButton* _plusBtn;
};

EL_END_NAMESPACE

#endif // INPUTNUMBER_H
