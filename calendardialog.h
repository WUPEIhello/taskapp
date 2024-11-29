#ifndef CALENDARDIALOG_H
#define CALENDARDIALOG_H
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
#include <QComboBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QIcon>
#include <QListWidget>  // 用于显示任务条目



class CalendarDialog : public QWidget
{

    Q_OBJECT // 宏，支持Qt的元对象系统，包括信号和槽

public:
    explicit CalendarDialog(QWidget *parent = nullptr);

signals:
    void ddlSet(const QDateTime &ddl); // 声明一个信号，当DDL时间被设置时发出

private slots:
    void onSaveClicked() ;

private:
    QDateTimeEdit *dateTimeEdit; // 日期时间编辑器的成员变量
};
#endif // CALENDARDIALOG_H
