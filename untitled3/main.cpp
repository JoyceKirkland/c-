#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstdio>
#include <cstring>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
/* 华南理工大学广州学院2020-2021学年度第2学期数据结构大作业
 * 题目：迷宫问题
 * 专业班级：计算机科学与技术1班
 * 年级：2019级
 * 姓名：张阳
 * 学号：201910089008
 */


/*————测试数据定义————*/
//因为起点坐标从（1，1）开始，数组下标从零开始，因此在迷宫外围增加一圈“障碍”。
int pmaze[11][10] = { 1,1,1,1,1,1,1,1,1,1,
                      1,0,0,1,0,0,0,1,0,1,
                      1,0,0,1,0,0,0,1,0,1,
                      1,0,0,0,0,1,1,0,1,1,
                      1,0,1,1,1,0,0,1,0,1,
                      1,0,0,0,1,0,0,0,0,1,
                      1,0,1,0,0,0,1,0,1,1,
                      1,0,1,1,1,1,0,0,1,1,
                      1,1,1,0,0,0,1,0,1,1,
                      1,1,1,0,0,0,0,0,0,1,
                      1,1,1,1,1,1,1,1,1,1 };

/*————链栈定义————*/
struct point              //定义描述迷宫中当前位置的结构类型
{
    int x;                //x代表当前位置的行坐标
    int y;                //y代表当前位置的列坐标
    int direction;        //0:无效,1:下,2:右,3:上,4:左
};


struct LinkNode         //链表结点
{
    point data;
    LinkNode* next;
};


struct path_routes      //存放通路的结构体
{
    point route_point[1000];//定义存放通路路径的数组，用于多通道输出
    int len;		        //通路路径长度
};

class Stack
{
private:
    LinkNode* top;               //指向第一个结点的栈顶指针
public:

    Stack()                      //构造函数，置空栈
    {
        top = NULL;
    }

