#include "se_terminal.h"
#include "ui_se_terminal.h"

se_terminal::se_terminal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::se_terminal)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    MemTime = 0;
    FIFOCmd = 0;
    GuanBiaoZhiWei= 0;
    RectGround = new QLabel(this);
  //  RectGround->resize(1280,720);
    RectGround->setPixmap(QPixmap("/Icon_TranRot90/IconShow/RectGround.png"));
    RectGround->move(0,0);

    /*7 Button*/
    ButtonLeft  = new QLabel(this);
   // ButtonLeft->resize(71,170);
    ButtonLeft->move(116,1162);
    ButtonLeft->setPixmap(QPixmap("/Icon_TranRot90/IconShow/ButtonLeft.png"));

    ButtonRight = new QLabel(this);
    ButtonRight->move(116,1044);
    ButtonRight->setPixmap(QPixmap("/Icon_TranRot90/IconShow/ButtonRight.png"));

    ButtonUp    = new QLabel(this);
    ButtonUp->move(105,1056);
    ButtonUp->setPixmap(QPixmap("/Icon_TranRot90/IconShow/ButtonUp.png"));

    ButtonDown  = new QLabel(this);
    ButtonDown->move(224,1055);
    ButtonDown->setPixmap(QPixmap("/Icon_TranRot90/IconShow/ButtonDown.png"));

    ButtonEnter  = new QLabel(this);
    ButtonEnter->move(165,1102);
    ButtonEnter->setPixmap(QPixmap("/Icon_TranRot90/IconShow/ButtonEnter.png"));

    ButtonDownLeft  = new QLabel(this);
    ButtonDownLeft->move(316,1155);
    ButtonDownLeft->setPixmap(QPixmap("/Icon_TranRot90/IconShow/ButtonDownLeft.png"));

    ButtonDownRight  = new QLabel(this);
    ButtonDownRight->move(317,1039);
    ButtonDownRight->setPixmap(QPixmap("/Icon_TranRot90/IconShow/ButtonDownRight.png"));

    ButtonRightDownLeft  = new QLabel(this);
    ButtonRightDownLeft->move(316,176);
    ButtonRightDownLeft->setPixmap(QPixmap("/Icon_TranRot90/IconShow/ButtonDownLeft.png"));

    ButtonRightDownRight  = new QLabel(this);
    ButtonRightDownRight->move(317,60);
    ButtonRightDownRight->setPixmap(QPixmap("/Icon_TranRot90/IconShow/ButtonDownRight.png"));

    CTFZ  = new QLabel(this);
    CTFZ->move(679,583);
    CTFZ->setPixmap(QPixmap("/Icon_TranRot90/IconShow/CTFZ.png"));
    CTFZ->hide();
