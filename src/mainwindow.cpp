#include "mainwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QWidget>
#include <QApplication>
#include <QMessageBox>
#include <QListView>
#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QLineEdit>
#include <QStatusBar>
#include <QDateTime>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_tabWidget(nullptr),
      m_statusBar(nullptr),
      m_fileMenu(nullptr),
      m_helpMenu(nullptr),
      m_exitAction(nullptr),
      m_aboutAction(nullptr),
      m_label(nullptr),
      m_button(nullptr),
      m_listView(nullptr),
      m_listModel(nullptr),
      m_itemEdit(nullptr),
      m_addButton(nullptr),
      m_removeButton(nullptr),
      m_tableView(nullptr),
      m_tableModel(nullptr),
      m_addRowButton(nullptr),
      m_removeRowButton(nullptr)
{
    // Set window title
    setWindowTitle("Qt CMake Demo");

    // Create menus
    createMenus();

    // Create status bar
    createStatusBar();

    // Create the main tab widget
    createTabWidgets();

    // Set window size
    resize(800, 500);
}

MainWindow::~MainWindow()
{
    // Qt will handle deletion of child widgets
}

void MainWindow::createMenus()
{
    // File menu
    m_fileMenu = menuBar()->addMenu(tr("&File"));

    m_exitAction = new QAction(tr("E&xit"), this);
    m_exitAction->setShortcut(tr("Ctrl+Q"));
    connect(m_exitAction, &QAction::triggered, this, &MainWindow::onExitAction);
    m_fileMenu->addAction(m_exitAction);

    // Help menu
    m_helpMenu = menuBar()->addMenu(tr("&Help"));

    m_aboutAction = new QAction(tr("&About"), this);
    connect(m_aboutAction, &QAction::triggered, this, &MainWindow::onAboutAction);
    m_helpMenu->addAction(m_aboutAction);
}

void MainWindow::createStatusBar()
{
    m_statusBar = statusBar();
    m_statusBar->showMessage(tr("Ready"));
}

void MainWindow::createTabWidgets()
{
    m_tabWidget = new QTabWidget(this);
    connect(m_tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);

    // Create tabs
    createBasicTab();
    createListTab();
    createTableTab();

    // Set as central widget
    setCentralWidget(m_tabWidget);

    // Show initial status
    m_statusBar->showMessage(tr("Application started"));
}

void MainWindow::createBasicTab()
{
    QWidget *tab1 = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(tab1);

    m_label = new QLabel("Hello, Qt with CMake!", tab1);
    m_button = new QPushButton("Click Me", tab1);

    connect(m_button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);

    layout->addWidget(m_label);
    layout->addWidget(m_button);
    layout->addStretch();

    m_tabWidget->addTab(tab1, "Basic Tab");
}

void MainWindow::createListTab()
{
    QWidget *tab2 = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(tab2);

    // List view
    m_listView = new QListView(tab2);
    m_listModel = new QStandardItemModel(0, 1, this);
    m_listView->setModel(m_listModel);

    // Add some sample items
    for (int i = 0; i < 5; ++i)
    {
        QStandardItem *item = new QStandardItem(QString("Item %1").arg(i + 1));
        m_listModel->appendRow(item);
    }

    // Input field and buttons
    QHBoxLayout *inputLayout = new QHBoxLayout();

    m_itemEdit = new QLineEdit(tab2);
    m_itemEdit->setPlaceholderText(tr("Enter new item..."));

    m_addButton = new QPushButton(tr("Add"), tab2);
    m_removeButton = new QPushButton(tr("Remove"), tab2);

    connect(m_addButton, &QPushButton::clicked, this, &MainWindow::onAddItemClicked);
    connect(m_removeButton, &QPushButton::clicked, this, &MainWindow::onRemoveItemClicked);

    inputLayout->addWidget(m_itemEdit);
    inputLayout->addWidget(m_addButton);
    inputLayout->addWidget(m_removeButton);

    // Add widgets to main layout
    mainLayout->addWidget(m_listView);
    mainLayout->addLayout(inputLayout);

    m_tabWidget->addTab(tab2, "List Tab");
}

