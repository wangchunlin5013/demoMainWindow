#include "mainwindow.h"
#include "showwidget.h"
#include <QApplication>
#include <QFileDialog>
#include <QTextStream>
#include <QtPrintSupport/QPrintDialog>
#include <QPainter>
#include <QPrinter>
#include <QImage>
#include <QMatrix>

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
    m_openFileAction = new QAction(QIcon("images/open.png"),tr("open"),this);
    m_openFileAction->setShortcut(QString("Ctrl+O"));
    m_openFileAction->setStatusTip(tr("open one file"));
    connect(m_openFileAction, SIGNAL(triggered(bool)), this, SLOT(showOpenFile()));

    m_newFileAction = new QAction(QIcon("images/new.png"),tr("new"),this);
    m_newFileAction->setShortcut(QString("Ctrl+N"));
    m_newFileAction->setStatusTip(tr("new a file"));
    connect(m_newFileAction, SIGNAL(triggered(bool)), this, SLOT(showNewFile()));

    m_exitAction = new QAction(QIcon("images/exit.png"),tr("exit"),this);
    m_exitAction->setShortcut(QString("Ctrl+Q"));
    m_exitAction->setStatusTip(tr("exit this program"));
    connect(m_exitAction,SIGNAL(triggered(bool)),this,SLOT(close()));

    m_copyAction = new QAction(QIcon("images/copy.png"),tr("copy"),this);
    m_copyAction->setShortcut(QString("Ctrl+C"));
    m_copyAction->setStatusTip(tr("copy file"));
    connect(m_copyAction,SIGNAL(triggered(bool)),m_showWidget->m_text,SLOT(copy()));

    m_cutAction = new QAction(QIcon("images/cut.png"),tr("cut"),this);
    m_cutAction->setShortcut(QString("Ctrl+X"));
    m_cutAction->setStatusTip(tr("cut this file"));
    connect(m_cutAction,SIGNAL(triggered(bool)),m_showWidget->m_text,SLOT(cut()));

    m_pasteAction = new QAction(QIcon("images/paste.png"),tr("paste"),this);
    m_pasteAction->setShortcut(QString("Ctrl+V"));
    m_pasteAction->setStatusTip(tr("paste this file"));
    connect(m_pasteAction,SIGNAL(triggered(bool)),m_showWidget->m_text,SLOT(paste()));

    m_aboutAction = new QAction(tr("about"),this);
    connect(m_aboutAction,SIGNAL(triggered(bool)),this,SLOT(QApplication::aboutQt()));

    m_printTextAction = new QAction(QIcon("images/printText.png"),tr("printtext"),this);
    m_printTextAction->setStatusTip(tr("print a file"));
    connect(m_printTextAction, SIGNAL(triggered(bool)), this, SLOT(showPrintText()));

    m_printImageAction = new QAction(QIcon("images/printImage.png"),tr("printimage"),this);
    m_printImageAction->setStatusTip(tr("print a image"));
    connect(m_printImageAction, SIGNAL(triggered(bool)), this, SLOT(showPrintImage()));

    m_zoomInAction = new QAction(QIcon("images/zoomin.png"),tr("zoomin"),this);
    m_zoomInAction->setStatusTip(tr("zoom in image"));
    connect(m_zoomInAction, SIGNAL(triggered(bool)), this, SLOT(showZoomIn()));

    m_zoomOutAction = new QAction(QIcon("images/zoomout.png"),tr("zoomout"),this);
    m_zoomOutAction->setStatusTip(tr("zoom out image"));
    connect(m_zoomOutAction, SIGNAL(triggered(bool)), this, SLOT(showZoomOut()));

    m_rotate90Action = new QAction(QIcon("images/rotate90.png"),tr("rotate90"),this);
    m_rotate90Action->setStatusTip(tr("zoom image 90"));
    connect(m_rotate90Action, SIGNAL(triggered(bool)), this, SLOT(showRotate90()));

    m_rotate180Action = new QAction(QIcon("images/rotate180.png"),tr("rotate180"),this);
    m_rotate180Action->setStatusTip(tr("zoom image 180"));
    connect(m_rotate180Action, SIGNAL(triggered(bool)), this, SLOT(showRotate180()));

    m_rotate270Action = new QAction(QIcon("images/rotate270.png"),tr("rotate270"),this);
    m_rotate270Action->setStatusTip(tr("zoom image 270"));
    connect(m_rotate270Action, SIGNAL(triggered(bool)), this, SLOT(showRotate270()));

    m_mirrorVerticalAction = new QAction(QIcon("images/mirrorVertical.png"),tr("mirrorVertical"),this);
    m_mirrorVerticalAction->setStatusTip(tr("mirror image vertical"));
    connect(m_mirrorVerticalAction, SIGNAL(triggered(bool)), this, SLOT(showMirrorVertical()));

    m_mirrorHorizontalAction = new QAction(QIcon("images/mirrorHorizontal.png"),tr("mirrorHorizontal"),this);
    m_mirrorHorizontalAction->setStatusTip(tr("mirror image horizontal"));
    connect(m_mirrorHorizontalAction, SIGNAL(triggered(bool)), this, SLOT(showMirrorHorizontal()));

    m_undoAction = new QAction(QIcon("images/undo.png"),tr("undo"),this);
    m_redoAction = new QAction(QIcon("images/redo.png"),tr("redo"),this);
    connect(m_undoAction,SIGNAL(triggered(bool)),m_showWidget->m_text,SLOT(undo()));
    connect(m_redoAction,SIGNAL(triggered(bool)),m_showWidget->m_text,SLOT(redo()));
}

