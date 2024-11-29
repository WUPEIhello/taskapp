#include "calendardialog.h"

 CalendarDialog::CalendarDialog( QWidget *parent  )
{
    // 构造函数，parent参数默认为nullptr
        setWindowTitle("Set Date and Time"); // 设置窗口标题
        resize(300, 200); // 设置窗口大小

        QVBoxLayout *mainLayout = new QVBoxLayout(this); // 创建一个垂直布局，并将其设置为当前窗口的布局

        // 创建日期时间编辑器
        dateTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime(), this); // 创建一个QDateTimeEdit对象，显示当前日期和时间
        dateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss"); // 设置日期时间的显示格式
        dateTimeEdit->setCalendarPopup(true); // 启用日历弹出
        mainLayout->addWidget(dateTimeEdit); // 将日期时间编辑器添加到布局中

        // 创建保存按钮
        QPushButton *saveButton = new QPushButton("Save", this); // 创建一个按钮，显示文本为"Save"
        mainLayout->addWidget(saveButton); // 将按钮添加到布局中
        mainLayout->setAlignment(saveButton, Qt::AlignLeft); // 设置按钮的对齐方式为左对齐（在此布局中为左下角）

        // 连接保存按钮的信号槽
        connect(saveButton, &QPushButton::clicked, this, &CalendarDialog::onSaveClicked); // 当按钮被点击时，调用onSaveClicked槽函数

}
 void CalendarDialog::onSaveClicked() { // 保存按钮的槽函数
     QDateTime selectedDateTime = dateTimeEdit->dateTime(); // 获取选中的日期时间
     if (selectedDateTime <= QDateTime::currentDateTime()) { // 如果选中的日期时间不在未来
         QMessageBox::warning(this, "Invalid DDL", "The selected time must be in the future."); // 显示警告消息框
         return; // 返回，不继续执行
     }

     qDebug() << "Selected DateTime:" << selectedDateTime.toString("yyyy-MM-dd HH:mm:ss"); // 输出选中的日期时间到调试窗口
     emit ddlSet(selectedDateTime); // 发出DDL时间设置信号
     close(); // 关闭窗口
 }
