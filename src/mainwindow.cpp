#include "mainwindow.h"
#include "ui_mainwindow.h" // 自动生成的UI头文件
#include <QStandardItemModel>
#include <QMessageBox>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // 设置UI
    ui->setupUi(this);

    // 初始化数据模型
    setupModels();

    // 连接信号和槽
    setupConnections();

    // 初始状态
    statusBar()->showMessage(tr("Application started"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupModels()
{
    // 配置列表模型
    m_listModel = new QStandardItemModel(0, 1, this);
    ui->listView->setModel(m_listModel);

    // 添加列表示例数据
    for (int i = 0; i < 5; ++i)
    {
        QStandardItem *item = new QStandardItem(QString("Item %1").arg(i + 1));
        m_listModel->appendRow(item);
    }

    // 配置表格模型
    m_tableModel = new QStandardItemModel(0, 3, this);
    m_tableModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    m_tableModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    m_tableModel->setHeaderData(2, Qt::Horizontal, tr("Value"));
    ui->tableView->setModel(m_tableModel);

    // 添加表格示例数据
    for (int row = 0; row < 3; ++row)
    {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QString::number(row + 1)));
        items.append(new QStandardItem(QString("Item %1").arg(row + 1)));
        items.append(new QStandardItem(QString::number(row * 10 + 5)));
        m_tableModel->appendRow(items);
    }
}

void MainWindow::setupConnections()
{
    // 连接标签页切换信号
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);

    // 连接Basic标签页的按钮
    connect(ui->clickButton, &QPushButton::clicked, this, &MainWindow::onButtonClicked);

    // 连接List标签页的按钮
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::onAddItemClicked);
    connect(ui->removeButton, &QPushButton::clicked, this, &MainWindow::onRemoveItemClicked);

    // 连接Table标签页的按钮
    connect(ui->addRowButton, &QPushButton::clicked, this, &MainWindow::onAddRowClicked);
    connect(ui->removeRowButton, &QPushButton::clicked, this, &MainWindow::onRemoveRowClicked);

    // 连接菜单操作
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::onExitAction);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::onAboutAction);
}

void MainWindow::onButtonClicked()
{
    ui->label->setText("Button clicked! Welcome to Qt with Designer!");
    QMessageBox::information(this, "Button Clicked", "The button was clicked successfully!");
    statusBar()->showMessage(tr("Button clicked at %1").arg(QDateTime::currentDateTime().toString("hh:mm:ss")), 2000);
}

void MainWindow::onAddItemClicked()
{
    QString text = ui->itemEdit->text().trimmed();
    if (!text.isEmpty())
    {
        QStandardItem *item = new QStandardItem(text);
        m_listModel->appendRow(item);
        ui->itemEdit->clear();
        statusBar()->showMessage(tr("Added: %1").arg(text), 2000);
    }
    else
    {
        QMessageBox::warning(this, tr("Add Item"), tr("Please enter item text."));
    }
}

void MainWindow::onRemoveItemClicked()
{
    QModelIndexList selection = ui->listView->selectionModel()->selectedIndexes();
    if (!selection.isEmpty())
    {
        QModelIndex index = selection.first();
        QString text = m_listModel->data(index).toString();
        m_listModel->removeRow(index.row());
        statusBar()->showMessage(tr("Removed: %1").arg(text), 2000);
    }
    else
    {
        QMessageBox::warning(this, tr("Remove Item"), tr("Please select an item to remove."));
    }
}

void MainWindow::onTabChanged(int index)
{
    QString tabName = ui->tabWidget->tabText(index);
    statusBar()->showMessage(tr("Switched to %1").arg(tabName), 2000);
}

void MainWindow::onAddRowClicked()
{
    int row = m_tableModel->rowCount();
    QList<QStandardItem *> items;
    items.append(new QStandardItem(QString::number(row + 1)));
    items.append(new QStandardItem(QString("New Item %1").arg(row + 1)));
    items.append(new QStandardItem(QString::number(row * 10)));

    m_tableModel->appendRow(items);
    statusBar()->showMessage(tr("Added new row %1").arg(row + 1), 2000);
}

void MainWindow::onRemoveRowClicked()
{
    QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();
    if (!selection.isEmpty())
    {
        int row = selection.at(0).row();
        m_tableModel->removeRow(row);
        statusBar()->showMessage(tr("Removed row %1").arg(row + 1), 2000);
    }
    else
    {
        QMessageBox::warning(this, tr("Remove Row"), tr("Please select a row to remove."));
    }
}

void MainWindow::onAboutAction()
{
    QMessageBox::about(this, tr("About Qt Designer Demo"),
                       tr("This is a demonstration of Qt with Designer UI files.\n\n"
                          "Created as an example of using Qt Designer with CMake."));
}

void MainWindow::onExitAction()
{
    close();
}