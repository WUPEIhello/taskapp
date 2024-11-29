#include "taskcategory.h"

TaskCategory::TaskCategory()
{

}

// 按优先级分类任务
void TaskCategory::categorizeByPriority(QVector<Task*> *sortedTasks,QVector<Task*> *taskList) {
    for (const QString &priority : {"High", "Medium", "Low", "No"}) {
        for (Task *task : *taskList) {
            if (task->getPriority() == priority) {
                sortedTasks->append(task);
            }
        }
    }

}

// 按标签分类任务
void TaskCategory::categorizeByTags(QVector<Task*> *sortedTasks,QVector<Task*> *taskList) {
    QMap<QString, QVector<Task*>> tagGroups;
    for (Task *task : *taskList) {
        QString tag = task->getTags();
        tagGroups[tag].append(task);
    }


    for (auto it = tagGroups.begin(); it != tagGroups.end(); ++it) {
        sortedTasks->append(it.value());
    }

}
