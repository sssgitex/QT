#include <QtWidgets>
#include <QLocale>
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

    // Устанавливаем локализацию
    if (QLocale::system().language() == QLocale::Language::Russian)
        setLanguage (QLocale (QLocale::Russian));
    else
        setLanguage (QLocale (QLocale::English));

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

#endif // QT_NO_CLIPBOARD

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

void MainWindow::pasteDateAndTime ()
{
    if (activeMdiChild())
    {
        QTextCursor _cursor = activeMdiChild()->textCursor(); // получаем курсор
        QDateTime _dateTime = QDateTime::currentDateTime(); // получаем текущую дату и время
        //QString _formatted{_dateTime.toString("dd MMMM yyyy hh:mm:ss")};// = QLocale().toString(dateTime); // форматируем дату и время с учетом системной локали
        QString _formatted{locale.toString(_dateTime, " dd MMMM yyyyг hhч mmм ssс ")};
        _cursor.insertText(_formatted); // вставляем отформатированный текст в место курсора
    }
}



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
    printAct->setEnabled(hasMdiChild);
    dateAndTimeAct->setEnabled(hasMdiChild);

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
#endif

    copyFormatAct->setEnabled(hasSelection);
    applyFormatAct->setEnabled(hasSelection && fmt.has_value());
    changeFontAct->setEnabled(hasSelection);
    alignRightAct->setEnabled(hasSelection);
    alignLeftAct->setEnabled(hasSelection);
    alignCenterAct->setEnabled(hasSelection);

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
        if (qobject_cast<QAction*>(action))
        {
            QString title = action->text();
            QString current = QCoreApplication::translate("MainWindow", current_theme.toUtf8());

            bool _checked = (current.compare(title, Qt::CaseInsensitive) == 0);
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
#endif

    connect(child, &QTextEdit::copyAvailable, copyFormatAct,  &QAction::setEnabled);
    connect(child, &QTextEdit::copyAvailable, changeFontAct,  &QAction::setEnabled);
    connect(child, &QTextEdit::copyAvailable, alignRightAct,  &QAction::setEnabled);
    connect(child, &QTextEdit::copyAvailable, alignLeftAct,   &QAction::setEnabled);
    connect(child, &QTextEdit::copyAvailable, alignCenterAct, &QAction::setEnabled);
    //connect(child, &QTextEdit::copyAvailable, dateAndTimeAct, &QAction::setEnabled);

    return child;
}

void MainWindow::createActions()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileToolBar = addToolBar(tr("File"));

    const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/images/new.png"));
    //newAct = new QAction(newIcon, tr("&New"), this);
    newAct = new QAction(this);
    newAct->setIcon(newIcon);
    newAct->setShortcuts(QKeySequence::New);
    //newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
    fileMenu->addAction(newAct);
    fileToolBar->addAction(newAct);

    const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/images/open.png"));
    //openAct = new QAction(openIcon, tr("&Open..."), this);
    openAct = new QAction(this);
    openAct->setIcon(openIcon);
    openAct->setShortcuts(QKeySequence::Open);
    //openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
    fileMenu->addAction(openAct);
    fileToolBar->addAction(openAct);

    const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(":/images/save.png"));
    //saveAct = new QAction(saveIcon, tr("&Save"), this);
    saveAct = new QAction(this);
    saveAct->setIcon(saveIcon);
    saveAct->setShortcuts(QKeySequence::Save);
    //saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);
    fileToolBar->addAction(saveAct);

    const QIcon saveAsIcon = QIcon::fromTheme("document-save-as");
    //saveAsAct = new QAction(saveAsIcon, tr("Save &As..."), this);
    saveAsAct = new QAction(this);
    saveAsAct->setIcon(saveAsIcon);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    //saveAsAct->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAct, &QAction::triggered, this, &MainWindow::saveAs);
    fileMenu->addAction(saveAsAct);

    const QIcon printIcon = QIcon::fromTheme("document-print");
    //printAct = new QAction(printIcon, tr("Print"), this);
    printAct = new QAction(this);
    printAct->setIcon(printIcon);
    printAct->setShortcuts(QKeySequence::Print);
    //printAct->setStatusTip(tr("Print the document"));
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

    //switchLayout = fileMenu->addAction(tr("Switch layout direction"), this, &MainWindow::switchLayoutDirection);
    switchLayout = new QAction (this);
    fileMenu->addAction(switchLayout);
    connect(switchLayout, &QAction::triggered, this, &MainWindow::switchLayoutDirection);

    fileMenu->addSeparator();

