#include "widget.h"
#include "parser.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("PARSER beta v 0.0.1");

    const int minEditWidth = 600;
    const int minEditHeight = minEditWidth*9 / 16;

    sourceEdit = new QTextEdit;
    sourceEdit->setMinimumWidth(minEditWidth);
    sourceEdit->setMinimumHeight(minEditHeight);
    sourceEdit->setAcceptRichText(false);

    destinationEdit = new QTextEdit;
    destinationEdit->setMinimumWidth(minEditWidth);
    destinationEdit->setMinimumWidth(minEditHeight);
    destinationEdit->setAcceptRichText(false);

    openFileBtn = new QPushButton(tr("Open file"));
    saveFileBtn = new QPushButton(tr("Save File"));
    parseBtn = new QPushButton(tr("Parse"));
    QPushButton *clearBtn = new QPushButton(tr("Clear"));

    connect(openFileBtn, SIGNAL(clicked()), this, SLOT(openFileClicked()));
    connect(saveFileBtn, SIGNAL(clicked()), this, SLOT(saveFileClicked()));
    connect(parseBtn, SIGNAL(clicked()), this, SLOT(parseClicked()));
    connect(clearBtn, SIGNAL(clicked()), this, SLOT(clearEdit()));

    QVBoxLayout *topR = new QVBoxLayout;
    topR->addWidget(openFileBtn);
    topR->addWidget(parseBtn);
    topR->addWidget(clearBtn);
    topR->addStretch();

    QHBoxLayout *top = new QHBoxLayout;
    top->addWidget(sourceEdit);
    top->addLayout(topR);

    QVBoxLayout *bottonR = new QVBoxLayout;
    bottonR->addWidget(saveFileBtn);
    bottonR->addStretch();

    QHBoxLayout *botton = new QHBoxLayout;
    botton->addWidget(destinationEdit);
    botton->addLayout(bottonR);

    QFrame *hr = new QFrame;
    hr->setFrameShape(QFrame::HLine);
    hr->setFrameShadow(QFrame::Sunken);

    QVBoxLayout *l = new QVBoxLayout;
    l->addLayout(top);
    l->addWidget(hr);
    l->addLayout(botton);
    setLayout(l);
}

Widget::~Widget()
{

}

void Widget::openFileClicked()
{
    QString fileName =
            QFileDialog::getOpenFileName(this, tr("Open File"),  "",
                                         "Text Files (*.txt)");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, tr("Error"), tr("open failed."),
                             QMessageBox::Ok);
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        sourceEdit->append(in.readLine());
    }
}

void Widget::saveFileClicked()
{
    QString fileName =
            QFileDialog::getSaveFileName(this, tr("Save File"), ""
                                         ".txt", "Text Files (*.txt)");

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, tr("Error"), tr("Create save file failed."),
                             QMessageBox::Ok);
        return;
    }

    QTextStream out(&file);
    out << destinationEdit->toPlainText();
}

void Widget::parseClicked()
{
    QString str = sourceEdit->toPlainText();
    if (str.isEmpty())
        return;

    QStringList line = str.split("\n");
    Parser parse;
    for (int i = 0; i < line.size(); ++i)
    {
        QStringList match;
        match << parse.parse(line.at(i));

        for (int j = 0; j < match.size(); ++j)
            destinationEdit->append(match.at(j));
    }

    if (destinationEdit->toPlainText().isEmpty())
    {
        QMessageBox::information(this, tr("Oops"), tr("There are no match patterns."),
                             QMessageBox::Ok);
    }
}

void Widget::clearEdit()
{
   sourceEdit->clear();
   destinationEdit->clear();
}
