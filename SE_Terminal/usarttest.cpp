#include "usarttest.h"

T_KEYDATE g_iKeyDate;
T_CARSTATEINFO g_iCarStateInfo;
/*
Byte[8] 车体电量
Byte[9] 终端电量
Byte[10]      PITCH角度值。（范围 -90到+90）
              bit7 符号位。0-正数。1-负数。
              bit6—bit0    0—90.
Byte[11]—byte[12]   ROLL角度值（范围-180到+180）
              Byte[12].bit7 符号位。0-正数。1-负数。
              Byte[12].bit6—byte[11].bit0   0-180.
Byte[13]—byte[14]    DIR角度值（范围0-360）
              Byte[13].bit7—byte[12].bit0   0-360

Byte[15]:  车体速度
         bit7  车体的速度方向。 0-正向，1-反向。(m/s)
         bit6- bit4  车体速度方向的整数位。（范围0-7）
         bit3- bit0  车体速度方向的小数位。（范围0-9）

byte[16]—byte[17]  摆臂电机角度值和灯状态。
            byte17.bit[3] –byte16 摆臂电机角度值。（角度范围0-360）
            byte17.bit7  预警灯       0—关             1—开
            byte17.bit6  前灯         0—关            1—开
            byte17.bit5  后灯         0—关            1—开
            byte17.bit4  上灯         0—关            1—开
Byte[18]
            bit0  左电机温度报警位。 0-未报警  1-报警
            bit1  右电机温度报警位。 0-未报警  1-报警
            bit2  左电机电流报警位。 0-未报警  1-报警
            bit3  右电机电流报警位。 0-未报警  1-报警
            bit4  左电机保护位。     0-未保护  1-保护
            bit5  右电机保护位。     0-未保护  1-保护
            bit6  车体翻转。 0-没翻转。 1-翻转。
Byte[19] 环境温度
           bit7 符号位
           bit6—bit1  整数位
           bit0  小数位
*/
void UsartClassThr::run(){
    int ret;
    ret = uart_init(1, 0);
    if(ret < 0)
        printf("uart_init error.\n");
    while(1){
        ret = read(ut_fd,CarInformation,BUFFSIZE);
        if(ret < 0){
            printf("read Error.\n");
            return;
        }
        for(int i = 0; i< ret;i++){
            printf("%x ",CarInformation[i]);
            fflush(NULL);
        }
        if(CarInformation[0] == 0xee && CarInformation[20] == 0xff){
            g_iKeyDate.KeyVale[0]  = (CarInformation[1] >> 0) & 0x03;
            g_iKeyDate.KeyVale[1]  = (CarInformation[1] >> 2) & 0x03;
            g_iKeyDate.KeyVale[2]  = (CarInformation[1] >> 4) & 0x03;
            g_iKeyDate.KeyVale[3]  = (CarInformation[1] >> 6) & 0x03;
            g_iKeyDate.KeyVale[4]  = (CarInformation[2] >> 0) & 0x03;
            g_iKeyDate.KeyVale[5]  = (CarInformation[2] >> 2) & 0x03;
            g_iKeyDate.KeyVale[6]  = (CarInformation[2] >> 4) & 0x03;
            g_iKeyDate.KeyVale[7]  = (CarInformation[2] >> 6) & 0x03;
            g_iKeyDate.KeyVale[8]  = (CarInformation[3] >> 0) & 0x03;
            g_iKeyDate.KeyVale[9]  = (CarInformation[3] >> 2) & 0x03;
            g_iKeyDate.KeyVale[10] = (CarInformation[3] >> 4) & 0x03;
            g_iKeyDate.KeyVale[11] = (CarInformation[3] >> 6) & 0x03;
            g_iKeyDate.TouchDate_X =(CarInformation[5] << 8) + CarInformation[4];
            g_iKeyDate.TouchDate_Y =(CarInformation[7] << 8) + CarInformation[6];

            g_iCarStateInfo.CarPowerVal = CarInformation[8];
            g_iCarStateInfo.TerPowerVal = CarInformation[9];
            if(CarInformation[10] & 0x80)
                g_iCarStateInfo.Pitch = (CarInformation[10] & 0x7F)*(-1);
            else
                g_iCarStateInfo.Pitch = (CarInformation[10] & 0x7F);

            if(CarInformation[12] & 0x80)
                g_iCarStateInfo.Roll = (((CarInformation[12] & 0x7f) << 8)  + CarInformation[11])*(-1);
            else
                g_iCarStateInfo.Roll = ((CarInformation[12] & 0x7f) << 8)  + CarInformation[11];

            g_iCarStateInfo.Dir = (CarInformation[13] << 8) + CarInformation[12];

            if(CarInformation[15] & 0x80)
                g_iCarStateInfo.CarSpeed = (((float)(CarInformation[15] & 0x0F)/10) + ((CarInformation[15] & 0x70) >> 4))*-1;
            else
                g_iCarStateInfo.CarSpeed = ((float)(CarInformation[15] & 0x0F)/10) + ((CarInformation[15] & 0x70) >> 4);

            g_iCarStateInfo.BaiBiRot = ((CarInformation[17] & 0x0F) << 8) + CarInformation[16];
            g_iCarStateInfo.YuJingDengFlag =CarInformation[17] & 0x80;
            g_iCarStateInfo.QianDeng =  CarInformation[17] & 0x40;
            g_iCarStateInfo.HouDeng =CarInformation[17] & 0x20;
            g_iCarStateInfo.ShangDeng =CarInformation[17] & 0x10;
            g_iCarStateInfo.CheTiFanZhuan =CarInformation[18] & 0x40;

            if(CarInformation[19] & 0x80)
                g_iCarStateInfo.HuanJingWenDu = (((CarInformation[19] & 0x7E) >> 1) + ((float)(CarInformation[19] & 0x01)/10))*-1;
            else
                g_iCarStateInfo.HuanJingWenDu = ((CarInformation[19] & 0x7E) >> 1)+ ((float)(CarInformation[19] & 0x01)/10);
        }
    }
}

