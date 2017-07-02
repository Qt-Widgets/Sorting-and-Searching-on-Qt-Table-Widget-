#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "customtablewidgetitem.h"

#include <QFileIconProvider>
#include <QIcon>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    FillListWidget("C:\\Qt\\Qt5.7.1\\5.7\\mingw53_32\\bin");

    showMaximized();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::FillListWidget(QString driveChar)
{

    QFileIconProvider ipRoot;
    QIcon iconRoot;
    QFileInfo fileInfo;


    iconRoot = QIcon(ipRoot.icon(QFileIconProvider::Drive));

    fileInfo = driveChar;
    QListWidgetItem * itemAdd = itemToReturn(iconRoot,fileInfo.filePath());
    ui->m_lstwgtFolders->addItem(itemAdd);

}

QListWidgetItem* MainWindow::itemToReturn(QIcon icon,QString path){


    QListWidgetItem *item = new QListWidgetItem(icon,path);

    return item;

}

void MainWindow::on_m_lstwgtFolders_itemClicked(QListWidgetItem *item)
{
//   qDebug() << item->text();

   QString path=item->text();
   QString fileName;
   QString text;

   currentDir = QDir(path);
   QStringList files;
   findRecursion(path, fileName.isEmpty() ? QStringLiteral("*") : fileName, &files);
   if (!text.isEmpty())
       files = findFiles(files, text);
   showFiles(files);

}

void MainWindow::findRecursion(const QString &path, const QString &pattern, QStringList *result)
{
    QDir currentDir(path);
    const QString prefix = path + QLatin1Char('/');
    foreach (const QString &match, currentDir.entryList(QStringList(pattern), QDir::Files | QDir::NoSymLinks))
        result->append(prefix + match);
    foreach (const QString &dir, currentDir.entryList(QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot))
        findRecursion(prefix + dir, pattern, result);
}


QStringList MainWindow::findFiles(const QStringList &files, const QString &text)
{


    QStringList foundFiles;

    for (int i = 0; i < files.size(); ++i)
    {

        QCoreApplication::processEvents();

        const QString fileName = files.at(i);

        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly)) {
            QString line;
            QTextStream in(&file);
            while (!in.atEnd())
            {

                line = in.readLine();
                if (line.contains(text, Qt::CaseInsensitive)) {
                    foundFiles << files[i];
                    break;
                }
            }
        }
    }
    return foundFiles;
}

void MainWindow::showFiles(const QStringList &files)
{
    ui->m_tblwgtFiolderFiles->clearContents();
    ui->m_tblwgtFiolderFiles->setRowCount(0);

    for (int i = 0; i < files.size(); ++i)
    {
        const QString &fileName = files.at(i);
        const QString toolTip = QDir::toNativeSeparators(fileName);
        const QString relativePath = QDir::toNativeSeparators(currentDir.relativeFilePath(fileName));
        const qint64 size = QFileInfo(fileName).size();

       const QString strDate= QFileInfo(fileName).created().toString("ddMMMyyyy hh:mm:ss.zzz");
       const QString strPath= QFileInfo(fileName).absoluteFilePath();

        QTableWidgetItem *fileNameItem = new QTableWidgetItem(relativePath);
        fileNameItem->setToolTip(toolTip);

        fileNameItem->setFlags(fileNameItem->flags() ^ Qt::ItemIsEditable);

        QString strSize=tr("%1 KB")
                .arg(int((size + 1023) / 1024));

        QMimeDatabase mimeDatabase;
        const QMimeType mimeType = mimeDatabase.mimeTypeForFile(fileName);
        const QString strType= mimeType.name();

//        QTableWidgetItem *sizeItem = new QTableWidgetItem(strSize);
         CustomTableWidgetItem *sizeItem = new CustomTableWidgetItem();
         sizeItem->setText(strSize);

        sizeItem->setToolTip(toolTip);
        sizeItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        sizeItem->setFlags(sizeItem->flags() ^ Qt::ItemIsEditable);

        QTableWidgetItem *Date = new QTableWidgetItem(strDate);
        QTableWidgetItem *Path = new QTableWidgetItem(strPath);
        QTableWidgetItem *Type = new QTableWidgetItem(strType);


//        qDebug() << relativePath << strType<< strSize <<strDate << strPath ;

        int row = ui->m_tblwgtFiolderFiles->rowCount();
        ui->m_tblwgtFiolderFiles->insertRow(row);
        ui->m_tblwgtFiolderFiles->setItem(row, 0, fileNameItem);
        ui->m_tblwgtFiolderFiles->setItem(row, 1, Type);
        ui->m_tblwgtFiolderFiles->setItem(row, 2, sizeItem);
        ui->m_tblwgtFiolderFiles->setItem(row, 3, Date);
        ui->m_tblwgtFiolderFiles->setItem(row, 4, Path);

//        QEventLoop loop;
//        QTimer::singleShot(10,&loop,SLOT(quit()));
//        loop.exec();

    }

    ui->m_tblwgtFiolderFiles->setColumnWidth(0,500);
    ui->m_tblwgtFiolderFiles->setColumnWidth(1,300);
    ui->m_tblwgtFiolderFiles->setColumnWidth(2,200);
    ui->m_tblwgtFiolderFiles->setColumnWidth(3,200);
    ui->m_tblwgtFiolderFiles->setColumnWidth(4,500);

    ui->m_tblwgtFiolderFiles->sortByColumn(2);


}

void MainWindow::on_m_pbSearch_clicked()
{

    QString strFilterText = ui->m_leFileSearch->text();
    for( int nRowCount = 0; nRowCount < ui->m_tblwgtFiolderFiles->rowCount(); ++nRowCount )
    {
        bool bMatch = false;
        QTableWidgetItem *item =ui->m_tblwgtFiolderFiles->item( nRowCount, 0 );//row first column
        if( item->text().contains(strFilterText) )
        {
            bMatch = true;
        }
        ui->m_tblwgtFiolderFiles->setRowHidden(nRowCount, !bMatch );
    }

/*************************
NOTE: searching in all columns
*************************/


//    QString strFilterText = ui->m_leFileSearch->text();
//    for( int nRowCount = 0; nRowCount < ui->m_tblwgtFiolderFiles->rowCount(); ++nRowCount )
//    {
//        bool bMatch = false;
//        for( int nColumnCount = 0; nColumnCount < ui->m_tblwgtFiolderFiles->columnCount(); ++nColumnCount )
//        {
//            QTableWidgetItem *item =ui->m_tblwgtFiolderFiles->item( nRowCount, nColumnCount );
//            if( item->text().contains(strFilterText) )
//            {
//                bMatch = true;
//                break;
//            }
//        }
//        ui->m_tblwgtFiolderFiles->setRowHidden( nRowCount, !bMatch );
//    }

}
