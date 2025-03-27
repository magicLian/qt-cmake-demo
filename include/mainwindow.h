#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLabel;
class QPushButton;
class QTabWidget;
class QListView;
class QTableView;
class QStandardItemModel;
class QLineEdit;
class QStatusBar;
class QMenu;
class QAction;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onButtonClicked();
    void onAddItemClicked();
    void onRemoveItemClicked();
    void onTabChanged(int index);
    void onAddRowClicked();
    void onRemoveRowClicked();
    void onAboutAction();
    void onExitAction();

private:
    void createMenus();
    void createTabWidgets();
    void createBasicTab();
    void createListTab();
    void createTableTab();
    void createStatusBar();

    // Main widgets
    QTabWidget *m_tabWidget;
    QStatusBar *m_statusBar;

    // Menu items
    QMenu *m_fileMenu;
    QMenu *m_helpMenu;
    QAction *m_exitAction;
    QAction *m_aboutAction;

    // Basic tab widgets
    QLabel *m_label;
    QPushButton *m_button;

    // List tab widgets
    QListView *m_listView;
    QStandardItemModel *m_listModel;
    QLineEdit *m_itemEdit;
    QPushButton *m_addButton;
    QPushButton *m_removeButton;

    // Table tab widgets
    QTableView *m_tableView;
    QStandardItemModel *m_tableModel;
    QPushButton *m_addRowButton;
    QPushButton *m_removeRowButton;
};

#endif // MAINWINDOW_H