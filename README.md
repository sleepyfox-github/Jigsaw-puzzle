# Jigsaw-puzzle
拼图游戏，大一C语言结课作业，依赖于acllib库实现，仅支持Windows环境下运行。

#### 项目描述

滑块拼图是一款策略类游戏，把一幅图案分为相等的若干正方型小方块，取走其中一块留出空位，利用多余的空格滑动其他小方块，打乱图案形成拼图。复位时都不能取下任何小方块，利用缺少的空位滑动图案中的小方块使其复原。

程序运行后先随机打乱，然后利用鼠标点击将拼图复原。鼠标只能分别控制与空格相邻的上下左右的滑块往空格位移动，判断图片复原则显示拼图完成

#### 算法分析与概要设计

![image-20201024232101190](https://gitee.com/wanli-0ziyuan/gitee-graph-bed/raw/master/img/20201024232101.png)

![image-20201024232328779](https://gitee.com/wanli-0ziyuan/gitee-graph-bed/raw/master/img/20201024232328.png)

#### 运行测试

1.程序成功运行，拼图已打乱，并已加载绘制，原图片绘制在窗口右侧。

![image-20201024233014795](https://gitee.com/wanli-0ziyuan/gitee-graph-bed/raw/master/img/20201024233014.png)

2.鼠标左键点击控制与空格相邻的上下左右的滑块往空格位移动，移动时伴有钢琴音效，不同图片音效不同；点击其他区域无响应

![image-20201024233140696](https://gitee.com/wanli-0ziyuan/gitee-graph-bed/raw/master/img/20201024233140.png)

3. 拼图复原，窗口右上角显示拼图完成，并播放一段音乐

![image-20201024233251476](https://gitee.com/wanli-0ziyuan/gitee-graph-bed/raw/master/img/20201024233251.png)