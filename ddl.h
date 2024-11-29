#ifndef DDL_H
#define DDL_H

#include <QDateTime>
#include <QTimer>
#include <QObject>
#include <stdexcept>
#include<QMessageBox>
class DDL : public QObject
{
    Q_OBJECT
public:
    DDL();
    DDL(const QDateTime &ddl, const QDateTime &remind, QString frequency, QObject *parent = nullptr);
    void startReminders();
    QDateTime getDdl() const ;
    QDateTime getRemind() const ;
    QString getFrequency() const ;

    void setDdl(const QDateTime &ddl) ;
    void setRemind(const QDateTime &remind) ;
    void setFrequency(const QString &frequency);
private:
    void createReminderTimer(const QDateTime &reminderTime, qint64 interval);
private:
    QDateTime ddl;  // 任务的DDL时间
    QDateTime remind;  // 提醒时间
    QString frequency;  // 提醒频率
};

#endif // DDL_H