void MainWindow::createTableTab()
{
    QWidget *tab3 = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(tab3);

    // Table view
    m_tableView = new QTableView(tab3);
    m_tableModel = new QStandardItemModel(0, 3, this);

    // Set headers
    m_tableModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    m_tableModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    m_tableModel->setHeaderData(2, Qt::Horizontal, tr("Value"));

    m_tableView->setModel(m_tableModel);
    m_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Add some sample data
    for (int row = 0; row < 3; ++row)
    {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QString::number(row + 1)));
        items.append(new QStandardItem(QString("Item %1").arg(row + 1)));
        items.append(new QStandardItem(QString::number(row * 10 + 5)));
        m_tableModel->appendRow(items);
    }

    // Buttons for the table
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    m_addRowButton = new QPushButton(tr("Add Row"), tab3);
    m_removeRowButton = new QPushButton(tr("Remove Row"), tab3);

    connect(m_addRowButton, &QPushButton::clicked, this, &MainWindow::onAddRowClicked);
    connect(m_removeRowButton, &QPushButton::clicked, this, &MainWindow::onRemoveRowClicked);

    buttonLayout->addWidget(m_addRowButton);
    buttonLayout->addWidget(m_removeRowButton);
    buttonLayout->addStretch();

    // Add widgets to main layout
    mainLayout->addWidget(m_tableView);
    mainLayout->addLayout(buttonLayout);

    m_tabWidget->addTab(tab3, "Table Tab");
}

void MainWindow::onButtonClicked()
{
    m_label->setText("Button clicked! Welcome to Qt with CMake!");
    QMessageBox::information(this, "Button Clicked", "The button was clicked successfully!");
    m_statusBar->showMessage(tr("Button clicked at %1").arg(QDateTime::currentDateTime().toString("hh:mm:ss")), 2000);
}

void MainWindow::onAddItemClicked()
{
    QString text = m_itemEdit->text().trimmed();
    if (!text.isEmpty())
    {
        QStandardItem *item = new QStandardItem(text);
        m_listModel->appendRow(item);
        m_itemEdit->clear();
        m_statusBar->showMessage(tr("Added: %1").arg(text), 2000);
    }
    else
    {
        QMessageBox::warning(this, tr("Add Item"), tr("Please enter item text."));
    }
}

void MainWindow::onRemoveItemClicked()
{
    QModelIndexList selection = m_listView->selectionModel()->selectedIndexes();
    if (!selection.isEmpty())
    {
        QModelIndex index = selection.first();
        QString text = m_listModel->data(index).toString();
        m_listModel->removeRow(index.row());
        m_statusBar->showMessage(tr("Removed: %1").arg(text), 2000);
    }
    else
    {
        QMessageBox::warning(this, tr("Remove Item"), tr("Please select an item to remove."));
    }
}

void MainWindow::onTabChanged(int index)
{
    QString tabName = m_tabWidget->tabText(index);
    m_statusBar->showMessage(tr("Switched to %1").arg(tabName), 2000);
}

void MainWindow::onAddRowClicked()
{
    int row = m_tableModel->rowCount();
    QList<QStandardItem *> items;
    items.append(new QStandardItem(QString::number(row + 1)));
    items.append(new QStandardItem(QString("New Item %1").arg(row + 1)));
    items.append(new QStandardItem(QString::number(row * 10)));

    m_tableModel->appendRow(items);
    m_statusBar->showMessage(tr("Added new row %1").arg(row + 1), 2000);
}

void MainWindow::onRemoveRowClicked()
{
    QModelIndexList selection = m_tableView->selectionModel()->selectedRows();
    if (!selection.isEmpty())
    {
        int row = selection.at(0).row();
        m_tableModel->removeRow(row);
        m_statusBar->showMessage(tr("Removed row %1").arg(row + 1), 2000);
    }
    else
    {
        QMessageBox::warning(this, tr("Remove Row"), tr("Please select a row to remove."));
    }
}

void MainWindow::onAboutAction()
{
    QMessageBox::about(this, tr("About Qt CMake Demo"),
                       tr("This is a demonstration of Qt with CMake.\n\n"
                          "Created as an example of building a Qt application with CMake."));
}

void MainWindow::onExitAction()
{
    close();
}