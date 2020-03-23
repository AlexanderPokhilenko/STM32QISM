#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QResizeEvent>

class MyButton : public QPushButton
{
    Q_OBJECT
    public:
    explicit MyButton(QWidget *parent = 0);

    signals:

    public slots:

    protected:
    void resizeEvent(QResizeEvent *event);

    private:
    QLabel * label;
    QFont *m_font;
};

#endif // MYBUTTON_H
