//
// Created by 改 on 2023/3/4.
//
#include<bits/stdc++.h>
using namespace std;
#define MAX_ELE_NUM 2000
int AllJZ = 0;
struct Region
{
    double bottom;
    double up;
    double left;
    double right;
};
struct ElePoint
{
    double k;//代表斜率
    double x1;
    double y1;
    double x2;
    double y2;
    double v;
    int hour;
    int minute;
    double x;   //x坐标
    double y;   //y坐标
    double xinhao;
    char name[20];
    int index;
    int type;
    double distence;
    double  qiangdu;
    double TrueR;
    int Endhour;
    int Endminute;
    int Endsecond;
    int Endtime;//比较时间的区间
    int Begintime;
};
//四叉树结点
struct QuadTreeNode
{
    int depth;   //结点的深度
    int is_leaf;   //是否是叶子节点
    struct Region region;   //区域范围
    struct QuadTreeNode *LU;  //左上子节点指针
    struct QuadTreeNode *LB;   //左下子节点指针
    struct QuadTreeNode *RU;   //右上子节点指针
    struct QuadTreeNode *RB;   //右下子节点指针
    int ele_num;     //矩形区域中位置点数
    struct ElePoint *ele_list[MAX_ELE_NUM];   //矩形区域中位置点列表
};
//创建桶，存所有点的信息
vector <ElePoint> Sites;
vector<ElePoint>Sites_2;
vector<ElePoint> YDzuobiao;
vector<ElePoint> Moves[100];
vector<ElePoint> WJZzuobiao;
int GiveIndex = 0;//给出的编号，全局变量与上一次相比较，进行判断需不需要输出.
int Youxinhao = 1;//给出信号有或无，进行判断是否需要输出.
double vp[12];//记录终端每段轨迹段速度。vp表示每秒是多少米,但是我们步长设置为10米。
void Pretreatment_1();
int pn = 0;//这个pn的大小指向了终端运动轨迹的段数目
void Fread()//存入所有的基站的信息，用一个桶Sets装起来。
{
    ElePoint temp;
    char ch[20];
    FILE* fp;
    double x,y;
    double xh;
    int id;
    fp=fopen("jz001.txt", "r+");//默认是基站输入
    if(!fp){
        cout<<"文件不存在！"<<endl;
        exit(0);
    }
    else {
        fscanf(fp, "%s\n", ch);
        fscanf(fp, "%lf,%lf,", &x, &y);
        while(x!=-1||y!=-1)
        {

            fscanf(fp,"%s  %lf,%d",temp.name,&xh,&id);
            temp.x=x;
            temp.y=y;
            temp.xinhao=xh;
            temp.index=id;
            if (strcmp(temp.name, "城区") == 0)temp.type = 0;
            else if (strcmp(temp.name, "乡镇") == 0)temp.type = 1;
            else temp.type = 2;
            Sites.push_back(temp);
            fscanf(fp,"%lf,%lf,",&x,&y);
        }
        fclose(fp);
    }

    fp=fopen("jz002.txt", "r+");//默认是基站输入
    if(!fp){
        cout<<"文件不存在！"<<endl;
        exit(0);
    }
    else {
        fscanf(fp, "%s\n", ch);
        fscanf(fp, "%lf,%lf,", &x, &y);
        while(x!=-1&&y!=-1)
        {

            fscanf(fp,"%s  %lf,%d",temp.name,&xh,&id);
            temp.x=x;
            temp.y=y;
            temp.xinhao=xh;
            temp.index=id;
            if (strcmp(temp.name, "城区") == 0)temp.type = 0;
            else if (strcmp(temp.name, "乡镇") == 0)temp.type = 1;
            else temp.type = 2;
            Sites.push_back(temp);
//            cout<<x<<" "<<y<<endl;
            fscanf(fp,"%lf,%lf,",&x,&y);
        }
        fclose(fp);
    }
    return;
}
void F2read(){
    ElePoint newp;
    char ch[20];
    FILE* fp;
    double x,y;
    double xh;
    int id;
    fp=fopen("yd001.txt", "r+");//默认是基站输入
    if(!fp){
        cout<<"文件不存在！"<<endl;
        exit(0);
    }
    else{
        fscanf(fp, "%s\n", ch);
        fscanf(fp, "%lf,%lf,", &x, &y);
        while(x!=-1&&y!=-1)
        {newp.k = 6666;
            fscanf(fp,"%lf,%lf,%lf,%d,%d",&newp.x2,&newp.y2,&newp.v,&newp.hour,&newp.minute);
            newp.Begintime = newp.hour*3600+newp.minute*60;
            newp.x1 = x;newp.y1 = y;
            if(newp.x1!=newp.x2){
                newp.k = 1.0*(newp.y2-newp.y1)/(newp.x2-newp.x1);
            }
            YDzuobiao.push_back(newp);
            fscanf(fp, "%lf,%lf,", &x, &y);
        }
        fclose(fp);
    }
    return;
//    cout<<Moves.size()<<endl;

}
void F3read(){
    ElePoint newp;
    char Firstline[20];
    char ch[20];
    FILE* fp;
    double x,y;
    double xh;
    fp=fopen("wz001.txt", "r+");
    if(!fp){
        cout<<"文件不存在！"<<endl;
        exit(0);
    }
    else{
        fscanf(fp, "%s\n", ch);
        fscanf(fp, "%lf,%lf,", &x, &y);{
            while(x!=-1&&y!=-1)
            {newp.k = 6666;
                fscanf(fp,"%lf,%lf,%lf,%d,%d,%d",&newp.x2, &newp.y2, &newp.v, &newp.hour, &newp.minute,&newp.index);
                newp.Begintime = newp.hour*3600+newp.minute*60;
                newp.x1 = x;newp.y1 = y;
                if(newp.x1!=newp.x2){
                    newp.k = 1.0*(newp.y2-newp.y1)/(newp.x2-newp.x1);
                }
                WJZzuobiao.push_back(newp);
                fscanf(fp, "%lf,%lf,", &x, &y);
            }
        }
        fclose(fp);}
    return;
    //cout<<WJZzuobiao.size()<<endl;
}
//函数声明
void initNode(QuadTreeNode *node, int depth,  Region region);
void insertEle(QuadTreeNode *node,  ElePoint ele);
void splitNode(QuadTreeNode *node);
void queryEle( QuadTreeNode tree,  ElePoint ele);
void MoveSearch(struct QuadTreeNode node, struct ElePoint ele,int pi);
void FindPoint(struct QuadTreeNode node, struct ElePoint ele,int pi);
void FindCover_1(struct QuadTreeNode node, struct ElePoint ele);
void initRegion( Region *region, double up, double bottom, double left, double right);
void queryArea(QuadTreeNode *node, Region *region);
QuadTreeNode *createChildNode( QuadTreeNode *node, double bottom, double up, double left, double right);
void base(int x);//将总秒数转化为时间。
void base_2(int x);
void GetTime(ElePoint ele,int pi);
void Get2Time(ElePoint ele,int pi);
double GetDis(ElePoint a);//获取轨迹起点和终点的距离
int pflag = 0;
int vflag = 0;
double ltime,rtime;
double DIS;
ElePoint *JIZHAN ;
ElePoint *A;ElePoint *B;
int allnum;//记录重合站点的个数，>=2的时候跳出



