#pragma once
#include <QObject>
#include "externtoolwidget.h"

class ExternToolPlugin : public QObject{
	Q_OBJECT
public:
	ExternToolPlugin(QObject* parent = nullptr) : QObject(parent) {}
	virtual ~ExternToolPlugin() {}
	virtual QString key() = 0;
	virtual ExternalToolWidget* getExternalToolWidget(const QString& workDir, QWidget* parent = nullptr) = 0;
};

Q_DECLARE_INTERFACE(ExternToolPlugin,"org.zycdj.externtoolplugin")