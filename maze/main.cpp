#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstdio>
#include <cstring>
//typedef struct LNode* Stack;
typedef int ElementType;


using namespace std;


/*可以写进说明书的bug：因为不能越过第一个数组元素赋值，但是又要保证从（1，1）开始，所以在输入数据之前将数组外围（即
 * 第零行和第零列置1，所以创建迷宫时，二维数组的大小=输入迷宫二维数组大小的行列各+2）
 * 1-右，2-下，3-左，4-上
 * 递归和非递归两个都要写,所以上面的迷宫处理要变成+2，才能保证递归的时候四个方向都能检查到
 * 这个思考的过程也可以写上去,一开始写了行列各+1
 * 双栈操作，只用结构体发现无法实现双栈操作（会出现另一个栈不能初始化的情况）
 * 原本打算采用两个栈组成一个队列的方式实现双栈操作，但是后来发现只需要把栈定义为类的形式会更简洁。
 * bug:栈中元素，即找到的点>4时会出错。
*/


struct point//在迷宫中当前所在位置
{
    int x;//行下标
    int y;//列下标
    int direction;//方向
};
int move_x[4]={0,1,0,-1};
int move_y[4]={1,0,-1,0};


class LNode //堆栈链表节点//不改成类下面没法用
{
    friend class Stack;
public:
    LNode *Next;
    point po;
};


