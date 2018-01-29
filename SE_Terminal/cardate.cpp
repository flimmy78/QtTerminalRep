#include "cardate.h"
#include <QDebug>
DateShow::DateShow(QString TextDate1,QString TextDate2){
    Name1 = TextDate1;
    Name2 = TextDate2;

    DateFrame1 = new QLabel;
    DateFrame1->resize(80,18);
    DateFrame1->setAlignment(Qt::AlignLeft);
    DateFrame1->setFont(QFont("wenquanyi",12,QFont::Bold));
    DateFrame1->setStyleSheet("QLabel{color:white;font:14px;};");
    DateFrame2 = new QLabel;
    DateFrame2->resize(80,18);
    DateFrame2->setFont(QFont("wenquanyi",12,QFont::Bold));
    DateFrame2->setAlignment(Qt::AlignLeft);
    DateFrame2->setStyleSheet("QLabel{color:white;font:14px;};");

    DateFrameLayout = new QHBoxLayout;
    DateFrameLayout->addSpacing(980);
    DateFrameLayout->addWidget(DateFrame1);
    DateFrameLayout->addWidget(DateFrame2);
}

DateShow::~DateShow(){
    delete DateFrameLayout;
    delete DateFrame1;
    delete DateFrame2;
}

void DateShow::setDateText1(QString Date){
    QString tmp1;
    tmp1 = Name1 + Date;
    DateFrame1->setText(tmp1);
}

void DateShow::setDateText2(QString Date){
   QString tmp2;
   tmp2 = Name2 + Date;
   DateFrame2->setText(tmp2);
}


CarDate::CarDate(QWidget *parent) :
    QWidget(parent)
{
    MinCarNavigation_1 = new DateShow("东经:","北纬:");
    MinCarNavigation_2 = new DateShow("海拔:","俯仰:");
    MinCarNavigation_3 = new DateShow("横滚:","摆臂:");
    MinCarNavigation_4 = new DateShow("温度:"," ");

    MinCarStateArgc_1 = new DateShow("速度:","电机温度:");
    MinCarStateArgc_2 = new DateShow("左转速:","右转速:");
    MinCarStateArgc_3 = new DateShow("左电极电流:","右电极电流:");
    MinCarStateArgc_4 = new DateShow("电池电压:","速度挡位:");


    CarDateFrameLayout = new QVBoxLayout;
    CarDateFrameLayout->addLayout(MinCarNavigation_1->DateFrameLayout);
    CarDateFrameLayout->addLayout(MinCarNavigation_2->DateFrameLayout);
    CarDateFrameLayout->addLayout(MinCarNavigation_3->DateFrameLayout);
    CarDateFrameLayout->addLayout(MinCarNavigation_4->DateFrameLayout);
    CarDateFrameLayout->addLayout(MinCarStateArgc_1->DateFrameLayout);
    CarDateFrameLayout->addLayout(MinCarStateArgc_2->DateFrameLayout);
    CarDateFrameLayout->addLayout(MinCarStateArgc_3->DateFrameLayout);
    CarDateFrameLayout->addLayout(MinCarStateArgc_4->DateFrameLayout);

    SetEastLongitude(0.0);
    SetNorthernLatitude(0.0);
    SetLevation(0);
    SetPitch(0);
    SetRoll(0);
    SetSwingArm(0);
    SetTemperature(0);
    SetSpeed(0.0);
    SetMotorTemperature(0);
    SetLeftRotateSpeed(0);
    SetRightRotateSpeed(0);
    SetLeftMotorCurrent(0);
    SetRightMotorCurrent(0);
    SetCellVoltage(0);
    SetSpeedGear(0);
}

void CarDate::SetEastLongitude(float Date)       //东经:
{
    TmpString = QString("%0").arg(Date);
    TmpString += "°";
    MinCarNavigation_1->setDateText1(TmpString);
}
void CarDate::SetNorthernLatitude(float Date)    //北纬:
{
    TmpString  = QString("%0").arg(Date);
    TmpString += "°";
    MinCarNavigation_1->setDateText2(TmpString);
}

void CarDate::SetLevation(int Date)              //海拔:
{
    TmpString = QString("%0").arg(Date);
    TmpString += "m";
    MinCarNavigation_2->setDateText1(TmpString);
}

void CarDate::SetPitch(int Date)              //海拔:
{
    TmpString = QString("%0").arg(Date);
    TmpString += "°";
    MinCarNavigation_2->setDateText2(TmpString);
}

void CarDate::SetRoll(int Date)                 //横滚
{
    TmpString = QString("%0").arg(Date);
    TmpString += "°";
    MinCarNavigation_3->setDateText1(TmpString);
}

void CarDate::SetSwingArm(int Date)             //摆臂
{
    TmpString = QString("%0").arg(Date);
    TmpString += "°";
    MinCarNavigation_3->setDateText2(TmpString);
}

void CarDate::SetTemperature(int Date)           //温度
{
    TmpString = QString("%0").arg(Date);
    TmpString += "℃";
    MinCarNavigation_4->setDateText1(TmpString);
}

void CarDate::SetSpeed(float Date)                //速度
{
    TmpString  = QString("%0").arg(Date);
    TmpString += "m/s";
    MinCarStateArgc_1->setDateText1(TmpString);
}

void CarDate::SetMotorTemperature(int Date)      //电机温度
{
    TmpString = QString("%0").arg(Date);
    TmpString +="℃";
    MinCarStateArgc_1->setDateText2(TmpString);
}

void CarDate::SetLeftRotateSpeed(int Date){ //左转速
    TmpString = QString("%0").arg(Date);
    TmpString += "r/min";
    MinCarStateArgc_2->setDateText1(TmpString);
}

void CarDate::SetRightRotateSpeed(int Date){ //右转速
    TmpString = QString("%0").arg(Date);
    TmpString += "r/min";
    MinCarStateArgc_2->setDateText2(TmpString);
}

void CarDate::SetLeftMotorCurrent(int Date){ //左电极电流

    TmpString = QString("%0").arg(Date);
    TmpString += "A";
    MinCarStateArgc_3->setDateText1(TmpString);
}

void CarDate::SetRightMotorCurrent(int Date){ //右电极电流

    TmpString = QString("%0").arg(Date);
    TmpString += "A";
    MinCarStateArgc_3->setDateText2(TmpString);
}

void CarDate::SetCellVoltage(float Date){         //电池电压
    TmpString = QString("%0").arg(Date);
    TmpString += "V";
    MinCarStateArgc_4->setDateText1(TmpString);
}

void CarDate::SetSpeedGear(int Date){             //速度挡位

    TmpString = QString("%0").arg(Date);
    MinCarStateArgc_4->setDateText2(TmpString);
}
