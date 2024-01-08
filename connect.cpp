#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->username->setPlaceholderText("Enter your username");
    ui->password->setPlaceholderText("Enter your password");

    // Initialize the QSqlDatabase member variable
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("qt5.db");  // Specify the database name

    if (!database.isValid()) {
        qDebug() << "Invalid database";
        QMessageBox::critical(this, "Error", "Invalid database connection.");
    }

    // Create users table if it doesn't exist
    if (database.open()) {
        QSqlQuery qry(database);
        if (!qry.exec("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, username TEXT, password TEXT)")) {
            qDebug() << "Failed to create table:" << qry.lastError().text();
            QMessageBox::critical(this, "Error", "Failed to create table: " + qry.lastError().text());
        }
        database.close();
    } else {
        qDebug() << "Connection failed:" << database.lastError().text();
    }
}

MainWindow::~MainWindow()
{
    if (database.isOpen()) {
        database.close();
    }
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if (database.open()) {
        qDebug() << "Connection successful";
        QMessageBox::information(this, "Connection", "Successful");

        QString username = ui->username->text();
        QString password = ui->password->text();

        QSqlQuery qry(database);  // Use the member variable for the query

        // Check if the username already exists
        qry.prepare("SELECT * FROM users WHERE username = :username");
        qry.bindValue(":username", username);

        if (qry.exec() && qry.next()) {
            qDebug() << "User already exists";
            QMessageBox::warning(this, "Error", "Username already exists. Choose a different username.");
        } else {
            // Insert new user
            qry.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
            qry.bindValue(":username", username);
            qry.bindValue(":password", password);

            if (qry.exec()) {
                qDebug() << "Data inserted successfully";
                QMessageBox::information(this, "Inserted", "Data inserted successfully");
            } else {
                qDebug() << "Failed to insert data:" << qry.lastError().text();
                QMessageBox::critical(this, "Error", "Failed to insert data: " + qry.lastError().text());
            }
        }

        // No need to close the database explicitly; it will be closed when the QSqlDatabase object is destroyed
    } else {
        qDebug() << "Connection failed:" << database.lastError().text();
    }
}

void MainWindow::on_loginButton_clicked()
{
    if (database.open()) {
        qDebug() << "Connection successful";
        QMessageBox::information(this, "Connection", "Successful");

        QString username = ui->loginUsername->text();
        QString password = ui->loginPassword->text();

        QSqlQuery qry(database);  // Use the member variable for the query

        qry.prepare("SELECT * FROM users WHERE username = :username AND password = :password");
        qry.bindValue(":username", username);
        qry.bindValue(":password", password);

        if (qry.exec() && qry.next()) {
            qDebug() << "Login successful";
            QMessageBox::information(this, "Login", "Login successful");
        } else {
            qDebug() << "Login failed:" << qry.lastError().text();
            QMessageBox::critical(this, "Error", "Login failed. Check your username and password.");
        }

        // No need to close the database explicitly; it will be closed when the QSqlDatabase object is destroyed
    } else {
        qDebug() << "Connection failed:" << database.lastError().text();
    }
}