class Stack
{

private:
    LNode *top;//指向第一个结点的栈顶指针
public:
    Stack() //构造函数，初始化一个空栈
    {
        top==NULL;
    }
    LNode get_top()
    {
        return *top;
    }
    bool IsEmpty() //栈空返回true
    {
        if(top == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }


    void Push(point x)//进栈
    {
        LNode *temp = new LNode;	//申请一个节点，加到头结点的后面
//        temp->Next = S->Next;
        temp->po = x;
        temp->Next = top;
        top=temp;
    }


    point Pop() //将栈顶元素弹出
    {
        if(IsEmpty())
        {
            printf("堆栈为空,出栈失败\n");
            //return NULL;
        }
        else
        {
            LNode *temp;
            temp = top;
            top = top->Next;
            point x;
            x = temp->po;
            delete temp;
            return x;

//            LNode *temp;
//            temp=top->Next;
//            point x;
//            x=temp->po;
//            delete temp;
//            return x;
        }
    }


    point Get_top()
    {
        if(IsEmpty())
        {
            printf("堆栈为空,无栈顶元素\n");
    //        return NULL;
        }
        else
        {
    //        Stack temp;
    //        temp=S->Next;
    //        ElementType x;
    //        x=temp;
            return top->po;
        }
    }
    void clear()
    {
        top=NULL;
    }
    void test()
    {
        cout<<"????????"<<endl;
    }
};




int** input_maze(int &m,int &n)//创建迷宫
{
    int maze_rows=m+2;//行
    int maze_cols=n+2;
    int **pmaze;
    pmaze=new int*[maze_rows];//申请指向行数+1的二级指针


    for(int i=0;i<maze_rows;i++)//申请每个二维指针的空间
    {
        pmaze[i]=new int[maze_cols];
    }
    cout<<"请输入迷宫："<<endl;
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




//    for(int i=0;i<maze_rows;i++)//输出置1后的整个数组，调试用
//    {
//        for(int j=0;j<maze_cols;j++)
//        {
//            cout<<pmaze[i][j]<<'\t';
//        }
//        cout<<endl;
//    }
    return pmaze;
}


void print_path(Stack p)
{
    Stack t;
    int a,b;
    point poi;
    LNode *temp=new LNode;
    LNode *k=new LNode;
    temp->po=p.Pop();//取存储栈的栈顶元素
//    cout<<???<<endl;


    t.Push(temp->po);//第一个顶点入栈
    delete temp;
//    cout<<???<<endl;
    while (!p.IsEmpty())
    {
//        if(k->Next==NULL)
//        {
//            break;
//        }
        temp=new LNode;
        temp->po=p.Pop();//获取下一个位置
//        k->point=p.Get_top();
//        cout<<"temp->point:"<<temp->po.x<<temp->po.y<<endl;
//        cout<<"p.Get_top():"<<p.Get_top().x<<t.Get_top().y<<endl;


        a=t.Get_top().x-temp->po.x;
        b=t.Get_top().y-temp->po.y;
//        cout<<???<<endl;
        if(b==1)
        {
            temp->po.direction=1;//右
        }
        else if(a==1)
        {
            temp->po.direction=2;//下
        }
        else if(b==-1)
        {
            temp->po.direction=3;//左
        }
        else if(a==-1)
        {
            temp->po.direction=4;//上
        }
        t.Push(temp->po);//新位置入栈
        delete temp;
//        if(p.IsEmpty())
//        {
//            cout<<???<<endl;
//        }
//        cout<<"direction:"<<temp->po.direction<<endl;


//        cout<<???<<endl;
    }


//    cout<<point:<<t.Get_top().x<<t.Get_top().y<<endl;
//    cout<<"???"<<endl;


    while (!t.IsEmpty())
    {
        poi=t.Pop();
//        cout<<poi.direction<<poi.direction<<endl;

        cout<<'('<<poi.x<<','<<poi.y<<','<<poi.direction<<")";  //输出行坐标，列坐标

//        switch (poi.direction)
//        {


//        case 1:printf("(%d,%d,%d)->",poi.x,poi.y,1);
////            break;//右
//        case 2:printf("(%d,%d,%d)->",poi.x,poi.y,2);
////            break;//下
//        case 3:printf("(%d,%d,%d)->",poi.x,poi.y,3);
////            break;//左
//        case 4:printf("(%d,%d,%d)->",poi.x,poi.y,4);
////            break;//上
//        case 0:printf("(%d,%d,%d)已到达出口\n",poi.x,poi.y,0);
////            break;//


//        }
    }


}


void print_path1(Stack p)
{
    Stack t;
    int a,b;
    point poi;
    LNode *temp=new LNode;
    LNode *k=new LNode;
    temp->po=p.Pop();//取存储栈的栈顶元素
//    cout<<???<<endl;


    t.Push(temp->po);//第一个顶点入栈
    delete temp;
//    cout<<???<<endl;
    while (!p.IsEmpty())
    {
        if(k->Next==NULL)
        {
            break;
        }
        temp=new LNode;
        temp->po=p.Pop();//获取下一个位置
        k->po=p.Get_top();
//        cout<<temp->point:<<temp->point.x<<temp->point.y<<endl;
//        cout<<t.Get_top():<<t.Get_top().x<<t.Get_top().y<<endl;


        a=t.Get_top().x-temp->po.x;
        b=t.Get_top().y-temp->po.y;
//        cout<<???<<endl;
        if(b==1)
        {
            temp->po.direction=1;//右
        }
        else if(a==1)
        {
            temp->po.direction=2;//下
        }
        else if(b==-1)
        {
            temp->po.direction=3;//左
        }
        else if(a==-1)
        {
            temp->po.direction=4;//上
        }
//        p.Push(temp->point);//新位置入栈
        delete temp;
//        if(p.IsEmpty())
//        {
//            cout<<???<<endl;
//        }
//        cout<<point:<<t.Get_top().x<<t.Get_top().y<<endl;


//        cout<<???<<endl;
    }


//    cout<<point:<<t.Get_top().x<<t.Get_top().y<<endl;
//    cout<<???<<endl;


    while (!t.IsEmpty())
    {
        poi=p.Pop();
//        cout<<poi.direction<<poi.direction<<endl;


        switch (poi.direction)
        {
        case 0:printf("(%d,%d,%d)已到达出口\n",poi.x,poi.y,0);break;//
        case 1:printf("(%d,%d,%d)->",poi.x,poi.y,1);break;//右
        case 2:printf("(%d,%d,%d)->",poi.x,poi.y,2);break;//下
        case 3:printf("(%d,%d,%d)->",poi.x,poi.y,3);break;//左
        case 4:printf("(%d,%d,%d)->",poi.x,poi.y,4);break;//上


        }
    }


}


bool find_maze_route1(int **maze,int m,int n)//非递归，寻找通路
{
    Stack stored_procedure;//用于探索迷宫探索路程的栈
    Stack path_save;//用于存储路径的栈
    point p1,p2;
    int x,y;
    p1.x=1;
    p1.y=1;
    stored_procedure.Push(p1);//入口位置入栈
    path_save.Push(p1);//
    maze[1][1]=-1;//将入口位置状态标记为已到达过


    while (!stored_procedure.IsEmpty())
    {
        p2=stored_procedure.Get_top();//获取栈顶元素
        if(!(stored_procedure.Get_top().x==
             path_save.Get_top().x)&&
             stored_procedure.Get_top().y==
             path_save.Get_top().y)//若有新位置入栈，则把上一个探索的位置存入存储路程的栈
        {
           path_save.Push(p2);
        }
        for(int i=0;i<4;i++)
        {
            x=p2.x+move_x[i];//x新位置
            y=p2.y+move_y[i];//y新位置
            if(maze[x][y]==0)//判断是否可达
            {
                p1.x=x;
                p1.y=y;
                maze[x][y]=-1;//新位置已经到达过
                stored_procedure.Push(p1);//新位置保存进寻找通路的栈
            }
            if((x==m)&&(y==n))//到达出口
            {
                p1.x=m;
                p1.y=n;
                p1.direction=0;
                path_save.Push(p1);//最后一个位置入栈


                printf("成功找到通路\n");
//                cout<<point:<<path_save.Get_top().x<<path_save.Get_top().y<<endl;
                LNode *temp = new LNode;


//                cout<<"??"<<endl;
//                while (temp!=NULL)
//                {
////                    temp = new LNode;
////                    temp->point=path_save.Get_top();
//                    temp->point=path_save.Pop();
//        //            temp=temp->Next=temp;
//                    cout<<"point:"<<temp->point.x<<","<<temp->point.y<<endl;
////                    cout<<point:<<path_save.Get_top().x<<,<<path_save.Get_top().y<<endl;


//                    temp->Next=temp;
//                    cout<<"point:"<<temp->Next->point.x<<","<<temp->Next->point.y<<endl;

//                }


                print_path(path_save);
                return true;//表示成功找到路径
            }
        }


        if((stored_procedure.Get_top().x==
             path_save.Get_top().x)&&
             stored_procedure.Get_top().y==
             path_save.Get_top().y)//若没有新位置入栈，则返回到上一个位置
        {
            stored_procedure.Pop();
            path_save.Pop();
        }
    }


    return 0;
}


bool find_maze_route2(int **maze,int x,int y,int m,int n)//非递归，寻找通路
{
    int i;
//    con++;
    Stack stored_procedure;//用于存储迷宫探索路程的栈
    Stack path_save;//用于存储路径的栈
    point p1;
    p1.x=x;
    p1.y=y;
    stored_procedure.Push(p1);//入口位置入栈
    path_save.Push(p1);//


    maze[x][y]=-1;
    if(x==m&&y==n)
    {
        printf("递归成功找到通路\n");
        return true;//是否到达出口
    }
    if(maze[x][y+1]==0)//向右探索
    {
        p1.x=x;
        p1.y=y+1;
        maze[x][y+1]=-1;//新位置已经到达过
        path_save.Push(p1);//新位置保存进寻找通路的栈


        find_maze_route2(maze,x,y+1,m,n);
    }
    if(maze[x+1][y]==0)//向下探索
    {
        p1.x=x+1;
        p1.y=y;
        maze[x+1][y]=-1;//新位置已经到达过
        path_save.Push(p1);//新位置保存进寻找通路的栈


        find_maze_route2(maze,x+1,y,m,n);
    }
    if(maze[x-1][y]==0)//向上探索
    {
        p1.x=x-1;
        p1.y=y;
        maze[x-1][y]=-1;//新位置已经到达过
        path_save.Push(p1);//新位置保存进寻找通路的栈


        find_maze_route2(maze,x-1,y,m,n);
    }
    if(maze[x][y-1]==0)//向左探索
    {
        p1.x=x;
        p1.y=y-1;
        maze[x][y-1]=-1;//新位置已经到达过
        path_save.Push(p1);//新位置保存进寻找通路的栈


        find_maze_route2(maze,x,y-1,m,n);
    }
    maze[x][y]=0;//当前道路不通，回遂重新开始探索
    stored_procedure.clear();//
    path_save.clear();//当前道路不通，清空保存路径的栈
    return 0;
}






int main()
{
//    Stack S;
//    S = CreateStack();


//    char str[60];
//    scanf(%s, str);
//    for(int i = 0; i < strlen(str); i++)//将输入的字符串压栈
//    {
//        Push(S, str[i]);
//    }


//    for(int i = 0; i < strlen(str); i++)//输出堆栈元素
//    {
//        printf(%c\n,Pop(S));
//    }
//    int **maze;
    int m=3,n=3;
    int a=3,b=2;
//    cout<<"请输入迷宫的行数"<<endl;
//    cin>>m;
//    cout<<"请输入迷宫的列数"<<endl;
//    cin>>n;
//    cout<<"请输入终点坐标x"<<endl;
//    cin>>a;
//    cout<<"请输入终点坐标y"<<endl;
//    cin>>b;
    //maze=input_maze(m,n);
    find_maze_route1(input_maze(m,n),a,b);//非递归
//    find_maze_route2(input_maze(m,n),1,1,m,n);//递归
    return 0;
}
