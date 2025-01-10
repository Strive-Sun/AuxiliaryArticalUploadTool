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

protected:
    void wheelEvent(QWheelEvent *event) override;

signals:
    void scrollValueChanged(int value);

private:
    QString convertMarkdownToHtml(const QString &markdown);
    double calculateScrollRatio() const;
};

#endif // MARKDOWNPREVIEW_H 