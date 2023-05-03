#include <QtWidgets>
#include <QPrinter>
#include <QPrintDialog>
#include <QFont>
#include <QFontDialog>

#include "mainwindow.h"
#include "mdichild.h"

MainWindow::MainWindow()
    : mdiArea(new QMdiArea)
{
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);
    connect(mdiArea, &QMdiArea::subWindowActivated,
            this, &MainWindow::updateMenus);

    createActions();
    createStatusBar();
    updateMenus();

    readSettings();

    setWindowTitle(tr("MDI"));
    setUnifiedTitleAndToolBarOnMac(true);

    // Запоминаем стартовую тему
    DefaultTheme.set();
    current_theme = DefaultTheme.title;

    //retranslateUi();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    mdiArea->closeAllSubWindows();
    if (mdiArea->currentSubWindow()) {
        event->ignore();
    } else {
        writeSettings();
        event->accept();
    }
}

void MainWindow::newFile()
{
    MdiChild *child = createMdiChild();
    child->newFile();
    child->show();
}

void MainWindow::open()
{
    const QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        openFile(fileName);
}

bool MainWindow::openFile(const QString &fileName)
{
    if (QMdiSubWindow *existing = findMdiChild(fileName)) {
        mdiArea->setActiveSubWindow(existing);
        return true;
    }
    const bool succeeded = loadFile(fileName);
    if (succeeded)
        statusBar()->showMessage(tr("File loaded"), 2000);
    return succeeded;
}

bool MainWindow::loadFile(const QString &fileName)
{
    MdiChild *child = createMdiChild();
    const bool succeeded = child->loadFile(fileName);
    if (succeeded)
        child->show();
    else
        child->close();
    MainWindow::prependToRecentFiles(fileName);
    return succeeded;
}

static inline QString recentFilesKey() { return QStringLiteral("recentFileList"); }
static inline QString fileKey() { return QStringLiteral("file"); }

static QStringList readRecentFiles(QSettings &settings)
{
    QStringList result;
    const int count = settings.beginReadArray(recentFilesKey());
    for (int i = 0; i < count; ++i) {
        settings.setArrayIndex(i);
        result.append(settings.value(fileKey()).toString());
    }
    settings.endArray();
    return result;
}

static void writeRecentFiles(const QStringList &files, QSettings &settings)
{
    const int count = files.size();
    settings.beginWriteArray(recentFilesKey());
    for (int i = 0; i < count; ++i) {
        settings.setArrayIndex(i);
        settings.setValue(fileKey(), files.at(i));
    }
    settings.endArray();
}

bool MainWindow::hasRecentFiles()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    const int count = settings.beginReadArray(recentFilesKey());
    settings.endArray();
    return count > 0;
}

void MainWindow::prependToRecentFiles(const QString &fileName)
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());

    const QStringList oldRecentFiles = readRecentFiles(settings);
    QStringList recentFiles = oldRecentFiles;
    recentFiles.removeAll(fileName);
    recentFiles.prepend(fileName);
    if (oldRecentFiles != recentFiles)
        writeRecentFiles(recentFiles, settings);

    setRecentFilesVisible(!recentFiles.isEmpty());
}

void MainWindow::setRecentFilesVisible(bool visible)
{
    recentFileSubMenuAct->setVisible(visible);
    recentFileSeparator->setVisible(visible);
}

void MainWindow::updateRecentFileActions()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());

    const QStringList recentFiles = readRecentFiles(settings);
    const int count = qMin(int(MaxRecentFiles), recentFiles.size());
    int i = 0;
    for ( ; i < count; ++i) {
        const QString fileName = QFileInfo(recentFiles.at(i)).fileName();
        recentFileActs[i]->setText(tr("&%1 %2").arg(i + 1).arg(fileName));
        recentFileActs[i]->setData(recentFiles.at(i));
        recentFileActs[i]->setVisible(true);
    }
    for ( ; i < MaxRecentFiles; ++i)
        recentFileActs[i]->setVisible(false);
}

