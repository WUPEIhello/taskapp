#include "task.h"
Task::Task(const QString &details, const QString &tags, const QString &priority, const DDL &ddl)
    : m_details(details), m_tags(tags), m_priority(priority)
{
    this->m_ddl.setDdl(ddl.getDdl());
    this->m_ddl.setRemind(ddl.getRemind());
    this->m_ddl.setFrequency(ddl.getFrequency());
}
QString Task::getDetails() const { return m_details; }
QString Task::getTags() const { return m_tags; }
QString Task::getPriority() const { return m_priority; }
QDateTime Task::getDdl() const { return m_ddl.getDdl(); }

void Task::setDetails(const QString &details) { m_details = details; }
void Task::setTags(const QString &tags) { m_tags = tags; }
void Task::setPriority(const QString &priority) { m_priority = priority; }
void Task::setDdl(const QDateTime &ddl) {  this->m_ddl.setDdl(ddl); }
