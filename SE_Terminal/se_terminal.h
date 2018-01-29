#ifndef SE_TERMINAL_H
#define SE_TERMINAL_H

#include <QWidget>
#include <QLabel>
#include <QMatrix>
#include <QDebug>
#include <QString>
#include <QVBoxLayout>
#include <QListWidget>
#include <QFileInfoList>
#include <QMatrix>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDialog>
#include <QDir>
#include <QSlider>
#include <unistd.h>
#include "messageserver.h"
#include "keydel.h"

/*ButtonBroad current state*/
#define    CAMERCTLMODE    0
#define    LIGHTCTLMODE    1
#define    ROBOTCTLMODE    2
#define    MENUCTLMODE     3

/*MENU current state*/
#define    MENUSTATEHIDE   0
#define    MENUSTATESHOW   1
#define    MENUSTATESEC    2
namespace Ui {
    class se_terminal;
}

typedef  void (*TouchCallBack)(void);
class se_terminal : public QWidget
{
    Q_OBJECT
public:
    explicit se_terminal(QWidget *parent = 0);
    ~se_terminal();
    void UpdateDateTime(int year,int month,int day,int H,int M,int S);
    static  void QdebugCallBack1(void);
    static void QdebugCallBack2(void);

private slots:
    void  TouchButtonDeal(int x);
    void  PhyButtonDeal(int Num,int Type);
    void  TouchRockerDeal(int x,int y,int press);
    void  OsdUpdateFunc(int);
private:
    QLabel *RectGround;
    /*7 Button*/
    QLabel *ButtonLeft;
    QLabel *ButtonRight;
    QLabel *ButtonUp;
    QLabel *ButtonDown;
    QLabel *ButtonEnter;
    QLabel *ButtonDownLeft;
    QLabel *ButtonDownRight;
    QLabel *ButtonRightDownLeft;
    QLabel *ButtonRightDownRight;
    /*8 TileIcon*/
    QLabel *SignalNow;
    QLabel *LightIcon;
    QLabel *LightIconQ;
    QLabel *LightIconS;
    QLabel *LightIconY;
    QLabel *Photo;
    QLabel *Rec;
    QLabel *gps;
    QLabel *LuoPan;
    QLabel *CarPower;
    QLabel *TerminalPower;
    /*5 Rocker*/
    QLabel *UpDirection;
    QLabel *LeftDirection;
    QLabel *RightDirection;
    QLabel *DownDirection;
    QLabel *RockerGround;
    QLabel *Rocker;
    /*STATE Show*/
    QLabel  *FuYangSt;
    QLabel  *HeGunSt;
    QLabel  *HangXiangSt;
    QLabel  *BaiBiSt;
    QLabel  *WeDuSt;
    QLabel  *SuDuSt;
    QLabel  *SuDuDangWeiSt;
    /*3 Title*/
    QLabel *CTKZ;
    QLabel *ButtonKZName;
    QLabel *CTFZ;//车体翻转

    QLabel *TouchSN;
    QLabel *GMN;

    QLabel *ButtonSDPZLXName;
    KeyDel *iButtonMsg;
    int ICURRENTMODE;
    void UpdateCtlMode(void);

    int  MenuCurState;
    void ButtonUpDealFunc(void);
    void ButtonDownDealFunc(void);
    void ButtonLeftDealFunc(void);
    void ButtonRightDealFunc(void);
    void ButtonEnterDealFunc(void);
    void ButtonRightDownDealFunc(void);
    void ButtonLeftDownDealFunc(int Type);

    void PowerValSelect(int,QLabel *);
    void ButtonUpMenuDeal(void);
    void ButtonDownMenuDeal(void);
    void ButtonLeftMenuDeal(void);
    void ButtonRightMenuDeal(void);

    QListWidget *MenuList;
    QListWidget *SecMenuList;
    int OnelistFlag;
    int SeclistFlag;
    QStringList FileList;//用来保存wenjian名的表
    void GetDirFile(QString Type);
    void SecFileListDestory();
    void SecFileListCreate(QString Type);

    QLabel      *BlowUpssLable;
    int MemTime;
    int FIFOCmd;
    int GuanBiaoZhiWei;
    int CararFlag;//挡位标志位
    int RobotHandFlag;//摆臂标志位
    int BlowUpssFlag;//放大标志位
    QString BlowUpssStr;
    void slotActionSave();//截屏函数

    int fd_gpio;
    unsigned char gpiobuf[5];
    int SetGPIO(int value); //write GPIO22
    void SET_AUDIO_BYPASS();
    void SET_AUDIO_368OUT();
    unsigned char DetectTFCard(void);

    MessageServer msgServer;
    char cmdbuf[128];
    int DecodeFlag;
    int PauseFlag;
    Ui::se_terminal *ui;
};

#endif // SE_TERMINAL_H
