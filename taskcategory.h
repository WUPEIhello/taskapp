#ifndef TASKCATEGORY_H
#define TASKCATEGORY_H

#include <QObject>
#include <QVector>
#include<QMap>
#include "task.h"

class TaskCategory
{


public:
    explicit TaskCategory();

    // 按优先级分类任务
    void categorizeByPriority(QVector<Task*> *sortedTasks,QVector<Task*> *taskList);

    // 按标签分类任务
   void categorizeByTags(QVector<Task*> *sortedTasks,QVector<Task*> *taskList);

};

#endif // TASKCATEGORY_H
