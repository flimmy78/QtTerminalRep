#ifndef KEYDEL_H
#define KEYDEL_H
#include <QThread>
#include <QObject>
#include "usarttest.h"

#define BUTTONFREE            0
#define BUTTONUPPRESS         1
#define BUTTONUPRELEASE       2
#define BUTTONLEFTPRESS       3
#define BUTTONLEFTRELEASE     4
#define BUTTONENTERPRESS      5
#define BUTTONENTERRELEASE    6
#define BUTTONRIGHTFPRESS     7
#define BUTTONRIGHTRELEASE    8
#define BUTTONDOWNPRESS       9
#define BUTTONDOWNRELEASE     10

#define BUTTONLDLPRESS        11
#define BUTTONLDLRELEASE      12
#define BUTTONLDRPRESS        13
#define BUTTONLDRRELEASE      14
#define BUTTONRDLPRESS        15
#define BUTTONRDLRELEASE      16
#define BUTTONRDRPRESS        17
#define BUTTONRDRRELEASE      18


#define RELEASE         0
#define SHORTPRESS      1
#define LONGPRESS       2

#define MAXROCKRADIUS           81
#define MAXROCKLAB_X            1040
#define MAXROCKLAB_Y            133
#define MAXROCKCENTER_X      (MAXROCKLAB_X+80)
#define MAXROCKCENTER_Y      (MAXROCKLAB_Y-81)

#define MIXROCKLAB_X            1077
#define MIXROCKLAB_Y            166
#define MINROCKCENTER_X      (MIXROCKLAB_X + 45)
#define MINROCKCENTER_Y      (MIXROCKLAB_Y - 43)

extern unsigned char g_SendSTM[5];        //按键、触屏信息

class KeyDel : public QThread
{
    Q_OBJECT
protected:
   void run();
signals:
   void PhyButtonMsg(int,int);
   void TouchButtonMsg(int);
   void RockerSgl(int,int,int);
   void OsdUpdate(int);
public:
   KeyDel();
   void CapacityDelKeyDate(void (*ShortDelFun) (void),void (*LongDelFun) (void),int Num);
   void CapacityDelTouch(int iX,int iY);
private:
   int RockerPressFlag;
   UsartClassThr *iUsart;
   int MemLastRockerPos_X;
   int MemLastRockerPos_Y;
   int PhyTouchButtonFlag;
   int DelayUpdateOsdFlag;

   static void QdebugLong(void);
   static void QdebugShort(void);
   int iButtonMode;
};

#endif // KEYDEL_H