void MainWindow::openRecentFile()
{
    if (const QAction *action = qobject_cast<const QAction *>(sender()))
        openFile(action->data().toString());
}

void MainWindow::save()
{
    if (activeMdiChild() && activeMdiChild()->save())
        statusBar()->showMessage(tr("File saved"), 2000);
}

void MainWindow::saveAs()
{
    MdiChild *child = activeMdiChild();
    if (child && child->saveAs()) {
        statusBar()->showMessage(tr("File saved"), 2000);
        MainWindow::prependToRecentFiles(child->currentFile());
    }
}

#ifndef QT_NO_CLIPBOARD
void MainWindow::cut()
{
    if (activeMdiChild())
        activeMdiChild()->cut();
}

void MainWindow::copy()
{
    if (activeMdiChild())
        activeMdiChild()->copy();
}

void MainWindow::paste()
{
    if (activeMdiChild())
        activeMdiChild()->paste();
}


void MainWindow::print()
{
    QPrinter printer;
    QPrintDialog dlg(&printer, this);

    dlg.setWindowTitle("Print");
    if (dlg.exec() != QDialog::Accepted)
        return;

    if (activeMdiChild())
        activeMdiChild()->print(&printer);
}


void MainWindow::copyFormat()
{

    if (activeMdiChild())
    {
        fmt = activeMdiChild()->textCursor().charFormat();
        updateMenus();
    }

}

void MainWindow::applyFormat()
{

    if (activeMdiChild() && fmt.has_value())
    {
        activeMdiChild()->textCursor().setCharFormat(fmt.value());
        fmt = std::nullopt;
        updateMenus();
    }

}


void MainWindow::changeFont()
{

    if (activeMdiChild())
    {
        QTextCharFormat _fmt = activeMdiChild()->textCursor().charFormat();
        QFont _font = _fmt.font();
        QFontDialog _fntDlg(activeMdiChild());
        bool _ok;
        _font = _fntDlg.getFont(&_ok, _font);
        if (_ok)
        {
            _fmt.setFont(_font);
            activeMdiChild()->textCursor().setCharFormat(_fmt);
        }
    }

}

void MainWindow::changeAlignment(const Qt::AlignmentFlag align)
{

    if (activeMdiChild())
    {
        QTextCursor _cursor = activeMdiChild()->textCursor();
        QTextBlockFormat _fmt = _cursor.blockFormat();
        _fmt.setAlignment(align);//or another alignment
        _cursor.mergeBlockFormat(_fmt);
        activeMdiChild()->setTextCursor(_cursor);
    }

}

#endif

void MainWindow::about()
{
   QMessageBox::about(this, tr("About MDI"),
            tr("The <b>MDI</b> example demonstrates how to write multiple "
               "document interface applications using Qt."));
}

void MainWindow::updateMenus()
{
    bool hasMdiChild = (activeMdiChild() != nullptr);
    saveAct->setEnabled(hasMdiChild);
    saveAsAct->setEnabled(hasMdiChild);
    printAct->setEnabled(hasMdiChild);
#ifndef QT_NO_CLIPBOARD
    pasteAct->setEnabled(hasMdiChild);
#endif
    closeAct->setEnabled(hasMdiChild);
    closeAllAct->setEnabled(hasMdiChild);
    tileAct->setEnabled(hasMdiChild);
    cascadeAct->setEnabled(hasMdiChild);
    nextAct->setEnabled(hasMdiChild);
    previousAct->setEnabled(hasMdiChild);
    windowMenuSeparatorAct->setVisible(hasMdiChild);

#ifndef QT_NO_CLIPBOARD
    bool hasSelection = (activeMdiChild() &&
                         activeMdiChild()->textCursor().hasSelection());
    cutAct->setEnabled(hasSelection);
    copyAct->setEnabled(hasSelection);

    copyFormatAct->setEnabled(hasSelection);
    applyFormatAct->setEnabled(hasSelection && fmt.has_value());
    changeFontAct->setEnabled(hasSelection);
    alignRightAct->setEnabled(hasSelection);
    alignLeftAct->setEnabled(hasSelection);
    alignCenterAct->setEnabled(hasSelection);

#endif
}

