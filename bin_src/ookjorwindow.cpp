/*
    Copyright (C) 2009 Kasidit Yusuf.

    This file is part of Ookjor.

    Ookjor is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Ookjor is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Ookjor.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ookjorwindow.h"
#include "ui_ookjorwindow.h"
#include <QMessageBox>
#include "aboutookjordialog.h"
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QGraphicsTextItem>
#include <QMovie>
#include <QFile>
#include <QFileInfo>

#include <QGtkStyle>

#include "ookjorengine.h"

OokjorWindow::OokjorWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::OokjorWindow)
{
    ui->setupUi(this);
    iCOokjorEngine = NULL;  

    iFirstSendInstaller = true;
    iFirstConnect = true;

     //QApplication::setStyle(new  QGtkStyle);
    //QApplication::setStyle(new  QCleanlooksStyle);


    qDebug(QCoreApplication::argv()[0]);

    iCOokjorEngine = new OokjorEngine(this);

    if(iCOokjorEngine->GetBTEngine() == NULL)
    {
    QMessageBox::critical(this, tr("No Bluetooth device found on this computer"),tr("Ookjor can't find any Bluetooth device on this computer (running the BlueZ driver).\r\nPlease get/start/insert your Blueooth device (USB/onboard/etc..) and try again."));
    exit(1);
    }

    QObject::connect(iCOokjorEngine->GetBTEngine(), SIGNAL(EngineStateChangeSignal(int)),this, SLOT (EngineStateChangeSlot(int)));
    QObject::connect(iCOokjorEngine->GetBTEngine(), SIGNAL(EngineStatusMessageSignal(QString)),this, SLOT (EngineStatusMessageSlot(QString)));
    QObject::connect(iCOokjorEngine, SIGNAL(GotNewJpgSignal(void)),this, SLOT (GotNewJpgSlot(void)));

    //test load pic
    //iPixmap.load("gnu.jpg");
    /////////////

    QPixmap smallss;
    smallss.load(":/images/mobissori_small.jpg");
    ui->startPicLabel->setPixmap(smallss);

   iPixmapItem.setPixmap(iPixmap);
   iScene.addItem(&iPixmapItem);
   
   iAnimGif = NULL;

   iAnimGif = new QMovie(":/images/ajax-loader.gif");
   ui->connectLoadingLabel->setMovie(iAnimGif);
   iAnimGif->start();
   ///////////test
   /*QGraphicsItem *ball = new QGraphicsEllipseItem(0, 0, 20, 20);
   QGraphicsTextItem *ball = new QGraphicsTextItem ();
   ball->setHtml("<big><>Press Connect to Mobile</big>");

     QTimeLine *timer = new QTimeLine(5000);
     timer->setFrameRange(0, 100);

     QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
     animation->setItem(ball);
     animation->setTimeLine(timer);

     for (int i = 0; i < 200; ++i)
         animation->setPosAt(i / 200.0, QPointF(i, i));


     //iScene.setSceneRect(0, 0, 250, 250);
     iScene.addItem(ball);


     timer->start();
     */
   ////////


    ui->liveView->setScene(&iScene);
    //ui->liveView->hide();

    //checkbox state         
     QFile f( "prevdevchecked" );
      if(f.open(QIODevice::ReadOnly))
      {
          ui->connectPrevCheckBox->setChecked(true);
          on_connectPrevCheckBox_clicked();
      }
      /////////

    EngineStateChangeSlot(PatienceBTClientEngine::EBtIdle);

}

void OokjorWindow::GotNewJpgSlot()
{
bool loadsuccess = iPixmap.loadFromData(iCOokjorEngine->iNewJpgBuffer,"JPG");
if(loadsuccess)
{    


        //EngineStatusMessageSlot("frame load ok");

    iPixmapItem.setPixmap(iPixmap);
    iScene.setSceneRect(iPixmapItem.boundingRect());

        //ui->liveView->update();

    }
    else
        EngineStatusMessageSlot("frame load failed");
}



OokjorWindow::~OokjorWindow()
{
    delete ui;
    delete iCOokjorEngine;
    delete iAnimGif;
}

void OokjorWindow::on_connectButton_clicked()
{
      if(iFirstConnect)
    {
    //doesn't happen anymore, it's probably related to the sdp channel not used bug that was fixed QMessageBox::information(this, tr("If this connect fails..."),tr("On some versions of BlueZ (bluetooth driver that comes with Ubuntu 9.10)\r\nTHE FIRST CONNECT MIGHT NOT SHOW PHONE SCREEN, if so:\r\n 1. Turn-off phone's bluetooth,\r\n 2. Exit phone Ookjor program.\r\n 3. Start phone Ookjor program again and let it turn on the bluetooth.\r\n 4. Press Connect here again."));
    iFirstConnect = false;
    }

    if(ui->connectPrevCheckBox->isChecked() && this->iPrevDevAddr.length()==6)
    {        
        qDebug("starting connect to prevdev");
        iCOokjorEngine->GetBTEngine()->StartPrevdev(iPrevDevAddr);
    }
else
    {
        if(!iCOokjorEngine->GetBTEngine()->StartSearch())
        {
            ui->statusBar->showMessage("Start search failed...",3000);
        }
    }
}


