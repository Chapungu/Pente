#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "BoardWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_board = new BoardWidget(this);

    setCentralWidget(m_board);
    m_board->setMinimumSize(800, 800);
    m_board->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    m_board->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // set the size policy

    //centralWidget()->setMinimumSize(800,800);
}

MainWindow::~MainWindow()
{
    delete ui;
}
