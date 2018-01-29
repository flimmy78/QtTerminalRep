#include "se_terminal.h"
#include "ui_se_terminal.h"
#include <QFrame>
se_terminal::se_terminal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::se_terminal)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    DetectTFCard();
    msgServer.start(QThread::HighPriority);


    MemTime = 0;
    FIFOCmd = 0;
    GuanBiaoZhiWei= 0;
    RectGround = new QLabel(this);
    RectGround->resize(1280,720);
    RectGround->setPixmap(QPixmap("/Icon_TranRot/IconShow/RectGround.png"));
    RectGround->move(0,0);

    /*7 Button*/
    ButtonLeft  = new QLabel(this);
   // ButtonLeft->resize(71,170);
    ButtonLeft->move(47,116);
    ButtonLeft->setPixmap(QPixmap("/Icon_TranRot/IconShow/ButtonLeft.png"));

    ButtonRight = new QLabel(this);
    ButtonRight->move(165,116);
    ButtonRight->setPixmap(QPixmap("/Icon_TranRot/IconShow/ButtonRight.png"));

    ButtonUp    = new QLabel(this);
    ButtonUp->move(59,104);
    ButtonUp->setPixmap(QPixmap("/Icon_TranRot/IconShow/ButtonUp.png"));

    ButtonDown  = new QLabel(this);
    ButtonDown->move(59,224);
    ButtonDown->setPixmap(QPixmap("/Icon_TranRot/IconShow/ButtonDown.png"));

    ButtonEnter  = new QLabel(this);
    ButtonEnter->move(106,165);
    ButtonEnter->setPixmap(QPixmap("/Icon_TranRot/IconShow/ButtonEnter.png"));

    ButtonDownLeft  = new QLabel(this);
    ButtonDownLeft->move(43,317);
    ButtonDownLeft->setPixmap(QPixmap("/Icon_TranRot/IconShow/ButtonDownLeft.png"));

    ButtonDownRight  = new QLabel(this);
    ButtonDownRight->move(160,316);
    ButtonDownRight->setPixmap(QPixmap("/Icon_TranRot/IconShow/ButtonDownRight.png"));

    ButtonRightDownLeft  = new QLabel(this);
    ButtonRightDownLeft->move(1018,331);
    ButtonRightDownLeft->setPixmap(QPixmap("/Icon_TranRot/IconShow/ButtonDownLeft.png"));

    ButtonRightDownRight  = new QLabel(this);
    ButtonRightDownRight->move(1149,331);
    ButtonRightDownRight->setPixmap(QPixmap("/Icon_TranRot/IconShow/ButtonDownRight.png"));

    CTFZ  = new QLabel(this);
    CTFZ->move(554,682);
    CTFZ->setPixmap(QPixmap("/Icon_TranRot/IconShow/CTFZ.png"));
    CTFZ->hide();
/********************************************************************************/
    /*8 Tile*/
    SignalNow = new QLabel(this);
    SignalNow->move(30,12);
    SignalNow->setPixmap(QPixmap("/Icon_TranRot/Signal/signalEmpty.png"));

    LightIcon = new QLabel(this);
    LightIcon->move(80,14);
    LightIcon->setPixmap(QPixmap("/Icon_TranRot/IconShow/HLight.png"));
    LightIcon->hide();

    LightIconQ = new QLabel(this);
    LightIconQ->move(130,14);
    LightIconQ->setPixmap(QPixmap("/Icon_TranRot/IconShow/QLight.png"));
    LightIconQ->hide();

    LightIconS = new QLabel(this);
    LightIconS->move(180,14);
    LightIconS->setPixmap(QPixmap("/Icon_TranRot/IconShow/SLight.png"));
    LightIconS->hide();

    LightIconY = new QLabel(this);
    LightIconY->move(230,14);
    LightIconY->setPixmap(QPixmap("/Icon_TranRot/IconShow/YLight.png"));
    LightIconY->hide();

    Photo = new QLabel(this);
    Photo->move(517,14);
    Photo->setPixmap(QPixmap("/Icon_TranRot/IconShow/Photo.png"));
    Photo->hide();

    Rec = new QLabel(this);
    Rec->move(626,14);
    Rec->setPixmap(QPixmap("/Icon_TranRot/IconShow/Rec.png"));
    Rec->hide();

    LuoPan = new QLabel(this);
    LuoPan->move(1033,14);
    LuoPan->setPixmap(QPixmap("/Icon_TranRot/IconShow/LuoPan.png"));

    CarPower = new QLabel(this);
    CarPower->move(1115,18);
    CarPower->setPixmap(QPixmap("/Icon_TranRot/power/100.png"));

    TerminalPower = new QLabel(this);
    TerminalPower->move(1210,18);
    TerminalPower->setPixmap(QPixmap("/Icon_TranRot/power/100.png"));

    TouchSN = new QLabel(this);
    TouchSN->resize(35,32);
    TouchSN->move(870,14);
    TouchSN->setScaledContents(true);
    TouchSN->setPixmap(QPixmap("/Icon_TranRot/IconShow/ZCMPN.png"));
    TouchSN->hide();

    GMN = new QLabel(this);
    GMN->move(950,14);
    GMN->resize(30,30);
    GMN->setScaledContents(true);   //setScaleContents
    GMN->setPixmap(QPixmap("/Icon_TranRot/IconShow/ZGMN.png"));
    GMN->hide();