/********************************************************************************/
    /*8 Tile*/
    SignalNow = new QLabel(this);
    SignalNow->move(11,1223);
    SignalNow->setPixmap(QPixmap("/Icon_TranRot90/Signal/signalEmpty.png"));

    LightIcon = new QLabel(this);
    LightIcon->move(14,1150);
    LightIcon->setPixmap(QPixmap("/Icon_TranRot90/IconShow/HLight.png"));
    LightIcon->hide();

    LightIconQ = new QLabel(this);
    LightIconQ->move(14,1100);
    LightIconQ->setPixmap(QPixmap("/Icon_TranRot90/IconShow/QLight.png"));
    LightIconQ->hide();

    LightIconS = new QLabel(this);
    LightIconS->move(14,1050);
    LightIconS->setPixmap(QPixmap("/Icon_TranRot90/IconShow/SLight.png"));
    LightIconS->hide();

    LightIconY = new QLabel(this);
    LightIconY->move(14,1000);
    LightIconY->setPixmap(QPixmap("/Icon_TranRot90/IconShow/YLight.png"));
    LightIconY->hide();

    Photo = new QLabel(this);
    Photo->move(14,700);
    Photo->setPixmap(QPixmap("/Icon_TranRot90/IconShow/Photo.png"));
    Photo->hide();

    Rec = new QLabel(this);
    Rec->move(17,600);
    Rec->setPixmap(QPixmap("/Icon_TranRot90/IconShow/Rec.png"));
    Rec->hide();

    LuoPan = new QLabel(this);
    LuoPan->move(15,222);
    LuoPan->setPixmap(QPixmap("/Icon_TranRot90/IconShow/LuoPan.png"));

    CarPower = new QLabel(this);
    CarPower->move(18,126);
    CarPower->setPixmap(QPixmap("/Icon_TranRot90/power/100.png"));

    TerminalPower = new QLabel(this);
    TerminalPower->move(20,30);
    TerminalPower->setPixmap(QPixmap("/Icon_TranRot90/power/100.png"));

    TouchSN = new QLabel(this);
    TouchSN->resize(35,40);
    TouchSN->move(10,300);
    TouchSN->setScaledContents(true);
    TouchSN->setPixmap(QPixmap("/Icon_TranRot90/IconShow/ZCMPN.png"));
    TouchSN->hide();

    GMN = new QLabel(this);
    GMN->move(12,380);
    GMN->resize(30,36);
    GMN->setScaledContents(true);   //setScaleContents
    GMN->setPixmap(QPixmap("/Icon_TranRot90/IconShow/ZGMN.png"));
    GMN->hide();
