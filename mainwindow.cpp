#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    newDocument = new QAction(this);
    newDocument->setText("Новый документ");
    openDocument = new QAction(this);
    openDocument->setText("Открыть документ");
    saveDocument = new QAction(this);
    saveDocument->setText("Сохранить документ");
    exitProgram = new QAction(this);
    exitProgram->setText("Выход");

    centralwidget = new QWidget(this);
    centralwidget->setMinimumSize(QSize(0, 0));
    centralwidget->setMaximumSize(QSize(16777215, 16777215));

    labelInputText = new QLabel(centralwidget);
    labelInputText->setAlignment(Qt::AlignCenter);
    labelInputText->setText("Введите текст:");
    labelDirection = new QLabel(centralwidget);
    labelDirection->setAlignment(Qt::AlignCenter);
    labelDirection->setText("Направления подготовки");
    labelGroup = new QLabel(centralwidget);
    labelGroup->setAlignment(Qt::AlignCenter);
    labelGroup->setText("Номера групп");
    labelStudent = new QLabel(centralwidget);
    labelStudent->setAlignment(Qt::AlignCenter);
    labelStudent->setText("ФИО студентов");
    labelNumber = new QLabel(centralwidget);
    labelNumber->setAlignment(Qt::AlignCenter);
    labelNumber->setText("Номер зачетки");
    labelStrNumber = new QLabel(centralwidget);
    labelStrNumber->setAlignment(Qt::AlignCenter);
    labelStrNumber->setText("");

    buttonAddDirection = new QPushButton(centralwidget);
    buttonAddDirection->setText("Добавить направление");
    buttonAddGroup = new QPushButton(centralwidget);
    buttonAddGroup->setText("Добавить группу");
    buttonAddStudent = new QPushButton(centralwidget);
    buttonAddStudent->setText("Добавить студента");
    buttonAddNumber = new QPushButton(centralwidget);
    buttonAddNumber->setText("Указать номер зачетки");

    listWidgetDirection = new QListWidget(centralwidget);
    listWidgetGroup = new QListWidget(centralwidget);
    listWidgetStudent = new QListWidget(centralwidget);

    lineEdit = new QLineEdit(centralwidget);

    horizontalLayoutInputText = new QHBoxLayout();
    horizontalLayoutInputText->addWidget(labelInputText);
    horizontalLayoutInputText->addWidget(lineEdit);

    gridLayoutButton = new QGridLayout();
    gridLayoutButton->addWidget(buttonAddNumber, 1, 1, 1, 1);
    gridLayoutButton->addWidget(buttonAddStudent, 1, 0, 1, 1);
    gridLayoutButton->addWidget(buttonAddGroup, 0, 1, 1, 1);
    gridLayoutButton->addWidget(buttonAddDirection, 0, 0, 1, 1);

    verticalLayoutOne = new QVBoxLayout();
    verticalLayoutOne->setSpacing(10);
    verticalLayoutOne->addLayout(horizontalLayoutInputText);
    verticalLayoutOne->addLayout(gridLayoutButton);
    verticalLayoutOne->addWidget(labelDirection);
    verticalLayoutOne->addWidget(listWidgetDirection);
    verticalLayoutOne->addWidget(labelStudent);
    verticalLayoutOne->addWidget(listWidgetStudent);
    verticalLayoutOne->setStretch(3, 1);
    verticalLayoutOne->setStretch(5, 3);

    verticalLayoutTwo = new QVBoxLayout();
    verticalLayoutTwo->addWidget(labelGroup);
    verticalLayoutTwo->addWidget(listWidgetGroup);
    verticalLayoutTwo->addWidget(labelNumber);
    verticalLayoutTwo->addWidget(labelStrNumber);

    gridLayout = new QGridLayout();
    gridLayout->setSpacing(10);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->addLayout(verticalLayoutOne, 0, 0, 1, 1);
    gridLayout->addLayout(verticalLayoutTwo, 0, 1, 1, 1);
    gridLayout->setColumnStretch(0, 3);
    gridLayout->setColumnStretch(1, 1);

    verticalLayout = new QVBoxLayout(centralwidget);
    verticalLayout->setSpacing(6);
    verticalLayout->setContentsMargins(10, 10, 10, 0);
    verticalLayout->addLayout(gridLayout);

    menubar = new QMenuBar(this);
    menubar->setGeometry(QRect(0, 0, 800, 20));

    menu = new QMenu(menubar);
    menu->setTitle("Действие");
    menu->addAction(newDocument);
    menu->addAction(openDocument);
    menu->addAction(saveDocument);
    menu->addSeparator();
    menu->addAction(exitProgram);

    menubar->addAction(menu->menuAction());

    statusbar = new QStatusBar(this);

    this->setMinimumSize(QSize(400, 320));
    this->setCentralWidget(centralwidget);
    this->setMenuBar(menubar);
    this->setStatusBar(statusbar);

    connect(newDocument, SIGNAL(triggered()), this, SLOT(newDocument_triggered()));
    connect(openDocument, SIGNAL(triggered()), this, SLOT(openDocument_triggered()));
    connect(saveDocument, SIGNAL(triggered()), this, SLOT(saveDocument_triggered()));
    connect(exitProgram, SIGNAL(triggered()), this, SLOT(close()));

    connect(buttonAddDirection, SIGNAL(clicked()), this, SLOT(buttonAddDirection_clicked()));
    connect(buttonAddGroup, SIGNAL(clicked()), this, SLOT(buttonAddGroup_clicked()));
    connect(buttonAddStudent, SIGNAL(clicked()), this, SLOT(buttonAddStudent_clicked()));
    connect(buttonAddNumber, SIGNAL(clicked()), this, SLOT(buttonAddNumber_clicked()));

    connect(listWidgetDirection, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(listWidgetDirection_itemClicked()));
    connect(listWidgetDirection, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(listWidgetDirection_itemDoubleClicked()));
    connect(listWidgetGroup, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(listWidgetGroup_itemClicked()));
    connect(listWidgetGroup, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(listWidgetGroup_itemDoubleClicked()));
    connect(listWidgetStudent, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(listWidgetStudent_itemClicked()));
    connect(listWidgetStudent, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(listWidgetStudent_itemDoubleClicked()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::clearWidgetDirection() {
    numberDirection = -1;
    listStringDirection.clear();
    listWidgetDirection->clear();
}

void MainWindow::clearWidgetGroup() {
    numberGroup = -1;
    listStringGroup.clear();
    listWidgetGroup->clear();
}

void MainWindow::clearWidgetStudent() {
    numberStudent = -1;
    listStringStudent.clear();
    listWidgetStudent->clear();
}

void MainWindow::clearWidgetNumber() {
    number = "";
    labelStrNumber->setText(number);
}

void MainWindow::viewWidgetDirection() {
    clearWidgetDirection();

    QJsonObject allDirection = doc.object();
    QJsonArray arrayDirection = allDirection.value("DIRECTION").toArray();

    QJsonObject temp;
    for(int i = 0; i < arrayDirection.count(); i++) {
        temp = arrayDirection.at(i).toObject();
        listStringDirection.append(temp.value("NAME_DIRECTION").toString());
    }

    listWidgetDirection->addItems(listStringDirection);
}

void MainWindow::viewWidgetGroup() {
    clearWidgetGroup();

    numberDirection = listWidgetDirection->currentRow();

    QJsonObject allDirection = doc.object();
    QJsonArray arrayDirection = allDirection.value("DIRECTION").toArray();

    QJsonObject allGroup = arrayDirection.at(numberDirection).toObject();
    QJsonArray arrayGroup = allGroup.value("LIST_GROUP").toArray();

    QJsonObject temp;
    for(int i = 0; i < arrayGroup.count(); i++) {
        temp = arrayGroup.at(i).toObject();
        listStringGroup.append(temp.value("NAME_GROUP").toString());
    }

    listWidgetGroup->addItems(listStringGroup);
}

void MainWindow::viewWidgetStudent() {
    clearWidgetStudent();

    numberDirection = listWidgetDirection->currentRow();
    numberGroup = listWidgetGroup->currentRow();

    QJsonObject allDirection = doc.object();
    QJsonArray arrayDirection = allDirection.value("DIRECTION").toArray();

    QJsonObject allGroup = arrayDirection.at(numberDirection).toObject();
    QJsonArray arrayGroup = allGroup.value("LIST_GROUP").toArray();

    QJsonObject allStudent = arrayGroup.at(numberGroup).toObject();
    QJsonArray arrayStudent = allStudent.value("LIST_STUDENT").toArray();

    QJsonObject temp;
    for(int i = 0; i < arrayStudent.count(); i++) {
        temp = arrayStudent.at(i).toObject();
        listStringStudent.append(temp.value("NAME_STUDENT").toString());
    }

    listWidgetStudent->addItems(listStringStudent);
}

void MainWindow::viewWidgetNumber() {
    labelStrNumber->setText(number);
}

void MainWindow::newDocument_triggered() {
    doc = *(new QJsonDocument);
    wayDoc = "";

    clearWidgetDirection();
    clearWidgetGroup();
    clearWidgetStudent();
    clearWidgetNumber();
}

void MainWindow::openDocument_triggered() {
    QFile file;

    wayDoc = QFileDialog::getOpenFileName(nullptr, "", "C:\\lab_QT\\LAB_2", "*.json");
    file.setFileName(wayDoc);

    if(file.open(QIODevice::ReadOnly | QFile::Text)) {
        doc = QJsonDocument::fromJson(QByteArray(file.readAll()), &docError);
    }

    file.close();

    clearWidgetDirection();
    clearWidgetGroup();
    clearWidgetStudent();
    clearWidgetNumber();

    viewWidgetDirection();

    labelStrNumber->setText("Загружен");
}

void MainWindow::saveDocument_triggered() {
    if(wayDoc.isEmpty()) {
        labelStrNumber->setText("Не открыт файл");
        return;
    }

    QFile file;

    file.setFileName(wayDoc);
    file.open(QIODevice::WriteOnly | QFile::Text);
    file.write(doc.toJson());

    file.close();

    labelStrNumber->setText("Сохранен");
}

void MainWindow::buttonAddDirection_clicked() {
    QString tempStr = lineEdit->text();

    if(tempStr.isEmpty()) return;

    QJsonObject newDirection;
    newDirection.insert("NAME_DIRECTION", tempStr);
    newDirection.insert("LIST_GROUP", QJsonArray {});

    QJsonObject allDirection = doc.object();
    QJsonArray arrayDirection = allDirection.value("DIRECTION").toArray();
    arrayDirection.append(newDirection);

    QJsonObject All;
    All.insert("DIRECTION", arrayDirection);

    doc.setObject(All);

    clearWidgetDirection();
    clearWidgetGroup();
    clearWidgetStudent();
    clearWidgetNumber();

    viewWidgetDirection();
}

void MainWindow::buttonAddGroup_clicked() {
    if(numberDirection == -1) {
        labelStrNumber->setText("Неудача");
        return;
    }

    QString tempStr = lineEdit->text();

    if(tempStr.isEmpty()) return;

    QJsonObject newGroup;
    newGroup.insert("NAME_GROUP", tempStr);
    newGroup.insert("LIST_STUDENT", QJsonArray{});

    QJsonObject allDirection = doc.object();
    QJsonArray arrayDirection = allDirection.value("DIRECTION").toArray();

    QJsonObject allGroup = arrayDirection.at(numberDirection).toObject();
    QJsonArray arrayGroup = allGroup.value("LIST_GROUP").toArray();
    arrayGroup.append(newGroup);

    QJsonObject temp;
    temp.insert("NAME_DIRECTION", arrayDirection.at(numberDirection).toObject().value("NAME_DIRECTION").toString());
    temp.insert("LIST_GROUP", arrayGroup);
    arrayDirection.replace(numberDirection, temp);

    QJsonObject All;
    All.insert("DIRECTION", arrayDirection);
    doc.setObject(All);

    clearWidgetGroup();
    clearWidgetStudent();
    clearWidgetNumber();

    viewWidgetGroup();
}

void MainWindow::buttonAddStudent_clicked() {
    if(numberDirection == -1 || numberGroup == -1) {
        labelStrNumber->setText("Неудача");
        return;
    }

    QString tempStr = lineEdit->text();

    if(tempStr.isEmpty()) return;

    QJsonObject newStudent;
    newStudent.insert("NAME_STUDENT", tempStr);
    newStudent.insert("NUMBER_STUDENT", "");

    QJsonObject allDirection = doc.object();
    QJsonArray arrayDirection = allDirection.value("DIRECTION").toArray();

    QJsonObject allGroup = arrayDirection.at(numberDirection).toObject();
    QJsonArray arrayGroup = allGroup.value("LIST_GROUP").toArray();

    QJsonObject allStudent = arrayGroup.at(numberGroup).toObject();
    QJsonArray arrayStudent = allStudent.value("LIST_STUDENT").toArray();

    arrayStudent.append(newStudent);

    QJsonObject temp1;
    temp1.insert("NAME_GROUP", arrayGroup.at(numberGroup).toObject().value("NAME_GROUP").toString());
    temp1.insert("LIST_STUDENT", arrayStudent);
    arrayGroup.replace(numberGroup, temp1);

    QJsonObject temp2;
    temp2.insert("NAME_DIRECTION", arrayDirection.at(numberDirection).toObject().value("NAME_DIRECTION").toString());
    temp2.insert("LIST_GROUP", arrayGroup);
    arrayDirection.replace(numberDirection, temp2);

    QJsonObject All;
    All.insert("DIRECTION", arrayDirection);
    doc.setObject(All);

    clearWidgetStudent();
    clearWidgetNumber();

    viewWidgetStudent();
}

void MainWindow::buttonAddNumber_clicked() {
    if(numberDirection == -1 || numberGroup == -1 || numberStudent == -1) {
        labelStrNumber->setText("Неудача");
        return;
    }

    QString tempStr = lineEdit->text();

    if(tempStr.isEmpty()) return;

    number = tempStr;

    QJsonObject allDirection = doc.object();
    QJsonArray arrayDirection = allDirection.value("DIRECTION").toArray();

    QJsonObject allGroup = arrayDirection.at(numberDirection).toObject();
    QJsonArray arrayGroup = allGroup.value("LIST_GROUP").toArray();

    QJsonObject allStudent = arrayGroup.at(numberGroup).toObject();
    QJsonArray arrayStudent = allStudent.value("LIST_STUDENT").toArray();

    QJsonObject newStudent;
    newStudent.insert("NAME_STUDENT", arrayStudent.at(numberStudent).toObject().value("NAME_STUDENT").toString());
    newStudent.insert("NUMBER_STUDENT", tempStr);

    arrayStudent.replace(numberStudent, newStudent);

    QJsonObject temp1;
    temp1.insert("NAME_GROUP", arrayGroup.at(numberGroup).toObject().value("NAME_GROUP").toString());
    temp1.insert("LIST_STUDENT", arrayStudent);
    arrayGroup.replace(numberGroup, temp1);

    QJsonObject temp2;
    temp2.insert("NAME_DIRECTION", arrayDirection.at(numberDirection).toObject().value("NAME_DIRECTION").toString());
    temp2.insert("LIST_GROUP", arrayGroup);
    arrayDirection.replace(numberDirection, temp2);

    QJsonObject All;
    All.insert("DIRECTION", arrayDirection);
    doc.setObject(All);

    viewWidgetNumber();
}

void MainWindow::listWidgetDirection_itemClicked() {
    clearWidgetGroup();
    clearWidgetStudent();
    clearWidgetNumber();

    viewWidgetGroup();
}

void MainWindow::listWidgetDirection_itemDoubleClicked() {
    QJsonObject allDirection = doc.object();
    QJsonArray arrayDirection = allDirection.value("DIRECTION").toArray();
    arrayDirection.removeAt(numberDirection);

    QJsonObject All;
    All.insert("DIRECTION", arrayDirection);
    doc.setObject(All);

    clearWidgetDirection();
    clearWidgetGroup();
    clearWidgetStudent();
    clearWidgetNumber();

    viewWidgetDirection();
}

void MainWindow::listWidgetGroup_itemClicked() {
    clearWidgetStudent();
    clearWidgetNumber();

    viewWidgetStudent();
}

void MainWindow::listWidgetGroup_itemDoubleClicked() {
    if(numberDirection == -1) {
        labelStrNumber->setText("Неудача");
        return;
    }

    QJsonObject allDirection = doc.object();
    QJsonArray arrayDirection = allDirection.value("DIRECTION").toArray();

    QJsonObject allGroup = arrayDirection.at(numberDirection).toObject();
    QJsonArray arrayGroup = allGroup.value("LIST_GROUP").toArray();
    arrayGroup.removeAt(numberGroup);

    QJsonObject temp;
    temp.insert("NAME_DIRECTION", arrayDirection.at(numberDirection).toObject().value("NAME_DIRECTION").toString());
    temp.insert("LIST_GROUP", arrayGroup);
    arrayDirection.replace(numberDirection, temp);

    QJsonObject All;
    All.insert("DIRECTION", arrayDirection);
    doc.setObject(All);

    clearWidgetGroup();
    clearWidgetStudent();
    clearWidgetNumber();

    viewWidgetGroup();
}

void MainWindow::listWidgetStudent_itemClicked() {
    numberDirection = listWidgetDirection->currentRow();
    numberGroup = listWidgetGroup->currentRow();
    numberStudent = listWidgetStudent->currentRow();

    QJsonObject allDirection = doc.object();
    QJsonArray arrayDirection = allDirection.value("DIRECTION").toArray();

    QJsonObject allGroup = arrayDirection.at(numberDirection).toObject();
    QJsonArray arrayGroup = allGroup.value("LIST_GROUP").toArray();

    QJsonObject allStudent = arrayGroup.at(numberGroup).toObject();
    QJsonArray arrayStudent = allStudent.value("LIST_STUDENT").toArray();

    QJsonObject temp = arrayStudent.at(numberStudent).toObject();

    number = temp.value("NUMBER_STUDENT").toString();

    viewWidgetNumber();
}

void MainWindow::listWidgetStudent_itemDoubleClicked() {
    if(numberDirection == -1 || numberGroup == -1) {
        labelStrNumber->setText(tr("Неудача"));
        return;
    }

    QJsonObject allDirection = doc.object();
    QJsonArray arrayDirection = allDirection.value("DIRECTION").toArray();

    QJsonObject allGroup = arrayDirection.at(numberDirection).toObject();
    QJsonArray arrayGroup = allGroup.value("LIST_GROUP").toArray();

    QJsonObject allStudent = arrayGroup.at(numberGroup).toObject();
    QJsonArray arrayStudent = allStudent.value("LIST_STUDENT").toArray();
    arrayStudent.removeAt(numberStudent);

    QJsonObject temp1;
    temp1.insert("NAME_GROUP", arrayGroup.at(numberGroup).toObject().value("NAME_GROUP").toString());
    temp1.insert("LIST_STUDENT", arrayStudent);
    arrayGroup.replace(numberGroup, temp1);

    QJsonObject temp2;
    temp2.insert("NAME_DIRECTION", arrayDirection.at(numberDirection).toObject().value("NAME_DIRECTION").toString());
    temp2.insert("LIST_GROUP", arrayGroup);
    arrayDirection.replace(numberDirection, temp2);

    QJsonObject All;
    All.insert("DIRECTION", arrayDirection);
    doc.setObject(All);

    clearWidgetStudent();
    clearWidgetNumber();

    viewWidgetStudent();
}
