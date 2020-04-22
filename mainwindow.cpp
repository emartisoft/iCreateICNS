#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/res/emarti.png"));
    fileName = "";
    ui->bCreate->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bOpenImage_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, "Open image file", QDir::homePath(), tr("Image file (*.png);;All files (*.*)"));
    if(!fileName.isEmpty())
    {
        ui->fImage->setIcon(QIcon(fileName));
        QFileInfo fi(fileName);
        ui->tIconsetname->setText(fi.fileName().split('.')[0]);
        fileNamePath = fi.absolutePath();
        ui->bCreate->setEnabled(true);
    }
}

void MainWindow::on_bCreate_clicked()
{
    if ((fileName.isEmpty()) || (ui->tIconsetname->text().length()<1))
    {
        QMessageBox::information(this, "Info", "Please, type icon set name.", QMessageBox::Ok);
        return;
    }

    QString iconsetfolder = fileNamePath + "/" + ui->tIconsetname->text() + ".iconset";

    //    mkdir set.iconset
    p.startDetached("mkdir", QStringList() << iconsetfolder);

    //    sips -z 16 16 image.png --out set/icon_16x16.png
    p.startDetached("sips", QStringList() << "-z" << "16" << "16" << fileName << "--out" << iconsetfolder + "/icon_16x16.png");

    //    sips -z 32 32 image.png --out set/icon_16x16@2x.png
    p.startDetached("sips", QStringList() << "-z" << "32" << "32" << fileName << "--out" << iconsetfolder + "/icon_16x16@2x.png");

    //    sips -z 32 32 image.png --out set/icon_32x32.png
    p.startDetached("sips", QStringList() << "-z" << "32" << "32" << fileName << "--out" << iconsetfolder + "/icon_32x32.png");

    //    sips -z 25 25 image.png --out set/icon_25x25@2x.png
    p.startDetached("sips", QStringList() << "-z" << "25" << "25" << fileName << "--out" << iconsetfolder + "/icon_25x25@2x.png");

    //    sips -z 64 64 image.png --out set/icon_32x32@2x.png
    p.startDetached("sips", QStringList() << "-z" << "64" << "64" << fileName << "--out" << iconsetfolder + "/icon_32x32@2x.png");

    //    sips -z 128 128 image.png --out set/icon_128x128.png
    p.startDetached("sips", QStringList() << "-z" << "128" << "128" << fileName << "--out" << iconsetfolder + "/icon_128x128.png");

    //    sips -z 256 256 image.png --out set/icon_128x128@2x.png
    p.startDetached("sips", QStringList() << "-z" << "256" << "256" << fileName << "--out" << iconsetfolder + "/icon_128x128@2x.png");

    //    sips -z 256 256 image.png --out set/icon_256x256.png
    p.startDetached("sips", QStringList() << "-z" << "256" << "256" << fileName << "--out" << iconsetfolder + "/icon_256x256.png");

    //    sips -z 512 512 image.png --out set/icon_256x256@2x.png
    p.startDetached("sips", QStringList() << "-z" << "512" << "512" << fileName << "--out" << iconsetfolder + "/icon_256x256@2x.png");

    //    sips -z 512 512 image.png --out set/icon_512x512.png
    p.startDetached("sips", QStringList() << "-z" << "512" << "512" << fileName << "--out" << iconsetfolder + "/icon_512x512.png");

    //    cp image.png set/icon_512x512@2x.png
    p.startDetached("cp", QStringList() << fileName << iconsetfolder + "/icon_512x512@2x.png");

    //    iconutil -c icns set.iconset
    p.startDetached("iconutil", QStringList() << "-c" << "icns" << iconsetfolder);

    QMessageBox::information(this, "Info", "Operation completed.", QMessageBox::Ok);

    //    #rm -R set.iconset
    p.startDetached("rm", QStringList() << "-R" << iconsetfolder);

    QDesktopServices::openUrl(QUrl("file://" + fileNamePath));

}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About iCreateICNS"),
                 tr("<b><h1>iCreateICNS 1.0</b></h1><br><br>Coded by emarti, Murat Ozdemir<br>Licensed under the GNU GPL V3.0"));
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}
