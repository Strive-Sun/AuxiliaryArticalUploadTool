#include "markdownpreview.h"
#include <QRegularExpression>
#include <QWheelEvent>
#include <QScrollBar>
#include <QTextEdit>

MarkdownPreview::MarkdownPreview(QWidget *parent)
    : QTextBrowser(parent)
{
    setReadOnly(true);
    setOpenExternalLinks(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    
    // 连接滚动条信号
    connect(verticalScrollBar(), &QScrollBar::valueChanged,
            this, [this](int value) {
                if (!verticalScrollBar()->signalsBlocked()) {
                    double percent = static_cast<double>(value) / verticalScrollBar()->maximum();
                    emit scrollValueChanged(static_cast<int>(percent * 100));
                }
            });
}

void MarkdownPreview::updatePreview(const QString &text)
{
    setHtml(convertMarkdownToHtml(text));
}

void MarkdownPreview::syncScrollBar(int value)
{
    QScrollBar* thisScroll = verticalScrollBar();
    if (!thisScroll) return;

    QTextEdit* editor = qobject_cast<QTextEdit*>(parent()->findChild<QTextEdit*>());
    if (!editor) return;

    QScrollBar* editorScroll = editor->verticalScrollBar();
    if (!editorScroll) return;

    // 使用百分比来同步滚动位置
    double percent = static_cast<double>(value) / editorScroll->maximum();
    int targetValue = static_cast<int>(thisScroll->maximum() * percent);
    
    // 阻止信号循环
    thisScroll->blockSignals(true);
    thisScroll->setValue(targetValue);
    thisScroll->blockSignals(false);

    // 立即更新视图
    viewport()->update();
}

void MarkdownPreview::wheelEvent(QWheelEvent *event)
{
    // 处理滚轮事件
    QTextBrowser::wheelEvent(event);
}

QString MarkdownPreview::convertMarkdownToHtml(const QString &markdown)
{
    // 这里实现一个简单的 Markdown 到 HTML 的转换
    // 实际项目中应该使用成熟的 Markdown 解析库，如 cmark-gfm
    QString html = markdown;
    
    // 处理标题
    html.replace(QRegularExpression("^# (.+)$", QRegularExpression::MultilineOption), "<h1>\\1</h1>");
    html.replace(QRegularExpression("^## (.+)$", QRegularExpression::MultilineOption), "<h2>\\1</h2>");
    html.replace(QRegularExpression("^### (.+)$", QRegularExpression::MultilineOption), "<h3>\\1</h3>");
    
    // 处理粗体
    html.replace(QRegularExpression("\\*\\*(.+?)\\*\\*"), "<strong>\\1</strong>");
    
    // 处理斜体
    html.replace(QRegularExpression("\\*(.+?)\\*"), "<em>\\1</em>");
    
    // 处理代码块
    html.replace(QRegularExpression("```([^`]+)```"), "<pre><code>\\1</code></pre>");
    
    // 处理行内代码
    html.replace(QRegularExpression("`([^`]+)`"), "<code>\\1</code>");
    
    // 处理链接
    html.replace(QRegularExpression("\\[([^\\]]+)\\]\\(([^\\)]+)\\)"), "<a href=\"\\2\">\\1</a>");
    
    // 处理列表
    html.replace(QRegularExpression("^- (.+)$", QRegularExpression::MultilineOption), "<li>\\1</li>");
    
    // 将换行符转换为 <br>
    html.replace(QRegularExpression("\\n"), "<br>");
    
    return QString("<html><body style='font-family: Arial, sans-serif;'>%1</body></html>").arg(html);
} 