void insertEle(QuadTreeNode *node, ElePoint ele) {
    //是叶子结点
    if (1 == node->is_leaf) {
        if (node->ele_num + 1 > MAX_ELE_NUM) {
            splitNode(node);

            //分裂后的 node 不是叶子节点，所以新插入的元素会插入到 node 的子节点上
            insertEle(node, ele);  //将新插入的元素插入到node的子节点上
        } else {
            ElePoint *ele_ptr = (ElePoint *) malloc(sizeof(ElePoint));
            ele_ptr->x = ele.x;
            ele_ptr->y = ele.y;
            ele_ptr->type = ele.type;
            ele_ptr->index = ele.index;
            ele_ptr->xinhao = ele.xinhao;
            //将新插入的点加入到父节点的位置点列表中
            node->ele_list[node->ele_num] = ele_ptr;
            node->ele_num++;
        }

        return;
    }

    //不是叶子结点
    double mid_vertical = (node->region.up + node->region.bottom) / 2;
    double mid_horizontal = (node->region.left + node->region.right) / 2;
    if (ele.y > mid_vertical) {
        if (ele.x > mid_horizontal) {
            insertEle(node->RU, ele);
        } else {
            insertEle(node->LU, ele);
        }
    } else {
        if (ele.x > mid_horizontal) {
            insertEle(node->RB, ele);
        } else {
            insertEle(node->LB, ele);
        }
    }
}

/*分裂结点
1.通过父结点获取子结点的深度和范围
2.生成四个结点，挂载到父结点下
 */
