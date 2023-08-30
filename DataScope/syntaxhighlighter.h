#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class SyntaxHighlighter : public QSyntaxHighlighter
{
public:
    explicit SyntaxHighlighter(QTextDocument *parent = nullptr);
    enum { NormalState = -1, InsideCStyleComment };
    virtual void highlightBlock(const QString& str);
    QString getKeyword(int nPos, const QString& str) const;

private:
    QStringList m_lstKeywords;

signals:

};

#endif // SYNTAXHIGHLIGHTER_H
