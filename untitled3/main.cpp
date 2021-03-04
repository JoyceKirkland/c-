#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstdio>
#include <cstring>
//typedef struct LNode* Stack;

#define MAX 100

int pmaze[11][10]={1,1,1,1,1,1,1,1,1,1,
                   1,0,0,1,0,0,0,1,0,1,
                   1,0,0,1,0,0,0,1,0,1,
                   1,0,0,0,0,1,1,0,1,1,
                   1,0,1,1,1,0,0,1,0,1,
                   1,0,0,0,1,0,0,0,0,1,
                   1,0,1,0,0,0,1,0,1,1,
                   1,0,1,1,1,1,0,0,1,1,
                   1,1,1,0,0,0,1,0,1,1,
                   1,1,1,0,0,0,0,0,0,1,
                   1,1,1,1,1,1,1,1,1,1};


typedef int ElementType;


using namespace std;


struct point       //定义描述迷宫中当前位置的结构类型
{
         int x;          //x代表当前位置的行坐标
         int y;          //y代表当前位置的列坐标
         int direction;        //0:无效,1:下,2:右,3:上,4:左
};


struct LinkNode      //链表结点
{
      point data;
      LinkNode *next;
};


struct path_
{
    point data[10000];
    int length;		//路径长度
};

class Stack
{
            private:
    LinkNode *top;           //指向第一个结点的栈顶指针
//    point output[MAX];
    //int count;
            public:


Stack()          //构造函数，置空栈
{  top=NULL; }

void Push(point e)          //把元素x压入栈中
{
//    if(!IsEmpty())
    {
//            count++;
            LinkNode *P;
            P=new LinkNode;
            P->data=e;
            P->next=top;
            top=P;
    }
//    output[count].x=e.x;
//    output[count].y=e.y;
}
point Pop()                 //使栈顶元素出栈
{
    if(!IsEmpty())
    {
            point Temp;
            LinkNode *P;
            P=top;
            top=top->next;
            Temp=P->data;
            delete P;
            return Temp;
    }
}
point get_top()               //取出栈顶元素的值
{
    if(!IsEmpty())
    {
        return top->data;
    }
}
void Clear()                    //把栈清空
{
            top=NULL;
}
bool IsEmpty()        //判断栈是否为空，如果为空则返回，否则返回
{
            if(top==NULL)
            {
                return 1;
            }
            else
            {
                return 0;
            }
}


};

int move_x[4]={0,1,0,-1};
int move_y[4]={1,0,-1,0};
int count=0;	//记录当前为第几号迷宫路径
class stack_1
{
public:
    class stack;
    
};


int** CreatMaze(int &m,int &n)//创建迷宫,返回存取迷宫的二维指针
{
    int maze_rows=m+2;//行
    int maze_cols=n+2;
    int **pmaze;
//    int **cmaze;
    int a=0;
    pmaze=new int*[maze_rows];//申请指向行数+1的二级指针


    for(int i=0;i<maze_rows;i++)//申请每个二维指针的空间
    {
        pmaze[i]=new int[maze_cols];
    }
    cout<<"请输入迷宫："<<endl;
//    if(a==1)
    {
    for(int i=0;i<maze_rows;i++)
    {
        pmaze[i][0]=1;//左边第一列
        pmaze[i][maze_cols-1]=1;//右边第一列
    }
    for(int j=0;j<maze_cols;j++)
    {
        pmaze[0][j]=1;//上边第一行
        pmaze[maze_rows-1][j]=1;//下边最后一行
    }


    for(int i=1;i<maze_rows-1;i++)
    {
        for(int j=1;j<maze_cols-1;j++)
        {
                cin>>pmaze[i][j];       
         }
    }
    }
    return pmaze;
}

void CreatMaze_co(int **cmaze,int m,int n)//创建迷宫,返回存取迷宫的二维指针
{
//    int maze_rows=m+2;//行
//    int maze_cols=n+2;
    int **pmaze;
    pmaze=cmaze;
//    int **cmaze;
    int a=0;
//    pmaze=new int*[11];//申请指向行数+1的二级指针

    for(int i=1;i<m;i++)
    {
        for(int j=1;j<n;j++)
        {
            cout<<pmaze[i][j]<<'\t';
        }
        cout<<endl;
    }


//    int **pmaze=cmaze;

}