/********************************************************************************/
    UpDirection  = new QLabel(this);
    UpDirection->move(1109,105);
    UpDirection->setPixmap(QPixmap("/Icon_TranRot/IconShow/Up.png"));

    LeftDirection  = new QLabel(this);
    LeftDirection->move(1010,204);
    LeftDirection->setPixmap(QPixmap("/Icon_TranRot/IconShow/Left.png"));

    RightDirection  = new QLabel(this);
    RightDirection->move(1216,204);
    RightDirection->setPixmap(QPixmap("/Icon_TranRot/IconShow/Right.png"));

    DownDirection  = new QLabel(this);
    DownDirection->move(1109,307);
    DownDirection->setPixmap(QPixmap("/Icon_TranRot/IconShow/Down.png"));

    RockerGround  = new QLabel(this);
    RockerGround->move(MAXROCKLAB_X,MAXROCKLAB_Y);
    RockerGround->setPixmap(QPixmap("/Icon_TranRot/IconShow/RockerGround.png"));

    Rocker  = new QLabel(this);
    Rocker->move(MIXROCKLAB_X,MIXROCKLAB_Y);
    Rocker->setPixmap(QPixmap("/Icon_TranRot/IconShow/Rocker.png"));

    /*1 Title*/

    CTKZ = new QLabel(this);
    CTKZ->move(1077,75);
    CTKZ->setPixmap(QPixmap("/Icon_TranRot/IconShow/CTKZ.png"));

    ButtonKZName = new QLabel(this);
    ButtonKZName->move(73,74);
    ButtonKZName->setPixmap(QPixmap("/Icon_TranRot/IconShow/SXTKZ.png"));

    ButtonSDPZLXName = new QLabel(this);
    ButtonSDPZLXName->move(52,346);
    ButtonSDPZLXName->setPixmap(QPixmap("/Icon_TranRot/IconShow/CALXDW.png"));

    iButtonMsg = new KeyDel;
    iButtonMsg ->start();
    connect(iButtonMsg,SIGNAL(TouchButtonMsg(int)),this,SLOT(TouchButtonDeal(int)));
    connect(iButtonMsg,SIGNAL(PhyButtonMsg(int,int)),this,SLOT(PhyButtonDeal(int,int)));
    connect(iButtonMsg,SIGNAL(RockerSgl(int,int,int)),this,SLOT(TouchRockerDeal(int,int,int)));
    connect(iButtonMsg,SIGNAL(OsdUpdate(int)),this,SLOT(OsdUpdateFunc(int)));

    system("./encodertsp -v 1.264 -a 1.aac -y 2 -I 1 &");
    SET_AUDIO_BYPASS();

    /*State Info*/
    FuYangSt= new QLabel(this);
    FuYangSt->resize(140,24);
    FuYangSt->move(1020,470);
    FuYangSt->setAlignment(Qt::AlignLeft);
    FuYangSt->setFont(QFont("JPTZ",20,QFont::AnyStyle));
    FuYangSt->setStyleSheet("QLabel{background:transparent;color:white;};");

    HeGunSt = new QLabel(this);
    HeGunSt->resize(140,24);
    HeGunSt->move(1140,470);
    HeGunSt->setAlignment(Qt::AlignLeft);
    HeGunSt->setFont(QFont("JPTZ",20,QFont::AnyStyle));
    HeGunSt->setStyleSheet("QLabel{background:transparent;color:white;};");

    HangXiangSt = new QLabel(this);
    HangXiangSt->resize(140,24);
    HangXiangSt->move(1020,510);
    HangXiangSt->setAlignment(Qt::AlignLeft);
    HangXiangSt->setFont(QFont("JPTZ",20,QFont::AnyStyle));
    HangXiangSt->setStyleSheet("QLabel{background:transparent;color:white;};");

    BaiBiSt = new QLabel(this);
    BaiBiSt->resize(140,24);
    BaiBiSt->move(1140,510);
    BaiBiSt->setAlignment(Qt::AlignLeft);
    BaiBiSt->setFont(QFont("JPTZ",20,QFont::AnyStyle));
    BaiBiSt->setStyleSheet("QLabel{background:transparent;color:white;};");

    WeDuSt  = new QLabel(this);
    WeDuSt->resize(140,24);
    WeDuSt->move(1020,550);
    WeDuSt->setAlignment(Qt::AlignLeft);
    WeDuSt->setFont(QFont("JPTZ",20,QFont::AnyStyle));
    WeDuSt->setStyleSheet("QLabel{background:transparent;color:white;};");

    SuDuSt  = new QLabel(this);
    SuDuSt->resize(140,24);
    SuDuSt->move(1140,550);
    SuDuSt->setAlignment(Qt::AlignLeft);
    SuDuSt->setFont(QFont("JPTZ",20,QFont::AnyStyle));
    SuDuSt->setStyleSheet("QLabel{background:transparent;color:white;};");

    SuDuDangWeiSt  = new QLabel(this);
    SuDuDangWeiSt->resize(140,24);
    SuDuDangWeiSt->move(1020,590);
    SuDuDangWeiSt->setAlignment(Qt::AlignLeft);
    SuDuDangWeiSt->setFont(QFont("JPTZ",20,QFont::AnyStyle));
    SuDuDangWeiSt->setStyleSheet("QLabel{background:transparent;color:white;};");


    BlowUpssFlag = 0;
    BlowUpssLable = new QLabel(this);
    BlowUpssLable->resize(60,20);
    BlowUpssLable->move(938,50);//1020,140);
    BlowUpssLable->setAlignment(Qt::AlignLeft);
    BlowUpssLable->setFont(QFont("JPTZ",20,QFont::AnyStyle));
    BlowUpssLable->setStyleSheet("QLabel{background:transparent;color:white;};");
    BlowUpssStr = "X" + QString("%0").arg((float)(BlowUpssFlag+10)/10);
    BlowUpssLable->setText(BlowUpssStr);

    CararFlag = 0;
    ICURRENTMODE = CAMERCTLMODE;
    MenuCurState = MENUSTATEHIDE;
    /***********************************MENU********************************************/
    OnelistFlag = 0;
    SeclistFlag = 0;
    MenuList = new QListWidget(this);
    MenuList->resize(275,240);
    MenuList->move(990,412);
    MenuList->setIconSize(QSize(40,26));
    //光感 放大 触屏
    MenuList->addItem(new QListWidgetItem(QIcon("/Icon_TranRot/IconShow/SHIPIN.png"),tr("      视频")));
    MenuList->addItem(new QListWidgetItem(QIcon("/Icon_TranRot/IconShow/TUPIAN.png"),tr("      图片")));
    MenuList->addItem(new QListWidgetItem(QIcon("/Icon_TranRot/IconShow/SFJ.png"), tr("      缩放")));
    MenuList->addItem(new QListWidgetItem(QIcon("/Icon_TranRot/IconShow/GM.png"), tr("      光感")));
    MenuList->addItem(new QListWidgetItem(QIcon("/Icon_TranRot/IconShow/CMP.png"), tr("      触屏")));
    MenuList->setFont(QFont("JPTZ",20,QFont::Bold));

    MenuList->setStyleSheet("QListWidget{background-color:rgb(70,70,70);border:8px solid gray;border-color:rgb(60,60,60);}"
                            "QListWidget::Item{padding-top:8px; padding-bottom:8px; }");
                            //"QListWidget::item:selected:!active{border-width:0px; background:lightgreen; color:red;}");

    SecMenuList = new QListWidget(this);
    SecMenuList->resize(275,240);
    SecMenuList->move(990,412);
    SecMenuList->setIconSize(QSize(40,26));
    SecMenuList->setFont(QFont("JPTZ",18,QFont::AnyStyle));
    SecMenuList->setStyleSheet("QListWidget{background-color:rgb(70,70,70);border:8px solid gray;border-color:rgb(60,60,60);}"
                        "QListWidget::Item{padding-top:8px; padding-bottom:8px; }");
                    //    "QListWidget::item:selected:!active{border-width:0px; background:lightgreen; color:red;}");
    SecMenuList->setCurrentRow(SeclistFlag);
    SecMenuList->hide();
    MenuList->setCurrentRow(OnelistFlag);
    MenuList->hide();

    DecodeFlag = 0;
    PauseFlag = 0;
    ui->setupUi(this);
}