void MainWindow::updateWindowMenu()
{
    windowMenu->clear();
    windowMenu->addAction(closeAct);
    windowMenu->addAction(closeAllAct);
    windowMenu->addSeparator();
    windowMenu->addAction(tileAct);
    windowMenu->addAction(cascadeAct);
    windowMenu->addSeparator();
    windowMenu->addAction(nextAct);
    windowMenu->addAction(previousAct);
    windowMenu->addAction(windowMenuSeparatorAct);

    QList<QMdiSubWindow *> windows = mdiArea->subWindowList();
    windowMenuSeparatorAct->setVisible(!windows.isEmpty());

    for (int i = 0; i < windows.size(); ++i) {
        QMdiSubWindow *mdiSubWindow = windows.at(i);
        MdiChild *child = qobject_cast<MdiChild *>(mdiSubWindow->widget());

        QString text;
        if (i < 9) {
            text = tr("&%1 %2").arg(i + 1)
                               .arg(child->userFriendlyCurrentFile());
        } else {
            text = tr("%1 %2").arg(i + 1)
                              .arg(child->userFriendlyCurrentFile());
        }
        QAction *action = windowMenu->addAction(text, mdiSubWindow, [this, mdiSubWindow]() {
            mdiArea->setActiveSubWindow(mdiSubWindow);
        });
        action->setCheckable(true);
        action ->setChecked(child == activeMdiChild());
    }

}

void MainWindow::updateThemesMenu()
{
    QList<QAction*> actionsThemes = menuThemes->actions();

    for (QAction* action : actionsThemes)
    {
        if (dynamic_cast<QAction*>(action))
        {
            bool _checked = (current_theme.compare(action->text(), Qt::CaseInsensitive) == 0);
            action ->setChecked(_checked);
        }
    }
}

MdiChild *MainWindow::createMdiChild()
{
    MdiChild *child = new MdiChild;
    mdiArea->addSubWindow(child);

#ifndef QT_NO_CLIPBOARD
    connect(child, &QTextEdit::copyAvailable, cutAct,  &QAction::setEnabled);
    connect(child, &QTextEdit::copyAvailable, copyAct, &QAction::setEnabled);

    connect(child, &QTextEdit::copyAvailable, copyFormatAct,  &QAction::setEnabled);
    connect(child, &QTextEdit::copyAvailable, changeFontAct,  &QAction::setEnabled);
    connect(child, &QTextEdit::copyAvailable, alignRightAct,  &QAction::setEnabled);
    connect(child, &QTextEdit::copyAvailable, alignLeftAct,   &QAction::setEnabled);
    connect(child, &QTextEdit::copyAvailable, alignCenterAct, &QAction::setEnabled);
#endif

    return child;
}

