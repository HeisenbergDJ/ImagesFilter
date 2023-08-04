#include "ImagesFilter.h"
#include "pluginmanager.h"


ImagesFilter::ImagesFilter(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    //重置窗口
    resize(600, 400);
    //读取菜单栏配置文件

    ZLogger::getInstance()->log("读取菜单栏配置文件");
    if (!readMenuConfig(qApp->applicationDirPath() + "/config/custombarconfig.xml")) {
        ZLogger::getInstance()->log("读取菜单栏配置文件失败");
    }
    ZLogger::getInstance()->log("读取菜单栏配置文件完毕");


    //读取工具栏配置文件
    ZLogger::getInstance()->log("读取工具栏配置文件");
    readToolConfig(qApp->applicationDirPath() + "/config/custombarconfig.xml");
    ZLogger::getInstance()->log("读取工具栏配置文件完毕");

   

}

ImagesFilter::~ImagesFilter()
{
    ZLogger::getInstance()->closeLogFile();
}

void ImagesFilter::closeEvent(QCloseEvent* event)
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(u8"提示");
    msgBox.setText(u8"提示");
    msgBox.setIconPixmap(QPixmap(":/image/warning.png"));
    msgBox.setInformativeText(u8"是否退出？");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);

    msgBox.button(QMessageBox::Ok)->setText(u8"确定");
    msgBox.button(QMessageBox::Cancel)->setText(u8"取消");
    int ret = msgBox.exec();
    if (ret == QMessageBox::Ok) {
        ZLogger::getInstance()->log("关闭软件");
        event->accept();
    }
    else {
        ZLogger::getInstance()->log("取消关闭软件");
        event->ignore();
    }
}

bool ImagesFilter::readMenuConfig(const QString customBarConfigFilePath)
{
    QFile file(customBarConfigFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        string errorMsgstr = QStringLiteral("配置文件：%1\n无法打开").arg(customBarConfigFilePath).toLocal8Bit();
        ZLogger::getInstance()->log(errorMsgstr);
        return false;
    }
    QDomDocument doc;
    if (!doc.setContent(&file)) {
        // Handle XML parse error
        string errorMsgstr = QStringLiteral("配置文件：%1\n无法解析").arg(customBarConfigFilePath).toLocal8Bit();
        ZLogger::getInstance()->log(errorMsgstr);
        file.close();
        return false;
    }
    file.close();
    QMenuBar* menuBar = ui.menuBar;
    QDomElement root = doc.documentElement();
    QDomNodeList menuNodes = root.elementsByTagName("Menu");
    for (int i = 0; i < menuNodes.size(); ++i) {
        QDomElement menuElement = menuNodes.at(i).toElement();
        QString menuTitle = menuElement.attribute("Title");
        QMenu* menu = menuBar->addMenu(menuTitle);
        parseConfig(menuElement, menu);
    }
    return true;
}

bool ImagesFilter::readToolConfig(const QString customBarConfigFilePath)
{
    ////工具栏，可以有多个
    //QToolBar* toolBar = new QToolBar(this);
    //this->addToolBar(toolBar);  // 将工具栏添加
    //this->addToolBar(Qt::LeftToolBarArea, toolBar);//令其默认出现在左边
    //this->addToolBar(Qt::RightToolBarArea, toolBar);
    ////设置允许的停靠范围
    //toolBar->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea);//不会让其停靠在上边，但会浮动
    ////设置浮动
    //toolBar->setFloatable(false);//禁止浮动
    ////设置移动
    //toolBar->setMovable(false);//禁止移动
    ////工具栏可设置内容
    //QAction* build_act = new QAction();
    //QAction* open_act = new QAction();
    //toolBar->addAction(build_act);//将新建菜单项添加进来，传入的是QAction指针
    //toolBar->addSeparator();//添加分割线
    //toolBar->addAction(open_act);//将打开项目添加进来
    //toolBar->addSeparator();
    //toolBar->addAction(QStringLiteral("其他"));//传入字符串
    ////工具栏添加控件
    //QPushButton* p = new QPushButton(this);
    //p->setText("自定义的按钮");
    //toolBar->addWidget(p);// 添加控件
    return true;

}

void ImagesFilter::parseConfig(const QDomElement& menuElement, QMenu* parentMenu)
{

    QDomElement childElement = menuElement.firstChildElement();
    while (!childElement.isNull())
    {
        QString tagName = childElement.tagName();
        if (tagName == "SubMenu")
        {
            QString subMenuTitle = childElement.attribute("Title");
            QMenu* subMenu = parentMenu->addMenu(subMenuTitle);
            parseConfig(childElement, subMenu);
        }
        else if (tagName == "SubMenuBarItem")
        {
            QString subMenuItemTitle = childElement.attribute("Title");
            QString libraryPath = childElement.attribute("LibraryPath");
            QString exeInvoke = childElement.attribute("ExeInvoke");
            QAction* subMenuItemAction = nullptr;
            if (!libraryPath.isEmpty()) {
                // Handle SubMenuBarItem with LibraryPath attribute
                subMenuItemAction = new QAction(subMenuItemTitle);
                // Connect the action to a slot that handles LibraryPath
                // You can implement this slot in your QMainWindow class
                QObject::connect(subMenuItemAction, &QAction::triggered, [=]() {
                    //IModelPlugin* pToolPlugin = CPluginManager::instance()->getModelPlugin(m_pProject->model().pluginKey);
                    // Handle libraryPath action here
                    // Example: QMainWindow::handleLibraryPath(libraryPath);
                    });
            }
            else if (!exeInvoke.isEmpty()) {
                // Handle SubMenuBarItem with ExeInvoke attribute
                subMenuItemAction = new QAction(subMenuItemTitle);
                // Connect the action to a slot that handles ExeInvoke
                // You can implement this slot in your QMainWindow class
                QObject::connect(subMenuItemAction, &QAction::triggered, [=]() {
                    // Handle exeInvoke action here
                    // Example: QMainWindow::handleExeInvoke(exeInvoke);
                    });
            }

            if (subMenuItemAction) {
                parentMenu->addAction(subMenuItemAction);
            }

        }
        childElement = childElement.nextSiblingElement();
    }
}