se_terminal::~se_terminal()
{
    delete ui;
}

unsigned char se_terminal::DetectTFCard(void)
{
    unsigned char cardexist = 0;
    if(fopen("/dev/mmcblk0p1", "r") == NULL){                              //是否有TF卡设备
        printf("No TF Card Insert!\r\n");
        cardexist = 0;
    }else{
        system("mount -t vfat /dev/mmcblk0p1 /home/root/media/");           //挂在TF卡
        system("insmod /dm368/g_file_storage.ko file=/dev/mmcblk0p1 stall=0 removable=1");//安装TF卡导出驱动
        printf("Mount TF Card OK!  (/dev/mmcblk0p1)\r\n");
        cardexist = 1;
        return cardexist;
    }

    if(0 == cardexist){
        if(fopen("/dev/mmcblk0", "r") == NULL){
            printf("No TF Card Insert!\r\n");
            cardexist = 0;
        }else{
            system("mount -t vfat /dev/mmcblk0 /home/root/media/");
            system("insmod /dm368/g_file_storage.ko file=/dev/mmcblk0 stall=0 removable=1");
            printf("Mount TF Card OK!  (/dev/mmcblk0)\r\n");
            cardexist = 1;
        }
    }
    return cardexist;
}


void se_terminal::TouchRockerDeal(int iX,int iY,int iPress){
    if(iPress){
        Rocker->setPixmap(QPixmap("/Icon_TranRot/ButtonNow/RockerNow.png"));
        Rocker->move(iX-45,iY+43);
    }else{
        Rocker->setPixmap(QPixmap("Icon_TranRot/IconShow/Rocker.png"));
        Rocker->move(MIXROCKLAB_X,MIXROCKLAB_Y);
   }
}

