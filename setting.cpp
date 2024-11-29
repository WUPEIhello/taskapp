#include "setting.h"
#include <QLabel>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

Setting::Setting(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("设置");
    setFixedSize(300, 200);  // 设置固定大小

    // 创建布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 创建用户名和密码输入框
    QLabel *usernameLabel = new QLabel("用户名:", this);
    usernameEdit = new QLineEdit(this);
    QLabel *passwordLabel = new QLabel("密码:", this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);  // 密码框显示为*号

    // 创建保存按钮
    saveButton = new QPushButton("保存", this);

    // 布局安排
    QVBoxLayout *formLayout = new QVBoxLayout;
    formLayout->addWidget(usernameLabel);
    formLayout->addWidget(usernameEdit);
    formLayout->addWidget(passwordLabel);
    formLayout->addWidget(passwordEdit);

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(saveButton);

    // 合并布局
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);

    connect(saveButton, &QPushButton::clicked, this, &Setting::onSaveClicked);
}

Setting::~Setting()
{
}

void Setting::onSaveClicked()
{
    // 获取用户名和密码
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "用户名和密码不能为空！");
        return;
    }

    // 这里可以加入用户名密码保存到文件或其他操作
    QMessageBox::information(this, "设置", "用户名和密码保存成功！");

    // 关闭设置窗口
    accept();  // 关闭当前窗口并返回
}
