#include "markdownpreview.h"

MarkdownPreview::MarkdownPreview(QWidget *parent)
    : QTextBrowser(parent)
{
    setReadOnly(true);
    setOpenExternalLinks(true);
}

void MarkdownPreview::updatePreview(const QString &text)
{
    setHtml(convertMarkdownToHtml(text));
}

QString MarkdownPreview::convertMarkdownToHtml(const QString &markdown)
{
    // 这里实现一个简单的 Markdown 到 HTML 的转换
    // 实际项目中应该使用成熟的 Markdown 解析库，如 cmark-gfm
    QString html = markdown;
    
    // 处理标题
    html.replace(QRegExp("^# (.+)$", Qt::CaseInsensitive), "<h1>\\1</h1>");
    html.replace(QRegExp("^## (.+)$", Qt::CaseInsensitive), "<h2>\\1</h2>");
    html.replace(QRegExp("^### (.+)$", Qt::CaseInsensitive), "<h3>\\1</h3>");
    
    // 处理粗体
    html.replace(QRegExp("\\*\\*(.+?)\\*\\*"), "<strong>\\1</strong>");
    
    // 处理斜体
    html.replace(QRegExp("\\*(.+?)\\*"), "<em>\\1</em>");
    
    // 处理代码块
    html.replace(QRegExp("```([^`]+)```"), "<pre><code>\\1</code></pre>");
    
    // 处理行内代码
    html.replace(QRegExp("`([^`]+)`"), "<code>\\1</code>");
    
    // 处理链接
    html.replace(QRegExp("\\[([^\\]]+)\\]\\(([^\\)]+)\\)"), "<a href=\"\\2\">\\1</a>");
    
    // 处理列表
    html.replace(QRegExp("^- (.+)$"), "<li>\\1</li>");
    
    // 将换行符转换为 <br>
    html.replace(QRegExp("\\n"), "<br>");
    
    return QString("<html><body style='font-family: Arial, sans-serif;'>%1</body></html>").arg(html);
} 