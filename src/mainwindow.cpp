#include "mainwindow.h"
#include "showwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Easy Word"));
    m_showWidget = new ShowWidget(this);
    setCentralWidget(m_showWidget);

    createActions();
    createMenus();
    createTooBars();

    m_img = new QImage;
    if(m_img->load("images/image.png"))
    {
        m_showWidget->m_imageLabel->setPixmap(QPixmap::fromImage(*m_img));
    }
}

MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{

}

void MainWindow::createMenus()
{

}

void MainWindow::createTooBars()
{

}

void MainWindow::loadFile(const QString &fileName)
{

}

void MainWindow::mergeFormat(QTextCharFormat &format)
{

}