void print_path(Stack p,int m,int n,int mark,int **maze)        //输出路径
{
            cout<<endl;
            cout<<"(非递归)迷宫的路径为\n";
            cout<<"括号内的内容分别表示为(行坐标,列坐标,数字化方向)\n";
            Stack t;            //定义一个栈，按从入口到出口存取路径
            int a,b;
                    point poi;
                    LinkNode *temp;
                    temp=new LinkNode;         //申请空间
            temp->data=p.Pop();        //取栈p的顶点元素，即第一个位置
            t.Push(temp->data);  //第一个位置入栈t
            delete temp;         //释放空间
            while(!p.IsEmpty())    //栈p非空，则反复转移
            {
                temp=new LinkNode;
                temp->data=p.Pop();         //获取下一个位置   //得到行走方向
                a=t.get_top().x-temp->data.x;   //行坐标方向
                b=t.get_top().y-temp->data.y;   //列坐标方向
                if(b==1)//右
                {
                    temp->data.direction=1;
                }else if(a==1)//下
                {
                    temp->data.direction=2;
                }else if(b==-1)//左
                {
                    temp->data.direction=3;
                }else if(a==-1)//上
                {
                    temp->data.direction=4;
                }


                t.Push(temp->data);            //把新位置入栈
                delete temp;
        }
                    //输出路径，包括行坐标，列坐标，下一个位置方向
            while(!t.IsEmpty())         //栈非空，继续输出
            {
                 poi=t.Pop();
                 if(poi.direction==0)
                 {
                     cout<<'('<<poi.x<<','<<poi.y<<','<<poi.direction<<")"<<endl;  //输出行坐标，列坐标
                 }else
                 {
                     cout<<'('<<poi.x<<','<<poi.y<<','<<poi.direction<<")->";  //输出行坐标，列坐标
                 }
//                 for(int i=1;i<m+1;i++)
//                 {
//                     for(int j=1;j<n+1;j++)
//                     {
//                         pmaze[poi.x][poi.y]=-1;
////                         cout<<pmaze[i][j]<<'\t';
//                     }
////                     cout<<endl;
//                 }

            }
            if(mark==1)//手动
            {
                for(int i=1;i<m+1;i++)
                {
                    for(int j=1;j<n+1;j++)
                    {
    //                    pmaze[poi.x][poi.y]=-1;
//                        cout<<pmaze[i][j]<<'\t';
                        cout<<maze[i][j]<<'\t';

                    }
                    cout<<endl;
                }
            }
            if(mark==0)//自动
            {
                for(int i=1;i<m+1;i++)
                {
                    for(int j=1;j<n+1;j++)
                    {
    //                    pmaze[poi.x][poi.y]=-1;
                        cout<<pmaze[i][j]<<'\t';
                    }
                    cout<<endl;
                }

            }

}

bool Manual_non_recursive(int **maze,int a,int b,int mark)//非递归,手动输入            //到则返回true,否则返回false
{
    Stack channel,path_save;       //定义栈p存储路径,q存探索迷宫的过程
    point p1,p2;
    int x,y;
    p1.x=1;
    p1.y=1;
    channel.Push(p1);           //将入口位置入栈
    path_save.Push(p1);
    maze[1][1]=-1;          //标志入口位置已到达过
    while(!channel.IsEmpty())      //栈q非空，则反复探索
    {
        p2=channel.get_top();      //获取栈顶元素
        if(!(path_save.get_top().x==channel.get_top().x && path_save.get_top().y==channel.get_top().y))
        {
            path_save.Push(p2);               //如果有新位置入栈，则把上一个探索的位置存入栈p
        }

        for(int i=0;i<4;i++)   //探索当前位置的个相邻位置
        {
            x=p2.x+move_x[i];     //计算出新位置x位置值
            y=p2.y+move_y[i];      //计算出新位置y位置值
            if(maze[x][y]==0)         //判断新位置是否可达
            {
                p1.x=x;
                p1.y=y;
                maze[x][y]=-1;          //标志新位置已到达过
                channel.Push(p1);         //新位置入栈
            }
            if((x==(a))&&(y==(b)))    //成功到达出口
            {
                p1.x=a;
                p1.y=b;
                p1.direction=0;                
                path_save.Push(p1);       //把最后一个位置入栈
                print_path(path_save,a,b,mark,maze);//输出路径
                return 1;           //表示成功找到路径
            }
}
    if(path_save.get_top().x==channel.get_top().x&&path_save.get_top().y==channel.get_top().y)         //如果没有新位置入栈，则返回到上一个位置
    {
        path_save.Pop();
        channel.Pop();
    }
}
            return 0;           //表示查找失败，即迷宫无路经
}

