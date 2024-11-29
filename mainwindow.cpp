#include "mainwindow.h"
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QDebug>
#include <QObject>
#include"createtaskwindow.h"
#include"setddl.h"
#include<QMouseEvent>
#include"task.h"
#include"edittask.h"
#include"setting.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    settingWindow(new Setting(this)), // 初始化 settingWindow 指针
    sortedTaskList(nullptr),
    currentTaskIndex(0),
    isEditing(false),
    isClassifying(false),
    classifyByPriority(false),
    taskManager(new TaskManager(new QVector<Task*>())),
    taskCategory(new TaskCategory()),
    taskTimeline(new TaskTimeline())
{
    setWindowTitle("Main Window");
    setFixedSize(600, 400);
    this->setStyleSheet("background-color: white;");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 创建菜单栏
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *fileMenu = menuBar->addMenu("Start");
    QAction *exitAction = new QAction("Exit", this);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    fileMenu->addAction(exitAction);

    QMenu *taskMenu = menuBar->addMenu("Task Management");
    QAction *timelineAction = new QAction(QIcon(":/res/sort.png"), "Timeline View", this);
    connect(timelineAction, &QAction::triggered, this, &MainWindow::onTimelineView);
    taskMenu->addAction(timelineAction);

    QAction *taskEditAction = new QAction(QIcon(":/res/edit.png"), "Task Edit", this);
    connect(taskEditAction, &QAction::triggered, this, &MainWindow::onTaskEdit);
    taskMenu->addAction(taskEditAction);

    QAction *taskCategoryAction = new QAction(QIcon(":/res/category.png"), "Task Category", this);
    connect(taskCategoryAction, &QAction::triggered, this, &MainWindow::onTaskCategory);
    taskMenu->addAction(taskCategoryAction);

    QMenu *settingsMenu = menuBar->addMenu("Setting");
    QAction *settingsAction = new QAction(tr("用户名与密码"), this);
    connect(settingsAction, &QAction::triggered, this, &MainWindow::openSettingsWindow);
    settingsMenu->addAction(settingsAction);

    mainLayout->setMenuBar(menuBar);


    // 向上按钮
    QPushButton *upButton = new QPushButton("Λ", this);
    connect(upButton, &QPushButton::clicked, this, &MainWindow::onUpClicked);
    upButton->setGeometry(260, 30, 80, 20);

    // 向下按钮
    QPushButton *downButton = new QPushButton("V", this);
    connect(downButton, &QPushButton::clicked, this, &MainWindow::onDownClicked);
    downButton->setGeometry(260, 341, 80, 20);

    // 添加新建任务按钮
    QPushButton *addButton = new QPushButton("Add Task", this);
    connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddTaskClicked);
    addButton->setGeometry(500, 340, 100, 60);

    backButton = new QPushButton("Back", this);
    connect(backButton, &QPushButton::clicked, this, &MainWindow::onBackClicked);
    backButton->hide();
    backButton->setGeometry(0, 380, 40, 20);

    // 应用样式表到所有按钮（除了添加任务按钮，因为它没有被添加到布局中）
    QList<QPushButton*> buttons = {upButton, downButton, backButton};
    QString buttonStyleSheet = R"(
        QPushButton {
            background-color: white;
            border: none;
            color: #555555;
        }
        QPushButton:hover {
            background-color: lightgray;
        }
        QPushButton:pressed {
            background-color: gray;
        }
    )";
    for (QPushButton* button : buttons) {
        button->setStyleSheet(buttonStyleSheet);
    }

}
// 绘制任务矩形

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setBrush(QBrush(Qt::lightGray));

    int yPos = 50;  // Y坐标开始位置
    int visibleTasks = 6;  // 最大显示任务数

    QVector<Task*> *displayList = nullptr;

    // 判断是否进入任务分类模式
    if (isClassifying) {
        // 根据分类方式来选择不同的显示列表
        if (classifyByPriority) {
            // 按优先级分类任务
            prioritySortedTasks.clear();  // 清空之前的排序结果
            taskCategory->categorizeByPriority(&prioritySortedTasks, taskManager->getTaskList());
            displayList = &prioritySortedTasks;  // 设置按优先级分类显示的任务列表
        } else {
            // 按标签分类任务
            // 注意：这里应该使用 categorizeByTag 而不是 categorizeByPriority
            tagSortedTasks.clear();  // 清空之前的排序结果
            taskCategory->categorizeByTags(&tagSortedTasks, taskManager->getTaskList());
            displayList = &tagSortedTasks;  // 设置按标签分类显示的任务列表
        }

        // 绘制分类后的任务列表
        if (displayList) {
            for (int i = currentTaskIndex; i < displayList->size() && i < currentTaskIndex + visibleTasks; ++i) {
                Task *task = displayList->at(i);

                QColor rectColor;
                if (classifyByPriority) {
                    // 设置矩形的颜色，根据任务优先级
                    if (task->getPriority() == "High") {
                        rectColor = Qt::red;
                    } else if (task->getPriority() == "Medium") {
                        rectColor = Qt::yellow;
                    } else if (task->getPriority() == "Low") {
                        rectColor = Qt::green;
                    } else if (task->getPriority() == "No") {
                        rectColor = Qt::lightGray;
                    }
                } else {
                    // 如果不是按优先级分类，则使用默认颜色
                    rectColor = Qt::lightGray;
                }

                painter.setBrush(QBrush(rectColor));
                QRect taskRect(50, yPos, 500, 40);
                painter.drawRect(taskRect);

                QString text;
                if (classifyByPriority) {
                    text = task->getDetails() + " - " + task->getPriority();
                } else {
                    text = task->getDetails() + " - " + task->getTags();
                }

                painter.drawText(taskRect, Qt::AlignCenter, text);
                yPos += 50;  // 为下一个任务留空间
            }
        }
    } else {
        // 普通模式
        displayList = sortedTaskList ? sortedTaskList : taskManager->getTaskList();
        for (int i = currentTaskIndex; i < displayList->size() && i < currentTaskIndex + visibleTasks; ++i) {
            Task *task = displayList->at(i);
            QRect taskRect(50, yPos, 500, 40);
            painter.drawRect(taskRect);
            painter.drawText(taskRect, Qt::AlignCenter, task->getDetails());
            yPos += 50;
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    QPoint clickPos = event->pos(); // 获取鼠标点击位置

    int yPos = 50; // 起始 Y 坐标
    int visibleTasks = 6;
    QVector<Task*> *displayList = nullptr;

    // 判断分类方式选择对应的任务列表
    if (isClassifying) {
        // 任务分类模式
        if (classifyByPriority) {
            displayList = &prioritySortedTasks;
        } else {
            displayList = &tagSortedTasks;
        }
    } else {
        // 普通模式
        displayList = sortedTaskList ? sortedTaskList : taskManager->getTaskList();
    }

    if (displayList) {
        for (int i = currentTaskIndex; i < displayList->size() && i < currentTaskIndex + visibleTasks; ++i) {
            QRect taskRect(50, yPos, 500, 40);

            if (taskRect.contains(clickPos)) { // 检测点击是否在任务矩形内
                Task *clickedTask = displayList->at(i);

                if (isEditing) {
                    // 编辑模式：显示编辑或删除按钮
                    QMenu taskMenu;
                    QAction *editAction = new QAction("Edit", this);
                    QAction *deleteAction = new QAction("Delete", this);

                    connect(editAction, &QAction::triggered, this, [this, clickedTask]() {
                        // 编辑任务
                        EditTask dialog(clickedTask, this);
                        if (dialog.exec() == QDialog::Accepted) {
                            update(); // 刷新任务界面
                        }
                    });

                    connect(deleteAction, &QAction::triggered, this, [this, clickedTask]() {
                        // 删除任务
                        taskManager->removeTask(clickedTask);
                        update();
                    });

                    taskMenu.addAction(editAction);
                    taskMenu.addAction(deleteAction);
                    taskMenu.exec(event->globalPos()); // 显示右键菜单
                } else {
                    // 普通模式：显示任务详情
                    QMessageBox::information(this, "Task Details",
                        QString("Details: %1\nPriority: %2\nTags: %3\nDeadline: %4")
                            .arg(clickedTask->getDetails())
                            .arg(clickedTask->getPriority())
                            .arg(clickedTask->getTags())
                            .arg(clickedTask->getDdl().toString()));
                }
                break; // 找到任务后退出循环
            }

            yPos += 50; // 下一个任务矩形的 Y 坐标
        }
    }
}

void MainWindow::onAddTaskClicked() {
    ConfigurableWindow *configWindow = new ConfigurableWindow();
    connect(configWindow, &ConfigurableWindow::taskCreated, this, &MainWindow::onTaskCreated);
    configWindow->show();
    // configWindow->setAttribute(Qt::WA_DeleteOnClose);  // 关闭时自动删除,不能删除，因为包含了定时器类，他需要一直在后台跑
}



void MainWindow::onTaskCreated(Task* newTask) {
    // 将新任务添加到任务数组
    taskManager->addTask(newTask);
    // 重新绘制窗口
    update();
}

void MainWindow::onUpClicked() {
    // 向上滚动，显示前面的任务
    if (currentTaskIndex > 0) {
        currentTaskIndex--;
        update();  // 更新窗口绘制
    }
}

void MainWindow::onDownClicked() {
    // 向下滚动，显示后面的任务
    if (currentTaskIndex + 6 < taskManager->getTaskList()->size()) {
        currentTaskIndex++;
        update();  // 更新窗口绘制
    }
}

void MainWindow::onTimelineView() {
    // 创建一个排序后的任务列表，对时间线一览任务进行绘画
    sortedTaskList = new QVector<Task*>(*(taskManager->getTaskList()));  // 复制原始任务列表
    taskTimeline->getTimelineSortedTasks(sortedTaskList);
    currentTaskIndex = 0;  // 重置当前显示任务的索引
    update();  // 刷新绘制
    // 显示“Back”按钮
    backButton->show();
}

void MainWindow::onBackClicked() {
    // 还原为原始任务列表
    isClassifying = false;  // 退出分类模式
    delete sortedTaskList;  // 使用delete来释放动态分配的内存
    sortedTaskList = nullptr;
    isEditing = false;   // 返回普通显示模式
    currentTaskIndex = 0;
    update();  // 刷新绘制
    // 隐藏“Back”按钮
    backButton->hide();
}

void MainWindow::onTaskEdit() {
    // 编辑任务的逻辑，显示任务列表并点击任务进行编辑或删除
    isEditing = true;    // 进入编辑模式
    currentTaskIndex = 0;
    backButton->show();  // 显示“Back”按钮
    update();            // 刷新界面
}

void MainWindow::onTaskCategory() {
    // 创建任务分类菜单，选择按标签分类或按优先级分类
    currentTaskIndex = 0;
    QMenu categoryMenu(this);
    QAction* byPriorityAction = new QAction("By Priority", this);
    QAction* byTagsAction = new QAction("By Tags", this);

    connect(byPriorityAction, &QAction::triggered, this, [this]() {
        classifyByPriority = true;
        isClassifying = true;
        backButton->show();  // 显示Back按钮
        qDebug() << "Priority Category";
        update();
    });

    connect(byTagsAction, &QAction::triggered, this, [this]() {
        classifyByPriority = false;
        isClassifying = true;
        backButton->show();  // 显示Back按钮
        update();
    });

    categoryMenu.addAction(byPriorityAction);
    categoryMenu.addAction(byTagsAction);
    categoryMenu.exec(QCursor::pos());  // 弹出分类选择菜单
}

void MainWindow::openSettingsWindow() {
    settingWindow->exec();  // 打开设置窗口并阻塞主窗口
}
MainWindow::~MainWindow()
{

}