/********************************************************************************/
    UpDirection    = new QLabel(this);
    UpDirection->move(105,145);
    UpDirection->setPixmap(QPixmap("/Icon_TranRot90/IconShow/Up.png"));

    LeftDirection  = new QLabel(this);
    LeftDirection->move(203,256);
    LeftDirection->setPixmap(QPixmap("/Icon_TranRot90/IconShow/Left.png"));

    RightDirection  = new QLabel(this);
    RightDirection->move(203,51);
    RightDirection->setPixmap(QPixmap("/Icon_TranRot90/IconShow/Right.png"));

    DownDirection  = new QLabel(this);
    DownDirection->move(307,146);
    DownDirection->setPixmap(QPixmap("/Icon_TranRot90/IconShow/Down.png"));

    RockerGround  = new QLabel(this);
    RockerGround->move(MAXROCKLAB_X,MAXROCKLAB_Y);
    RockerGround->setPixmap(QPixmap("/Icon_TranRot90/IconShow/RockerGround.png"));

    Rocker  = new QLabel(this);
    Rocker->move(MIXROCKLAB_X,MIXROCKLAB_Y);
    Rocker->setPixmap(QPixmap("/Icon_TranRot90/IconShow/Rocker.png"));

    /*1 Title*/
    CarArgUp = new QLabel(this);
    CarArgUp->move(504,29);
    CarArgUp->setPixmap(QPixmap("/Icon_TranRot90/IconShow/CarArgUp.png"));

    CTKZ = new QLabel(this);
    CTKZ->move(74,118);
    CTKZ->setPixmap(QPixmap("/Icon_TranRot90/IconShow/CTKZ.png"));

    ButtonKZName = new QLabel(this);
    ButtonKZName->move(74,1070);
    ButtonKZName->setPixmap(QPixmap("/Icon_TranRot90/IconShow/SXTKZ.png"));

    ButtonSDPZLXName = new QLabel(this);
    ButtonSDPZLXName->move(345,1060);
    ButtonSDPZLXName->setPixmap(QPixmap("/Icon_TranRot90/IconShow/CALXDW.png"));

    iButtonMsg = new KeyDel;
    iButtonMsg ->start();
    connect(iButtonMsg,SIGNAL(TouchButtonMsg(int)),this,SLOT(TouchButtonDeal(int)));
    connect(iButtonMsg,SIGNAL(PhyButtonMsg(int,int)),this,SLOT(PhyButtonDeal(int,int)));
    connect(iButtonMsg,SIGNAL(RockerSgl(int,int,int)),this,SLOT(TouchRockerDeal(int,int,int)));
    connect(iButtonMsg,SIGNAL(OsdUpdate(int)),this,SLOT(OsdUpdateFunc(int)));

    ICURRENTMODE = CAMERCTLMODE;
    MenuCurState = MENUSTATEHIDE;
    /***********************************MENU********************************************/
    OnelistFlag = 0;
    SeclistFlag = 0;
    MenuList = new QListWidget;
    MenuList->resize(275,240);
    MenuList->move(990,400);
    MenuList->setIconSize(QSize(40,26));
    //光感 放大 触屏
    MenuList->addItem(new QListWidgetItem(QIcon("/Icon_TranRot90/IconShow/SHIPIN.png"),tr("      视频")));
    MenuList->addItem(new QListWidgetItem(QIcon("/Icon_TranRot90/IconShow/TUPIAN.png"),tr("      图片")));
    MenuList->addItem(new QListWidgetItem(QIcon("/Icon_TranRot90/IconShow/SFJ.png"), tr("      缩放")));
    MenuList->addItem(new QListWidgetItem(QIcon("/Icon_TranRot90/IconShow/GM.png"), tr("      光感")));
    MenuList->addItem(new QListWidgetItem(QIcon("/Icon_TranRot90/IconShow/CMP.png"), tr("      触屏")));
    MenuList->setFont(QFont("JPTZ",20,QFont::Bold));

    MenuList->setStyleSheet("QListWidget{background-color:rgb(70,70,70);border:8px solid gray;border-color:rgb(60,60,60);}"
                            "QListWidget::Item{padding-top:8px; padding-bottom:8px; }");
                            //"QListWidget::item:selected:!active{border-width:0px; background:lightgreen; color:red;}");

    SecMenuList = new QListWidget;
    SecMenuList->resize(275,240);
    SecMenuList->move(1000,400);
    SecMenuList->setIconSize(QSize(40,26));
    SecMenuList->setFont(QFont("JPTZ",18,QFont::AnyStyle));
    SecMenuList->setStyleSheet("QListWidget{background-color:rgb(70,70,70);border:8px solid gray;border-color:rgb(60,60,60);}"
                        "QListWidget::Item{padding-top:8px; padding-bottom:8px; }");
                    //    "QListWidget::item:selected:!active{border-width:0px; background:lightgreen; color:red;}");
    SecMenuList->setCurrentRow(SeclistFlag);
    SecMenuList->hide();
    MenuList->setCurrentRow(OnelistFlag);
    MenuList->hide();

    /*State Info*/
    FuYangSt= new QLabel;
    FuYangSt->resize(140,24);
    FuYangSt->move(1020,460);
    FuYangSt->setAlignment(Qt::AlignLeft);
    FuYangSt->setFont(QFont("JPTZ",20,QFont::AnyStyle));
    FuYangSt->setStyleSheet("QLabel{background:transparent;color:white;};");

    HeGunSt = new QLabel;
    HeGunSt->resize(140,24);
    HeGunSt->move(1140,460);
    HeGunSt->setAlignment(Qt::AlignLeft);
    HeGunSt->setFont(QFont("JPTZ",20,QFont::AnyStyle));
    HeGunSt->setStyleSheet("QLabel{background:transparent;color:white;};");

    HangXiangSt = new QLabel;
    HangXiangSt->resize(140,24);
    HangXiangSt->move(1020,500);
    HangXiangSt->setAlignment(Qt::AlignLeft);
    HangXiangSt->setFont(QFont("JPTZ",20,QFont::AnyStyle));
    HangXiangSt->setStyleSheet("QLabel{background:transparent;color:white;};");

    BaiBiSt = new QLabel;
    BaiBiSt->resize(140,24);
    BaiBiSt->move(1140,500);
    BaiBiSt->setAlignment(Qt::AlignLeft);
    BaiBiSt->setFont(QFont("JPTZ",20,QFont::AnyStyle));
    BaiBiSt->setStyleSheet("QLabel{background:transparent;color:white;};");

    WeDuSt  = new QLabel;
    WeDuSt->resize(140,24);
    WeDuSt->move(1020,540);
    WeDuSt->setAlignment(Qt::AlignLeft);
    WeDuSt->setFont(QFont("JPTZ",20,QFont::AnyStyle));
    WeDuSt->setStyleSheet("QLabel{background:transparent;color:white;};");

    SuDuSt  = new QLabel;
    SuDuSt->resize(140,24);
    SuDuSt->move(1140,540);
    SuDuSt->setAlignment(Qt::AlignLeft);
    SuDuSt->setFont(QFont("JPTZ",20,QFont::AnyStyle));
    SuDuSt->setStyleSheet("QLabel{background:transparent;color:white;};");

    SuDuDangWeiSt  = new QLabel;
    SuDuDangWeiSt->resize(140,24);
    SuDuDangWeiSt->move(1020,580);
    SuDuDangWeiSt->setAlignment(Qt::AlignLeft);
    SuDuDangWeiSt->setFont(QFont("JPTZ",20,QFont::AnyStyle));
    SuDuDangWeiSt->setStyleSheet("QLabel{background:transparent;color:white;};");

    pScene = new QGraphicsScene;
    pScene->addWidget(FuYangSt);
    pScene->addWidget(HeGunSt);
    pScene->addWidget(HangXiangSt);
    pScene->addWidget(BaiBiSt);
    pScene->addWidget(WeDuSt);
    pScene->addWidget(SuDuSt);
    pScene->addWidget(SuDuDangWeiSt);
    pScene->addWidget(MenuList);
    pScene->addWidget(SecMenuList);
    pView = new QGraphicsView(pScene, this);
    pView->setStyleSheet("background: transparent;border:0px");
    //pView->setAutoFillBackground(true);
    pView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pView->setGeometry(412,12,240,280);
    pView->rotate(-90);

    BlowUpssFlag = 0;
    BlowUpssLable = new QLabel;
    BlowUpssLable->resize(60,20);
    //BlowUpssLable->move(40,295);//1020,140);
    BlowUpssLable->setAlignment(Qt::AlignLeft);
    BlowUpssLable->setFont(QFont("JPTZ",20,QFont::AnyStyle));
    BlowUpssLable->setStyleSheet("QLabel{background:transparent;color:white;};");
    BlowUpssStr = "X" + QString("%0").arg((float)(BlowUpssFlag+10)/10);
    BlowUpssLable->setText(BlowUpssStr);

    BlowUpssScene = new QGraphicsScene;
    BlowUpssScene->addWidget(BlowUpssLable);
    BlowUpsspView = new QGraphicsView(BlowUpssScene, this);
    BlowUpsspView->setStyleSheet("background: transparent;border:0px");
    //pView->setAutoFillBackground(true);
    BlowUpsspView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    BlowUpsspView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    BlowUpsspView->setGeometry(40,295,35,60);
    BlowUpsspView->rotate(-90);

    CararFlag = 0;
    ui->setupUi(this);
}