void se_terminal::TouchButtonDeal(int x){                                      //Touch  5  Button
    switch(x){
    case BUTTONUPPRESS:
        ButtonUp->setPixmap(QPixmap("/Icon_TranRot/ButtonNow/ButtonUpNow.png"));
        break;
    case BUTTONUPRELEASE:
        ButtonUp->setPixmap(QPixmap("/Icon_TranRot/IconShow/ButtonUp.png"));
        ButtonUpDealFunc();
        break;
    case BUTTONLEFTPRESS:
        ButtonLeft->setPixmap(QPixmap("/Icon_TranRot/ButtonNow/ButtonLeftNow.png"));
        break;
    case BUTTONLEFTRELEASE:
        ButtonLeft->setPixmap(QPixmap("/Icon_TranRot/IconShow/ButtonLeft.png"));
        ButtonLeftDealFunc();
        break;
    case BUTTONENTERPRESS:
        ButtonEnter->setPixmap(QPixmap("/Icon_TranRot/ButtonNow/ButtonEnterNow.png"));
        break;
    case BUTTONENTERRELEASE:
        ButtonEnter->setPixmap(QPixmap("/Icon_TranRot/IconShow/ButtonEnter.png"));
        ButtonEnterDealFunc();
        break;
    case BUTTONRIGHTFPRESS:
        ButtonRight->setPixmap(QPixmap("/Icon_TranRot/ButtonNow/ButtonRightNow.png"));
        break;
    case BUTTONRIGHTRELEASE:
        ButtonRight->setPixmap(QPixmap("/Icon_TranRot/IconShow/ButtonRight.png"));
        ButtonRightDealFunc();
        break;
    case BUTTONDOWNPRESS:
        ButtonDown->setPixmap(QPixmap("/Icon_TranRot/ButtonNow/ButtonDownNow.png"));
        break;
    case BUTTONDOWNRELEASE:
        ButtonDown->setPixmap(QPixmap("/Icon_TranRot/IconShow/ButtonDown.png"));
        ButtonDownDealFunc();
       break;
    }
}

void  se_terminal::UpdateCtlMode(void){
    switch(ICURRENTMODE){
    case CAMERCTLMODE:
        g_SendSTM[3] &= ~0x60;
        g_SendSTM[3] |= 0x20;
        ButtonKZName->setPixmap(QPixmap("/Icon_TranRot/IconShow/SXTKZ.png"));
        break;
    case LIGHTCTLMODE:
        g_SendSTM[3] &= ~0x60;
        g_SendSTM[3] |= 0x20;
        ButtonKZName->setPixmap(QPixmap("/Icon_TranRot/IconShow/DGKZ.png"));
        break;
    case ROBOTCTLMODE:
        g_SendSTM[3] &= ~0x60;
        g_SendSTM[3] |= 0x40;
        ButtonKZName->setPixmap(QPixmap("/Icon_TranRot/IconShow/BBKZ.png"));
        break;
    case MENUCTLMODE:
        g_SendSTM[3] &= ~0x60;
        g_SendSTM[3] |= 0x20;
        ButtonKZName->setPixmap(QPixmap("/Icon_TranRot/IconShow/CDKZ.png"));
        break;
    }

}

void  se_terminal::PhyButtonDeal(int Num,int Type){
    switch(Num){
    case 0:
        ButtonUp->setPixmap(QPixmap("/Icon_TranRot/ButtonNow/ButtonUpNow.png"));
        ButtonUpDealFunc();
        break;
    case 1:
        ButtonDown->setPixmap(QPixmap("/Icon_TranRot/ButtonNow/ButtonDownNow.png"));
        ButtonDownDealFunc();
        break;
    case 2:
        ButtonLeft->setPixmap(QPixmap("/Icon_TranRot/ButtonNow/ButtonLeftNow.png"));
        ButtonLeftDealFunc();
        break;
    case 3:
        ButtonRight->setPixmap(QPixmap("/Icon_TranRot/ButtonNow/ButtonRightNow.png"));
        ButtonRightDealFunc();
        break;
    case 4:
        ButtonEnter->setPixmap(QPixmap("/Icon_TranRot/ButtonNow/ButtonEnterNow.png"));
        ButtonEnterDealFunc();
        break;
    case 5:
        ButtonDownRight->setPixmap(QPixmap("/Icon_TranRot/ButtonNow/ButtonDownRightNow.png"));
        ButtonRightDownDealFunc();
        break;
    case 6:
        ButtonDownLeft->setPixmap(QPixmap("/Icon_TranRot/ButtonNow/ButtonDownLeftNow.png"));
        ButtonLeftDownDealFunc(Type);
        break;
    case 7:
        if(!Type){                          //Select Mode
            ICURRENTMODE++;
            if(ICURRENTMODE > MENUCTLMODE)
                ICURRENTMODE = CAMERCTLMODE;
            UpdateCtlMode();
            if(MenuCurState != MENUSTATEHIDE){
                MenuCurState = MENUSTATEHIDE;
                OnelistFlag = 0;
                MenuList->hide();
                SeclistFlag = 0;
                SecMenuList->hide();
                SecFileListDestory();
            }
        } break;
    case 8:break;
    case 9:break;
    case 10:break;
    case 11:break;
    }
}

