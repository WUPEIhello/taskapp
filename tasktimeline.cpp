#include "tasktimeline.h"

TaskTimeline::TaskTimeline(){

}


// 获取排序后的任务时间线
void  TaskTimeline::getTimelineSortedTasks(QVector<Task*> *taskList) {
    std::sort(taskList->begin(), taskList->end(), [](Task *a, Task *b) {
        return a->getDdl() < b->getDdl();
    });
}