void splitNode(struct QuadTreeNode *node)
{
    double mid_vertical = (node->region.up + node->region.bottom) / 2;  //垂直放向的中间线
    double mid_horizontal = (node->region.left + node->region.right) / 2; //水平方向的中间线

    node->is_leaf = 0;

    //生成四个孩子结点
    node->RU = createChildNode(node, mid_vertical, node->region.up, mid_horizontal, node->region.right);
    node->LU = createChildNode(node, mid_vertical, node->region.up, node->region.left, 					mid_horizontal);
    node->RB = createChildNode(node, node->region.bottom, mid_vertical, mid_horizontal, 				node->region.right);
    node->LB = createChildNode(node, node->region.bottom, mid_vertical, node->region.left, mid_horizontal);

    for (int i = 0; i < node->ele_num; i++)
    {
        //此时插入的时候，node不是叶子节点，此时执行 insert 函数，会将元素插入到孩子节点上
        insertEle(node, *node->ele_list[i]);   // 将父节点元素 插入到子节点
        free(node->ele_list[i]);   //释放父节点元素

        //node->ele_num--;//这里每次循环的时候i在增加，而node.ele_num在减少，会导致有的点没有插进去
        //所以直接在循环结束后，将node.ele_num置为0即可
    }
    node->ele_num = 0;
}
//创建子节点
QuadTreeNode *createChildNode(struct QuadTreeNode *node, double bottom, double up, double left, double right)
{
    int depth = node->depth + 1;
    QuadTreeNode *childNode = (QuadTreeNode *) malloc(sizeof(QuadTreeNode));
    Region *region = (Region *) malloc(sizeof(Region));
    initRegion(region, bottom, up, left, right);
    initNode(childNode, depth, *region);

    return childNode;
}
//区域查询  输出该点所在的矩形区域的所有点
void queryEle(struct QuadTreeNode node, struct ElePoint ele)
{
    //是叶子结点
    if (node.is_leaf == 1)
    {
//        cout << "附近点有" << node.ele_num << "个,分别是：" << endl;
//        for (int j = 0; j < node.ele_num; j++)
//        {
//            cout<<"编号:"<<node.ele_list[j]->index <<" "<<"坐标："<< "(" << node.ele_list[j]->x << "," << node.ele_list[j]->y << ")"<<"\t";
//            cout<<"信号强度:"<<node.ele_list[j]->xinhao<<" "<<"类型"<<node.ele_list[j]->type;
//            puts("");
//        }
        int flag =0;
        for(int j=0;j<node.ele_num;j++){
            node.ele_list[j]->distence = sqrt(pow((ele.x-node.ele_list[j]->x),2)+pow((ele.y-node.ele_list[j]->y),2));
            //cout<<node.ele_list[j]->distence<<" ";
            if(node.ele_list[j]->type==0){
                node.ele_list[j]->TrueR = 300* sqrt(node.ele_list[j]->xinhao);
                if(node.ele_list[j]->distence<=node.ele_list[j]->TrueR){
                    node.ele_list[j]->qiangdu = node.ele_list[j]->xinhao*pow(node.ele_list[j]->TrueR/node.ele_list[j]->distence,2);
                    flag = 1;
                }
            }
            else if(node.ele_list[j]->type==1){
                node.ele_list[j]->TrueR = 1000* sqrt(node.ele_list[j]->xinhao);
                if(node.ele_list[j]->distence<=node.ele_list[j]->TrueR){
                    node.ele_list[j]->qiangdu = node.ele_list[j]->xinhao*pow(node.ele_list[j]->TrueR/node.ele_list[j]->distence,2);
                    flag = 1;
                }
            }
            else if(node.ele_list[j]->type==2){
                node.ele_list[j]->TrueR = 5000* sqrt(node.ele_list[j]->xinhao);
                if(node.ele_list[j]->distence<=node.ele_list[j]->TrueR ){
                    node.ele_list[j]->qiangdu = node.ele_list[j]->xinhao*pow(node.ele_list[j]->TrueR /node.ele_list[j]->distence,2);
                    flag = 1;
                }
            }
        }
        int maxj = 0;
        double  maxn = 0;
        if(flag == 0){
            cout<<"周围没有基站可以传播到信号";
        }
        else{
            cout<<"周围有基站可以传播到信号的是："<<endl;
            for(int j=0;j<node.ele_num;j++){
                if(node.ele_list[j]->qiangdu){
                    cout<<"编号:"<<node.ele_list[j]->index <<" "<<"坐标："<< "(" << node.ele_list[j]->x << "," << node.ele_list[j]->y << ")"<<"\t";
                    cout<<"信号强度:"<<node.ele_list[j]->xinhao<<" "<<"类型"<<node.ele_list[j]->type<<" ";
                    if(node.ele_list[j]->type==0)cout<<"城市 ";
                    else if(node.ele_list[j]->type==1)cout<<"乡村 ";
                    else cout<<"高速 ";
                    cout<<"有效半径："<<node.ele_list[j]->TrueR<<" ";
                    cout<<"当前距离: "<<node.ele_list[j]->distence<<" ";
                    cout<<"当前强度:"<<node.ele_list[j]->qiangdu;
                    puts("");
                    if(node.ele_list[j]->qiangdu>maxn){
                        maxj = j;
                        maxn = node.ele_list[j]->qiangdu;
                    }
                    //回复现场；
                    node.ele_list[j]->qiangdu=0;
                    node.ele_list[j]->distence = 0;
                    node.ele_list[j]->TrueR = 0;
                }
            }
        }
        if(flag == 1)
            cout<<"选取信号强度最大的链接是："<<node.ele_list[maxj]->index;

        puts("");
        return;
    }

    //不是叶子节点
    double mid_vertical = (node.region.up + node.region.bottom) / 2;
    double mid_horizontal = (node.region.left + node.region.right) / 2;

    if (ele.y > mid_vertical)
    {
        if (ele.x > mid_horizontal)
        {
            queryEle(*node.RU, ele);
        }
        else
        {
            queryEle(*node.LU, ele);
        }
    }
    else
    {
        if (ele.x > mid_horizontal)
        {
            queryEle(*node.RB, ele);
        }
        else
        {
            queryEle(*node.LB, ele);
        }
    }
}
//点查询
void queryPoint(struct QuadTreeNode node, ElePoint &ele)
{
    //是叶子节点
    if (node.is_leaf == 1)
    {
        for (int i = 0; i < node.ele_num; i++)
        {
            if (ele.x == node.ele_list[i]->x &&ele.y == node.ele_list[i]->y)
            {
                cout << "(" << node.ele_list[i]->x << "," << node.ele_list[i]->y << ") 位于第" << node.depth << "层" << endl;
                return;
            }
        }
        cout << "未找到该点！" << endl;
        return;
    }

    //不是叶子结点
    double mid_vertical = (node.region.up + node.region.bottom) / 2;
    double mid_horizontal = (node.region.left + node.region.right) / 2;

    if (ele.x> mid_horizontal) {
        if (ele.y > mid_vertical) {
            queryPoint(*node.RU, ele);
        }
        else {
            queryPoint(*node.RB, ele);
        }
    }
    else {
        if (ele.y > mid_vertical) {
            queryPoint(*node.LU, ele);
        }
        else {
            queryPoint(*node.LB, ele);
        }
    }
}
//任意区域查询
void queryArea(QuadTreeNode *node, Region *region)
{	//是叶子节点
    if (node->is_leaf == 1)
    {
        //遍历叶子节点中的所有点
        for (int i = 0; i < node->ele_num; i++)
        {
            //如果叶子节点中有点在该矩形区域中，就输出该点坐标
            if (node->ele_list[i]->x >= region->left &&
                node->ele_list[i]->x <= region->right &&
                node->ele_list[i]->y >= region->bottom &&
                node->ele_list[i]->y <= region->up)
            {
                cout<<"编号:"<<node->ele_list[i]->index <<" "<<"坐标："<< "(" << node->ele_list[i]->x << "," << node->ele_list[i]->y << ")"<<"\t";
                cout<<"信号强度:"<<node->ele_list[i]->xinhao<<" "<<"类型"<<node->ele_list[i]->type<<" ";
                if(node->ele_list[i]->type==0)cout<<"城市 ";
                else if(node->ele_list[i]->type==1)cout<<"乡村 ";
                else cout<<"高速 ";
                puts("");
            }
        }
        return;
    }

    //不是叶子结点 ， 递归查找与矩形区域有交集的叶子结点
    double mid_vertical = (node->region.up + node->region.bottom) / 2;
    double mid_horizontal = (node->region.left + node->region.right) / 2;

    //讨论矩形区域的9种分布情况
    if (region->bottom > mid_vertical){
        if (region->left > mid_horizontal){
            //如果矩形区域的下边界大，左边界大，就在右上区域查询
            queryArea(node->RU, region);
        }
        else if (region->right < mid_horizontal){
            queryArea(node->LU, region);
        }
        else{
            //将该矩形区域分成两块，逐块递归判断其所属的子区域
            Region *region1 = (Region *)malloc(sizeof(Region));
            *region1 = { region->bottom,region->up,region->left,mid_horizontal };
            queryArea(node->LU, region1);

            Region *region2 = (Region *)malloc(sizeof(Region));
            *region2 = { region->bottom,region->up,mid_horizontal,region->right };
            queryArea(node->RU, region2);
        }
    }

    else if (region->up < mid_vertical){
        if (region->right < mid_horizontal){
            queryArea(node->LB, region);
        }
        else if (region->left > mid_horizontal){
            queryArea(node->RB, region);
        }
        else{
            Region *region1 = (Region *)malloc(sizeof(Region));
            *region1 = { region->bottom, region->up,region->left,mid_horizontal };
            queryArea(node->LB, region1);

            Region *region2 = (Region *)malloc(sizeof(Region));
            *region2 = { region->bottom,region->up,mid_horizontal,region->right };
            queryArea(node->RB, region2);
        }
    }

    else{
        if (region->right < mid_horizontal){
            Region *region1 = (Region *)malloc(sizeof(Region));
            *region1 = { mid_vertical,region->up,region->left,region->right };
            queryArea(node->LU, region1);

            Region *region2 = (Region *)malloc(sizeof(Region));
            *region2 = { region->bottom,mid_vertical,region->left,region->right };
            queryArea(node->LB, region2);

        }
        else if (region->left > mid_horizontal)	{
            Region *region1 = (Region *)malloc(sizeof(Region));
            *region1 = { mid_vertical,region->up,region->left,region->right };
            queryArea(node->RU, region1);

            Region *region2 = (Region *)malloc(sizeof(Region));
            *region2 = { region->bottom,mid_vertical,region->left,region->right };
            queryArea(node->RB, region2);
        }
        else {
            Region *region1 = (Region *)malloc(sizeof(Region));
            *region1 = { mid_vertical,region->up,region->left,mid_horizontal };
            queryArea(node->LU, region1);

            Region *region2 = (Region *)malloc(sizeof(Region));
            *region2 = { mid_vertical,region->up,mid_horizontal,region->right };
            queryArea(node->RU, region2);

            Region *region3 = (Region *)malloc(sizeof(Region));
            *region3 = { region->bottom,mid_vertical,region->left,mid_horizontal };
            queryArea(node->LB, region3);

            Region *region4 = (Region *)malloc(sizeof(Region));
            *region4 = { region->bottom, mid_vertical,mid_horizontal,region->right };
            queryArea(node->RB, region4);
        }
    }
}
//初始化四叉树结点
void initNode(QuadTreeNode *node, int depth, Region region)
{
    node->depth = depth;
    node->is_leaf = 1;
    node->ele_num = 0;
    node->region = region;
}
//初始化矩形区域
void initRegion(Region *region, double bottom, double up, double left, double right)
{
    region->bottom = bottom;
    region->up = up;
    region->left = left;
    region->right = right;
}
//对移动轨迹的查询
void MoveSearch(struct QuadTreeNode node, struct ElePoint ele,int pi)
{
    //是叶子结点
    if (node.is_leaf == 1)
    {
        int flag =0;
        for(int j=0;j<node.ele_num;j++){
            node.ele_list[j]->distence = sqrt(pow((ele.x-node.ele_list[j]->x),2)+pow((ele.y-node.ele_list[j]->y),2));
            if(node.ele_list[j]->type==0){
                node.ele_list[j]->TrueR = 300* sqrt(node.ele_list[j]->xinhao);
                if(node.ele_list[j]->distence<=node.ele_list[j]->TrueR){
                    node.ele_list[j]->qiangdu = node.ele_list[j]->xinhao*pow(node.ele_list[j]->TrueR/node.ele_list[j]->distence,2);
                    flag = 1;
                }
            }
            else if(node.ele_list[j]->type==1){
                node.ele_list[j]->TrueR = 1000* sqrt(node.ele_list[j]->xinhao);
                if(node.ele_list[j]->distence<=node.ele_list[j]->TrueR){
                    node.ele_list[j]->qiangdu = node.ele_list[j]->xinhao*pow(node.ele_list[j]->TrueR/node.ele_list[j]->distence,2);
                    flag = 1;
                }
            }
            else {
                node.ele_list[j]->TrueR = 5000* sqrt(node.ele_list[j]->xinhao);
                if(node.ele_list[j]->distence<=node.ele_list[j]->TrueR ){
                    node.ele_list[j]->qiangdu = node.ele_list[j]->xinhao*pow(node.ele_list[j]->TrueR /node.ele_list[j]->distence,2);
                    flag = 1;
                }
            }
        }
        int maxj = 0;
        double  maxn = 0;

        if(flag == 0&&Youxinhao==1){
            GetTime(ele,pi);
            printf("当前位置为：(%.0lf,%.0lf)\t",ele.x,ele.y);
            cout<<"终端失去连接\n";
            AllJZ++;
            Youxinhao = 0;
        }
        else{
            for(int j=0;j<node.ele_num;j++){
                if(node.ele_list[j]->qiangdu){
                    if(node.ele_list[j]->qiangdu>=maxn){
                        maxj = j;
                        maxn = node.ele_list[j]->qiangdu;
                    }
                    //回复现场；
                    node.ele_list[j]->qiangdu=0;
                    node.ele_list[j]->distence = 0;
                    // node.ele_list[j]->TrueR = 0;
                }
            }
        }
        if(flag == 1&&GiveIndex!=node.ele_list[maxj]->index) {
            GetTime(ele,pi);
            printf("当前位置为：(%.0lf,%.0lf)\t",ele.x,ele.y);
            cout << "成功连接!选取信号强度最大的连接基站编号是：" << node.ele_list[maxj]->index<<endl;
            Youxinhao = 1;
            AllJZ++;
        }
        GiveIndex = node.ele_list[maxj]->index;
        return;
    }

    //不是叶子节点
    double mid_vertical = (node.region.up + node.region.bottom) / 2;
    double mid_horizontal = (node.region.left + node.region.right) / 2;

    if (ele.y > mid_vertical)
    {
        if (ele.x > mid_horizontal)
        {
            MoveSearch(*node.RU, ele,pi);
        }
        else
        {
            MoveSearch(*node.LU, ele,pi);
        }
    }
    else
    {
        if (ele.x > mid_horizontal)
        {
            MoveSearch(*node.RB, ele,pi);
        }
        else
        {
            MoveSearch(*node.LB, ele,pi);
        }
    }
}
void FindPoint(struct QuadTreeNode node, struct ElePoint ele,int pi)
{
    //是叶子结点
    if (node.is_leaf == 1)
    {
        int flag =0;
        for(int j=0;j<node.ele_num;j++){
            node.ele_list[j]->distence = sqrt(pow((ele.x-node.ele_list[j]->x),2)+pow((ele.y-node.ele_list[j]->y),2));
            //cout<<node.ele_list[j]->distence<<" ";
            if(node.ele_list[j]->type==0){
                node.ele_list[j]->TrueR = 300* sqrt(node.ele_list[j]->xinhao);
                if(node.ele_list[j]->distence<=node.ele_list[j]->TrueR){
                    node.ele_list[j]->qiangdu = node.ele_list[j]->xinhao*pow(node.ele_list[j]->TrueR/node.ele_list[j]->distence,2);
                    flag = 1;
                }
            }
            else if(node.ele_list[j]->type==1){
                node.ele_list[j]->TrueR = 1000* sqrt(node.ele_list[j]->xinhao);
                if(node.ele_list[j]->distence<=node.ele_list[j]->TrueR){
                    node.ele_list[j]->qiangdu = node.ele_list[j]->xinhao*pow(node.ele_list[j]->TrueR/node.ele_list[j]->distence,2);
                    flag = 1;
                }
            }
            else if(node.ele_list[j]->type==2){
                node.ele_list[j]->TrueR = 5000* sqrt(node.ele_list[j]->xinhao);
                if(node.ele_list[j]->distence<=node.ele_list[j]->TrueR ){
                    node.ele_list[j]->qiangdu = node.ele_list[j]->xinhao*pow(node.ele_list[j]->TrueR /node.ele_list[j]->distence,2);
                    flag = 1;
                }
            }
        }
        int maxj = 0;
        double  maxn = 0;

        if(flag == 0&&Youxinhao==1){
            Get2Time(ele,pi);
//            printf("当前位置为：(%.0lf,%.0lf)\t",ele.x,ele.y);
//            cout<<"终端失去连接\n";
            vflag++;
            Youxinhao = 0;
        }
        else{
            for(int j=0;j<node.ele_num;j++){
                if(node.ele_list[j]->qiangdu){
                    if(node.ele_list[j]->qiangdu>maxn){
                        maxj = j;
                        maxn = node.ele_list[j]->qiangdu;
                    }
                    //回复现场；
                    node.ele_list[j]->qiangdu=0;
                    node.ele_list[j]->distence = 0;
//                    node.ele_list[j]->TrueR = 0;
                }
            }
        }
        if(flag == 1&&GiveIndex!=node.ele_list[maxj]->index) {
            Get2Time(ele,pi);
//            printf("当前位置为：(%.0lf,%.0lf)\t",ele.x,ele.y);
//            cout << "成功连接!选取信号强度最大的连接基站编号是：" << node.ele_list[maxj]->index<<endl;
            DIS = node.ele_list[maxj]->TrueR;
            JIZHAN = node.ele_list[maxj];
            Youxinhao = 1;
            pflag++;
            if(vflag>=1)
                vflag--;
        }

        GiveIndex = node.ele_list[maxj]->index;
        for(int j=0;j<node.ele_num;j++){
            //回复现场；
            node.ele_list[j]->qiangdu=0;
            node.ele_list[j]->distence = 0;
            node.ele_list[j]->TrueR = 0;
        }
        return;
    }

    //不是叶子节点
    double mid_vertical = (node.region.up + node.region.bottom) / 2;
    double mid_horizontal = (node.region.left + node.region.right) / 2;

    if (ele.y > mid_vertical)
    {
        if (ele.x > mid_horizontal)
        {
            FindPoint(*node.RU, ele,pi);
        }
        else
        {
            FindPoint(*node.LU, ele,pi);
        }
    }
    else
    {
        if (ele.x > mid_horizontal)
        {
            FindPoint(*node.RB, ele,pi);
        }
        else
        {
            FindPoint(*node.LB, ele,pi);
        }
    }
}
void FindCover_1(struct QuadTreeNode node, struct ElePoint ele)
{allnum = 0;
    //是叶子结点
    if (node.is_leaf == 1)
    {
        int flag =0;
        for(int j=0;j<node.ele_num;j++){
            node.ele_list[j]->distence = sqrt(pow((ele.x-node.ele_list[j]->x),2)+pow((ele.y-node.ele_list[j]->y),2));
            //cout<<node.ele_list[j]->distence<<" ";
            if(node.ele_list[j]->type==0){
                node.ele_list[j]->TrueR = 300* sqrt(node.ele_list[j]->xinhao);
                if(node.ele_list[j]->distence<=node.ele_list[j]->TrueR){
                    node.ele_list[j]->qiangdu = node.ele_list[j]->xinhao*pow(node.ele_list[j]->TrueR/node.ele_list[j]->distence,2);
                    flag = 1;
                }
            }
            else if(node.ele_list[j]->type==1){
                node.ele_list[j]->TrueR = 1000* sqrt(node.ele_list[j]->xinhao);
                if(node.ele_list[j]->distence<=node.ele_list[j]->TrueR){
                    node.ele_list[j]->qiangdu = node.ele_list[j]->xinhao*pow(node.ele_list[j]->TrueR/node.ele_list[j]->distence,2);
                    flag = 1;
                }
            }
            else if(node.ele_list[j]->type==2){
                node.ele_list[j]->TrueR = 5000* sqrt(node.ele_list[j]->xinhao);
                if(node.ele_list[j]->distence<=node.ele_list[j]->TrueR ){
                    node.ele_list[j]->qiangdu = node.ele_list[j]->xinhao*pow(node.ele_list[j]->TrueR /node.ele_list[j]->distence,2);
                    flag = 1;
                }
            }
        }
        int a[2] ;

        if(flag==1){

            for(int j=0;j<node.ele_num;j++){
                if(node.ele_list[j]->qiangdu){
                    a[allnum]=j;
                    allnum++;
                    node.ele_list[j]->qiangdu=0;
                    node.ele_list[j]->distence = 0;
//                    //node.ele_list[j]->TrueR = 0;
                }
            }
        }
        if(allnum==2){
            A = node.ele_list[a[0]];
            B = node.ele_list[a[1]];
        }
        return;
    }

    //不是叶子节点
    double mid_vertical = (node.region.up + node.region.bottom) / 2;
    double mid_horizontal = (node.region.left + node.region.right) / 2;

    if (ele.y > mid_vertical)
    {
        if (ele.x > mid_horizontal)
        {
            FindCover_1(*node.RU, ele);
        }
        else
        {
            FindCover_1(*node.LU, ele);
        }
    }
    else
    {
        if (ele.x > mid_horizontal)
        {
            FindCover_1(*node.RB, ele);
        }
        else
        {
            FindCover_1(*node.LB, ele);
        }
    }
}
void Pretreatment_1(){
    int k= 0 ;
    for(auto t:YDzuobiao) {
        double vm = 10;//选取步长为10米
        double vs = t.v / 3.6;
        vp[k++]=vs;
        // cout << t.x1 << " " << t.y1 << " " << t.v << " " << t.v / 3 * 50 << " " << t.k << endl;
        if (t.k == 0) {
            ElePoint myroad;
            myroad.x = t.x1;
            myroad.y = t.y1;
            //  cout << "沿着x轴的平行方向运动\n";
            if (t.x2 > t.x1) {
                while (myroad.x < t.x2) {
                    Moves[pn].push_back(myroad);
                    myroad.x += vm;
                }
                pn++;
            } else {
                while (myroad.x > t.x2) {
                    Moves[pn].push_back(myroad);
                    myroad.x -= vm;
                }
                pn++;
            }
        } else if (t.k == 6666) {
            ElePoint tem;
            tem.x = t.x1;
            tem.y = t.y1;
            // cout << "沿着y轴的平行方向运动\n";
            if (t.y1 < t.y2) {
                while (tem.y < t.y2) {
                    Moves[pn].push_back(tem);
                    tem.y += vm;
                }pn++;
            } else {
                while (tem.y > t.y2) {
                    Moves[pn].push_back(tem);
                    tem.y -= vm;
                }
                pn++;
            }
        } else {
            ElePoint mypoint;
            mypoint.x = t.x1;
            mypoint.y = t.y1;
            //  cout << "正常的斜线运动\n";
            double sita = atan(t.k);
            if (t.k > 0) {
                if (t.x1 < t.x2) {
                    while (mypoint.x < t.x2) {
                        Moves[pn].push_back(mypoint);
                        mypoint.x += vm * abs(cos(sita));
                        mypoint.y += vm * abs(sin(sita));
                    }
                    pn++;
                } else {
                    while (mypoint.x > t.x2) {
                        Moves[pn].push_back(mypoint);
                        mypoint.x -= vm * abs(cos(sita));
                        mypoint.y -= vm * abs(sin(sita));
                    }
                    pn++;
                }
            } else {
                if (t.x1 < t.x2) {
                    while (mypoint.x < t.x2) {
                        Moves[pn].push_back(mypoint);
                        mypoint.x += vm *abs ( cos(sita));
                        mypoint.y -= vm * abs(sin(sita));
                    }
                    pn++;
                } else {
                    while (mypoint.x > t.x2) {
                        Moves[pn].push_back(mypoint);
                        mypoint.x -= vm * abs(cos(sita));
                        mypoint.y += vm * abs(sin(sita));
                    }
                    pn++;
                }
            }

        }
    }
    ElePoint tem= YDzuobiao.back();
    ElePoint p ;
    p.x = tem.x2;
    p.y = tem.y2;
    Moves[--pn].push_back(p);
    pn++;
}
void GetTime(ElePoint ele,int pi){
    double d = 0;
    d = sqrt(pow((YDzuobiao[pi].x1-ele.x),2)+pow((YDzuobiao[pi].y1-ele.y),2));
    int t = d/vp[pi];
    int shour = YDzuobiao[pi].hour;
    int sminute = YDzuobiao[pi].minute;
    int xt = t/60;
    int second = t%60;
    sminute+=xt;
    xt = sminute/60;
    int minute = sminute%60;
    int hour = shour+xt;
    printf("当前时间是%02d时%02d分%02d秒,",hour,minute,second);
}
void Get2Time(ElePoint ele,int pi){
    double d = 0;
    d = sqrt(pow((YDzuobiao[pi].x1-ele.x),2)+pow((YDzuobiao[pi].y1-ele.y),2));
    int t = d/vp[pi];
    ltime = t;
    int s2hour = YDzuobiao[pi].hour;
    int s2minute = YDzuobiao[pi].minute;
    int xt = t/60;
    int second = t%60;
    s2minute+=xt;
    xt = s2minute/60;
    int minute = s2minute%60;
    int hour = s2hour+xt;
    if(rtime!=0)
    {printf("%02d时%02d分",hour,minute);}
}
double GetDis(ElePoint a) {
    double d = sqrt(pow(a.x1 - a.x2, 2) + pow(a.y1 - a.y2, 2));
    return d;
}
void base(int x){
    int alltime =x;
    int hour = alltime/3600;
    int minute = (alltime - hour*3600)/60;
    int second = (alltime-hour*3600-minute*60);
    ::printf("%02d:%02d:%02d\n",hour,minute,second);
}
void base_2(int x){
    int alltime =x;
    int hour = alltime/3600;
    int minute = (alltime - hour*3600)/60;
    int second = (alltime-hour*3600-minute*60);
    ::printf("%02d时%02d分%2d+",hour,minute,second);
}