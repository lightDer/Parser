#include "parser.h"

QStringList Parser::parse(const QString source)
{
    QStringList matchPattern;
    QRegExp rx(pattern);

    int pos = 0;
    while ((pos = rx.indexIn(source, pos)) != -1)
    {
        matchPattern << rx.cap().prepend("0086").remove(QChar('-'));
        pos += rx.matchedLength();
    }

    return matchPattern;
}
