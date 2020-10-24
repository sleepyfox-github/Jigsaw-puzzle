/*滑块拼图是一款策略类游戏，把一幅图案分为相等的若干正方型小方块，取走其中一块留出空位，
利用多余的空格滑动其他小方块，打乱图案形成拼图。复位时都不能取下任何小方块，利用缺少的空位
滑动图案中的小方块使其复原。*/
/*程序运行后先随机打乱，然后利用鼠标点击将拼图复原。鼠标只能分别控制与空格相邻的上下左右的
滑块往空格位移动，判断图片复原则显示拼图完成*/

/*预处理指令读取头文件*/
#include"acllib.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/*宏定义区*/
#define WNDWIDTH 800
#define WNDHEIGHT 600
#define SIZE 200
#define ROW WNDHEIGHT/SIZE
#define COL WNDHEIGHT/SIZE

/*全局变量声明*/
ACL_Image img[ROW* COL],preimg;
ACL_Sound clicksonud[ROW * COL], winsound;
int map[ROW][COL];
int r0,c0,temp;
char img_name[] = "1.jpg";
char son_name[] = "1.mp3";
boolean suc = true;

/*函数声明*/
void loadImages();//图片加载
void loadSounds();//音效加载
void initPos();//随机打乱函数
void MouseEvent(int x, int y, int button, int event);//游戏过程

/*主函数*/
int Setup()
{
    initWindow("拼图游戏", 0, 0, WNDWIDTH, WNDHEIGHT);
    loadSounds();//音效加载
    loadImages();//图片加载
    initPos();//随机打乱函数
    registerMouseEvent(MouseEvent);//游戏过程
    return 0;
}

/*图片加载*/
void loadImages()
{
    loadImage("原图片.jpg", &preimg);
	for (int i = 0; i < ROW * COL; ++i)
	{
		img_name[0] = i + 1 + '0';
		loadImage(img_name, &img[i]);
	}
//初始化map坐标数组，映射9个位置
//之后的图片交换，均只用交换map数组中的值，绘制时取其值即可
    for (int i = 0; i <  ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            map[i][j] = i + j*ROW;
        } 
    }
}

/*音效加载*/
void loadSounds()
{
    loadSound("日暮里.mp3",&winsound);
    for (int i = 0; i < ROW * COL; ++i)
    {
        son_name[0] = i + 1 + '0';
        loadSound(son_name, &clicksonud[i]);
    }
}

/*随机打乱函数*/
void initPos()
{
    srand((unsigned)time(NULL));
    int pos = 0;
    int i;
        r0=2,c0=2;
//生成随机数，并交给switch判断，使得空白块与周围相应的块交换
    for (i = 0; i < 100; i++)
    {
            pos = rand() % 4;
            switch (pos)
            {
            case 0:
                if ( (r0-1) >= 0)
                {
                    temp = map[r0][c0];
                    map[r0][c0] = map[r0-1][c0];
                    map[r0-1][c0] = temp;
                    r0--;
                    break;
                }
            case 1:
                if ((r0 + 1) <= 2)
                {
                    temp = map[r0][c0];
                    map[r0][c0] = map[r0 + 1][c0];
                    map[r0 + 1][c0] = temp;
                    r0++;
                    break;
                }
            case 2:
                if ((c0-1) >= 0)
                {
                    temp = map[r0][c0];
                    map[r0][c0] = map[r0][c0-1];
                    map[r0][c0-1] = temp;
                    c0--;
                    break;
                }
            case 3:
                if ((c0 + 1) <= 2)
                {
                    temp = map[r0][c0];
                    map[r0][c0] = map[r0][c0+1];
                    map[r0][c0+1] = temp;
                    c0++;
                    break;
                }
            default:
                break;
            }
    }
    beginPaint();
    putImageScale(&preimg, 600, 200, SIZE, SIZE);
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            putImageScale(&img[map[i][j]], i * SIZE, j * SIZE, SIZE, SIZE);
        }

    }
    endPaint();
}

/*游戏过程*/
void MouseEvent(int x, int y, int button, int event)
{
    int r, c;
    if (x<(WNDWIDTH-SIZE)&&(button == LEFT_BUTTON && event == BUTTON_DOWN))
    {
        c = y / SIZE;
        r = x / SIZE;
        if ((r==r0&&c==c0-1)||(r==r0&&c==c0+1)||   //通过鼠标点击时的坐标与空白块坐标比对，判断是否可交换
            (c==c0&&r==r0-1)||(c==c0&&r==r0+1))
        {
            playSound(clicksonud[map[r][c]], 0);
            map[r0][c0] = map[r][c];
            map[r][c] = ROW*COL -1;
        beginPaint();
            putImageScale(&img[map[r0][c0]], r0 * SIZE, c0 * SIZE, SIZE, SIZE);
            putImageScale(&img[map[r][c]], r * SIZE,c  * SIZE, SIZE, SIZE);
        endPaint();
            r0 = r;
            c0 = c;
        }
    }
    //判断拼图是否复原
    int count = 0;
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            if (map[i][j] == i + j * ROW)//将map数组中的值与初始值比较，从而判断
                count++;
    if (count == ROW * COL)
    {
        if (suc)
        {
            char str[50];
            playSound(winsound, 1);
            sprintf_s(str, 50, "拼图完成");
            beginPaint();
            setTextSize(40);
            paintText(WNDWIDTH - 180, 20, str);//绘制文字
            endPaint();
            suc = false;
        }
    }
}