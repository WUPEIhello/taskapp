#ifndef EDITTASKDIALOG_H
#define EDITTASKDIALOG_H

#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QDateTimeEdit>
#include"task.h"
#include"QLabel"
// 编辑任务对话框类：用于修改任务的细节
class EditTask : public QDialog {
    Q_OBJECT
public:
    explicit EditTask(Task *task, QWidget *parent = nullptr);

private slots:
    void onSaveClicked();
private:
    Task *m_task;
    QLineEdit *detailsInput;
    QLineEdit *tagsInput;
    QComboBox *priorityComboBox;
    QDateTimeEdit *ddlInput;
};
#endif // EDITTASKDIALOG_H
