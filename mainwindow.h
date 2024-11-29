#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QVector>
#include <QMainWindow>
#include <QListWidget>
#include<QComboBox>
#include"QPushButton"
#include"task.h"
#include"taskmanage.h"
#include"taskcategory.h"
#include"tasktimeline.h"
#include"setting.h"
class MainWindow : public  QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     void paintEvent(QPaintEvent *event) ;
protected:
     void mousePressEvent(QMouseEvent *event) ;
private slots:
    void onAddTaskClicked() ;
    //void onDdlSet(const QDateTime &ddl, const QString &reminder, const QString &frequency) ;
    //void onOpen();
    void onTaskCreated(Task *newTask);
    void onUpClicked();
    void onDownClicked();
    void onTimelineView() ;
    void onTaskEdit() ;
    void onBackClicked() ;
    void onTaskCategory() ;
    void openSettingsWindow();
private:
    QVector<Task*> *sortedTaskList;  // 临时存储排序后的任务列表
    QVector<Task*> prioritySortedTasks;  // 按优先级分类后的任务
    QVector<Task*> tagSortedTasks;  // 按标签分类后的任务
    int currentTaskIndex;  // 当前任务数组中的起始索引
    QPushButton *backButton;  // Back按钮
    bool isEditing; // 用于标识是否处于编辑模式
    bool isClassifying;
    bool classifyByPriority;
    TaskManager *taskManager;
    TaskCategory *taskCategory;
    TaskTimeline *taskTimeline;
    Setting *settingWindow;
};

#endif // MAINWINDOW_H
