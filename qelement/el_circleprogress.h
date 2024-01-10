#ifndef EL_CIRCLEPROGRESS_H
#define EL_CIRCLEPROGRESS_H

#include "el_global.h"
#include <QWidget>

EL_BEGIN_NAMESPACE

// 环形进度条
class EL_EXPORT CircleProgress : public QWidget {
    Q_OBJECT
public:
    // 进度条状态
    enum Status {
        Default,
        Success,
        Warning,
        Exception
    };
    Q_ENUM(Status)

    explicit CircleProgress(QWidget* parent = nullptr);
    void setPercent(int percent);
    // 设置进度条当前状态
    void setStatus(Status status);

protected:
    void paintEvent(QPaintEvent*);
    QSize sizeHint() const;
    QColor getColor();

private:
    int _percent = 0;
    int _rotateAngle = 0;
    Status _status = Default;
};

EL_END_NAMESPACE

#endif // EL_CIRCLEPROGRESS_H