bool Automatic_non_recursive(int a,int b,int m,int n,int mark)//非递归,自动
{
    Stack channel,path_save;       //定义栈p存储路径,q存探索迷宫的过程
    int **cmaze;
    point p1,p2;
    int x,y;
    p1.x=1;
    p1.y=1;
//    int **cmaze=pmaze[11][10];
    channel.Push(p1);           //将入口位置入栈
    path_save.Push(p1);
    pmaze[1][1]=-1;          //标志入口位置已到达过
    while(!channel.IsEmpty())      //栈q非空，则反复探索
    {
        p2=channel.get_top();      //获取栈顶元素
        if(!(path_save.get_top().x==channel.get_top().x && path_save.get_top().y==channel.get_top().y))
        {
            path_save.Push(p2);               //如果有新位置入栈，则把上一个探索的位置存入栈p
        }

        for(int i=0;i<4;i++)   //探索当前位置的个相邻位置
        {
            x=p2.x+move_x[i];     //计算出新位置x位置值
            y=p2.y+move_y[i];      //计算出新位置y位置值
            if(pmaze[x][y]==0)         //判断新位置是否可达
            {
                p1.x=x;
                p1.y=y;
                pmaze[x][y]=-1;          //标志新位置已到达过
                channel.Push(p1);         //新位置入栈
            }
            if((x==(a))&&(y==(b)))    //成功到达出口
            {
                p1.x=m;
                p1.y=n;
                p1.direction=0;
                path_save.Push(p1);       //把最后一个位置入栈
                print_path(path_save,m,n,mark,cmaze);//输出路径
                return 1;           //表示成功找到路径
            }
}
    if(path_save.get_top().x==channel.get_top().x&&path_save.get_top().y==channel.get_top().y)         //如果没有新位置入栈，则返回到上一个位置
    {
        path_save.Pop();
        channel.Pop();
    }
}
            return 0;           //表示查找失败，即迷宫无路经
}




bool Manual_Recursion(int x,int y,int a,int b,path_ path,int **pmaze,int m,int n)//递归，手动输入
{//起点，终点，存路线的数组，迷宫大小
//    CreatMaze_co(CreatMaze(m,n),m,n);
//    int count=0;	//记录当前为第几号迷宫路径
    {
        int x1,y1;

        if(x==a&&y==b)
        {
            //将终点坐标进入路径中
            path.data[path.length].x=x;
            path.data[path.length].y=y;
            path.length++;

            printf("迷宫路径 %d 如下：\n",++count);
            path.data[path.length-1].direction=0;
            for(int k=0;k<path.length;k++)
            {

                if(path.data[k].direction==0)
                {
                    printf("(%d,%d,%d)",path.data[k].x,path.data[k].y,path.data[k].direction);
                }
                else
                {
                    printf("(%d,%d,%d)->",path.data[k].x,path.data[k].y,path.data[k].direction);
                }
//                if((k+1)%5==0)
//                {	//每输出5个方块后换行
//                    printf("\n");
//                }
            }
            printf("\n");
            for(int i=1;i<m+1;i++)
            {
                for(int j=1;j<n+1;j++)
                {
                    pmaze[a][b]=-1;
                    cout<<pmaze[i][j]<<'\t';
                }
                cout<<endl;
            }
        }
        else{
            if(pmaze[x][y]==0){
                int di=1;	//用于四个方位移动的变量
                while(di<5){
                    //第一步：将(xi,yi)进入path路径中
                    path.data[path.length].x=x;
                    path.data[path.length].y=y;
                    //对四个方位寻找相邻方块

                    switch(di){
                        case 1:{x1=x,y1=y+1;path.data[path.length].direction=di;break;}
                        case 2:{x1=x+1,y1=y;path.data[path.length].direction=di;break;}
                        case 3:{x1=x,y1=y-1;path.data[path.length].direction=di;break;}
                        case 4:{x1=x-1,y1=y;path.data[path.length].direction=di;break;}
                    }

                    path.length++;
                    //第二步：将mg[xi][yi]=-1，避免来回走动
                    pmaze[x][y]=-1;

                    //第三步：递归调用迷宫函数求解小问题
                    Manual_Recursion(x1,y1,a,b,path,pmaze,m,n);

                    //第四步：回退path数组中的元素，并将回退元素mg[xi][yi]=0来寻找其他路径
                    path.length--;
                    pmaze[x][y]=0;

                    di++;
                }
            }
        }
    }
}

