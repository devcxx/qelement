#ifndef LINEPROGRESS_H
#define LINEPROGRESS_H

#include "el_global.h"
#include <QProgressBar>

EL_BEGIN_NAMESPACE

// 线形进度条
class EL_EXPORT LineProgress : public QProgressBar {
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

    LineProgress(QWidget* parent = nullptr);
    // 设置进度条当前状态
    void setStatus(Status status);

protected:
    void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;
    QColor getColor();

private:
    Status _status = Default;
};

EL_END_NAMESPACE

#endif // LINEPROGRESS_H