    void Push(point e)          //把元素x压入栈中
    {
        {
            LinkNode* P;
            P = new LinkNode;
            P->data = e;
            P->next = top;
            top = P;
        }
    }
    point Pop()                 //使栈顶元素出栈
    {
        if (!IsEmpty())
        {
            point Temp;
            LinkNode* P;
            P = top;
            top = top->next;
            Temp = P->data;
            delete P;
            return Temp;
        }
    }
    point get_top()               //取出栈顶元素的值
    {
        if (!IsEmpty())
        {
            return top->data;
        }
    }
    void Clear()                    //把栈清空
    {
        top = NULL;
    }
    bool IsEmpty()                  //判断栈是否为空，如果为空则返回1，否则返回0
    {
        if (top == NULL)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
};

int move_x[4] = { 0,1,0,-1 };//定义坐标的移动数组
int move_y[4] = { 1,0,-1,0 };
int sum = 0;	             //记录当前为第几号迷宫路径

int** Input_Maze(int& m, int& n)//创建迷宫,返回存取迷宫的二维指针
{
    int maze_rows = m + 2;//行
    int maze_cols = n + 2;//列
    int** pmaze;
    int a = 0;
    pmaze = new int* [maze_rows];//申请指向行数+1的二级指针


    for (int i = 0; i < maze_rows; i++)//申请每个二维指针的空间
    {
        pmaze[i] = new int[maze_cols];
    }
    printf("请输入迷宫：\n");
    
    for (int i = 0; i < maze_rows; i++)//迷宫外加一圈“围墙”，即最外圈置1
    {
        pmaze[i][0] = 1;//左边第一列
        pmaze[i][maze_cols - 1] = 1;//右边第一列
    }
    for (int j = 0; j < maze_cols; j++)
    {
        pmaze[0][j] = 1;//上边第一行
        pmaze[maze_rows - 1][j] = 1;//下边最后一行
    }

    for (int i = 1; i < maze_rows - 1; i++)//输入迷宫内容
    {
        for (int j = 1; j < maze_cols - 1; j++)
        {
                scanf_s("%d", &pmaze[i][j]);
        }
    }
    return pmaze;
}

/*————输出寻找到的迷宫路径————*/
void print_path(Stack s, int m, int n, int mark, int** maze)
{
    printf("\n");
    printf("(非递归)迷宫的路径为\n");
    printf("括号内的内容分别表示为(横坐标,纵坐标,数字化方向)\n");
    
    Stack t;            //定义一个栈，用于从入口到出口存取路径
    int a, b;           //定义临时变量判断行进方向
    point poi;          //定义临时坐标变量输出
    LinkNode* temp;     //定义临时节点用于获取栈中的元素，用于判断行进方向
    temp = new LinkNode;         //申请空间
    temp->data = s.Pop();        //取栈p的顶点元素，即第一个位置
    t.Push(temp->data);  //第一个位置入栈t
    delete temp;         //释放空间
    while (!s.IsEmpty())    //栈p非空
    {
        temp = new LinkNode;
        temp->data = s.Pop();         //获取下一个位置
        a = t.get_top().x - temp->data.x;   //列坐标方向
        b = t.get_top().y - temp->data.y;   //行坐标方向

        //得到行走方向
        if (b == 1)//右
        {
            temp->data.direction = 1;
        }
        else if (a == 1)//下
        {
            temp->data.direction = 2;
        }
        else if (b == -1)//左
        {
            temp->data.direction = 3;
        }
        else if (a == -1)//上
        {
            temp->data.direction = 4;
        }

        t.Push(temp->data);            //把新位置入栈
        delete temp;    
    }

    //输出路径，包括具体坐标，去往下一个位置的行进方向
    while (!t.IsEmpty())         //栈非空，继续输出
    {
        poi = t.Pop();
        if (poi.direction == 0)//到达终点
        {
            printf("(%d,%d,%d)\n",poi.y,poi.x,poi.direction);
        }
        else
        {
            printf("(%d,%d,%d)->", poi.y, poi.x, poi.direction);
        }

    }
    if (mark == 1)//手动输入的迷宫
    {
        for (int i = 1; i < m + 1; i++)
        {
            for (int j = 1; j < n + 1; j++)
            {
                printf("%d\t", maze[i][j]);
            }
            printf("\n");
        }
    }
    if (mark == 0)//给定数据的迷宫
    {
        for (int i = 1; i < m + 1; i++)
        {
            for (int j = 1; j < n + 1; j++)
            {
                printf("%d\t", pmaze[i][j]);
            }
            printf("\n");
        }
    }
}
/*————非递归方法寻找迷宫通路————*/
bool Manual_non_recursive(int** maze, int a, int b, int mark)//手动输入
{
    Stack channel, path_save;                  //定义栈path_save存储路径,channel存探索迷宫的过程
    point p1, p2;                              //定义临时变量
    int x, y;                       
    p1.x = 1;                                  //起点为（1，1）
    p1.y = 1;
    channel.Push(p1);                          //将入口位置入栈
    path_save.Push(p1);
    maze[1][1] = -1;                           //标志入口位置已到达过

    while (!channel.IsEmpty())                 //栈channel非空，反复探索
    {
        p2 = channel.get_top();                //获取栈顶元素
        if (!(path_save.get_top().x == channel.get_top().x && path_save.get_top().y == channel.get_top().y))
        {
            path_save.Push(p2);               //如果有新位置入栈，则把上一个探索的位置存入栈path_save
        }
        if (maze[a][b] == 1)                  //如果终点不可达，代表无通路，直接返回零。
        {
            return 0;
        }
        for (int i = 0; i < 4; i++)           //探索当前位置的四个相邻位置
        {
            x = p2.x + move_x[i];             //计算出新位置
            y = p2.y + move_y[i];             
            if (maze[x][y] == 0)              //判断新位置是否可达
            {
                p1.x = x;
                p1.y = y;
                maze[x][y] = -1;             //标志新位置已到达过
                channel.Push(p1);            //新位置入栈
            }
            if (maze[a][b] == 1)             //如果终点为不可达，说明
            {
                return 0;
            }
            if ((x == (a)) && (y == (b)))    //成功到达出口
            {
                p1.x = a;
                p1.y = b;
                p1.direction = 0;
                path_save.Push(p1);         //把最后一个位置入栈
                print_path(path_save, a, b, mark, maze);//输出路径
                return 1;                  //表示成功找到路径
            }
        }
        //如果没有新位置入栈，则返回到上一个位置
        if (path_save.get_top().x == channel.get_top().x && path_save.get_top().y == channel.get_top().y)         
        {
            path_save.Pop();
            channel.Pop();
        }
    }
    return 0;           //表示查找失败，即迷宫无路经
}

bool Automatic_non_recursive(int a, int b, int m, int n, int mark)//给定数据
{
    Stack channel, path_save;               //定义栈path_save存储路径,channel存探索迷宫的过程
    int** cmaze=0;                          //初始化一个二级指针，仅用于方便调用输出路径函数
    point p1, p2;                           //定义临时变量
    int x, y;   
    p1.x = 1;                               //起点为（1，1）
    p1.y = 1;
    channel.Push(p1);                       //将入口位置入栈
    path_save.Push(p1);
    pmaze[1][1] = -1;                       //标志入口位置已到达过
    while (!channel.IsEmpty())              //栈path_save非空，则反复探索
    {
        p2 = channel.get_top();             //获取栈顶元素
        if (!(path_save.get_top().x == channel.get_top().x && path_save.get_top().y == channel.get_top().y))
        {
            path_save.Push(p2);             //如果有新位置入栈，则把上一个探索的位置存入栈channel
        }
        if (pmaze[a][b] == 1)               //如果终点不可达，代表无通路，直接返回零。
        {
            return 0;
        }
        for (int i = 0; i < 4; i++)         //探索当前位置的个相邻位置
        {
            x = p2.x + move_x[i];           //计算出新位置
            y = p2.y + move_y[i];           
            if (pmaze[x][y] == 0)           //判断新位置是否可达
            {
                p1.x = x;
                p1.y = y;
                pmaze[x][y] = -1;          //标志新位置已到达过
                channel.Push(p1);          //新位置入栈
            }
            if ((x == (a)) && (y == (b)))  //成功到达出口
            {
                p1.x = m;
                p1.y = n;
                p1.direction = 0;
                path_save.Push(p1);       //把最后一个位置入栈
                print_path(path_save, m, n, mark, cmaze);//输出路径
                return 1;                 //表示成功找到路径
            }
        }

        //如果没有新位置入栈，则返回到上一个位置
        if (path_save.get_top().x == channel.get_top().x && path_save.get_top().y == channel.get_top().y)         
        {
            path_save.Pop();
            channel.Pop();
        }
    }
    return 0;                           //表示查找失败，即迷宫无路经
}


/*————递归方法寻找迷宫通路————*/
bool Manual_Recursion(int x, int y, int a, int b, path_routes path, int** maze, int m, int n)//手动输入迷宫
{//起点，终点，存路线的数组，迷宫大小     
    
        int x1, y1;                     //定义临时变量，用于行进到下一步      
        if (maze[a][b] == 1)            //如果终点不可达，代表无通路，直接返回零。
        {
            return 0;
        }
        if (x == a && y == b)           //当递归后的坐标与终点坐标相同时，即找到了迷宫出口
        {
            //将终点坐标进入路径数组中
            path.route_point[path.len].x = x;
            path.route_point[path.len].y = y;
            path.len++;                 //每输入进一个坐标，通路长+1
            printf("第%d 条通路：\n", ++sum);
            path.route_point[path.len - 1].direction = 0;//让终点坐标置为0，即到达终点
            for (int k = 0; k < path.len; k++)//输出数组中的通路
            {

                if (path.route_point[k].direction == 0)//输出到达终点
                {
                    printf("(%d,%d,%d)", path.route_point[k].y, path.route_point[k].x, path.route_point[k].direction);
                }
                else
                {
                    printf("(%d,%d,%d)->", path.route_point[k].y, path.route_point[k].x, path.route_point[k].direction);
                }
                
            }
            printf("\n");
            for (int i = 1; i < m + 1; i++)           //输出含有通路的迷宫地图
            {
                for (int j = 1; j < n + 1; j++)
                {
                    maze[a][b] = -1;                 //将终点坐标也置为-1
                    printf("%d\t", maze[i][j]);
                }
                printf("\n");
            }
            return 1;                                 //成功找到通路，返回1
        }
        else 
        {
            if (maze[x][y] == 0)                     //当新位置可达
            {
                for(int dir=1;dir<5;dir++)
                {
                    //将(x,y)进入路径数组中
                    path.route_point[path.len].x = x;
                    path.route_point[path.len].y = y;
                    //对四个方位寻找相邻通路
                    switch (dir) 
                    {
                        case 1: {x1 = x, y1 = y + 1; path.route_point[path.len].direction = dir; break; }//右
                        case 2: {x1 = x + 1, y1 = y; path.route_point[path.len].direction = dir; break; }//下
                        case 3: {x1 = x, y1 = y - 1; path.route_point[path.len].direction = dir; break; }//左
                        case 4: {x1 = x - 1, y1 = y; path.route_point[path.len].direction = dir; break; }//上
                    }
                    path.len++;//因为找到了通路，所以通路长度+1
                    //将已经通过的坐标置为-1
                    maze[x][y] = -1;

                    //递归
                    Manual_Recursion(x1, y1, a, b, path, maze, m, n);

                    //回退路径数组中的元素，用于寻找其他路径，即将原本置为不可达的路径重新变成可达坐标
                    path.len--;//因为回退，因此存储通路数组的长度-1
                    maze[x][y] = 0;
                }
            }
        }
        if (sum == 0)//表示查找失败，即迷宫无路经
        {
            return 0;
        }
}

bool Automatic_Recursion(int x, int y, int a, int b, path_routes path, int m, int n)//自动递归，即给定迷宫输入automatic_recursion
{
    
        int x1, y1;                           //定义临时变量，用于行进到下一步   
        if (pmaze[a][b] == 1)                 //如果终点不可达，代表无通路，直接返回零。
        {
            return 0;
        }
        if (x == a && y == b)                 //当递归后的坐标与终点坐标相同时，即找到了迷宫出口
        {
            //将终点坐标进入路径数组中
            path.route_point[path.len].x = x;
            path.route_point[path.len].y = y;
            path.len++;                       //每输入进一个坐标，通路长+1
            printf("第%d 条通路：\n", ++sum); //输出这是找到的第几条通路
            path.route_point[path.len-1].direction = 0;//让终点坐标方向置为0，即到达终点
            for (int k = 0; k < path.len; k++)//输出数组中的通路
            {

                if (path.route_point[k].direction == 0)//输出到达终点
                {
                    printf("(%d,%d,%d)", path.route_point[k].y, path.route_point[k].x, path.route_point[k].direction);
                }
                else
                {
                    printf("(%d,%d,%d)->", path.route_point[k].y, path.route_point[k].x, path.route_point[k].direction);
                }
            }
            cout << endl;
            for (int i = 1; i < m + 1; i++)         //输出含有通路的迷宫地图
            {
                for (int j = 1; j < n + 1; j++)
                {
                    pmaze[m][n] = -1;               //将终点坐标也置为-1
                    printf("%d\t", pmaze[i][j]);
                }
                printf("\n");

            }
            return 1;                               //成功找到通路，返回1
        }
        else {
            if (pmaze[x][y] == 0)                 //当新位置可达
            {
                for(int dir=1;dir<5;dir++)
                {
                    //将(x,y)进入路径数组中
                    path.route_point[path.len].x = x;
                    path.route_point[path.len].y = y;

                    //对四个方位寻找相邻通路
                    switch (dir) 
                    {
                    case 1: {x1 = x, y1 = y + 1; path.route_point[path.len].direction = dir; break; }//右
                    case 2: {x1 = x + 1, y1 = y; path.route_point[path.len].direction = dir; break; }//下
                    case 3: {x1 = x, y1 = y - 1; path.route_point[path.len].direction = dir; break; }//左
                    case 4: {x1 = x - 1, y1 = y; path.route_point[path.len].direction = dir; break; }//上
                    }
                    path.len++;//因为找到了通路,所以通路长度+1
                    //将已经通过的坐标置为-1
                    pmaze[x][y] = -1;

                    //递归
                    Automatic_Recursion(x1, y1, a, b, path, m, n);

                    //回退路径数组中的元素，用于寻找其他路径，即将原本置为不可达的路径重新变成可达坐标
                    path.len--;//因为回退，因此存储通路数组的长度-1
                    pmaze[x][y] = 0;
                }
            }
        }
        if (sum == 0)//表示查找失败，即迷宫无路经
        {
            return 0;
        }
    
}


/*————主函数————*/
int main()
{
    Stack S;//初始化一个栈
    path_routes path;//初始化一个放多通路的结构体
    path.len = 0;//初始化通路长度为0

    int tag = 0;//选择模式
    int mark = 0;//选择方法
    while (1)
    {
        int** maze;        //定义二维指针存取迷宫
        int m, n;//长短
        int a, b;//终点
        printf("请选择:输入0输出给定迷宫的通路，输入1自定义迷宫求解。\n");
        cin >> tag;
        while (tag == 0)//给定迷宫
        {
            printf("1非递归方法，2递归方法。");
            cin >> mark;
            if (mark == 1)
            {
                if (Automatic_non_recursive(9, 8, 9, 8, mark - 1))//非递归
                {
                    printf("成功找到路径！\n");
                    return 0;
                }
                else
                {
                    printf("该迷宫不存在通路！\n");
                    return 0;
                }
            }
            if (mark == 2)
            {
                if (Automatic_Recursion(1, 1, 9, 8, path, 9, 8))//递归
                {
                    printf("成功找到路径！\n");
                    return 0;
                }
                else
                {
                    printf("该迷宫不存在通路！\n");
                    return 0;
                }
            }
        }
        while (tag == 1)//手动给迷宫
        {
            printf("请输入迷宫的行数\n");
            scanf_s("%d", &m);

            printf("请输入迷宫的列数\n");
            scanf_s("%d", &n);

            printf("请输入终点所在行数(y)\n");
            scanf_s("%d", &a);

            printf("请输入终点所在列数(x)\n");
            scanf_s("%d", &b);

            maze = Input_Maze(m, n);  //调用Input_Maze函数，得到迷宫
            printf("1非递归方法，2递归方法。");
            cin >> mark;
            if (mark == 1)
            {
                if (Manual_non_recursive(maze, a, b, mark))//非递归，手动输入
                {
                    cout << "迷宫路径探索成功!\n";
                    return 0;
                }
                else
                {
                    cout << "路径不存在!\n";
                    return 0;
                }
            }
            if (mark == 2)
            {
                if (Manual_Recursion(1, 1, a, b, path, maze, m, n))//递归，手动输入
                {
                    cout << "迷宫路径探索成功!\n";
                    return 0;
                }
                else
                {
                    cout << "路径不存在!\n";
                    return 0;
                }
            }
        }

    }
}

