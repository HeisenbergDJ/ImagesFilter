#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ImagesFilter.h"
#include "ZLogger.h"
#include <QMessageBox>
#include <QPushButton>
#include <QCloseEvent>
#include <QTextCodec>
#include <QDomDocument>

class ImagesFilter : public QMainWindow
{
    Q_OBJECT

public:
    ImagesFilter(QWidget *parent = nullptr);
    ~ImagesFilter();
    void closeEvent(QCloseEvent* event) override;

private:
    Ui::ImagesFilterClass ui;

    //读取菜单栏配置文件接口
    bool readMenuConfig(const QString customBarConfigFilePath);
    //读取工具栏配置文件接口
    bool readToolConfig(const QString customBarConfigFilePath);
    void parseConfig(const QDomElement& menuElement, QMenu* parentMenu);


};