void MainWindow::createActions()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileToolBar = addToolBar(tr("File"));

    const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/images/new.png"));
    newAct = new QAction(newIcon, tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
    fileMenu->addAction(newAct);
    fileToolBar->addAction(newAct);

    const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/images/open.png"));
    openAct = new QAction(openIcon, tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
    fileMenu->addAction(openAct);
    fileToolBar->addAction(openAct);

    const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(":/images/save.png"));
    saveAct = new QAction(saveIcon, tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);
    fileToolBar->addAction(saveAct);

    const QIcon saveAsIcon = QIcon::fromTheme("document-save-as");
    saveAsAct = new QAction(saveAsIcon, tr("Save &As..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAct, &QAction::triggered, this, &MainWindow::saveAs);
    fileMenu->addAction(saveAsAct);

    const QIcon printIcon = QIcon::fromTheme("document-print");
    printAct = new QAction(printIcon, tr("Print"), this);
    printAct->setShortcuts(QKeySequence::Print);
    printAct->setStatusTip(tr("Print the document"));
    connect(printAct, &QAction::triggered, this, &MainWindow::print);
    fileMenu->addAction(printAct);

    fileMenu->addSeparator();

    recentMenu = fileMenu->addMenu(tr("Recent..."));
    connect(recentMenu, &QMenu::aboutToShow, this, &MainWindow::updateRecentFileActions);
    recentFileSubMenuAct = recentMenu->menuAction();

    for (int i = 0; i < MaxRecentFiles; ++i) {
        recentFileActs[i] = recentMenu->addAction(QString(), this, &MainWindow::openRecentFile);
        recentFileActs[i]->setVisible(false);
    }

    recentFileSeparator = fileMenu->addSeparator();

    setRecentFilesVisible(MainWindow::hasRecentFiles());

    switchLayout = fileMenu->addAction(tr("Switch layout direction"), this, &MainWindow::switchLayoutDirection);

    fileMenu->addSeparator();

//! [0]
    const QIcon exitIcon = QIcon::fromTheme("application-exit");
    exitAct = fileMenu->addAction(exitIcon, tr("E&xit"), qApp, &QApplication::quit);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    fileMenu->addAction(exitAct);
//! [0]

#ifndef QT_NO_CLIPBOARD
    editMenu = menuBar()->addMenu(tr("&Edit"));
    QToolBar *editToolBar = addToolBar(tr("Edit"));

    const QIcon cutIcon = QIcon::fromTheme("edit-cut", QIcon(":/images/cut.png"));
    cutAct = new QAction(cutIcon, tr("Cu&t"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    connect(cutAct, &QAction::triggered, this, &MainWindow::cut);
    editMenu->addAction(cutAct);
    editToolBar->addAction(cutAct);

    const QIcon copyIcon = QIcon::fromTheme("edit-copy", QIcon(":/images/copy.png"));
    copyAct = new QAction(copyIcon, tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    connect(copyAct, &QAction::triggered, this, &MainWindow::copy);
    editMenu->addAction(copyAct);
    editToolBar->addAction(copyAct);

    const QIcon pasteIcon = QIcon::fromTheme("edit-paste", QIcon(":/images/paste.png"));
    pasteAct = new QAction(pasteIcon, tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    connect(pasteAct, &QAction::triggered, this, &MainWindow::paste);
    editMenu->addAction(pasteAct);
    editToolBar->addAction(pasteAct);


    editMenu->addSeparator();

    copyFormatAct = new QAction(copyIcon, tr("Copy format"), this);
    copyFormatAct->setStatusTip(tr("Copy the selected text format"));
    connect(copyFormatAct, &QAction::triggered, this, &MainWindow::copyFormat);
    editMenu->addAction(copyFormatAct);

    applyFormatAct = new QAction(copyIcon, tr("Apply format"), this);
    applyFormatAct->setStatusTip(tr("Apply format to selected text"));
    connect(applyFormatAct, &QAction::triggered, this, &MainWindow::applyFormat);
    editMenu->addAction(applyFormatAct);

    changeFontAct = new QAction(copyIcon, tr("Сhange font"), this);
    changeFontAct->setStatusTip(tr("Сhange the font of the selected text"));
    connect(changeFontAct, &QAction::triggered, this, &MainWindow::changeFont);
    editMenu->addAction(changeFontAct);

    editMenu->addSeparator();

    alignRightAct = new QAction(copyIcon, tr("Align right"), this);
    alignRightAct->setStatusTip(tr("Change the alignment of the selected text"));
    connect(alignRightAct, &QAction::triggered, this, [=]() { changeAlignment( Qt::AlignmentFlag::AlignRight ); });
    editMenu->addAction(alignRightAct);

    alignLeftAct = new QAction(copyIcon, tr("Align left"), this);
    alignLeftAct->setStatusTip(tr("Change the alignment of the selected text"));
    connect(alignLeftAct, &QAction::triggered, this, [=]() { changeAlignment( Qt::AlignmentFlag::AlignLeft ); });
    editMenu->addAction(alignLeftAct);

    alignCenterAct = new QAction(copyIcon, tr("Align center"), this);
    alignCenterAct->setStatusTip(tr("Change the alignment of the selected text"));
    connect(alignCenterAct, &QAction::triggered, this, [=]() { changeAlignment( Qt::AlignmentFlag::AlignCenter ); });
    editMenu->addAction(alignCenterAct);

#endif

    windowMenu = menuBar()->addMenu(tr("&Window"));
    connect(windowMenu, &QMenu::aboutToShow, this, &MainWindow::updateWindowMenu);

    closeAct = new QAction(tr("Cl&ose"), this);
    closeAct->setStatusTip(tr("Close the active window"));
    connect(closeAct, &QAction::triggered,
            mdiArea, &QMdiArea::closeActiveSubWindow);

    closeAllAct = new QAction(tr("Close &All"), this);
    closeAllAct->setStatusTip(tr("Close all the windows"));
    connect(closeAllAct, &QAction::triggered, mdiArea, &QMdiArea::closeAllSubWindows);

    tileAct = new QAction(tr("&Tile"), this);
    tileAct->setStatusTip(tr("Tile the windows"));
    connect(tileAct, &QAction::triggered, mdiArea, &QMdiArea::tileSubWindows);

    cascadeAct = new QAction(tr("&Cascade"), this);
    cascadeAct->setStatusTip(tr("Cascade the windows"));
    connect(cascadeAct, &QAction::triggered, mdiArea, &QMdiArea::cascadeSubWindows);

    nextAct = new QAction(tr("Ne&xt"), this);
    nextAct->setShortcuts(QKeySequence::NextChild);
    nextAct->setStatusTip(tr("Move the focus to the next window"));
    connect(nextAct, &QAction::triggered, mdiArea, &QMdiArea::activateNextSubWindow);

    previousAct = new QAction(tr("Pre&vious"), this);
    previousAct->setShortcuts(QKeySequence::PreviousChild);
    previousAct->setStatusTip(tr("Move the focus to the previous "
                                 "window"));
    connect(previousAct, &QAction::triggered, mdiArea, &QMdiArea::activatePreviousSubWindow);

    windowMenuSeparatorAct = new QAction(this);
    windowMenuSeparatorAct->setSeparator(true);

    updateWindowMenu();

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));

    aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
    aboutAct->setStatusTip(tr("Show the application's About box"));

    aboutQtAct = helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));


    menuThemes = menuBar()->addMenu(tr("Themes"));
    connect(menuThemes, &QMenu::aboutToShow, this, &MainWindow::updateThemesMenu);

    themeClientor = new QAction(tr("Clientor"), this);
    themeClientor->setStatusTip(tr("theme clientor"));
    themeClientor->setCheckable(true);
    connect(themeClientor, &QAction::triggered, this, [=]() { setNewTheme( "Clientor" ); });
    menuThemes->addAction(themeClientor);

    themeDtor = new QAction(tr("Dtor"), this);
    themeDtor->setStatusTip(tr("theme dtor"));
    themeDtor->setCheckable(true);
    connect(themeDtor, &QAction::triggered, this, [=]() { setNewTheme( "Dtor" ); });
    menuThemes->addAction(themeDtor);

    themeMaterial_blue = new QAction(tr("material-blue"), this);
    themeMaterial_blue->setStatusTip(tr("theme material-blue"));
    themeMaterial_blue->setCheckable(true);
    connect(themeMaterial_blue, &QAction::triggered, this, [=]() { setNewTheme( "Material-blue" ); });
    menuThemes->addAction(themeMaterial_blue);

    themeMaterial_dark = new QAction(tr("material_dark"), this);
    themeMaterial_dark->setStatusTip(tr("theme material-dark"));
    themeMaterial_dark->setCheckable(true);
    connect(themeMaterial_dark, &QAction::triggered, this, [=]() { setNewTheme( "Material-dark" ); });
    menuThemes->addAction(themeMaterial_dark);

    themeNeonButtons = new QAction(tr("NeonButtons"), this);
    themeNeonButtons->setStatusTip(tr("theme NeonButtons"));
    themeNeonButtons->setCheckable(true);
    connect(themeNeonButtons, &QAction::triggered, this, [=]() { setNewTheme( "NeonButtons" ); });
    menuThemes->addAction(themeNeonButtons);

    themeUbuntu = new QAction(tr("ubuntu"), this);
    themeUbuntu->setStatusTip(tr("theme ubuntu"));
    themeUbuntu->setCheckable(true);
    connect(themeUbuntu, &QAction::triggered, this, [=]() { setNewTheme( "Ubuntu" ); });
    menuThemes->addAction(themeUbuntu);

    menuThemes->addSeparator();

    themeDefault = new QAction(DefaultTheme.title, this);
    themeDefault->setStatusTip(tr("restore default theme"));
    themeDefault->setCheckable(true);
    connect(themeDefault, &QAction::triggered, this, &MainWindow::setDefaultTheme);
    menuThemes->addAction(themeDefault);

}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::readSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
    if (geometry.isEmpty()) {
        const QRect availableGeometry = screen()->availableGeometry();
        resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2,
             (availableGeometry.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }
}

void MainWindow::writeSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue("geometry", saveGeometry());
}

MdiChild *MainWindow::activeMdiChild() const
{
    if (QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow())
        return qobject_cast<MdiChild *>(activeSubWindow->widget());
    return nullptr;
}

QMdiSubWindow *MainWindow::findMdiChild(const QString &fileName) const
{
    QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();

    const QList<QMdiSubWindow *> subWindows = mdiArea->subWindowList();
    for (QMdiSubWindow *window : subWindows) {
        MdiChild *mdiChild = qobject_cast<MdiChild *>(window->widget());
        if (mdiChild->currentFile() == canonicalFilePath)
            return window;
    }
    return nullptr;
}

void MainWindow::switchLayoutDirection()
{
    if (layoutDirection() == Qt::LeftToRight)
        QGuiApplication::setLayoutDirection(Qt::RightToLeft);
    else
        QGuiApplication::setLayoutDirection(Qt::LeftToRight);
}


void MainWindow::setNewTheme(const QString theme)
{
    QString style_sheet = readTextFile(":/stylesheets/"+ theme + ".qss");
    if (!style_sheet.isEmpty())
    {
        qApp->setStyleSheet(style_sheet);
        current_theme = theme;
    }
}

void MainWindow::setDefaultTheme()
{
    DefaultTheme.restore();
    current_theme = DefaultTheme.title;
}




QByteArray readTextFile(const QString &file_path)
{
    QFile input_file(file_path);
    QByteArray input_data;

    if (input_file.open(QIODevice::Text | QIODevice::Unbuffered | QIODevice::ReadOnly))
    {
        input_data = input_file.readAll();
        input_file.close();
        return input_data;
    }
    else
    {
        return QByteArray();
    }
}

void MainWindow::m_Theme::set()
{
    // Запоминаем тему
    m_StyleName  = QApplication::style()->objectName();
    m_StyleSheet = qApp->styleSheet();
}

void MainWindow::m_Theme::restore()
{
    qApp->setStyle(m_StyleName);
    qApp->setStyleSheet(m_StyleSheet);
    qApp->setPalette(qApp->style()->standardPalette());
}

void MainWindow::retranslateUi()
{
    // просто для примера
    setWindowTitle(QCoreApplication::translate("MainWindow", "MDI", nullptr));

    fileMenu->setTitle(QCoreApplication::translate("MainWindow", "&File", nullptr));

    newAct->setText(QCoreApplication::translate("MainWindow", "&New", nullptr));
    newAct->setStatusTip(QCoreApplication::translate("MainWindow", "Create a new file", nullptr));

    openAct->setText(QCoreApplication::translate("MainWindow", "&Open...", nullptr));
    openAct->setStatusTip(QCoreApplication::translate("MainWindow", "Open an existing file", nullptr));

    saveAct->setText(QCoreApplication::translate("MainWindow", "&Save", nullptr));
    saveAct->setStatusTip(QCoreApplication::translate("MainWindow", "Save the document to disk", nullptr));

    saveAsAct->setText(QCoreApplication::translate("MainWindow", "Save &As...", nullptr));
    saveAsAct->setStatusTip(QCoreApplication::translate("MainWindow", "Save the document under a new name", nullptr));

    printAct->setText(QCoreApplication::translate("MainWindow", "Print", nullptr));
    printAct->setStatusTip(QCoreApplication::translate("MainWindow", "Print the document", nullptr));

    recentMenu->setTitle(QCoreApplication::translate("MainWindow", "Recent...", nullptr));

    switchLayout->setText(QCoreApplication::translate("MainWindow", "Switch layout direction", nullptr));

    exitAct->setText(QCoreApplication::translate("MainWindow", "E&xit", nullptr));
    exitAct->setStatusTip(QCoreApplication::translate("MainWindow", "Exit the application", nullptr));

#ifndef QT_NO_CLIPBOARD
    editMenu->setTitle(QCoreApplication::translate("MainWindow", "&Edit", nullptr));
    cutAct->setText(QCoreApplication::translate("MainWindow", "Cu&t", nullptr));
    cutAct->setStatusTip(QCoreApplication::translate("MainWindow",
                                                     "Cut the current selection's contents to the clipboard", nullptr));
    copyAct->setText(QCoreApplication::translate("MainWindow", "&Copy", nullptr));
    copyAct->setStatusTip(QCoreApplication::translate("MainWindow",
                                                      "Copy the current selection's contents to the clipboard", nullptr));
    pasteAct->setText(QCoreApplication::translate("MainWindow", "&Paste", nullptr));
    pasteAct->setStatusTip(QCoreApplication::translate("MainWindow",
                                                       "Paste the clipboard's contents into the current selection", nullptr));
    copyFormatAct->setText(QCoreApplication::translate("MainWindow", "Copy format", nullptr));
    copyFormatAct->setStatusTip(QCoreApplication::translate("MainWindow", "Copy the selected text format", nullptr));
    applyFormatAct->setText(QCoreApplication::translate("MainWindow", "Apply format", nullptr));
    applyFormatAct->setStatusTip(QCoreApplication::translate("MainWindow", "Apply format to selected text", nullptr));
    changeFontAct->setText(QCoreApplication::translate("MainWindow", "Сhange font", nullptr));
    changeFontAct->setStatusTip(QCoreApplication::translate("MainWindow", "Сhange the font of the selected text", nullptr));

    alignRightAct->setText(QCoreApplication::translate("MainWindow", "Align right", nullptr));
    alignRightAct->setStatusTip(QCoreApplication::translate("MainWindow", "Change the alignment of the selected text", nullptr));
    alignLeftAct->setText(QCoreApplication::translate("MainWindow", "Align left", nullptr));
    alignLeftAct->setStatusTip(QCoreApplication::translate("MainWindow", "Change the alignment of the selected text", nullptr));
    alignCenterAct->setText(QCoreApplication::translate("MainWindow", "Align left", nullptr));
    alignCenterAct->setStatusTip(QCoreApplication::translate("MainWindow", "Change the alignment of the selected text", nullptr));

#endif

    // и т.д. и т.п.

} // retranslateUi
