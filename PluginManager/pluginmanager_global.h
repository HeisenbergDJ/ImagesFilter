#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(PLUGINMANAGER_LIB)
#  define PLUGINMANAGER_EXPORT Q_DECL_EXPORT
# else
#  define PLUGINMANAGER_EXPORT Q_DECL_IMPORT
# endif
#else
# define PLUGINMANAGER_EXPORT
#endif