void OokjorWindow::EngineStatusMessageSlot(QString str)
{
    ui->statusBar->showMessage(str);
    qDebug(str.toAscii());
    //repaint();
}

void OokjorWindow::EngineStateChangeSlot(int aState)
{
    switch(aState)
    {
    case PatienceBTClientEngine::EBtIdle:

        ui->liveWidget->hide();
        ui->liveDisconnectButton->hide();

        ui->connectLoadingLabel->hide();
        ui->connectButton->setText("Connect to Mobile");
        ui->connectButton->setEnabled(true);
        ui->connectPrevCheckBox->show();

        ui->groupBox_1->show();
        ui->groupBox_2->show();
        adjustSize();
        //this->adjustSize();


        break;
    case PatienceBTClientEngine::EBtSearching:
        ui->groupBox_1->hide();

        ui->connectPrevCheckBox->hide();

        ui->connectButton->setEnabled(false);
        ui->connectButton->setText("Please wait...");
        ui->connectLoadingLabel->show();
        adjustSize();

        //this->adjustSize();
        //this->resize(this->minimumSize());
        break;
    case PatienceBTClientEngine::EBtSelectingPhoneToSDP:

        break;
    case PatienceBTClientEngine::EBtSearchingSDP:

        break;
    case PatienceBTClientEngine::EBtSearchingSDPDone:

        break;
    case PatienceBTClientEngine::EBtConnectingRFCOMM:

        break;
    case PatienceBTClientEngine::EBtConnectionActive:

        ui->groupBox_2->hide();

    //ui->textBrowser->hide();
    ui->liveWidget->show();
    ui->liveDisconnectButton->setEnabled(true);
    ui->liveDisconnectButton->show();
    adjustSize();
    //this->resize(this->minimumSize());

    //this->adjustSize();
        break;
    case PatienceBTClientEngine::EBtDisconnected:

        break;
    default:
        ui->statusBar->showMessage("WARNING: UNKNOWN ENGINE STATE");
        break;
    }

    //this->resize(this->minimumSize());
    //
    //update();
    //repaint();
    //ui->centralWidget->repaint(ui->centralWidget->rect());
}

void OokjorWindow::OnMenuAbout()
{
//QMessageBox::information(this, tr("About"),tr(""));
      aboutookjordialog w(this);
      w.exec();
}

void OokjorWindow::OnMenuHelp()
{
//QMessageBox::information(this, tr("Help"),tr("Please visit www.ClearEvo.com for details."));
}

void OokjorWindow::on_liveDisconnectButton_clicked()
{
    ui->liveDisconnectButton->setEnabled(false);
    qDebug("user pressed disconnect");
    iCOokjorEngine->GetBTEngine()->Disconnect();
    qDebug("probably closed engine running socket already");
}

void OokjorWindow::on_startSendButton_clicked()
{

    //check if file exist found or not
    if(iFirstSendInstaller)
    {
    QMessageBox::information(this, tr("If this send fails, try again"),tr("On some versions of BlueZ (bluetooth driver that comes with Ubuntu 9.10)\r\nTHE FIRST SEND MIGHT FAIL, if so - try again."));
    iFirstSendInstaller = false;
    }

    QString cmd;
    cmd = "bluetooth-sendto ";
    cmd += QFileInfo( QCoreApplication::argv()[0] ).absolutePath();
    cmd += "/OokjorS60/sis/OokjorS603rdAnd5th.sisx";
    qDebug(cmd.toAscii());
    int ret = system(cmd.toAscii());
    qDebug("bluetooth-sendto exited with %d",ret);

}

void OokjorWindow::ClearAndGetPrevDevAddr()
{
         iPrevDevAddr.clear();

         QFile f( "prevdev.bdaddr" );
          if(f.open(QIODevice::ReadOnly))
          {
              iPrevDevAddr = f.readAll();
              f.close();
          }
}

void OokjorWindow::on_connectPrevCheckBox_clicked()
{
    if(ui->connectPrevCheckBox->isChecked())
    {
        ClearAndGetPrevDevAddr();

       if(iPrevDevAddr.length()==6)
          {
                //ok
             QFile f( "prevdevchecked" );
              if(f.open(QIODevice::WriteOnly))
              {
                  f.close();
              }
          }
       else
          {
           QFile delf("prevdevchecked");
           delf.remove();

            iPrevDevAddr.clear();
            ui->connectPrevCheckBox->setChecked(false);
            QMessageBox::information(this, tr("No previous device yet"),tr("No previous device data found"));
          }

    }
    else
    {
        QFile delf("prevdevchecked");
        delf.remove();

        iPrevDevAddr.clear();
    }

}


void OokjorWindow::on_pushButton_2_clicked()
{
    ui->liveView->scale(1.1,1.1);
}

void OokjorWindow::on_pushButton_clicked()
{
    ui->liveView->scale(1/1.1,1/1.1);
}
