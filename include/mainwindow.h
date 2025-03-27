#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// 前向声明
class QStandardItemModel;

// 命名空间Ui包含所有由uic自动生成的界面类
namespace Ui
{
    class MainWindow;
}

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
    void setupModels();
    void setupConnections();

    // UI指针，由Qt自动管理
    Ui::MainWindow *ui;

    // Model(s)
    QStandardItemModel *m_listModel;
    QStandardItemModel *m_tableModel;
};

#endif // MAINWINDOW_H