//! [0]
    const QIcon exitIcon = QIcon::fromTheme("application-exit");
    //exitAct = fileMenu->addAction(exitIcon, tr("E&xit"), qApp, &QApplication::quit);
    exitAct = new QAction (this);
    exitAct->setIcon(exitIcon);
    exitAct->setShortcuts(QKeySequence::Quit);
    //exitAct->setStatusTip(tr("Exit the application"));
    fileMenu->addAction(exitAct);
    connect(exitAct, &QAction::triggered, qApp, &QApplication::quit);
//! [0]

#ifndef QT_NO_CLIPBOARD
    editMenu = menuBar()->addMenu(tr("&Edit"));
    QToolBar *editToolBar = addToolBar(tr("Edit"));

    const QIcon cutIcon = QIcon::fromTheme("edit-cut", QIcon(":/images/cut.png"));
    //cutAct = new QAction(cutIcon, tr("Cu&t"), this);
    cutAct = new QAction(this);
    cutAct->setIcon(cutIcon);
    cutAct->setShortcuts(QKeySequence::Cut);
    //cutAct->setStatusTip(tr("Cut the current selection's contents to the clipboard"));
    connect(cutAct, &QAction::triggered, this, &MainWindow::cut);
    editMenu->addAction(cutAct);
    editToolBar->addAction(cutAct);

    const QIcon copyIcon = QIcon::fromTheme("edit-copy", QIcon(":/images/copy.png"));
    //copyAct = new QAction(copyIcon, tr("&Copy"), this);
    copyAct = new QAction(this);
    copyAct->setIcon(copyIcon);
    copyAct->setShortcuts(QKeySequence::Copy);
    //copyAct->setStatusTip(tr("Copy the current selection's contents to the clipboard"));
    connect(copyAct, &QAction::triggered, this, &MainWindow::copy);
    editMenu->addAction(copyAct);
    editToolBar->addAction(copyAct);

    const QIcon pasteIcon = QIcon::fromTheme("edit-paste", QIcon(":/images/paste.png"));
    //pasteAct = new QAction(pasteIcon, tr("&Paste"), this);
    pasteAct = new QAction(this);
    pasteAct->setIcon(pasteIcon);
    pasteAct->setShortcuts(QKeySequence::Paste);
    //pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current selection"));
    connect(pasteAct, &QAction::triggered, this, &MainWindow::paste);
    editMenu->addAction(pasteAct);
    editToolBar->addAction(pasteAct);

