#include "editorwindow.h"
#include "markdownpreview.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QCloseEvent>
#include <QApplication>
#include <QFileInfo>
#include <QScrollBar>

EditorWindow::EditorWindow(QWidget *parent)
    : QMainWindow(parent), isPreviewVisible(false)
{
    setupEditor();
    createActions();
    createMenus();
    createToolBars();
    setupPreview();

    setCentralWidget(splitter);
    setWindowTitle(tr("Editor"));
    resize(800, 600);
}

EditorWindow::~EditorWindow()
{
}

void EditorWindow::setupEditor()
{
    editor = new QTextEdit;
    editor->setAcceptRichText(false);
    editor->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    
    splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(editor);
    
    connect(editor->document(), &QTextDocument::contentsChanged,
            this, &EditorWindow::documentWasModified);
            
    connect(editor->verticalScrollBar(), &QScrollBar::valueChanged,
            this, [this](int value) {
                if (preview && preview->isVisible() && !editor->verticalScrollBar()->signalsBlocked()) {
                    preview->syncScrollBar(value);
                }
            });
}

void EditorWindow::setupPreview()
{
    preview = new MarkdownPreview(this);
    preview->setVisible(false);
    splitter->addWidget(preview);
    
    connect(preview, &MarkdownPreview::scrollValueChanged,
            this, [this](int percent) {
                if (editor && preview->isVisible()) {
                    QScrollBar* editorScroll = editor->verticalScrollBar();
                    if (!editorScroll) return;
                    
                    editorScroll->blockSignals(true);
                    int targetValue = static_cast<int>(editorScroll->maximum() * (percent / 100.0));
                    editorScroll->setValue(targetValue);
                    editorScroll->blockSignals(false);
                }
            });
}

void EditorWindow::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, &QAction::triggered, this, &EditorWindow::openFile);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    connect(saveAct, &QAction::triggered, this, [this]() { saveFile(); });

    saveAsAct = new QAction(tr("Save &As..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    connect(saveAsAct, &QAction::triggered, this, &EditorWindow::saveFileAs);

    closeAct = new QAction(tr("&Close"), this);
    closeAct->setShortcut(QKeySequence::Close);
    connect(closeAct, &QAction::triggered, this, &EditorWindow::closeFile);

    previewAct = new QAction(tr("Toggle Preview"), this);
    previewAct->setCheckable(true);
    connect(previewAct, &QAction::triggered, this, &EditorWindow::togglePreview);
}

void EditorWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(closeAct);
}

void EditorWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->addAction(previewAct);
}

void EditorWindow::openFile()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open File"), "",
            tr("All Files (*.*);;Text Files (*.txt);;Markdown Files (*.md);;Word Files (*.doc *.docx)"));

        if (!fileName.isEmpty()) {
            loadFile(fileName);
        }
    }
}

void EditorWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
            tr("Cannot read file %1:\n%2.")
            .arg(fileName)
            .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
    editor->setPlainText(in.readAll());
    
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
    
    if (isMarkdownFile(fileName)) {
        previewAct->setEnabled(true);
        if (isPreviewVisible) {
            updatePreview();
        }
    } else {
        previewAct->setEnabled(false);
        preview->setVisible(false);
        isPreviewVisible = false;
    }
}

bool EditorWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
            tr("Cannot write file %1:\n%2.")
            .arg(fileName)
            .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
    out << editor->toPlainText();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void EditorWindow::saveFileAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save As"), currentFile,
        tr("All Files (*);;Text Files (*.txt);;Markdown Files (*.md)"));
    
    if (fileName.isEmpty())
        return;

    if (saveFile(fileName)) {
        setCurrentFile(fileName);
    }
}

void EditorWindow::saveFile()
{
    if (currentFile.isEmpty()) {
        saveFileAs();
    } else {
        saveFile(currentFile);
    }
}

void EditorWindow::closeFile()
{
    if (maybeSave()) {
        editor->clear();
        setCurrentFile("");
    }
}

bool EditorWindow::maybeSave()
{
    if (editor->document()->isModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Application"),
            tr("The document has been modified.\n"
               "Do you want to save your changes?"),
            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        
        if (ret == QMessageBox::Save)
            return saveFile(currentFile);
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void EditorWindow::setCurrentFile(const QString &fileName)
{
    currentFile = fileName;
    editor->document()->setModified(false);
    
    if (fileName.isEmpty()) {
        setWindowTitle(tr("Editor"));
    } else {
        setWindowTitle(tr("%1 - %2").arg(QFileInfo(fileName).fileName(), tr("Editor")));
    }
}

void EditorWindow::documentWasModified()
{
    setWindowModified(editor->document()->isModified());
    if (isPreviewVisible && isMarkdownFile(currentFile)) {
        updatePreview();
    }
}

bool EditorWindow::isMarkdownFile(const QString &fileName) const
{
    return fileName.endsWith(".md", Qt::CaseInsensitive);
}

void EditorWindow::togglePreview()
{
    if (!isMarkdownFile(currentFile)) {
        return;
    }
    
    isPreviewVisible = !isPreviewVisible;
    preview->setVisible(isPreviewVisible);
    previewAct->setChecked(isPreviewVisible);
    
    if (isPreviewVisible) {
        updatePreview();
        preview->syncScrollBar(editor->verticalScrollBar()->value());
    }
}

void EditorWindow::updatePreview()
{
    if (preview && preview->isVisible()) {
        preview->updatePreview(editor->toPlainText());
    }
} 