void se_terminal::GetDirFile(QString Type){
    QDir dir("/home/root/media/");//定义一个QDir变量,设置路径为当前目录的music文件夹(这里可用绝对路径也可以用相对路径)
    QFileInfoList FileInfoList;//文件信息表
    QFileInfo FileInfo;//文件信息变量
    QString StringSong;//用于保存文件信息字符串

    FileList << Type;//把所有mp3文件加入到stringlist_song表中
    dir.setNameFilters(FileList);//过滤文件
    FileInfoList = dir.entryInfoList();//列出所有符合的文件
    for( int i = 0;i < FileInfoList.length();i++){
        FileInfo = FileInfoList.at(i);//把fileinfolist表中某个位置的歌曲名赋给fileinfo变量
        StringSong = FileInfo.fileName();//把fileinfo变量中的文件名转换成QString并赋给string_song
        FileList << StringSong;//把歌曲名赋给stringlist_song表
    }
}

void se_terminal::SecFileListCreate(QString Type){
    GetDirFile(Type);
    for(int i = 1; i < FileList.length();i++){
         QListWidgetItem *lst = new QListWidgetItem(FileList.at(i));
         SecMenuList->addItem(lst);
    }
}

void se_terminal::SecFileListDestory(){
    int index,tmp = SecMenuList->count();
    for(index = 0;index < tmp ;index++){
        QListWidgetItem *item = SecMenuList->takeItem(0);
        delete item;
    }
    FileList.clear();
}

void se_terminal::ButtonUpMenuDeal(void){
    int sum;
    switch(MenuCurState){
    case MENUSTATEHIDE: break;
    case MENUSTATESHOW:
        sum = MenuList->count();
        if((--OnelistFlag) < 0) OnelistFlag = sum - 1;
        MenuList->setCurrentRow(OnelistFlag);
        break;
    case MENUSTATESEC:                                     //判读菜单进入的选项
        switch(OnelistFlag){
        case 0:                                          //视频和图片项
        case 1:
        case 2:
        case 3:
        case 4:
            sum = SecMenuList->count();
            if((--SeclistFlag) < 0) SeclistFlag = sum - 1;
            SecMenuList->setCurrentRow(SeclistFlag);
            break;
         }
        break;
    }
}

void se_terminal::ButtonDownMenuDeal(void){
    int sum;
    switch(MenuCurState){
    case MENUSTATEHIDE: break;
    case MENUSTATESHOW:
        sum = MenuList->count();
        if((++OnelistFlag) > sum - 1) OnelistFlag = 0;
        MenuList->setCurrentRow(OnelistFlag);
        break;
    case MENUSTATESEC:
        switch(OnelistFlag){
        case 0:                                          //视频和图片项
        case 1:
        case 2:
        case 3:
        case 4:
            sum = SecMenuList->count();
            if((++SeclistFlag) > sum - 1) SeclistFlag = 0;
            SecMenuList->setCurrentRow(SeclistFlag);
            break;
        }
        break;
    }
}

void se_terminal::ButtonLeftMenuDeal(void){
    if(DecodeFlag){
        system("pkill -9 decode");
        system("./encodertsp -v 1.264 -a 1.aac -y 2 -I 1 &");
        SET_AUDIO_BYPASS();
        DecodeFlag = 0;
    }else{
        switch(MenuCurState){
        case MENUSTATEHIDE: break;
        case MENUSTATESHOW:
            OnelistFlag = 0;
            MenuList->hide();
            MenuCurState = MENUSTATEHIDE;
            SeclistFlag = 0;
            SecMenuList->hide();
            SecFileListDestory();
            break;
        case MENUSTATESEC:
            switch(OnelistFlag){
            case 0:                                          //视频和图片项
            case 1:
            case 2:
            case 3:
            case 4:
                MenuCurState = MENUSTATESHOW;
                SeclistFlag = 0;
                SecMenuList->hide();
                SecFileListDestory();
                MenuList->show();
                MenuList->setCurrentRow(OnelistFlag);
                break;
            }
            break;
        }
    }
}

