#ifndef EL_TOOLTIP_H
#define EL_TOOLTIP_H

#include "el_global.h"
#include <QTooltip>

EL_BEGIN_NAMESPACE

class Tooltip : public QToolTip {
    Q_OBJECT
public:
    enum Effect {
        Dark, // 深色
        Light, // 浅色
    };
    Q_ENUM(Effect)

    Tooltip(Effect effect = Dark, QWidget* parent = nullptr);
};

EL_END_NAMESPACE

#endif // EL_TOOLTIP_H
