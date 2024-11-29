#include <QApplication> // 引入QApplication类，它是Qt应用程序的基础
#include <QWidget> // 引入QWidget类，它是所有用户界面对象的基类
#include <QVBoxLayout> // 引入QVBoxLayout类，用于垂直布局
#include <QHBoxLayout> // 引入QHBoxLayout类，用于水平布局
#include <QLabel> // 引入QLabel类，用于显示文本或图片
#include <QPushButton> // 引入QPushButton类，用于创建按钮
#include <QDateTimeEdit> // 引入QDateTimeEdit类，用于编辑日期和时间
#include <QMessageBox> // 引入QMessageBox类，用于显示消息框
#include <QTimer> // 引入QTimer类，用于处理定时器
#include <QDebug> // 引入QDebug类，用于输出调试信息
#include"calendardialog.h"
#include"createtaskwindow.h"
#include"mainwindow.h"
// 日历窗口类


// 主窗口类


int main(int argc, char *argv[]) { // 应用程序的入口点
    QApplication app(argc, argv); // 创建QApplication对象，管理应用程序的控制流和主要设置

    MainWindow window; // 创建ConfigurableWindow对象
    window.show(); // 显示窗口

    return app.exec(); // 进入应用程序的主事件循环，等待直到exit()被调用
}