void se_terminal::ButtonRightMenuDeal(void){
    switch(MenuCurState){
    case MENUSTATEHIDE:
        if(MenuCurState == MENUSTATEHIDE){
            MenuCurState = MENUSTATESHOW;
            MenuList->show();
            MenuList->setCurrentRow(OnelistFlag);
            g_SendSTM[3] |= 0x60;
        }break;
    case MENUSTATESHOW:
        MenuCurState = MENUSTATESEC;
        MenuList->hide();
        switch(OnelistFlag){
        case 0:
             SecMenuList->show();
             SecFileListCreate("*.avi");                    //"*.bmp"
             SecMenuList->setCurrentRow(SeclistFlag);break;      //视频和图片项
        case 1:
             SecMenuList->show();
             SecFileListCreate("*.png");                   //"*.avi"
             SecMenuList->setCurrentRow(SeclistFlag);break;      //视频和图片项
            break;
        case 2:
            SecMenuList->show();
            SecMenuList->addItem(new QListWidgetItem("放大"));
            SecMenuList->addItem(new QListWidgetItem("缩小"));
            SecMenuList->setCurrentRow(SeclistFlag);
            break;
        case 3:
            SecMenuList->show();
            SecMenuList->addItem(new QListWidgetItem("打开")); //打开 关闭
            SecMenuList->addItem(new QListWidgetItem("关闭"));
            SecMenuList->setCurrentRow(SeclistFlag);
            break;
        case 4:
            SecFileListDestory();
            SecMenuList->show();
            SecMenuList->addItem(new QListWidgetItem("打开"));
            SecMenuList->addItem(new QListWidgetItem("关闭"));
            SecMenuList->setCurrentRow(SeclistFlag);
            break;
        }
        break;
    case MENUSTATESEC:
        switch(OnelistFlag){
        case 0:                                          //视频和图片项
            printf("%s\n",SecMenuList->item(SeclistFlag)->text().toLatin1().data());
            fflush(NULL);
            if(DecodeFlag){
               system("pkill -9 decode");
            }else{
               system("pkill -9 encodertsp");
            }
            memset(cmdbuf,0,128);
            sprintf(cmdbuf, "./decode -y 2 -v h264 -f /home/root/media/%s &",\
                     SecMenuList->item(SeclistFlag)->text().toLatin1().data());
            system(cmdbuf);
            SET_AUDIO_368OUT();
            PauseFlag = 0;
            DecodeFlag = 1;
            break;
        case 1:

            break;
        case 2:
            if(!SeclistFlag){
                BlowUpssFlag += 1;
                if(BlowUpssFlag > 30) BlowUpssFlag = 0;
                BlowUpssStr = "X" + QString("%0").arg((float)(BlowUpssFlag+10)/10);
                BlowUpssLable->setText(BlowUpssStr);
            }else{
                BlowUpssFlag -= 1;
                if(BlowUpssFlag < 0) BlowUpssFlag = 30;
                BlowUpssStr = "X" + QString("%0").arg((float)(BlowUpssFlag+10)/10);
                BlowUpssLable->setText(BlowUpssStr);
            }
            g_SendSTM[2] &= ~0x1F;
            g_SendSTM[2] |= BlowUpssFlag;
            break;
        case 3:
            if(SeclistFlag){
                g_SendSTM[2] &= ~0x20;              //光感
                GMN->show();
                GuanBiaoZhiWei = 0;
            }else{
                g_SendSTM[2] |= 0x20;
                GMN->hide();
                GuanBiaoZhiWei = 1;
            }break;
        case 4:
            if(SeclistFlag){                      //触屏
                g_SendSTM[3] &= ~0x80;
                TouchSN->show();
            }else{
                g_SendSTM[3] |= 0x80;
                TouchSN->hide();
                } break;
        }
        break;
    }
}


void se_terminal::ButtonUpDealFunc(void){
    switch(ICURRENTMODE){
    case CAMERCTLMODE:
        g_SendSTM[2] |= 0x00;
        break;
    case LIGHTCTLMODE:
        if(!GuanBiaoZhiWei){
            if(g_SendSTM[2]&0x01)
                g_SendSTM[2] &= ~0x01;          //上灯
            else
                g_SendSTM[2] |= 0x01;
        }
        break;
    case ROBOTCTLMODE:
        break;
    case MENUCTLMODE:
        ButtonUpMenuDeal();
        break;
    }
}

//Byte[2] bit7—bit6   高低速档    0—低   1—中  2—高
void se_terminal::ButtonDownDealFunc(void){
    switch(ICURRENTMODE){
    case CAMERCTLMODE:
        g_SendSTM[2] |= 0x10;
        break;
    case LIGHTCTLMODE:
        if(g_SendSTM[2]&0x02)           //后灯
            g_SendSTM[2] &= ~0x02;
        else
            g_SendSTM[2] |= 0x02;
        break;
    case ROBOTCTLMODE:
        break;
    case MENUCTLMODE:
        ButtonDownMenuDeal();
        break;
    }
}

