#ifndef CONFIGURABLEWINDOW_H
#define CONFIGURABLEWINDOW_H


#include<QWidget>
#include <QDateTimeEdit>
#include<QComboBox>
#include"task.h"
class ConfigurableWindow : public QWidget
{
    Q_OBJECT // 宏，支持Qt的元对象系统

public:
    ConfigurableWindow();

private slots:
     void onDdlSet(const QDateTime &ddl, const  QDateTime &reminder, const QString &frequency) ;
     void onSaveAllClicked();

private:
     QDateTime ddl;
     QDateTime reminder;
     QString frequency;
     QLineEdit *detailsInput;
         QLineEdit *tagsInput;
         QComboBox *priorityComboBox;
 signals:
         void taskCreated(Task *newTask);
};
#endif // CONFIGURABLEWINDOW_H
