#ifndef EL_GLOBAL_H
#define EL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(EL_LIBRARY)
#define EL_EXPORT Q_DECL_EXPORT
#else
#define EL_EXPORT
#endif

#define EL_BEGIN_NAMESPACE namespace el {
#define EL_END_NAMESPACE }


#endif // EL_GLOBAL_H
