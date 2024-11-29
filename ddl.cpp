#include "ddl.h"

DDL::DDL(const QDateTime &ddl, const QDateTime &remind, QString frequency, QObject *parent)
    : QObject(parent), ddl(ddl), remind(remind), frequency(frequency)
{
    if (remind < QDateTime::currentDateTime()) {
        throw std::invalid_argument("Remind time must be in the future.");
    }
    if (remind >= ddl) {
        throw std::invalid_argument("Remind time must be before the DDL.");
    }
}
DDL::DDL()
{

}
void DDL::startReminders()
{
    qint64 interval = QDateTime::currentDateTime().msecsTo(remind);
    if (interval <= 0) {
        throw std::invalid_argument("Reminder time must be in the future.");
    }

    // 使用 QTimer 来根据提醒时间设置定时器
    createReminderTimer(remind, interval);

    // 根据频率，创建多个定时器，但都要确保提醒时间在 DDL 之前
    if (frequency == QString("Daily")) {
        for (int i = 1; i < 5; ++i) {
            QDateTime nextReminder = remind.addDays(i);
            if (nextReminder >= ddl) {
                break;  // 如果下一个提醒时间超过 DDL，停止创建定时器
            }
            interval = QDateTime::currentDateTime().msecsTo(nextReminder);
            createReminderTimer(nextReminder, interval);
        }
    } else if (frequency ==QString(" Weekly")) {
        for (int i = 1; i < 5; ++i) {
            QDateTime nextReminder = remind.addDays(7*i);
            if (nextReminder >= ddl) {
                break;  // 如果下一个提醒时间超过 DDL，停止创建定时器
            }
            interval = QDateTime::currentDateTime().msecsTo(nextReminder);
            createReminderTimer(nextReminder, interval);
        }
    } else if (frequency == QString("Monthly")) {
        for (int i = 1; i < 5; ++i) {
            QDateTime nextReminder = remind.addMonths(i);
            if (nextReminder >= ddl) {
                break;  // 如果下一个提醒时间超过 DDL，停止创建定时器
            }
            interval = QDateTime::currentDateTime().msecsTo(nextReminder);
            createReminderTimer(nextReminder, interval);
        }
    } else if (frequency == QString("Minute")) {
        for (int i = 1; i < 5; ++i) {
            QDateTime nextReminder = remind.addSecs(60 * i);  // 每分钟递增
            if (nextReminder >= ddl) {
                break;  // 如果下一个提醒时间超过 DDL，停止创建定时器
            }
            interval = QDateTime::currentDateTime().msecsTo(nextReminder);
            createReminderTimer(nextReminder, interval);
        }
    } else if (frequency == QString("Hourly")) {
        for (int i = 1; i < 5; ++i) {
            QDateTime nextReminder = remind.addSecs(3600 * i);  // 每小时递增
            if (nextReminder >= ddl) {
                break;  // 如果下一个提醒时间超过 DDL，停止创建定时器
            }
            interval = QDateTime::currentDateTime().msecsTo(nextReminder);
            createReminderTimer(nextReminder, interval);
        }
    }
}
QDateTime DDL::getDdl() const
{
    return ddl;
}
QDateTime DDL::getRemind() const {
    return remind;
}
QString DDL::getFrequency() const {
    return this->frequency;
}

void DDL::setDdl(const QDateTime &ddl) {
    this->ddl=ddl;
}
void DDL::setRemind(const QDateTime &remind) {
    this->remind=remind;
}
void DDL::setFrequency(const QString &frequency){
    this->frequency=frequency;
}


void DDL::createReminderTimer(const QDateTime &reminderTime, qint64 interval)
{
    QTimer *timer = new QTimer(this);
    timer->setSingleShot(true); // 一次性定时器
    connect(timer, &QTimer::timeout, [reminderTime]() {
        QMessageBox::information(nullptr, "Task Reminder",
                                    QString("The task is due at %1").arg(reminderTime.toString("yyyy-MM-dd HH:mm:ss")));
    });
    timer->start(interval);
}
