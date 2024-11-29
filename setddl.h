#ifndef SETDDL_H
#define SETDDL_H
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
#include <QSizePolicy>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QMessageBox>
#include <QTimer>
#include <QDebug>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QIcon>
#include <QListWidget>  // 用于显示任务条目
#include<QPainter>
#include<QPushButton>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QIcon>
#include <QSizePolicy>
#include <QDateTimeEdit>
#include <QDebug>


// 设置DDL的窗口类
class SetDDL : public QWidget {
    Q_OBJECT

public:
    explicit SetDDL(QWidget *parent = nullptr) ;
signals:
    void ddlSet(const QDateTime &ddl, const QDateTime &reminder, const QString &frequency);

private slots:
    void onSetTimeClicked() ;

    void onSaveClicked() ;

private:
    QDateTimeEdit *dateTimeEdit = nullptr;
    QDateTimeEdit *remindTimeEdit = nullptr;
    QComboBox *frequencyComboBox;
};
#endif // SETDDL_H
