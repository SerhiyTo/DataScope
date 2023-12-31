#include "syntaxhighlighter.h"

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    m_lstKeywords
        << "ADD" << "ADD CONSTRAINT" << "ALL" << "ALTER" << "ALTER COLUMN"
        << "ALTER TABLE" << "AND" << "ANY" << "AS" << "ASC"
        << "BACKUP DATABASE" << "BETWEEN" << "CASE" << "CHECK" << "COLUMN"
        << "CONSTRAINT" << "CREATE" << "CREATE DATABASE" << "CREATE INDEX" << "CREATE OR REPLACE VIEW"
        << "CREATE TABLE" << "CREATE PROCEDURE" << "CREATE UNIQUE INDEX" << "CREATE VIEW" << "DATABASE"
        << "DEFAULT" << "DELETE" << "DESC" << "DISTINCT" << "DROP"
        << "DROP COLUMN" << "DROP CONSTRAINT" << "DROP DATABASE" << "DROP DEFAULT" << "DROP INDEX"
        << "DROP TABLE" << "DROP VIEW" << "EXEC" << "EXISTS" << "FOREIGN KEY"
        << "FROM" << "FULL OUTER JOIN" << "GROUP BY" << "HAVING" << "IN"
        << "INDEX" << "INNER JOIN" << "INSERT INTO" << "INSERT INTO SELECT" << "IS NULL"
        << "IS NOT NULL" << "JOIN" << "LEFT JOIN" << "LIKE" << "LIMIT"
        << "NOT" << "NOT NULL" << "OR" << "ORDER BY" << "OUTER JOIN"
        << "PRIMARY KEY" << "PROCEDURE" << "RIGHT JOIN" << "ROWNUM" << "SELECT"
        << "SELECT DISTINCT" << "SELECT INTO" << "SELECT TOP" << "SET" << "TABLE"
        << "TOP" << "TRUNCATE TABLE" << "UNION" << "UNION ALL" << "UNIQUE"
        << "UPDATE" << "VALUES" << "VIEW" << "WHERE";
}

QString SyntaxHighlighter::getKeyword(int nPos, const QString &str) const
{
    QString strTemp = "";

    foreach (QString strKeyword, m_lstKeywords)
    {
        if (str.mid(nPos, strKeyword.length()) == strKeyword)
        {
            strTemp = strKeyword;
            break;
        }
    }

    return strTemp;
}

void SyntaxHighlighter::highlightBlock(const QString &str)
{
    int nState = previousBlockState();
    int nStart = 0;
    for (int i = 0; i < str.length(); ++i)
    {
        if (nState == InsideCStyleComment)
        {
            if (str.mid(i, 2) == "*/")
            {
                nState = NormalState;
                setFormat(nStart, i - nStart + 2, Qt::darkGray);
                ++i;
            }
        }
        else
        {
            if (str.at(i).isNumber())
            {
                QTextCharFormat format;
                format.setFontWeight(QFont::Bold);
                format.setForeground(QColor("#f74c02"));
                setFormat(i, 1, format);
            }
            else if (str.mid(i, 2) == "/*")
            {
                nStart = i;
                nState = InsideCStyleComment;
            }
            else
            {
                bool isKeyword = false;
                foreach (const QString &strKeyword, m_lstKeywords)
                {
                    if (str.mid(i, strKeyword.length()).toUpper() == strKeyword.toUpper())
                    {
                        QTextCharFormat format;
                        format.setFontWeight(QFont::Bold);
                        format.setForeground(QColor("#3F15FD"));
                        setFormat(i, strKeyword.length(), format);
                        i += strKeyword.length() - 1;
                        isKeyword = true;
                        break;
                    }
                }
                if (!isKeyword)
                {
                    QTextCharFormat format;
                    format.setFontItalic(true);
                    format.setFontWeight(QFont::Bold);
                    // format.setForeground(QColor("#800080"));
                    setFormat(i, str.length(), format);
                }
            }
        }
    }
    if (nState == InsideCStyleComment)
    {
        setFormat(nStart, str.length() - nStart, Qt::darkGray);
    }
    setCurrentBlockState(nState);
}

