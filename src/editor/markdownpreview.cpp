#include "markdownpreview.h"
#include <QRegularExpression>
#include <QWheelEvent>
#include <QScrollBar>
#include <QTextEdit>
#include <QTextDocument>
#include <QTextBlock>
#include <QTextCharFormat>

MarkdownPreview::MarkdownPreview(QWidget *parent)
    : QTextBrowser(parent)
{
    setReadOnly(true);
    setOpenExternalLinks(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    
    // 设置文档边距，使其与编辑器一致
    document()->setDocumentMargin(10);
    
    // 设置默认样式
    setStyleSheet("QTextBrowser { background-color: white; }");
}

void MarkdownPreview::updatePreview(const QString &text)
{
    // 先获取编辑器的信息
    QTextEdit* editor = qobject_cast<QTextEdit*>(parent()->findChild<QTextEdit*>());
    if (!editor) return;

    // 保存当前滚动位置的百分比
    double scrollProgress = 0.0;
    QScrollBar* thisScroll = verticalScrollBar();
    if (thisScroll && thisScroll->maximum() > 0) {
        scrollProgress = static_cast<double>(thisScroll->value()) / thisScroll->maximum();
    }

    // 设置与编辑器相同的字体和格式
    QTextDocument* doc = document();
    QTextDocument* editorDoc = editor->document();
    
    // 复制编辑器的字体设置
    QFont editorFont = editorDoc->defaultFont();
    doc->setDefaultFont(editorFont);
    
    // 设置相同的默认文本格式
    QTextCharFormat format;
    format.setFont(editorFont);
    format.setFontPointSize(editorFont.pointSize());
    
    // 设置相同的文档宽度
    setLineWrapColumnOrWidth(editor->lineWrapColumnOrWidth());
    setLineWrapMode(editor->lineWrapMode());
    
    // 转换并设置HTML内容
    QString htmlContent = convertMarkdownToHtml(text);
    // 在HTML中设置基础字体大小和行高
    htmlContent = QString("<html><head><style>"
                         "body { font-size: %1pt; line-height: 1.6; }"
                         "p { margin: 1em 0; }"
                         "h1, h2, h3 { line-height: 1.4; }"
                         "</style></head><body>%2</body></html>")
                     .arg(editorFont.pointSize())
                     .arg(htmlContent);
    setHtml(htmlContent);
    
    // 确保预览窗口和编辑器的大小一致
    setMinimumWidth(editor->width());
    setMinimumHeight(editor->height());
    
    // 设置预览窗口的行距
    QTextBlockFormat blockFormat;
    blockFormat.setLineHeight(editorFont.pointSize() * 1.6, QTextBlockFormat::LineDistanceHeight);
    
    // 应用行距到所有段落
    QTextCursor cursor(doc);
    cursor.select(QTextCursor::Document);
    cursor.mergeBlockFormat(blockFormat);
    
    // 恢复滚动位置，考虑内容高度比例
    if (thisScroll && thisScroll->maximum() > 0) {
        double editorHeight = editor->document()->size().height();
        double previewHeight = document()->size().height();
        double heightRatio = previewHeight / editorHeight;
        
        int targetValue = static_cast<int>(thisScroll->maximum() * scrollProgress * heightRatio);
        targetValue = qMin(targetValue, thisScroll->maximum());
        thisScroll->setValue(targetValue);
    }
    
    viewport()->update();
}

void MarkdownPreview::syncScrollBar(int value)
{
    if (isScrolling) return;
    
    QScrollBar* thisScroll = verticalScrollBar();
    if (!thisScroll) return;

    QTextEdit* editor = qobject_cast<QTextEdit*>(parent()->findChild<QTextEdit*>());
    if (!editor) return;

    QScrollBar* editorScroll = editor->verticalScrollBar();
    if (!editorScroll) return;

    // 计算两个窗口的内容实际高度
    double editorHeight = editor->document()->size().height();
    double previewHeight = document()->size().height();
    
    // 计算高度比例
    double heightRatio = previewHeight / editorHeight;
    
    // 计算编辑器的滚动进度（0-1之间）
    double scrollProgress = static_cast<double>(value) / editorScroll->maximum();
    
    // 根据高度比例调整预览窗口的滚动位置
    int targetValue = static_cast<int>(thisScroll->maximum() * scrollProgress * heightRatio);
    targetValue = qMin(targetValue, thisScroll->maximum()); // 确保不超过最大值
    
    isScrolling = true;
    thisScroll->setValue(targetValue);
    isScrolling = false;

    viewport()->update();
}

void MarkdownPreview::wheelEvent(QWheelEvent *event)
{
    QTextBrowser::wheelEvent(event);
    if (!isScrolling) {
        QTextEdit* editor = qobject_cast<QTextEdit*>(parent()->findChild<QTextEdit*>());
        if (editor) {
            QScrollBar* editorScroll = editor->verticalScrollBar();
            QScrollBar* thisScroll = verticalScrollBar();
            if (editorScroll && thisScroll && thisScroll->maximum() > 0) {
                // 计算两个窗口的内容实际高度
                double editorHeight = editor->document()->size().height();
                double previewHeight = document()->size().height();
                
                // 计算高度比例
                double heightRatio = editorHeight / previewHeight;
                
                // 计算预览窗口的滚动进度（0-1之间）
                double scrollProgress = static_cast<double>(thisScroll->value()) / thisScroll->maximum();
                
                // 根据高度比例调整编辑器的滚动位置
                int targetValue = static_cast<int>(editorScroll->maximum() * scrollProgress * heightRatio);
                targetValue = qMin(targetValue, editorScroll->maximum()); // 确保不超过最大值
                
                isScrolling = true;
                editorScroll->setValue(targetValue);
                editor->update();
                isScrolling = false;
            }
        }
    }
}

void MarkdownPreview::scrollContentsBy(int dx, int dy)
{
    QTextBrowser::scrollContentsBy(dx, dy);
    if (!isScrolling) {
        QTextEdit* editor = qobject_cast<QTextEdit*>(parent()->findChild<QTextEdit*>());
        if (editor) {
            QScrollBar* editorScroll = editor->verticalScrollBar();
            QScrollBar* thisScroll = verticalScrollBar();
            if (editorScroll && thisScroll && thisScroll->maximum() > 0) {
                // 计算两个窗口的内容实际高度
                double editorHeight = editor->document()->size().height();
                double previewHeight = document()->size().height();
                
                // 计算高度比例
                double heightRatio = editorHeight / previewHeight;
                
                // 计算预览窗口的滚动进度（0-1之间）
                double scrollProgress = static_cast<double>(thisScroll->value()) / thisScroll->maximum();
                
                // 根据高度比例调整编辑器的滚动位置
                int targetValue = static_cast<int>(editorScroll->maximum() * scrollProgress * heightRatio);
                targetValue = qMin(targetValue, editorScroll->maximum()); // 确保不超过最大值
                
                isScrolling = true;
                editorScroll->setValue(targetValue);
                editor->update();
                isScrolling = false;
            }
        }
    }
}

void MarkdownPreview::emitScrollValue()
{
    QScrollBar* thisScroll = verticalScrollBar();
    if (!thisScroll) return;

    double percent = static_cast<double>(thisScroll->value()) / thisScroll->maximum() * 100;
    isScrolling = true;
    emit scrollValueChanged(static_cast<int>(percent));
    isScrolling = false;
}

QString MarkdownPreview::convertMarkdownToHtml(const QString &markdown)
{
    QString html = markdown;
    
    // 处理标题（保持相对字体大小）
    html.replace(QRegularExpression("^# (.+)$", QRegularExpression::MultilineOption), 
                "<h1 style='font-size: 1.5em; margin: 1em 0;'>\\1</h1>");
    html.replace(QRegularExpression("^## (.+)$", QRegularExpression::MultilineOption), 
                "<h2 style='font-size: 1.3em; margin: 0.8em 0;'>\\1</h2>");
    html.replace(QRegularExpression("^### (.+)$", QRegularExpression::MultilineOption), 
                "<h3 style='font-size: 1.1em; margin: 0.6em 0;'>\\1</h3>");
    
    // 处理粗体
    html.replace(QRegularExpression("\\*\\*(.+?)\\*\\*"), "<strong>\\1</strong>");
    
    // 处理斜体
    html.replace(QRegularExpression("\\*(.+?)\\*"), "<em>\\1</em>");
    
    // 处理代码块
    html.replace(QRegularExpression("```([^`]+)```"), 
                "<pre style='background-color: #f6f8fa; padding: 1em; margin: 1em 0; font-family: monospace; line-height: 1.4;'>\\1</pre>");
    
    // 处理行内代码
    html.replace(QRegularExpression("`([^`]+)`"), 
                "<code style='background-color: #f6f8fa; padding: 0.2em 0.4em; font-family: monospace;'>\\1</code>");
    
    // 处理链接
    html.replace(QRegularExpression("\\[([^\\]]+)\\]\\(([^\\)]+)\\)"), 
                "<a href=\"\\2\" style='color: #0366d6; text-decoration: none;'>\\1</a>");
    
    // 处理列表
    html.replace(QRegularExpression("^- (.+)$", QRegularExpression::MultilineOption), 
                "<li style='margin: 0.5em 0;'>\\1</li>");
    
    // 处理段落
    QStringList paragraphs = html.split("\n\n");
    html = "";
    for (const QString &p : paragraphs) {
        if (!p.trimmed().isEmpty()) {
            if (!p.trimmed().startsWith("<")) {
                html += QString("<p style='margin: 1em 0;'>%1</p>").arg(p.trimmed());
            } else {
                html += p.trimmed() + "\n";
            }
        }
    }
    
    return html;
} 