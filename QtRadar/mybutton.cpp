#include "mybutton.h"
MyButton::MyButton(QWidget *parent) :
QPushButton(parent)
{
setFlat(true);
setStyleSheet(
"QPushButton {""color: blue;""background-color: rgba(255, 255, 255, 90)""}""QPushButton:pressed {""color: lime;""background-color: rgba(255, 255, 255, 50)""}""QPushButton:flat {""border: none; ""}");

QHBoxLayout *layout = new QHBoxLayout;
setLayout(layout);
label = new QLabel("LOOOOOOOOOOOOOOOOOONGGGGGGGGGGG TEXXXXXXXXXT",this);
label->setWordWrap(true);
layout->addWidget(label);

m_font = new QFont();

}

void MyButton::resizeEvent(QResizeEvent *event)
{
int pixelsHeight = this->size().height()/2;
if(pixelsHeight > 24) pixelsHeight = 24;
if(pixelsHeight < 8) pixelsHeight = 8;

m_font->setPixelSize(pixelsHeight);
label->setFont(*m_font);
}
