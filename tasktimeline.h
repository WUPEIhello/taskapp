#ifndef TASKTIMELINE_H
#define TASKTIMELINE_H

#include <QObject>
#include <QVector>
#include "task.h"

class TaskTimeline
{

public:
    explicit TaskTimeline();

    // 获取排序后的任务时间线
    void getTimelineSortedTasks(QVector<Task*> *taskList) ;
};

#endif // TASKTIMELINE_H
