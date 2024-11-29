#include "taskmanage.h"

TaskManager::TaskManager(QVector<Task*> *taskList)
    :taskList(taskList) {

}

// 添加任务
void TaskManager::addTask(Task *newTask) {
    taskList->append(newTask);
}

// 删除任务
void TaskManager::removeTask(Task *taskToRemove) {
    taskList->removeAll(taskToRemove);
    delete taskToRemove;
}

// 获取任务列表
QVector<Task*>* TaskManager::getTaskList() {
    return taskList;
}

