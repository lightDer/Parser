#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <QStringList>
#include <QRegExp>

class Parser
{
public:
    QStringList parse(const QString source);

private:
    QStringList matchPattern;

    void cellphone(const QString s);
    void landlinePhone(const QString s);
};

#endif // PARSER_H
