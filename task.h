#ifndef TASK_H
#define TASK_H

#include<QString>
#include<QDateTime>
#include"ddl.h"
class Task {
public:
    Task(const QString &details, const QString &tags, const QString &priority, const DDL &ddl);

    QString getDetails() const ;
    QString getTags() const ;
    QString getPriority() const ;
    QDateTime getDdl() const ;

    void setDetails(const QString &details) ;
    void setTags(const QString &tags) ;
    void setPriority(const QString &priority) ;
    void setDdl(const QDateTime &ddl) ;

private:
    QString m_details;
    QString m_tags;
    QString m_priority;
    DDL m_ddl;  // 任务的ddl时间
};

#endif // TASK_H