#endif // QT_NO_CLIPBOARD

    editMenu->addSeparator();

    //copyFormatAct = new QAction(tr("Copy format"), this);
    copyFormatAct = new QAction(this);
    //copyFormatAct->setStatusTip(tr("Copy the selected text format"));
    connect(copyFormatAct, &QAction::triggered, this, &MainWindow::copyFormat);
    editMenu->addAction(copyFormatAct);

    //applyFormatAct = new QAction(tr("Apply format"), this);
    applyFormatAct = new QAction(this);
    //applyFormatAct->setStatusTip(tr("Apply format to selected text"));
    connect(applyFormatAct, &QAction::triggered, this, &MainWindow::applyFormat);
    editMenu->addAction(applyFormatAct);

    //changeFontAct = new QAction(tr("Сhange font"), this);
    changeFontAct = new QAction(this);
    //changeFontAct->setStatusTip(tr("Сhange the font of the selected text"));
    connect(changeFontAct, &QAction::triggered, this, &MainWindow::changeFont);
    editMenu->addAction(changeFontAct);

    editMenu->addSeparator();

    //alignRightAct = new QAction(tr("Align right"), this);
    alignRightAct = new QAction(this);
    //alignRightAct->setStatusTip(tr("Change the alignment of the selected text"));
    connect(alignRightAct, &QAction::triggered, this, [=]() { changeAlignment( Qt::AlignmentFlag::AlignRight ); });
    editMenu->addAction(alignRightAct);

    //alignLeftAct = new QAction(tr("Align left"), this);
    alignLeftAct = new QAction(this);
    //alignLeftAct->setStatusTip(tr("Change the alignment of the selected text"));
    connect(alignLeftAct, &QAction::triggered, this, [=]() { changeAlignment( Qt::AlignmentFlag::AlignLeft ); });
    editMenu->addAction(alignLeftAct);

    //alignCenterAct = new QAction(tr("Align center"), this);
    alignCenterAct = new QAction(this);
    //alignCenterAct->setStatusTip(tr("Change the alignment of the selected text"));
    connect(alignCenterAct, &QAction::triggered, this, [=]() { changeAlignment( Qt::AlignmentFlag::AlignCenter ); });
    editMenu->addAction(alignCenterAct);

    //dateAndTimeAct = new QAction(tr("Date and time"), this);
    dateAndTimeAct = new QAction(this);
    //dateAndTimeAct->setStatusTip(tr("Insert current date and time"));
    connect(dateAndTimeAct, &QAction::triggered, this, &MainWindow::pasteDateAndTime);
    editMenu->addAction(dateAndTimeAct);



    windowMenu = menuBar()->addMenu(tr("&Window"));
    connect(windowMenu, &QMenu::aboutToShow, this, &MainWindow::updateWindowMenu);

    //closeAct = new QAction(tr("Cl&ose"), this);
    closeAct = new QAction(this);
    //closeAct->setStatusTip(tr("Close the active window"));
    windowMenu->addAction(closeAct);
    connect(closeAct, &QAction::triggered, mdiArea, &QMdiArea::closeActiveSubWindow);

    //closeAllAct = new QAction(tr("Close &All"), this);
    closeAllAct = new QAction(this);
    //closeAllAct->setStatusTip(tr("Close all the windows"));
    windowMenu->addAction(closeAllAct);
    connect(closeAllAct, &QAction::triggered, mdiArea, &QMdiArea::closeAllSubWindows);

    //tileAct = new QAction(tr("&Tile"), this);
    tileAct = new QAction(this);
    //tileAct->setStatusTip(tr("Tile the windows"));
    windowMenu->addAction(tileAct);
    connect(tileAct, &QAction::triggered, mdiArea, &QMdiArea::tileSubWindows);

    //cascadeAct = new QAction(tr("&Cascade"), this);
    cascadeAct = new QAction(this);
    //cascadeAct->setStatusTip(tr("Cascade the windows"));
    windowMenu->addAction(cascadeAct);
    connect(cascadeAct, &QAction::triggered, mdiArea, &QMdiArea::cascadeSubWindows);

    //nextAct = new QAction(tr("Ne&xt"), this);
    nextAct = new QAction(this);
    nextAct->setShortcuts(QKeySequence::NextChild);
    //nextAct->setStatusTip(tr("Move the focus to the next window"));
    windowMenu->addAction(nextAct);
    connect(nextAct, &QAction::triggered, mdiArea, &QMdiArea::activateNextSubWindow);

    //previousAct = new QAction(tr("Pre&vious"), this);
    previousAct = new QAction(this);
    previousAct->setShortcuts(QKeySequence::PreviousChild);
    //previousAct->setStatusTip(tr("Move the focus to the previous window"));
    windowMenu->addAction(previousAct);
    connect(previousAct, &QAction::triggered, mdiArea, &QMdiArea::activatePreviousSubWindow);

    windowMenuSeparatorAct = new QAction(this);
    windowMenuSeparatorAct->setSeparator(true);

    updateWindowMenu();

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));

    //aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
    aboutAct = new QAction (this);
    //aboutAct->setStatusTip(tr("Show the application's About box"));
    helpMenu->addAction(aboutAct);
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

    //aboutQtAct = helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
    aboutQtAct = new QAction (this);
    //aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    helpMenu->addAction(aboutQtAct);
    connect(aboutQtAct, &QAction::triggered, qApp, &QApplication::aboutQt);

    helpMenu->addSeparator();

    //englishAct = helpMenu->addAction(tr("English"), this, [=]() { setLanguage(QLocale(QLocale::English)); });
    englishAct = new QAction(this);
    //englishAct->setStatusTip(tr("Switch the interface to English"));
    englishAct->setCheckable(true);
    helpMenu->addAction(englishAct);
    connect(englishAct, &QAction::triggered, this, [=]() { setLanguage(QLocale(QLocale::English)); });

    //russianAct = helpMenu->addAction(tr("Russian"), this, [=]() { setLanguage(QLocale(QLocale::Russian)); });
    russianAct = new QAction(this);
    //russianAct->setStatusTip(tr("Switch the interface to Russian"));
    russianAct->setCheckable(true);
    helpMenu->addAction(russianAct);
    connect(russianAct, &QAction::triggered, this, [=]() { setLanguage(QLocale(QLocale::Russian)); });

    menuThemes = menuBar()->addMenu(tr("Themes"));
    connect(menuThemes, &QMenu::aboutToShow, this, &MainWindow::updateThemesMenu);

    //themeClientor = new QAction(tr("Clientor"), this);
    themeClientor = new QAction(this);
    //themeClientor->setStatusTip(tr("theme clientor"));
    themeClientor->setCheckable(true);
    connect(themeClientor, &QAction::triggered, this, [=]() { setNewTheme( "Clientor" ); });
    menuThemes->addAction(themeClientor);

    //themeDtor = new QAction(tr("Dtor"), this);
    themeDtor = new QAction(this);
    //themeDtor->setStatusTip(tr("theme dtor"));
    themeDtor->setCheckable(true);
    connect(themeDtor, &QAction::triggered, this, [=]() { setNewTheme( "Dtor" ); });
    menuThemes->addAction(themeDtor);

    //themeMaterial_blue = new QAction(tr("material-blue"), this);
    themeMaterial_blue = new QAction(this);
    //themeMaterial_blue->setStatusTip(tr("theme material-blue"));
    themeMaterial_blue->setCheckable(true);
    connect(themeMaterial_blue, &QAction::triggered, this, [=]() { setNewTheme( "Material-blue" ); });
    menuThemes->addAction(themeMaterial_blue);

    //themeMaterial_dark = new QAction(tr("material_dark"), this);
    themeMaterial_dark = new QAction(this);
    //themeMaterial_dark->setStatusTip(tr("theme material-dark"));
    themeMaterial_dark->setCheckable(true);
    connect(themeMaterial_dark, &QAction::triggered, this, [=]() { setNewTheme( "Material-dark" ); });
    menuThemes->addAction(themeMaterial_dark);

    //themeNeonButtons = new QAction(tr("NeonButtons"), this);
    themeNeonButtons = new QAction(this);
    //themeNeonButtons->setStatusTip(tr("theme NeonButtons"));
    themeNeonButtons->setCheckable(true);
    connect(themeNeonButtons, &QAction::triggered, this, [=]() { setNewTheme( "NeonButtons" ); });
    menuThemes->addAction(themeNeonButtons);

    //themeUbuntu = new QAction(tr("ubuntu"), this);
    themeUbuntu = new QAction(this);
    //themeUbuntu->setStatusTip(tr("theme ubuntu"));
    themeUbuntu->setCheckable(true);
    connect(themeUbuntu, &QAction::triggered, this, [=]() { setNewTheme( "Ubuntu" ); });
    menuThemes->addAction(themeUbuntu);

    menuThemes->addSeparator();

    //themeDefault = new QAction(DefaultTheme.title, this);
    themeDefault = new QAction(this);
    //themeDefault->setStatusTip(tr("restore default theme"));
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
    setWindowTitle(QCoreApplication::translate("MainWindow", "MDI"));

    fileMenu->setTitle(QCoreApplication::translate("MainWindow", "&File"));

    newAct->setText(QCoreApplication::translate("MainWindow", "&New"));
    newAct->setStatusTip(QCoreApplication::translate("MainWindow", "Create a new file"));
    openAct->setText(QCoreApplication::translate("MainWindow", "&Open..."));
    openAct->setStatusTip(QCoreApplication::translate("MainWindow", "Open an existing file"));
    saveAct->setText(QCoreApplication::translate("MainWindow", "&Save"));
    saveAct->setStatusTip(QCoreApplication::translate("MainWindow", "Save the document to disk"));
    saveAsAct->setText(QCoreApplication::translate("MainWindow", "Save &As..."));
    saveAsAct->setStatusTip(QCoreApplication::translate("MainWindow", "Save the document under a new name"));
    printAct->setText(QCoreApplication::translate("MainWindow", "Print"));
    printAct->setStatusTip(QCoreApplication::translate("MainWindow", "Print the document"));
    recentMenu->setTitle(QCoreApplication::translate("MainWindow", "Recent..."));
    switchLayout->setText(QCoreApplication::translate("MainWindow", "Switch layout direction"));
    exitAct->setText(QCoreApplication::translate("MainWindow", "E&xit"));
    exitAct->setStatusTip(QCoreApplication::translate("MainWindow", "Exit the application"));

