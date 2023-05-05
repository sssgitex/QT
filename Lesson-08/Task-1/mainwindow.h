#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define APP_NAME "Lesson 07. Task 1."

#include <iostream>

#include <QMainWindow>
#include <QTextCharFormat>
#include <QLocale>
#include <QTranslator>


class MdiChild;
QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QMdiArea;
class QMdiSubWindow;
class QByteArray;


QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

    bool openFile(const QString &fileName);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void newFile();
    void open();
    void save();
    void saveAs();
    void print();
    void updateRecentFileActions();
    void openRecentFile();

#ifndef QT_NO_CLIPBOARD
    void cut();
    void copy();
    void paste();
#endif

    void copyFormat();
    void applyFormat();
    void changeFont();
    void changeAlignment(const Qt::AlignmentFlag);
    void pasteDateAndTime();

    void about();
    void updateMenus();
    void updateWindowMenu();
    void updateThemesMenu();
    MdiChild *createMdiChild();
    void switchLayoutDirection();

private:
    enum { MaxRecentFiles = 5 };

    void createActions();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool loadFile(const QString &fileName);
    static bool hasRecentFiles();
    void prependToRecentFiles(const QString &fileName);
    void setRecentFilesVisible(bool visible);
    MdiChild *activeMdiChild() const;
    QMdiSubWindow *findMdiChild(const QString &fileName) const;

    void setNewTheme(const QString );
    void setDefaultTheme();

    void retranslateUi();

    void setLanguage(const QLocale);

private:
    QMdiArea *mdiArea;
    QToolBar *fileToolBar;

    QMenu *fileMenu;
    QMenu *windowMenu;
    QMenu *menuThemes;
    QMenu *recentMenu;
    QMenu *editMenu;
    QMenu *helpMenu;

    QAction *openAct;
    QAction *newAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *printAct;
    QAction *recentFileActs[MaxRecentFiles];
    QAction *recentFileSeparator;
    QAction *recentFileSubMenuAct;
    QAction *exitAct;

#ifndef QT_NO_CLIPBOARD
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
#endif

    QAction *copyFormatAct;
    QAction *applyFormatAct;
    QAction *changeFontAct;

    QAction *alignRightAct;
    QAction *alignLeftAct;
    QAction *alignCenterAct;
    QAction *dateAndTimeAct;



    QAction *switchLayout;
    QAction *closeAct;
    QAction *closeAllAct;
    QAction *tileAct;
    QAction *cascadeAct;
    QAction *nextAct;
    QAction *previousAct;
    QAction *windowMenuSeparatorAct;

    QAction *themeClientor;
    QAction *themeDtor;
    QAction *themeMaterial_blue;
    QAction *themeMaterial_dark;
    QAction *themeNeonButtons;
    QAction *themeUbuntu;
    QAction *themeDefault;

    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *englishAct;
    QAction *russianAct;


    QString current_theme;

    struct m_Theme
    {
    public:
        const QString title {tr("default")};
        void set ();
        void restore ();
    private:
        QString m_StyleName, m_StyleSheet;
    } DefaultTheme;

    //friend struct m_Theme;

    std::optional <QTextCharFormat> fmt{std::nullopt};

    QTranslator translator;
    QLocale locale;
};

QByteArray readTextFile(const QString&);

#endif
