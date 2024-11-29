#include "edittask.h"


EditTask::EditTask(Task *task, QWidget *parent) : QDialog(parent), m_task(task) {
    setWindowTitle("Edit Task");
    setFixedSize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(this);

    // 输入框：Details
    detailsInput = new QLineEdit(task->getDetails(), this);
    layout->addWidget(new QLabel("Details:"));
    layout->addWidget(detailsInput);

    // 输入框：Tags
    tagsInput = new QLineEdit(task->getTags(), this);
    layout->addWidget(new QLabel("Tags:"));
    layout->addWidget(tagsInput);

    // 下拉框：Priority
    priorityComboBox = new QComboBox(this);
    priorityComboBox->addItem("Low");
    priorityComboBox->addItem("Medium");
    priorityComboBox->addItem("High");
    priorityComboBox->setCurrentText(task->getPriority());
    layout->addWidget(new QLabel("Priority:"));
    layout->addWidget(priorityComboBox);

    // 日期时间：DDL
    ddlInput = new QDateTimeEdit(task->getDdl(), this);
    layout->addWidget(new QLabel("DDL:"));
    layout->addWidget(ddlInput);

    // 保存按钮
    QPushButton *saveButton = new QPushButton("Save", this);
    connect(saveButton, &QPushButton::clicked, this, &EditTask::onSaveClicked);
    layout->addWidget(saveButton);
}
void EditTask::onSaveClicked() {
    // 更新任务信息
    m_task->setDetails(detailsInput->text());
    m_task->setTags(tagsInput->text());
    m_task->setPriority(priorityComboBox->currentText());
    m_task->setDdl(ddlInput->dateTime());

    // 关闭编辑窗口
    accept();
}
