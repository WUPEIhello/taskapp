#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

class Setting : public QDialog
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();

private slots:
    void onSaveClicked();  // 保存按钮点击槽函数

private:
    QLineEdit *usernameEdit;  // 用户名输入框
    QLineEdit *passwordEdit;  // 密码输入框
    QPushButton *saveButton;  // 保存按钮
};

#endif // SETTING_H