se_terminal::~se_terminal()
{
    delete ui;
}

void se_terminal::TouchRockerDeal(int iX,int iY,int iPress){
    if(iPress){
        Rocker->setPixmap(QPixmap("/Icon_TranRot90/ButtonNow/RockerNow.png"));
        Rocker->move(iX-45,iY+43);
    }else{
        Rocker->setPixmap(QPixmap("Icon_TranRot90/IconShow/Rocker.png"));
        Rocker->move(MIXROCKLAB_X,MIXROCKLAB_Y);
   }
}

void se_terminal::TouchButtonDeal(int x){                                      //Touch  5  Button
    switch(x){
    case BUTTONUPPRESS:
        ButtonUp->setPixmap(QPixmap("/Icon_TranRot90/ButtonNow/ButtonUpNow.png"));
        break;
    case BUTTONUPRELEASE:
        ButtonUp->setPixmap(QPixmap("/Icon_TranRot90/IconShow/ButtonUp.png"));
        ButtonUpDealFunc();
        break;
    case BUTTONLEFTPRESS:
        ButtonLeft->setPixmap(QPixmap("/Icon_TranRot90/ButtonNow/ButtonLeftNow.png"));
        break;
    case BUTTONLEFTRELEASE:
        ButtonLeft->setPixmap(QPixmap("/Icon_TranRot90/IconShow/ButtonLeft.png"));
        ButtonLeftDealFunc();
        break;
    case BUTTONENTERPRESS:
        ButtonEnter->setPixmap(QPixmap("/Icon_TranRot90/ButtonNow/ButtonEnterNow.png"));
        break;
    case BUTTONENTERRELEASE:
        ButtonEnter->setPixmap(QPixmap("/Icon_TranRot90/IconShow/ButtonEnter.png"));
        ButtonEnterDealFunc();
        break;
    case BUTTONRIGHTFPRESS:
        ButtonRight->setPixmap(QPixmap("/Icon_TranRot90/ButtonNow/ButtonRightNow.png"));
        break;
    case BUTTONRIGHTRELEASE:
        ButtonRight->setPixmap(QPixmap("/Icon_TranRot90/IconShow/ButtonRight.png"));
        ButtonRightDealFunc();
        break;
    case BUTTONDOWNPRESS:
        ButtonDown->setPixmap(QPixmap("/Icon_TranRot90/ButtonNow/ButtonDownNow.png"));
        break;
    case BUTTONDOWNRELEASE:
        ButtonDown->setPixmap(QPixmap("/Icon_TranRot90/IconShow/ButtonDown.png"));
        ButtonDownDealFunc();
       break;
    }
}

