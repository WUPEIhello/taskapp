#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QObject>
#include <QVector>
#include "task.h"

class TaskManager
{
public:
    explicit TaskManager(QVector<Task*> *taskList);

    // 添加任务
    void addTask(Task *newTask);
    // 删除任务
    void removeTask(Task *taskToRemove);

    // 获取任务列表
    QVector<Task*>* getTaskList() ;



private:
    QVector<Task*> *taskList;
};

#endif // TASKMANAGER_H
