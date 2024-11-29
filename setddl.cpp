#include "setddl.h"

 SetDDL::SetDDL(QWidget *parent ) : QWidget(parent)
 {
    setWindowTitle("Set DDL");
    resize(350, 300);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 设置具体时间条目
    QHBoxLayout *timeLayout = new QHBoxLayout;
    QLabel *timeLabel = new QLabel("Set DateTime:", this);


    timeLayout->addWidget(timeLabel);
    dateTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime(),this);
    dateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    dateTimeEdit->setCalendarPopup(true);
    timeLayout->addWidget(dateTimeEdit);
    mainLayout->addLayout(timeLayout);

    // 点击按钮时设置日期时间
   // connect(setTimeButton, &QPushButton::clicked, this, &SetDDL::onSetTimeClicked);

    // 设置开始提醒条目
    QHBoxLayout *reminderLayout = new QHBoxLayout;
    QLabel *reminderLabel = new QLabel("Set Reminder:", this);
    remindTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime(),this);
    remindTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    remindTimeEdit->setCalendarPopup(true);
    reminderLayout->addWidget(reminderLabel);
    reminderLayout->addWidget(remindTimeEdit);
    mainLayout->addLayout(reminderLayout);

    // 设置重复频率条目
    QHBoxLayout *frequencyLayout = new QHBoxLayout;
    QLabel *frequencyLabel = new QLabel("Repeat Frequency:", this);
    frequencyComboBox = new QComboBox(this);
    frequencyComboBox->addItem("None");
    frequencyComboBox->addItem("Hourly");
    frequencyComboBox->addItem("Minute");
    frequencyComboBox->addItem("Daily");
    frequencyComboBox->addItem("Weekly");
    frequencyComboBox->addItem("Monthly");
    frequencyLayout->addWidget(frequencyLabel);
    frequencyLayout->addWidget(frequencyComboBox);
    mainLayout->addLayout(frequencyLayout);

    // 创建保存按钮
    QPushButton *saveButton = new QPushButton("Save", this);
    mainLayout->addWidget(saveButton);
    mainLayout->setAlignment(saveButton, Qt::AlignLeft); // 左下角对齐

    // 连接保存按钮的信号槽
    connect(saveButton, &QPushButton::clicked, this, &SetDDL::onSaveClicked);
}
 void SetDDL::onSetTimeClicked() {
     // 弹出日期时间选择器
     dateTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime());
     dateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
     dateTimeEdit->setCalendarPopup(true);
     dateTimeEdit->show();
 }
 void SetDDL::onSaveClicked() {
     if (!dateTimeEdit) {
         QMessageBox::warning(this, "No Time Set", "Please set a specific date and time.");
         return;
     }

     // 获取设置的时间
     QDateTime ddl = dateTimeEdit->dateTime();

     // 获取提醒和重复频率的选择
     QDateTime reminder = remindTimeEdit->dateTime();
     QString frequency = frequencyComboBox->currentText();

     if (ddl <= QDateTime::currentDateTime()) {
         QMessageBox::warning(this, "Invalid DDL", "The selected time must be in the future.");
         return;
     }

     // 发送 DDL 设置的信号
     emit ddlSet(ddl, reminder, frequency);
     close(); // 关闭窗口
 }