void se_terminal::ButtonLeftDealFunc(void){
    switch(ICURRENTMODE){
    case CAMERCTLMODE:
        break;
    case LIGHTCTLMODE:
        if(!GuanBiaoZhiWei){
        if(g_SendSTM[2]&0x08)               //预警灯
            g_SendSTM[2] &= ~0x08;
        else
            g_SendSTM[2] |= 0x08;
        }
        break;
    case ROBOTCTLMODE:
        break;
    case MENUCTLMODE:
         ButtonLeftMenuDeal();
        break;
    }
}

void se_terminal::ButtonRightDealFunc(void){
    switch(ICURRENTMODE){
    case CAMERCTLMODE:
        break;
    case LIGHTCTLMODE:
            if(g_SendSTM[2]&0x04)
                g_SendSTM[2] &= ~0x04;          //前灯
            else
                g_SendSTM[2] |= 0x04;
        break;
    case ROBOTCTLMODE:
        break;
    case MENUCTLMODE:
         ButtonRightMenuDeal();
       break;
    }
}

void se_terminal::ButtonEnterDealFunc(void){
    switch(ICURRENTMODE){
    case CAMERCTLMODE:
        break;
    case LIGHTCTLMODE:
        break;
    case ROBOTCTLMODE:
        break;
    case MENUCTLMODE:
        if(DecodeFlag){
            if(PauseFlag){
                msgServer.sendCmd(QtInterface_Play);
                PauseFlag = 0;
            }else{
                msgServer.sendCmd(QtInterface_Pause);
                PauseFlag = 1;
            }
        }
        break;
    }
}

void se_terminal::ButtonRightDownDealFunc(void){
    CararFlag++;
    if(CararFlag > 2)CararFlag = 0;
        g_SendSTM[2] &= ~0xc0;
        g_SendSTM[2] |= CararFlag << 6;
}

void se_terminal::ButtonLeftDownDealFunc(int Type){
    if(Type){
        if(FIFOCmd & 0x02){
            Rec->hide();
            FIFOCmd &= ~0x02;
            msgServer.sendCmd(QtInterface_Stop);
            system("sync");
            ButtonSDPZLXName->setPixmap(QPixmap("/Icon_TranRot/IconShow/CALXDW.png"));
        }else{
            Rec->show();
            FIFOCmd |= 0x02;
            msgServer.sendCmd(QtInterface_Record);
            ButtonSDPZLXName->setPixmap(QPixmap("/Icon_TranRot/IconShow/CATXDW.png"));
        }
    }else{
        Photo->show();
        FIFOCmd |=  0x01;
        MemTime = 1;
        msgServer.sendCmd(QtInterface_Photo);
    }
}
void se_terminal::slotActionSave()
{
    QPixmap pix = QPixmap::grabWidget(this,0,0,720,1280);
    pix.save("pixture.png","png");
}

