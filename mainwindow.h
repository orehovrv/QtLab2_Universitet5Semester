#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonArray>
#include <QFile>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

    QAction * newDocument;
    QAction * openDocument;
    QAction * saveDocument;
    QAction * exitProgram;

    QWidget * centralwidget;

    QVBoxLayout * verticalLayout;
    QVBoxLayout * verticalLayoutTwo;
    QVBoxLayout * verticalLayoutOne;
    QHBoxLayout * horizontalLayoutInputText;
    QGridLayout * gridLayout;
    QGridLayout * gridLayoutButton;

    QLabel * labelGroup;
    QLabel * labelNumber;
    QLabel * labelStrNumber;
    QLabel * labelInputText;
    QLabel * labelDirection;
    QLabel * labelStudent;

    QListWidget * listWidgetGroup;
    QListWidget * listWidgetDirection;
    QListWidget * listWidgetStudent;

    QLineEdit * lineEdit;

    QPushButton * buttonAddNumber;
    QPushButton * buttonAddStudent;
    QPushButton * buttonAddGroup;
    QPushButton * buttonAddDirection;

    QMenuBar * menubar;
    QMenu * menu;
    QStatusBar * statusbar;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newDocument_triggered();
    void openDocument_triggered();
    void saveDocument_triggered();

    void buttonAddNumber_clicked();
    void buttonAddStudent_clicked();
    void buttonAddGroup_clicked();
    void buttonAddDirection_clicked();

    void listWidgetGroup_itemClicked();
    void listWidgetGroup_itemDoubleClicked();
    void listWidgetDirection_itemClicked();
    void listWidgetDirection_itemDoubleClicked();
    void listWidgetStudent_itemClicked();
    void listWidgetStudent_itemDoubleClicked();

private:
    QStringList listStringDirection;
    QStringList listStringGroup;
    QStringList listStringStudent;
    QString number = "";

    QJsonDocument doc;
    QJsonParseError docError;
    QString wayDoc;

    int numberDirection = -1;
    int numberGroup = -1;
    int numberStudent = -1;

    void clearWidgetDirection();
    void clearWidgetGroup();
    void clearWidgetStudent();
    void clearWidgetNumber();

    void viewWidgetDirection();
    void viewWidgetGroup();
    void viewWidgetStudent();
    void viewWidgetNumber();

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
