#include "showwidget.h"
#include <QHBoxLayout>

ShowWidget::ShowWidget(QWidget *parent)
    : QWidget(parent)
{
    m_img = new QImage;
    m_imageLabel = new QLabel;
    m_text = new QTextEdit;
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(m_imageLabel);
    mainLayout->addWidget(m_text);
}
