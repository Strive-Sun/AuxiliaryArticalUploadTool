#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QSplitter>
#include <QToolBar>
#include <QMenuBar>
#include <QStatusBar>
#include <QLabel>

class MarkdownPreview;  // 前向声明

class EditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditorWindow(QWidget *parent = nullptr);
    ~EditorWindow();

private slots:
    void openFile();
    void saveFile();
    void saveFileAs();
    void closeFile();
    void togglePreview();
    void documentWasModified();

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void setupEditor();
    void setupPreview();
    bool maybeSave();
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    bool isMarkdownFile(const QString &fileName) const;
    void updatePreview();

    QTextEdit *editor;              // 文本编辑器
    MarkdownPreview *preview;       // Markdown 预览窗口
    QSplitter *splitter;           // 分割窗口
    QToolBar *fileToolBar;         // 文件工具栏
    QMenu *fileMenu;               // 文件菜单
    QString currentFile;           // 当前文件路径
    bool isPreviewVisible;         // 预览窗口是否可见
    
    // 文件菜单动作
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *closeAct;
    QAction *previewAct;
};

#endif // EDITORWINDOW_H 