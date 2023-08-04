#pragma once

#include <QMap>
#include "pluginmanager_global.h"
#include "externtoolplugin.h"

class PLUGINMANAGER_EXPORT PluginManager
{
public:
    PluginManager();
    ~PluginManager();
    static PluginManager* instance() { return m_s_singleton; }
    ExternToolPlugin* getExternToolPlugin(const QString& key);


private:
    static PluginManager* m_s_singleton;
    QMap<QString, ExternToolPlugin*> m_ToolPluginMap;
};
