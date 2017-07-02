#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QDir>
#include <QDateTime>
#include <QMimeDatabase>
#include <QMimeType>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_m_lstwgtFolders_itemClicked(QListWidgetItem *item);

    void on_m_pbSearch_clicked();

private:

    Ui::MainWindow *ui;
    void showFiles(const QStringList &files);
    void FillListWidget(QString driveChar);
    QListWidgetItem *itemToReturn(QIcon icon, QString path);
    QDir currentDir;
    QStringList findFiles(const QStringList &files, const QString &text);
    void findRecursion(const QString &path, const QString &pattern, QStringList *result);
};

#endif // MAINWINDOW_H