bool Automatic_Recursion(int x,int y,int a,int b,path_ path,int m,int n)//自动递归，即给定迷宫输入automatic_recursion
{

//    int count=0;	//记录当前为第几号迷宫路径
    {
        int x1,y1;

        if(x==a&&y==b)
        {
            //将终点坐标进入路径中
            path.data[path.length].x=x;
            path.data[path.length].y=y;
            path.length++;
            pmaze[m+1][n+1]=-1;
            printf("迷宫路径 %d 如下：\n",++count);
            path.data[path.length].direction=0;
            for(int k=0;k<path.length;k++)
            {

                if(path.data[k].direction==0)
                {
                    printf("(%d,%d,%d)",path.data[k].x,path.data[k].y,path.data[k].direction);
                }
                else
                {
                    printf("(%d,%d,%d)->",path.data[k].x,path.data[k].y,path.data[k].direction);
                }
//                cout<<"???"<<endl;
//                if((k+1)%5==0)
//                {	//每输出5个方块后换行
//                    printf("\n");
//                }
            }
            cout<<endl;
            for(int i=1;i<m+1;i++)
            {
                for(int j=1;j<n+1;j++)
                {
                    pmaze[m][n]=-1;
                    cout<<pmaze[i][j]<<'\t';
                }
                cout<<endl;
            }

        }
        else{
            if(pmaze[x][y]==0){
                int di=1;	//用于四个方位移动的变量
                while(di<5){
                    //第一步：将(xi,yi)进入path路径中
                    path.data[path.length].x=x;
                    path.data[path.length].y=y;

                    //对四个方位寻找相邻方块
                    switch(di){
                    case 1:{x1=x,y1=y+1;path.data[path.length].direction=di;break;}
                    case 2:{x1=x+1,y1=y;path.data[path.length].direction=di;break;}
                    case 3:{x1=x,y1=y-1;path.data[path.length].direction=di;break;}
                    case 4:{x1=x-1,y1=y;path.data[path.length].direction=di;break;}
                    }
                    path.length++;
                    //第二步：将mg[xi][yi]=-1，避免来回走动
                    pmaze[x][y]=-1;

                    //第三步：递归调用迷宫函数求解小问题
                    Automatic_Recursion(x1,y1,a,b,path,m,n);

                    //第四步：回退path数组中的元素，并将回退元素mg[xi][yi]=0来寻找其他路径
                    path.length--;
                    pmaze[x][y]=0;

                    di++;
                }
            }
        }
    }
}



int main()
{
    Stack S;
    path_ path;
    path.length=0;

            int flag=1;
            int tag=0;
            int mark=0;
            while(flag)
            {
                int **maze;        //定义二维指针存取迷宫
                int **maze1;
                int m,n;//9，8//长短
                int a,b;//9，8//终点
                cin>>tag;
                while(tag==0)//给定迷宫
                {
                    printf("1非递归方法，2递归方法。");
                    cin>>mark;
                    if(mark==1)
                    {
                        if(Automatic_non_recursive(9,8,9,8,mark-1))//非递归
//                            if(Automatic_Recursion(1,1,9,8,path,9,8))//递归
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
                    if(mark==2)
                    {
                        if(Automatic_Recursion(1,1,9,8,path,9,8))//递归
//                            if(Automatic_non_recursive(9,8,9,8))//非递归
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
//                    break;
//                    cout<<"是否继续探索迷宫？(继续1 ,退出0 )\n";
//                    cin>>flag;
                }
                while(tag==1)//手动给迷宫
                {
                    cout<<"请输入迷宫的行数"<<endl;
                    cin>>m;

                    cout<<"请输入迷宫的列数"<<endl;
                    cin>>n;

                    cout<<"请输入终点坐标x"<<endl;
                    cin>>a;
                    cout<<"请输入终点坐标y"<<endl;
                    cin>>b;
                    maze=CreatMaze(m,n);  //调用CreatMaze(int &m,int &n)函数，得到迷宫
                    printf("1非递归方法，2递归方法。");
                    cin>>mark;
                    if(mark==1)
                    {
                        if(Manual_non_recursive(maze,a,b,mark))//非递归，手动输入
                        {
                            cout<<"迷宫路径探索成功!\n";
                            return 0;
                        }
                        else
                        {
                            cout<<"路径不存在!\n";
                            return 0;
                        }
                    }
                    if(mark==2)
                    {
                        if(Manual_Recursion(1,1,3,4,path,maze,m,n))//递归，手动输入
                        {
                            cout<<"迷宫路径探索成功!\n";
                            return 0;
                        }
                        else
                        {
                            cout<<"路径不存在!\n";
                            return 0;
                        }
                    }
//                      cout<<"是否继续探索迷宫？(继续1 ,退出0 )\n";
//                      cin>>tag;
              }

    }
}