void  se_terminal::UpdateCtlMode(void){
    switch(ICURRENTMODE){
    case CAMERCTLMODE:
        g_SendSTM[3] &= ~0x60;
        g_SendSTM[3] |= 0x20;
        ButtonKZName->setPixmap(QPixmap("/Icon_TranRot90/IconShow/SXTKZ.png"));
        break;
    case LIGHTCTLMODE:
        g_SendSTM[3] &= ~0x60;
        g_SendSTM[3] |= 0x20;
        ButtonKZName->setPixmap(QPixmap("/Icon_TranRot90/IconShow/DGKZ.png"));
        break;
    case ROBOTCTLMODE:
        g_SendSTM[3] &= ~0x60;
        g_SendSTM[3] |= 0x40;
        ButtonKZName->setPixmap(QPixmap("/Icon_TranRot90/IconShow/BBKZ.png"));
        break;
    case MENUCTLMODE:
        g_SendSTM[3] &= ~0x60;
        g_SendSTM[3] |= 0x20;
        ButtonKZName->setPixmap(QPixmap("/Icon_TranRot90/IconShow/CDKZ.png"));
        break;
    }

}

void  se_terminal::PhyButtonDeal(int Num,int Type){
    switch(Num){
    case 0:
        ButtonUp->setPixmap(QPixmap("/Icon_TranRot90/ButtonNow/ButtonUpNow.png"));
        ButtonUpDealFunc();
        break;
    case 1:
        ButtonDown->setPixmap(QPixmap("/Icon_TranRot90/ButtonNow/ButtonDownNow.png"));
        ButtonDownDealFunc();
        break;
    case 2:
        ButtonLeft->setPixmap(QPixmap("/Icon_TranRot90/ButtonNow/ButtonLeftNow.png"));
        ButtonLeftDealFunc();
        break;
    case 3:
        ButtonRight->setPixmap(QPixmap("/Icon_TranRot90/ButtonNow/ButtonRightNow.png"));
        ButtonRightDealFunc();
        break;
    case 4:
        ButtonEnter->setPixmap(QPixmap("/Icon_TranRot90/ButtonNow/ButtonEnterNow.png"));
        ButtonEnterDealFunc();
        break;
    case 5:
        ButtonDownRight->setPixmap(QPixmap("/Icon_TranRot90/ButtonNow/ButtonDownRightNow.png"));
        ButtonRightDownDealFunc();
        break;
    case 6:
        ButtonDownLeft->setPixmap(QPixmap("/Icon_TranRot90/ButtonNow/ButtonDownLeftNow.png"));
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
    QDir dir("/Icon/ButtonNow/");//定义一个QDir变量,设置路径为当前目录的music文件夹(这里可用绝对路径也可以用相对路径)
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
             SecFileListCreate("*.png");                    //"*.bmp"
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
        case 1:
            printf("%s\n",SecMenuList->item(SeclistFlag)->text().toLatin1().data());
            fflush(NULL);
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
            ButtonSDPZLXName->setPixmap(QPixmap("/Icon_TranRot90/IconShow/CALXDW.png"));
        }else{
            Rec->show();
            FIFOCmd |= 0x02;
            ButtonSDPZLXName->setPixmap(QPixmap("/Icon_TranRot90/IconShow/CATXDW.png"));
        }
    }else{
        Photo->show();
        FIFOCmd |=  0x01;
        MemTime = 1;
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
        ButtonUp->setPixmap(QPixmap("/Icon_TranRot90/IconShow/ButtonUp.png"));
        RobotHandFlag = 0;
    }
    if(RobotHandFlag == 2 && RetSt != 1){
        ButtonDown->setPixmap(QPixmap("/Icon_TranRot90/IconShow/ButtonDown.png"));
        RobotHandFlag = 0;
    }
    switch(RetSt){
    case 0:
        if(ICURRENTMODE == ROBOTCTLMODE)
            RobotHandFlag = 1;
        else
           ButtonUp->setPixmap(QPixmap("/Icon_TranRot90/IconShow/ButtonUp.png"));
        break;
    case 1:
        if(ICURRENTMODE == ROBOTCTLMODE)
         RobotHandFlag = 2;
        else
         ButtonDown->setPixmap(QPixmap("/Icon_TranRot90/IconShow/ButtonDown.png"));
        break;
    case 2:
       // ButtonLeft->setPixmap(QPixmap("/Icon_TranRot90/IconShow/ButtonLeft.png"));
       // break;
    case 3:
         //ButtonRight->setPixmap(QPixmap("/Icon_TranRot90/IconShow/ButtonRight.png"));
      //  break;
    case 4:
      //  ButtonEnter->setPixmap(QPixmap("/Icon_TranRot90/IconShow/ButtonEnter.png"));
     //   break;
    case 5:
     //   ButtonDownRight->setPixmap(QPixmap("/Icon_TranRot90/IconShow/ButtonDownRight.png"));
     //    break;
    case 6:
        ButtonLeft->setPixmap(QPixmap("/Icon_TranRot90/IconShow/ButtonLeft.png"));
        ButtonRight->setPixmap(QPixmap("/Icon_TranRot90/IconShow/ButtonRight.png"));
        ButtonEnter->setPixmap(QPixmap("/Icon_TranRot90/IconShow/ButtonEnter.png"));
        ButtonDownRight->setPixmap(QPixmap("/Icon_TranRot90/IconShow/ButtonDownRight.png"));
        ButtonDownLeft->setPixmap(QPixmap("/Icon_TranRot90/IconShow/ButtonDownLeft.png"));
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
        lable->setPixmap(QPixmap("/Icon_TranRot90/power/1.png"));
    else if(vale > 1 && vale <= 10)
        lable->setPixmap(QPixmap("/Icon_TranRot90/power/10.png"));
    else if(vale > 10 && vale <= 20)
        lable->setPixmap(QPixmap("/Icon_TranRot90/power/20.png"));
    else if(vale > 20 && vale <= 25)
        lable->setPixmap(QPixmap("/Icon_TranRot90/power/25.png"));
    else if(vale > 25 && vale <= 50)
        lable->setPixmap(QPixmap("/Icon_TranRot90/power/50.png"));
    else if(vale > 50 && vale <= 75)
        lable->setPixmap(QPixmap("/Icon_TranRot90/power/75.png"));
    else if(vale > 75 && vale <= 100)
        lable->setPixmap(QPixmap("/Icon_TranRot90/power/100.png"));
}

