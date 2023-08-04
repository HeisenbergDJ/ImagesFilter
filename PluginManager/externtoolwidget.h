#pragma once
#include <QWidget>

class ExternalToolWidget : public QWidget {
	
	Q_OBJECT

public:
	ExternalToolWidget(const QString &workDir, QWidget* parent = nullptr) : QWidget(parent), m_workDir(workDir) {}
	virtual ~ExternalToolWidget() {}
	void setWorkDir(const QString& workDir) { m_workDir = workDir; }
protected:
	QString m_workDir;
};