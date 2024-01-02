#ifndef EL_AWESOME_H
#define EL_AWESOME_H

#include "QtAwesome.h"
#include "el_global.h"

EL_BEGIN_NAMESPACE

class Awesome : public fa::QtAwesome {
    Q_OBJECT
public:
    static Awesome& instance()
    {
        static Awesome _instance;
        return _instance;
    }
};

EL_END_NAMESPACE

#define qAwesome (static_cast<el::Awesome*>(&el::Awesome::instance()))

#endif // EL_AWESOME_H
