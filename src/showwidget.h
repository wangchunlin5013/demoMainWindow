#ifndef SHOWWIDGET_H
#define SHOWWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QImage>

class ShowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ShowWidget(QWidget *parent = nullptr);

    QImage *m_img;
    QLabel *m_imageLabel;
    QTextEdit *m_text;
};

#endif // SHOWWIDGET_H
