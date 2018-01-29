#include "keydel.h"
#include <QDebug>
#include <QtCore/qmath.h>

unsigned char g_SendSTM[5] = {0xee,0x03,0x00,0x0a,0xff};

void KeyDel::QdebugLong(void){
   // qDebug() <<"QdebugLong";
}
void KeyDel::QdebugShort(void){
   // qDebug() <<"QdebugShort";
}

KeyDel::KeyDel()
{
    RockerPressFlag = 0;
    MemLastRockerPos_X = 0;
    MemLastRockerPos_Y = 0;
    PhyTouchButtonFlag = -1;
    DelayUpdateOsdFlag = 0;
    iButtonMode = BUTTONFREE;
    iUsart = new UsartClassThr;
    iUsart->start();
}

void KeyDel::run(){
    //CapacityDelKeyDate
    int i;
    for(i = 0;i < KEYNUM;i++)
        g_iKeyDate.KeyVale[i] = RELEASE;

    while(1){
        CapacityDelKeyDate(KeyDel::QdebugShort,KeyDel::QdebugLong,0);//传入按键处理
        CapacityDelKeyDate(KeyDel::QdebugShort,KeyDel::QdebugLong, 1);
        CapacityDelKeyDate(KeyDel::QdebugShort,KeyDel::QdebugLong, 2);
        CapacityDelKeyDate(KeyDel::QdebugShort,KeyDel::QdebugLong, 3);
        CapacityDelKeyDate(KeyDel::QdebugShort,KeyDel::QdebugLong, 4);
        CapacityDelKeyDate(KeyDel::QdebugShort,KeyDel::QdebugLong, 5);
        CapacityDelKeyDate(KeyDel::QdebugShort,KeyDel::QdebugLong, 6);
        CapacityDelKeyDate(KeyDel::QdebugShort,KeyDel::QdebugLong, 7);
        /*
        CapacityDelKeyDate(KeyDel::QdebugShort,KeyDel::QdebugLong, 8);
        CapacityDelKeyDate(KeyDel::QdebugShort,KeyDel::QdebugLong, 9);
        CapacityDelKeyDate(KeyDel::QdebugShort,KeyDel::QdebugLong, 10);
        CapacityDelKeyDate(KeyDel::QdebugShort,KeyDel::QdebugLong, 11);
        */
        CapacityDelTouch(g_iKeyDate.TouchDate_X,g_iKeyDate.TouchDate_Y);
        iUsart->UsartSend(g_SendSTM,5);
        usleep(60000);
        DelayUpdateOsdFlag++;
        if(DelayUpdateOsdFlag == 3){
            emit OsdUpdate(PhyTouchButtonFlag);
            PhyTouchButtonFlag = -1;
            DelayUpdateOsdFlag = 0;

        }

    }
}

void KeyDel::CapacityDelKeyDate(void (*ShortDelFun) (void),void(*LongDelFun) (void),int Num){
    switch (g_iKeyDate.KeyVale[Num]){
    case RELEASE:
            break;
    case SHORTPRESS:
        ShortDelFun();
        emit PhyButtonMsg(Num,0);                         //发送按键信号并带回按键值
        PhyTouchButtonFlag = Num;
        g_iKeyDate.KeyVale[Num] = 0;
        break;
    case LONGPRESS:
        LongDelFun();
        emit PhyButtonMsg(Num,1);
        PhyTouchButtonFlag = Num;
        g_iKeyDate.KeyVale[Num] = 0;
        break;
    default:
        break;
    }
}

void KeyDel::CapacityDelTouch(int iX,int iY){
    /*
    * 触屏有8个区域
    * 键盘区域：上、下、左、右、确认、左下、右下
    *           0  1  2   3   4     5   6
    * 摇杆区域：
    * 如果iX\iY匹配到区域就发出信号：
    *   1）在按键区域经过判断则带回按键的键值，int SelectTouchCoord(int x,int y);
    *   2）在摇杆区域则带回坐标 Signal(iX,iY);
    */
   // qDebug() <<"iX" << iX <<"iY"<< iY;
      /*按键区域*/
   if(iX == 10 && iY == 10){
       if(iButtonMode == BUTTONFREE){
            emit TouchButtonMsg(BUTTONUPPRESS);
            iButtonMode = BUTTONUPPRESS;
       }
    }else if(iButtonMode == BUTTONUPPRESS){
       emit TouchButtonMsg(BUTTONUPRELEASE);
       iButtonMode = BUTTONFREE;
    }

    if(iX == 11 && iY == 11){
        if(iButtonMode == BUTTONFREE){
             emit TouchButtonMsg(BUTTONLEFTPRESS);
             iButtonMode = BUTTONLEFTPRESS;
        }
    }else if(iButtonMode == BUTTONLEFTPRESS){
        emit TouchButtonMsg(BUTTONLEFTRELEASE);
        iButtonMode = BUTTONFREE;
    }
    if(iX == 12 && iY == 12){
        if(iButtonMode == BUTTONFREE){
             emit TouchButtonMsg(BUTTONENTERPRESS);
             iButtonMode = BUTTONENTERPRESS;
        }
    }else if(iButtonMode == BUTTONENTERPRESS){
        emit TouchButtonMsg(BUTTONENTERRELEASE);
        iButtonMode = BUTTONFREE;
    }

    if(iX == 13 && iY == 13){
        if(iButtonMode == BUTTONFREE){
             emit TouchButtonMsg(BUTTONRIGHTFPRESS);
             iButtonMode = BUTTONRIGHTFPRESS;
        }
    }else if(iButtonMode == BUTTONRIGHTFPRESS){
        emit TouchButtonMsg(BUTTONRIGHTRELEASE);
        iButtonMode = BUTTONFREE;
    }

    if(iX == 14 && iY == 14 ){
        if(iButtonMode == BUTTONFREE){
             emit TouchButtonMsg(BUTTONDOWNPRESS);
             iButtonMode = BUTTONDOWNPRESS;
        }
    }else if(iButtonMode == BUTTONDOWNPRESS){
        emit TouchButtonMsg(BUTTONDOWNRELEASE);
        iButtonMode = BUTTONFREE;
    }

   // qDebug() <<"iX"<<iX << "iY" << iY;
    /*判断触摸点是否在摇杆区域*/
    int RockerTmp_X,RockerTmp_Y;
    RockerTmp_X = qPow((iX-MAXROCKCENTER_X),2); //  (iX-MAXROCKCENTER_X)*(iX-MAXROCKCENTER_X);
    RockerTmp_Y = qPow((iY-MAXROCKCENTER_Y),2); //(iY-MAXROCKCENTER_Y)*(iY-MAXROCKCENTER_Y);
    if(RockerTmp_X + RockerTmp_Y < MAXROCKRADIUS*MAXROCKRADIUS || RockerTmp_X + RockerTmp_Y == MAXROCKRADIUS*MAXROCKRADIUS){
        RockerPressFlag = 1;
        if(MemLastRockerPos_X != iX || \
                MemLastRockerPos_Y != iY)
            emit RockerSgl(iX,iY,RockerPressFlag);
        MemLastRockerPos_X = iX;
        MemLastRockerPos_Y = iY;
    }else{
        if(RockerPressFlag){
            RockerPressFlag = 0;
            emit RockerSgl(0,0,RockerPressFlag);
        }
    }
}



