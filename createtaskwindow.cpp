#include "createtaskwindow.h"
#include "setddl.h"
#include "task.h"
#include "ddl.h"

ConfigurableWindow::ConfigurableWindow()
{
    setWindowTitle("Configurable Window");
    resize(400, 300);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 设置菜单栏下的各项配置

    // 添加条目：Details
    {
        QHBoxLayout *detailsLayout = new QHBoxLayout;
        QLabel *detailsIcon = new QLabel;
        detailsIcon->setPixmap(QPixmap(":/res/detail2.png").scaled(24, 24, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        QLabel *detailsLabel = new QLabel("Details:");
        detailsLabel->setMinimumWidth(0);
        detailsLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        detailsInput = new QLineEdit;

        detailsLayout->addWidget(detailsIcon);
        detailsLayout->addWidget(detailsLabel);
        detailsLayout->addWidget(detailsInput);
        mainLayout->addLayout(detailsLayout);
    }

    // 添加条目：Tags
    {
        QHBoxLayout *tagsLayout = new QHBoxLayout;
        QLabel *tagsIcon = new QLabel;
        tagsIcon->setPixmap(QPixmap(":/res/tag.png").scaled(24, 24, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        QLabel *tagsLabel = new QLabel("Tags:");
        tagsLabel->setMinimumWidth(0);
        tagsLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        tagsInput = new QLineEdit;

        tagsLayout->addWidget(tagsIcon);
        tagsLayout->addWidget(tagsLabel);
        tagsLayout->addWidget(tagsInput);
        mainLayout->addLayout(tagsLayout);
    }

    // 添加条目：Priority
    {
        QHBoxLayout *priorityLayout = new QHBoxLayout;
        QLabel *priorityIcon = new QLabel;
        priorityIcon->setPixmap(QPixmap(":/res/priority1.png").scaled(24, 24));

        QLabel *priorityLabel = new QLabel("Priority:");
        priorityLabel->setMinimumWidth(0);
        priorityLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        priorityComboBox = new QComboBox;
        priorityComboBox->addItem("No");
        priorityComboBox->addItem("Low");
        priorityComboBox->addItem("Medium");
        priorityComboBox->addItem("High");

        priorityLayout->addWidget(priorityIcon);
        priorityLayout->addWidget(priorityLabel);
        priorityLayout->addWidget(priorityComboBox);
        mainLayout->addLayout(priorityLayout);
    }

    // 添加条目：Share
    {
        QHBoxLayout *shareLayout = new QHBoxLayout;
        QLabel *shareIcon = new QLabel;
        shareIcon->setPixmap(QPixmap(":/res/share.png").scaled(24, 24, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        QLabel *shareLabel = new QLabel("Share:");
        shareLabel->setMinimumWidth(0);
        shareLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        QPushButton *shareButton = new QPushButton("Share Now");

        shareLayout->addWidget(shareIcon);
        shareLayout->addWidget(shareLabel);
        shareLayout->addWidget(shareButton);
        mainLayout->addLayout(shareLayout);
    }

    // 添加条目：设置DDL
    {
        QHBoxLayout *ddlLayout = new QHBoxLayout;
        QLabel *ddlIcon = new QLabel;
        ddlIcon->setPixmap(QPixmap(":/res/ddl.png").scaled(24, 24, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        QLabel *ddlLabel = new QLabel("Set DDL:");
        ddlLabel->setMinimumWidth(0);
        ddlLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        QPushButton *ddlButton = new QPushButton("Set DDL");

        ddlLayout->addWidget(ddlIcon);
        ddlLayout->addWidget(ddlLabel);
        ddlLayout->addWidget(ddlButton);
        mainLayout->addLayout(ddlLayout);

        // 连接DDL按钮的信号槽
        connect(ddlButton, &QPushButton::clicked, [this]() {
            SetDDL *setDdlDialog = new SetDDL;
            connect(setDdlDialog, &SetDDL::ddlSet, this, &ConfigurableWindow::onDdlSet);
            setDdlDialog->setAttribute(Qt::WA_DeleteOnClose); // 关闭时需要自动删除来回收所有资源
            setDdlDialog->show();
        });
    }

    // 添加保存按钮
    {
        QPushButton *saveButton = new QPushButton("Save All");
        mainLayout->addWidget(saveButton);
        mainLayout->setAlignment(saveButton, Qt::AlignLeft);

        connect(saveButton, &QPushButton::clicked, this, &ConfigurableWindow::onSaveAllClicked);
    }

    // 占位条目
    mainLayout->addStretch();
}
void ConfigurableWindow::onDdlSet(const QDateTime &ddl, const QDateTime &reminder, const QString &frequency) {
    this->ddl = ddl;
    this->reminder = reminder;
    this->frequency = frequency;
    qDebug() << "DDL Temporarily Saved:" << ddl.toString("yyyy-MM-dd HH:mm:ss");
    qDebug() << "Reminder Temporarily Saved:" << reminder.toString("yyyy-MM-dd HH:mm:ss");
    qDebug() << "Frequency Temporarily Saved:" << frequency;
}

void ConfigurableWindow::onSaveAllClicked() {
    if (!reminder.isValid()) {
        QMessageBox::warning(this, "Incomplete Settings", "Please set a valid reminder.");
        return;
    }

    qint64 interval = QDateTime::currentDateTime().msecsTo(reminder);
    if (interval <= 0) {
        QMessageBox::warning(this, "Invalid DDL", "The selected time must be in the future.");
        return;
    }

    try {
        DDL *taskDDL = new DDL(this->ddl, reminder, this->frequency);
        taskDDL->startReminders();

        qDebug() << "Timer started for" << interval << "milliseconds.";
        qDebug() << "Reminder:" << reminder.toString("yyyy-MM-dd HH:mm:ss");
        qDebug() << "Frequency:" << frequency;

        QString details = detailsInput->text();
        QString tags = tagsInput->text();
        QString priority = priorityComboBox->currentText();

        Task *newTask = new Task(details, tags, priority, *taskDDL);
        emit taskCreated(newTask);
    } catch (const std::invalid_argument &e) {
        QMessageBox::warning(this, "Invalid Reminder", e.what());
        return;
    }

    close();
}

