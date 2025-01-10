#ifndef MARKDOWNPREVIEW_H
#define MARKDOWNPREVIEW_H

#include <QTextBrowser>
#include <QScrollBar>

class MarkdownPreview : public QTextBrowser
{
    Q_OBJECT

public:
    explicit MarkdownPreview(QWidget *parent = nullptr);
    void updatePreview(const QString &text);
    void syncScrollBar(int value);

signals:
    void scrollValueChanged(int percent);

protected:
    void wheelEvent(QWheelEvent *event) override;
    void scrollContentsBy(int dx, int dy) override;

private:
    QString convertMarkdownToHtml(const QString &markdown);
    void emitScrollValue();
    bool isScrolling = false;
};

#endif // MARKDOWNPREVIEW_H 