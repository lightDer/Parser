#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <QStringList>
#include <QRegExp>

class Parser
{
public:
    Parser() { setPattern("(1\\d{10}|\\d{1,3}-\\d{6,})"); }
    Parser(const QString s) { setPattern(s); }

    QStringList parse(const QString source);
    void setPattern(const QString s) { pattern = s; }

private:
    QString pattern;
};

#endif // PARSER_H