int UsartClassThr::uart_init(int arg, int baud)
{
    char port[20];
    struct termios Opt;
    int uartbiit[50]= {B115200,B9600,B19200,B4800,B2400,B1200};
    sprintf(port,"/dev/ttyS%d",arg);
    printf("Use port: %s \n", port);
    ut_fd = open(port, O_RDWR);
    if (ut_fd < 0){
        printf("open error.\n");
        return -1;
    }
    tcgetattr(ut_fd,&Opt);
    tcflush(ut_fd,TCIFLUSH);
    cfsetispeed(&Opt,uartbiit[baud]);
    cfsetospeed(&Opt,uartbiit[baud]);
    Opt.c_cflag |= CS8;
    Opt.c_cflag &= ~PARENB;
    Opt.c_oflag &= ~(OPOST);
    Opt.c_cflag &= ~CSTOPB;
    Opt.c_lflag &= ~(ICANON|ISIG|ECHO|IEXTEN);
    Opt.c_iflag &= ~(INPCK|BRKINT|ICRNL|ISTRIP|IXON);
    Opt.c_cc[VMIN] = 64;
    Opt.c_cc[VTIME] = 1;
    if (tcsetattr(ut_fd,TCSANOW,&Opt) != 0){
        perror("SetupSerial!\n");
        close(ut_fd);
        return -1;
    }
    return 0;
}

void UsartClassThr::UsartSend(unsigned char *SendData,int size){
    int ret;
    do{
        ret = write(ut_fd, SendData,size);
        if(ret < 0){
            printf("UsartSend Error.\n");
            return;
        }
    }while(ret != size);
}


void UsartClassThr::close_fd(int fd){
    if(fd == 0)
        return;
    close(fd);
    fd = 0;
}