#ifndef QT_NO_CLIPBOARD

    editMenu->setTitle(QCoreApplication::translate("MainWindow", "&Edit"));

    cutAct->setText(QCoreApplication::translate("MainWindow", "Cu&t"));
    cutAct->setStatusTip(QCoreApplication::translate("MainWindow",
                                                     "Cut the current selection's contents to the clipboard"));
    copyAct->setText(QCoreApplication::translate("MainWindow", "&Copy"));
    copyAct->setStatusTip(QCoreApplication::translate("MainWindow",
                                                      "Copy the current selection's contents to the clipboard"));
    pasteAct->setText(QCoreApplication::translate("MainWindow", "&Paste"));
    pasteAct->setStatusTip(QCoreApplication::translate("MainWindow",
                                                       "Paste the clipboard's contents into the current selection"));

#endif

    copyFormatAct->setText(QCoreApplication::translate("MainWindow", "Copy format"));
    copyFormatAct->setStatusTip(QCoreApplication::translate("MainWindow", "Copy the selected text format"));
    applyFormatAct->setText(QCoreApplication::translate("MainWindow", "Apply format"));
    applyFormatAct->setStatusTip(QCoreApplication::translate("MainWindow", "Apply format to selected text"));
    changeFontAct->setText(QCoreApplication::translate("MainWindow", "Сhange font"));
    changeFontAct->setStatusTip(QCoreApplication::translate("MainWindow", "Сhange the font of the selected text"));

    alignRightAct->setText(QCoreApplication::translate("MainWindow", "Align right"));
    alignRightAct->setStatusTip(QCoreApplication::translate("MainWindow", "Change the alignment of the selected text"));
    alignLeftAct->setText(QCoreApplication::translate("MainWindow", "Align left"));
    alignLeftAct->setStatusTip(QCoreApplication::translate("MainWindow", "Change the alignment of the selected text"));
    alignCenterAct->setText(QCoreApplication::translate("MainWindow", "Align center"));
    alignCenterAct->setStatusTip(QCoreApplication::translate("MainWindow", "Change the alignment of the selected text"));
    dateAndTimeAct->setText(QCoreApplication::translate("MainWindow", "Date and time"));
    dateAndTimeAct->setStatusTip(QCoreApplication::translate("MainWindow", "Insert current date and time"));



    windowMenu->setTitle(QCoreApplication::translate("MainWindow", "&Window"));

    closeAct->setText(QCoreApplication::translate("MainWindow", "Cl&ose"));
    closeAct->setStatusTip(QCoreApplication::translate("MainWindow", "Close the active window"));
    closeAllAct->setText(QCoreApplication::translate("MainWindow", "Close &All"));
    closeAllAct->setStatusTip(QCoreApplication::translate("MainWindow", "Close all the windows"));
    tileAct->setText(QCoreApplication::translate("MainWindow", "&Tile"));
    tileAct->setStatusTip(QCoreApplication::translate("MainWindow", "Tile the windows"));
    cascadeAct->setText(QCoreApplication::translate("MainWindow", "&Cascade"));
    cascadeAct->setStatusTip(QCoreApplication::translate("MainWindow", "Cascade the windows"));
    nextAct->setText(QCoreApplication::translate("MainWindow", "Ne&xt"));
    nextAct->setStatusTip(QCoreApplication::translate("MainWindow", "Move the focus to the next window"));
    previousAct->setText(QCoreApplication::translate("MainWindow", "Pre&vious"));
    previousAct->setStatusTip(QCoreApplication::translate("MainWindow", "Move the focus to the previous window"));


    helpMenu->setTitle(QCoreApplication::translate("MainWindow", "&Help"));

    aboutAct->setText(QCoreApplication::translate("MainWindow", "&About"));
    aboutAct->setStatusTip(QCoreApplication::translate("MainWindow", "Show the application's About box"));
    aboutQtAct->setText(QCoreApplication::translate("MainWindow", "About &Qt"));
    aboutQtAct->setStatusTip(QCoreApplication::translate("MainWindow", "Show the Qt library's About box"));
    englishAct->setText(QCoreApplication::translate("MainWindow", "English"));
    englishAct->setStatusTip(QCoreApplication::translate("MainWindow", "Switch the interface to English"));
    russianAct->setText(QCoreApplication::translate("MainWindow", "Russian"));
    russianAct->setStatusTip(QCoreApplication::translate("MainWindow", "Switch the interface to Russian"));


    menuThemes->setTitle(QCoreApplication::translate("MainWindow", "Themes"));

    themeClientor->setText(QCoreApplication::translate("MainWindow", "Clientor"));
    themeClientor->setStatusTip(QCoreApplication::translate("MainWindow", "theme clientor"));
    themeDtor->setText(QCoreApplication::translate("MainWindow", "Dtor"));
    themeDtor->setStatusTip(QCoreApplication::translate("MainWindow", "theme dtor"));
    themeMaterial_blue->setText(QCoreApplication::translate("MainWindow", "material-blue"));
    themeMaterial_blue->setStatusTip(QCoreApplication::translate("MainWindow", "theme material-blue"));
    themeMaterial_dark->setText(QCoreApplication::translate("MainWindow", "material_dark"));
    themeMaterial_dark->setStatusTip(QCoreApplication::translate("MainWindow", "theme material-dark"));
    themeNeonButtons->setText(QCoreApplication::translate("MainWindow", "NeonButtons"));
    themeNeonButtons->setStatusTip(QCoreApplication::translate("MainWindow", "theme NeonButtons"));
    themeUbuntu->setText(QCoreApplication::translate("MainWindow", "ubuntu"));
    themeUbuntu->setStatusTip(QCoreApplication::translate("MainWindow", "theme ubuntu"));
    themeDefault->setText(QCoreApplication::translate("MainWindow", DefaultTheme.title.toUtf8()));
    themeDefault->setStatusTip(QCoreApplication::translate("MainWindow", "restore default theme"));

    // и т.д. и т.п.

    statusBar()->showMessage(QCoreApplication::translate("MainWindow", "Ready"));

}

void MainWindow::setLanguage(const QLocale newLocale)
{
    QLocale localeRU (QLocale::Russian);
    QLocale localeEN (QLocale::English);
    QString flName{""};

    if (newLocale.name() == localeRU.name())
    {
        flName = ":/i18n/MDIeditor_ru_RU.qm";
        locale = localeRU;
        russianAct->setChecked(true);
        englishAct->setChecked(false);
    }
    else
    {
        flName = ":/i18n/MDIeditor_en_001.qm";
        locale = localeEN;
        russianAct->setChecked(false);
        englishAct->setChecked(true);
    }

    // Загружаем файл перевода
    if (translator.load(flName))
    {
        qApp->installTranslator(&translator);
        QLocale::setDefault(locale);
        retranslateUi();
    }
    else
    {
        // Ошибка загрузки файла перевода
        qWarning() << "Failed to load translation file:" << flName;
    }

}