void MainWindow::createMenus()
{
    m_fileMenu = menuBar()->addMenu(tr("file"));
    m_fileMenu->addAction(m_openFileAction);
    m_fileMenu->addAction(m_newFileAction);
    m_fileMenu->addAction(m_printTextAction);
    m_fileMenu->addAction(m_printImageAction);
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_exitAction);

    m_zoomMenu = menuBar()->addMenu(tr("edit"));
    m_zoomMenu->addAction(m_copyAction);
    m_zoomMenu->addAction(m_cutAction);
    m_zoomMenu->addAction(m_pasteAction);
    m_zoomMenu->addAction(m_aboutAction);
    m_zoomMenu->addSeparator();
    m_zoomMenu->addAction(m_zoomInAction);
    m_zoomMenu->addAction(m_zoomOutAction);

    m_rotateMenu = menuBar()->addMenu(tr("rotate"));
    m_rotateMenu->addActions(QList<QAction*>()<<m_rotate90Action<<m_rotate180Action<<m_rotate270Action);

    m_mirrorMenu = menuBar()->addMenu(tr("mirror"));
    m_mirrorMenu->addActions(QList<QAction*>()<<m_mirrorVerticalAction<<m_mirrorHorizontalAction);
}

void MainWindow::createTooBars()
{
    m_fileTool = addToolBar(tr("file"));
    m_fileTool->addAction(m_openFileAction);
    m_fileTool->addAction(m_newFileAction);
    m_fileTool->addAction(m_printTextAction);
    m_fileTool->addAction(m_printImageAction);

    m_zoomTool = addToolBar(tr("edit"));
    m_zoomTool->addAction(m_copyAction);
    m_zoomTool->addAction(m_cutAction);
    m_zoomTool->addAction(m_pasteAction);
    m_zoomTool->addSeparator();
    m_zoomTool->addAction(m_zoomInAction);
    m_zoomTool->addAction(m_zoomOutAction);

    m_rotateTool = addToolBar(tr("rotate"));
    m_rotateTool->addActions(QList<QAction*>()<<m_rotate90Action<<m_rotate180Action<<m_rotate270Action);

    m_doTool = addToolBar(tr("doEdit"));
    m_doTool->addActions(QList<QAction*>()<<m_undoAction<<m_redoAction);
}

void MainWindow::loadFile(const QString &fileName)
{
//    printf("file name:%s\n",fileName.data());
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream textStream(&file);
        while(!textStream.atEnd())
        {
            m_showWidget->m_text->append(textStream.readLine());
//            printf("read line\n");
        }
//        printf("end\n");
    }
}

void MainWindow::mergeFormat(QTextCharFormat &format)
{

}

void MainWindow::showNewFile()
{
    MainWindow *newMainWindow = new MainWindow;
    newMainWindow->show();
}

void MainWindow::showOpenFile()
{
    m_fileName = QFileDialog::getOpenFileName(this);
    if(!m_fileName.isEmpty())
    {
        if(m_showWidget->m_text->document()->isEmpty())
        {
            loadFile(m_fileName);
        }
        else
        {
            MainWindow *newMainWindow = new MainWindow;
            newMainWindow->show();
            newMainWindow->loadFile(m_fileName);
        }
    }
}

void MainWindow::showPrintText()
{
    QPrinter printer;
    QPrintDialog printDialog(&printer,this);
    if(printDialog.exec())
    {
        QTextDocument *doc = m_showWidget->m_text->document();
        doc->print(&printer);
    }
}

void MainWindow::showPrintImage()
{
    QPrinter printer;
    QPrintDialog printDialog(&printer,this);
    if(printDialog.exec())
    {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = m_img->size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(m_img->rect());
        painter.drawImage(0, 0, *m_img);
    }
}

void MainWindow::showZoomIn()
{
    if(m_img->isNull())
        return;
    QMatrix martix;
    martix = martix.scale(2,2);
    *m_img = m_img->transformed(martix);
    m_showWidget->m_imageLabel->setPixmap(QPixmap::fromImage(*m_img));
}

void MainWindow::showZoomOut()
{
    if(m_img->isNull())
        return;
    QMatrix martix;
    martix = martix.scale(0.5, 0.5);
    *m_img = m_img->transformed(martix);
    m_showWidget->m_imageLabel->setPixmap(QPixmap::fromImage(*m_img));
}

void MainWindow::showRotate90()
{
    if(m_img->isNull())
        return;
    QMatrix matrix;
    matrix.rotate(90);
    *m_img = m_img->transformed(matrix);
    m_showWidget->m_imageLabel->setPixmap(QPixmap::fromImage(*m_img));
}

void MainWindow::showRotate180()
{
    if(m_img->isNull())
        return;
    QMatrix matrix;
    matrix.rotate(180);
    *m_img = m_img->transformed(matrix);
    m_showWidget->m_imageLabel->setPixmap(QPixmap::fromImage(*m_img));
}

void MainWindow::showRotate270()
{
    if(m_img->isNull())
        return;
    QMatrix matrix;
    matrix.rotate(270);
    *m_img = m_img->transformed(matrix);
    m_showWidget->m_imageLabel->setPixmap(QPixmap::fromImage(*m_img));
}

void MainWindow::showMirrorVertical()
{
    if(m_img->isNull())
        return;
    *m_img = m_img->mirrored(false, true);
    m_showWidget->m_imageLabel->setPixmap(QPixmap::fromImage(*m_img));
}

void MainWindow::showMirrorHorizontal()
{
    if(m_img->isNull())
        return;
    *m_img = m_img->mirrored(true, false);
    m_showWidget->m_imageLabel->setPixmap(QPixmap::fromImage(*m_img));
}