void  se_terminal::OsdUpdateFunc(int RetSt){
   // CarInformation
   // 俯仰 横滚 摆臂 温度 速度 电机温度 左转速 右转速  左电极电流 右电极电流  电池电压 速度挡位 航向
    if(RobotHandFlag == 1 && RetSt != 0) {
        ButtonUp->setPixmap(QPixmap("/Icon_TranRot/IconShow/ButtonUp.png"));
        RobotHandFlag = 0;
    }
    if(RobotHandFlag == 2 && RetSt != 1){
        ButtonDown->setPixmap(QPixmap("/Icon_TranRot/IconShow/ButtonDown.png"));
        RobotHandFlag = 0;
    }
    switch(RetSt){
    case 0:
        if(ICURRENTMODE == ROBOTCTLMODE)
            RobotHandFlag = 1;
        else
           ButtonUp->setPixmap(QPixmap("/Icon_TranRot/IconShow/ButtonUp.png"));
        break;
    case 1:
        if(ICURRENTMODE == ROBOTCTLMODE)
         RobotHandFlag = 2;
        else
         ButtonDown->setPixmap(QPixmap("/Icon_TranRot/IconShow/ButtonDown.png"));
        break;
    case 2:
       // ButtonLeft->setPixmap(QPixmap("/Icon_TranRot/IconShow/ButtonLeft.png"));
       // break;
    case 3:
         //ButtonRight->setPixmap(QPixmap("/Icon_TranRot/IconShow/ButtonRight.png"));
      //  break;
    case 4:
      //  ButtonEnter->setPixmap(QPixmap("/Icon_TranRot/IconShow/ButtonEnter.png"));
     //   break;
    case 5:
     //   ButtonDownRight->setPixmap(QPixmap("/Icon_TranRot/IconShow/ButtonDownRight.png"));
     //    break;
    case 6:
        ButtonLeft->setPixmap(QPixmap("/Icon_TranRot/IconShow/ButtonLeft.png"));
        ButtonRight->setPixmap(QPixmap("/Icon_TranRot/IconShow/ButtonRight.png"));
        ButtonEnter->setPixmap(QPixmap("/Icon_TranRot/IconShow/ButtonEnter.png"));
        ButtonDownRight->setPixmap(QPixmap("/Icon_TranRot/IconShow/ButtonDownRight.png"));
        ButtonDownLeft->setPixmap(QPixmap("/Icon_TranRot/IconShow/ButtonDownLeft.png"));
        break;
       default:      break;
    }
    if(MemTime) MemTime++;
    if(MemTime == 6){
        FIFOCmd &= ~0x01;
        MemTime = 0;
        Photo->hide();
    }
  if(MenuCurState == MENUSTATEHIDE){
    QString   TmpString;
    if(g_iCarStateInfo.Pitch > 90) g_iCarStateInfo.Pitch = 90;
    if(g_iCarStateInfo.Pitch < -90) g_iCarStateInfo.Pitch = -90;
    TmpString  = "俯仰:" + QString("%0").arg(g_iCarStateInfo.Pitch) + "°";
    FuYangSt->setText(TmpString);

    if(g_iCarStateInfo.Roll > 180) g_iCarStateInfo.Roll = 180;
    if(g_iCarStateInfo.Roll < -180) g_iCarStateInfo.Roll = -180;
    TmpString  = "横滚:" + QString("%0").arg(g_iCarStateInfo.Roll) + "°";
    HeGunSt->setText(TmpString);

    if(g_iCarStateInfo.Roll > 360) g_iCarStateInfo.Roll = 360;
    if(g_iCarStateInfo.Roll < 0) g_iCarStateInfo.Roll = 0;
    TmpString  = "航向:" + QString("%0").arg(g_iCarStateInfo.Dir) + "°";
    HangXiangSt->setText(TmpString);

    if(g_iCarStateInfo.BaiBiRot > 360) g_iCarStateInfo.BaiBiRot = 360;
    if(g_iCarStateInfo.BaiBiRot < 0) g_iCarStateInfo.BaiBiRot = 0;
    TmpString  = "摆臂:" + QString("%0").arg(g_iCarStateInfo.BaiBiRot) + "°";
    BaiBiSt->setText(TmpString);
    TmpString  = "温度:" + QString("%0").arg(g_iCarStateInfo.HuanJingWenDu) + "℃";
    WeDuSt->setText(TmpString);
    TmpString  = "速度:" + QString("%0").arg(g_iCarStateInfo.CarSpeed) + "m/s";
    SuDuSt->setText(TmpString);
    switch(CararFlag){
    case 0:
        TmpString  = "挡位:低";
        break;
    case 1:
        TmpString  = "挡位:中";
        break;
    case 2:
        TmpString  = "挡位:高";
        break;
    }
    SuDuDangWeiSt->setText(TmpString);
  }
  if(g_iCarStateInfo.YuJingDengFlag)
      LightIconY->show();
  else
      LightIconY->hide();
  if(g_iCarStateInfo.HouDeng)
      LightIcon->show();
  else
      LightIcon->hide();

  if(g_iCarStateInfo.ShangDeng)
      LightIconS->show();
  else
      LightIconS->hide();

  if(g_iCarStateInfo.QianDeng)
      LightIconQ->show();
  else
      LightIconQ->hide();
  if(g_iCarStateInfo.CheTiFanZhuan)
      CTFZ->show();
  else
      CTFZ->hide();
  PowerValSelect(g_iCarStateInfo.CarPowerVal,CarPower);
  PowerValSelect(g_iCarStateInfo.TerPowerVal,TerminalPower);
}

void se_terminal::PowerValSelect(int vale,QLabel *lable){
    if(vale == 1)
        lable->setPixmap(QPixmap("/Icon_TranRot/power/1.png"));
    else if(vale > 1 && vale <= 10)
        lable->setPixmap(QPixmap("/Icon_TranRot/power/10.png"));
    else if(vale > 10 && vale <= 20)
        lable->setPixmap(QPixmap("/Icon_TranRot/power/20.png"));
    else if(vale > 20 && vale <= 25)
        lable->setPixmap(QPixmap("/Icon_TranRot/power/25.png"));
    else if(vale > 25 && vale <= 50)
        lable->setPixmap(QPixmap("/Icon_TranRot/power/50.png"));
    else if(vale > 50 && vale <= 75)
        lable->setPixmap(QPixmap("/Icon_TranRot/power/75.png"));
    else if(vale > 75 && vale <= 100)
        lable->setPixmap(QPixmap("/Icon_TranRot/power/100.png"));
}

int se_terminal::SetGPIO(int value)  //write GPIO22
{
    fd_gpio = open("/dev/dm368_gpio", O_RDWR);
    if (fd_gpio < 0){
         printf("Can't open device /dev/dm368_gpio\r\n");
    } else {
        gpiobuf[0] = value;
        write(fd_gpio, gpiobuf, 2);
    }
   // UsartClassThr::close_fd(fd_gpio);
    return 0;
}

void se_terminal::SET_AUDIO_BYPASS()
{
    SetGPIO(0);
}
void se_terminal::SET_AUDIO_368OUT()
{
    SetGPIO(1);
}
