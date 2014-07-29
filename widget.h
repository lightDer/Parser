#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QLayout>
#include <QPushButton>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    QTextEdit* sourceEdit;
    QTextEdit* destinationEdit;

    QPushButton* openFileBtn;
    QPushButton* saveFileBtn;
    QPushButton* parseBtn;

private slots:
    void openFileClicked();
    void saveFileClicked();
    void parseClicked();
    void clearEdit();

};

#endif // WIDGET_H
