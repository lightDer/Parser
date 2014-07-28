#include "parser.h"


QStringList Parser::parse(const QString source)
{
    matchPattern.clear();

    cellphone(source);
    landlinePhone(source);

    return matchPattern;
}

void Parser::cellphone(const QString s)
{
    QRegExp rx("1\\d{10}");
    int pos = 0;
    while ((pos = rx.indexIn(s, pos)) != -1)
    {
        matchPattern << rx.cap();
        pos += rx.matchedLength();
    }
}

void Parser::landlinePhone(const QString s)
{
    QRegExp rx("\\d{3}-\\d{8}");
    int pos = 0;
    while ((pos = rx.indexIn(s, pos)) != -1)
    {
        matchPattern << rx.cap().remove(QChar('-')).insert(0, "+86");
        pos += rx.matchedLength();
    }
}
