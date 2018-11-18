#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QComboBox>
#include <QSpinBox>
#include <QToolBox>
#include <QToolBar>
#include <QFontComboBox>
#include <QToolButton>
#include <QTextCharFormat>

class ShowWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void createActions();
    void createMenus();
    void createTooBars();

    void loadFile(const QString &fileName);
    void mergeFormat(QTextCharFormat &format);

private:
    QMenu *m_fileMenu;
    QMenu *m_zoomMenu;
    QMenu *m_rotateMenu;
    QMenu *m_mirrorMenu;
    QImage *m_img;
    QString m_fileName;
    ShowWidget *m_showWidget;

    QAction *m_openFileAction;
    QAction *m_newFileAction;
    QAction *m_printTextAction;
    QAction *m_printImageAction;
    QAction *m_exitAction;
    QAction *m_copyAction;
    QAction *m_cutAction;
    QAction *m_pasteAction;
    QAction *m_aboutAction;
    QAction *m_zoomInAction;
    QAction *m_zoomOutAction;
    QAction *m_rotate90Action;
    QAction *m_rotate180Action;
    QAction *m_rotate270Action;
    QAction *m_mirrorVerticalAction;
    QAction *m_mirrorHorizontalAction;
    QAction *m_undoAction;
    QAction *m_redoAction;

    QToolBar *m_fileTool;
    QToolBar *m_zoomTool;
    QToolBar *m_rotateTool;
    QToolBar *m_mirrorTool;
    QToolBar *m_doTool;
};

#endif // MAINWINDOW_H
