#ifndef MARKDOWNPREVIEW_H
#define MARKDOWNPREVIEW_H

#include <QTextBrowser>

class MarkdownPreview : public QTextBrowser
{
    Q_OBJECT

public:
    explicit MarkdownPreview(QWidget *parent = nullptr);
    void updatePreview(const QString &text);

private:
    QString convertMarkdownToHtml(const QString &markdown);
};

#endif // MARKDOWNPREVIEW_H 