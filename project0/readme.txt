正确编译后，在build目录下生成fd.img映像文件，
project0.bxrc为本次项目在Windows下的配置文件;
在rh9中亦要安装bochs，
VGABIOS-lgpl-latest等文件的路径一般情况下是在/usr/share/bochs,

本次项目在虚拟机的rh9、物理机的红旗6.0 SP2和Windows XP测试通过。

测试（在build目录下进行）：
Windows XP:确定正确安装了bochs后，双击project0.bxrc即可。
rh9:在命令行输入bochs,选择6,即可。

确定Final版本时间：09-04-03 night
作者：Late Lee(FightNow! Team)