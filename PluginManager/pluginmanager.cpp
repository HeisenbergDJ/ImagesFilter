#include "pluginmanager.h"
#include <QDir>
#include <QApplication>
#include <QPluginLoader>


PluginManager* PluginManager::m_s_singleton = nullptr;


PluginManager::PluginManager()
{
	m_s_singleton = this;
	QDir pluginDir = QApplication::applicationDirPath() + "/../plugins";
	auto pluginList = pluginDir.entryList(QDir::Files);
	for (const auto& pluginName : pluginList)
	{
		QString path = pluginDir.absoluteFilePath(pluginName);
		QPluginLoader pluginLoader(pluginDir.absoluteFilePath(pluginName));
		QObject* pPlugin = pluginLoader.instance();
		QString error = pluginLoader.errorString();
		if (pPlugin) {
			ExternToolPlugin* pModelPlugin = qobject_cast<ExternToolPlugin*>(pPlugin);
			if (pModelPlugin) {
				m_ToolPluginMap.insert(pModelPlugin->key(), pModelPlugin);
			}
		}
	}
}

PluginManager::~PluginManager()
{
	for (auto iter = m_ToolPluginMap.cbegin(); iter != m_ToolPluginMap.cend(); ++iter)
	{
		iter.value()->deleteLater();
	}
}

ExternToolPlugin* PluginManager::getExternToolPlugin(const QString& key)
{
	auto iter = m_ToolPluginMap.find(key);
	if (iter != m_ToolPluginMap.end()) {
		return iter.value();
	}
	else {
		return nullptr;
	}
}
