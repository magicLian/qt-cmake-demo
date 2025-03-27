#include "mainwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_label(new QLabel("Hello, Qt with CMake!", this))
    , m_button(new QPushButton("Click Me", this))
{
    // Set window title
    setWindowTitle("Qt CMake Demo");
    
    // Create central widget and layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    
    // Add widgets to layout
    layout->addWidget(m_label);
    layout->addWidget(m_button);
    layout->addStretch();
    
    // Set central widget
    setCentralWidget(centralWidget);
    
    // Connect button signal to slot
    connect(m_button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    
    // Set window size
    resize(400, 300);
}

MainWindow::~MainWindow()
{
    // Qt will handle deletion of child widgets
}

void MainWindow::onButtonClicked()
{
    m_label->setText("Button clicked! Welcome to Qt with CMake!");
} 