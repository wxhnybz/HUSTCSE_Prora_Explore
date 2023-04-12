#include<QuadTreeNode.h>
using namespace  std;
const int N = 1e5;
struct Users//用户登陆系统
{
    int index;
    char zhanghao[100],mima[100];///账号、密码
} users[N];

int i,n,m,p,k=0;
char linshizhanghao[100],linshimima[100];
int xiabiao;
char panduan,formatting[100]= {'\0'},Admin[100]= {"Admin"},Password[100]= {"Admin"};//判断y/n，格式化，管理员账号

int main() {
    {
        //每次开机先初始化一边之前的账号登陆
        FILE *filep;
        filep = fopen("users/num.txt", "r+");
        if (!filep) {
            cout << "初始化进入系统\n";
            return 0;
        }
        ::fscanf(filep, "%d", &k);
        ::fclose(filep);
        if (k != 0) {
            for (int i = 0; i < k; i++) {
                string fname = "users/";
                string ch = to_string(i + 1);
                fname += ch;
                fname += ".txt";
                char filename[100];
                for (int i = 0; i < fname.size(); i++) {
                    filename[i] = fname[i];
                }
                //cout<<filename<<endl;
                filep = ::fopen(filename, "r+");
                if (!filep) {
                    cout << "文件打开失败\n";
                } else {
                    char a[100];
                    char b[100];
                    ::fscanf(filep, "%s", a);
                    ::fscanf(filep, "%s", b);
                    ::fscanf(filep, "%d", &users[i].index);
                    //  cout << users[i].index << endl;
                    ::fclose(filep);
                    for (int j = 0; j < ::strlen(a); j++) {
                        users[i].zhanghao[j] = a[j] ^ 1;
                    }
                    for (int j = 0; j < ::strlen(b); j++) {
                        users[i].mima[j] = b[j] ^ 1;
                    }
                }
            }
        }
//        for(int i=0;i<k;i++){
//            cout<<users[i].zhanghao<<" "<<users[i].mima<<endl;
//        }
        cout << "欢迎来到GMS系统的用户登陆界面：\n";
        cout << "**********************************************************\n";
        while (1) {
            ofstream fout;
            string s1 = "users/num.txt";
            fout.open(s1);
            fout << k;
            fout.close();
            cout << "1.注册 2.登陆 3.结束" << endl;   ///0.后台检测代码
            cout << "请输入需要执行的操作:\n";
            string sn;
            cin >> sn;
            //cin >> n;
            if (sn == "1")            ///-注册;
            {
                if (k < 400) {
                    cout << "账号：";
                    cin >> users[k].zhanghao;
                    cout << "密码：";
                    cin >> users[k].mima;
                    p = 0;
                    for (i = 0; i < k; i++) {
                        if (strcmp(users[i].zhanghao, users[k].zhanghao) == 0) {
                            p++;
                        }
                    }
                    if (p != 0) {
                        cout << "此用户名已被注册!" << endl;
                        strcpy(users[k].zhanghao, formatting);
                        strcpy(users[k].mima, formatting);
                    } else {
                        cout << "您成功注册为本系统的用户" << endl;
                        char zhanghao[100];
                        char mima[100];
                        ofstream outfile;
                        string s = "users/";
                        string ch = to_string(k + 1);
                        s += ch;
                        s += ".txt";
                        cout << s << endl;
                        outfile.open(s);
                        for (int j = 0; j < strlen(users[k].zhanghao); j++) {
                            zhanghao[j] = users[k].zhanghao[j] ^ 1;
                        }
                        for (int j = 0; j < strlen(users[k].mima); j++) {
                            mima[j] = users[k].mima[j] ^ 1;
                        }
                        outfile << zhanghao << "\n" << mima << "\n" << k + 1;
                        outfile.close();
                        k++;
                    }
                } else
                    cout << "用户已满！" << endl;

            }
            if (sn == "2")            ///-登录（包括管理员账号）;
            {
                cout << "账号：";
                cin >> linshizhanghao;
                cout << "密码：";
                cin >> linshimima;
                p = 0;
                xiabiao = 0;
                if (strcmp(Admin, linshizhanghao) == 0 && strcmp(Password, linshimima) == 0)                ///管理员登录操作
                {
                    strcpy(linshizhanghao, formatting);
                    strcpy(linshimima, formatting);
                    cout << endl << "————hello Administrator！————" << endl << endl;
                    for (i = 0; i < k; i++) {
                        cout << "已注册的第" << i + 1 << "号用户" << endl << "账号:" << users[i].zhanghao << '\t'
                             << "密码:"
                             << users[i].mima << endl;
                    }
                    cout << endl << "————hello Administrator！————" << endl << endl;
                    cout << "1.查询用户信息 2.注销 3.退出管理员模式" << endl << "请输入要执行的管理员操作:";
                    while (cin >> m) {
                        if (m == 1) {

                            cout << "请输入您想查询的用户的编号：\n";
                            int i = 0;
                            cin >> i;
                            ::printf("第%02d位用户的信息为\n", i);
                            cout << "账号:" << users[i - 1].zhanghao << endl;
                            cout << "密码:" << users[i - 1].mima << endl;
                            puts("");
                        }
                        if (m == 2) {
                            cout << "请输入需要注销的账号：";
                            cin >> linshizhanghao;
                            cout << "密码：";
                            cin >> linshimima;
                            cout << "请确认是否注销，一旦注销账号将无法找回 y/n" << endl;
                            cin >> panduan;
                            if (panduan == 'y') {
                                ///从注册的用户中找到需要注销的账号进行注销
                                p = 0;
                                xiabiao = 0;
                                for (i = 0; i < k; i++) {
                                    if (strcmp(users[i].zhanghao, linshizhanghao) == 0 &&
                                        strcmp(users[i].mima, linshimima) == 0) {
                                        p++;
                                    }
                                    if (p == 1) {
                                        xiabiao = i;
                                        p++;
                                    }
                                }
                                p--;
                                if (p == 1) {
                                    for (i = xiabiao; i < k; i++) {
                                        strcpy(users[i].zhanghao, users[i + 1].zhanghao);
                                        strcpy(users[i].mima, users[i + 1].mima);
                                        strcpy(users[i + 1].zhanghao, formatting);
                                        strcpy(users[i + 1].mima, formatting);
                                    }
                                    k--;
                                    cout << xiabiao + 1 << "号用户注销成功!" << endl;
                                }
                                if (p != 1)
                                    cout << "账号或密码错误，无法注销！" << endl;
                            }
                            if (panduan = 'n')
                                cout << "取消注销" << endl;
                        }
                        if (m == 3) {
                            cout << endl << "————Byebye Administrator！————" << endl << endl;
                            break;
                        }
                        cout << "请输入要执行的管理员操作:";
                    }
                } else                    ///普通用户登录操作
                {
                    int mj = 0;
                    for (i = 0; i < k; i++) {
                        if (strcmp(users[i].zhanghao, linshizhanghao) == 0 && strcmp(users[i].mima, linshimima) == 0) {
                            mj = i;
                            p++;
                        }
                        if (p == 1) {
                            xiabiao = i;

                        }
                    }
                    if (p == 1) {
                        cout << "第" << users[mj].index << "位用户登陆成功!" << endl;
                        cout << "您选择的操作：1.进入GMS基站查询系统  2.返回到用户登陆界面\n";
                        int key = 0;
                        cin >> key;
                        if (key == 1) {
                            cout << "即将进入GMS系统\n";
                            break;
                        } else if (key == 2) {
                            cout << "返回用户登陆系统\n";
                        }
                    } else {
                        cout << "账户或者是密码错误\n";
                    }
                }
            }
            if (sn == "3") {
                printf("界面退出，欢迎下次使用!\n");
                return 0;
            } else {
                cout << "输入错误，请重新输入！\n";
            }
        }
    }


    QuadTreeNode root;
    Region root_region;
    ElePoint ele;
    Fread();
    F2read();
    F3read();
    Pretreatment_1();//预处理数据，将每一分钟的具体坐标求出来，存放到容器Moves中
    //处理每一段的开始和结束时间，现在时间区间上寻找是否有重合的区域。
    int nflags = 0;
    //double dieta = ::atan(0.75);
    //cout<<abs(cos(dieta))<<" "<<abs(sin(dieta))<<endl;
    for (auto t: YDzuobiao) {
        //cout<<GetDis(t)<<" ";
        int CostTime = GetDis(t) / (t.v / 3.6);
        // cout<<GetDis(t)/(t.v/3.6)<<" ";
        t.Endsecond = CostTime % 60;
        t.Endminute = (CostTime / 60 + t.minute) % 60;
        t.Endhour = (CostTime / 60 + t.minute) / 60 + t.hour;
        t.Endtime = t.Endhour * 3600 + t.Endminute * 60 + t.Endsecond;
        YDzuobiao[nflags++].Endtime = t.Endtime;
    }
//            for(auto t:YDzuobiao){
//                cout<<t.k<<" ";
//                cout<<t.Begintime<<" "<<t.Endtime<<endl;
//            }
//            cout<<vp[11];
    //初始化
    initRegion(&root_region, -100, 40000, -100, 110000);
    initNode(&root, 1, root_region);
//通过插入建立四叉树
    for (auto t: Sites) {
        // cout<<t.index<<" "<<t.x<<" "<<t.y<<" "<<t.type<<endl;
        insertEle(&root, t);
        //cout<<t.index<<"\n";
    }
    while (1) {

                printf("\n");
                printf("\n");
                printf("            	******************欢迎来到GMS信息处理*************\n");
                printf("	______________________________________________________________________________\n");
                printf("	|---->                       请选择输入你要操作的选择                         <-----\n");
                printf("	|----> 1：想要实现任务一,查找西北角和东南角区域的基站                             <-----\n");
                printf("	|----> 2：想要实现任务二，查找西北角和东南角区域附近的基站                         <-----\n");
                printf("	|----> 3：想要查找任务三的点的连接信号                                         <-----\n");
                printf("	|----> 4：想要查找任务四的点的连接信号                                         <-----\n");
                printf("	|----> 5：想要寻找终端轨迹变化过程中的连接与断开                                 <-----\n");
                printf("	|----> 6：二分调查轨迹01的进入首个基站和离开时间区域                              <-----\n");
                printf("	|----> 7：查找重叠区域的信号变化过程                                           <-----\n");
                printf("	|----> 8：完成升级功能的检测，检测伪基站与终端连接的时间序列                        <-----\n");
                printf("	|----> 9：额外功能查找任意区域的基站(自主研究功能)                                <-----\n");
                printf("	|----> 0：结束查找                                                          <-----\n");
                printf("	|_______________________________________________________________________________\n");

       int choice;
       cout<<"请输入你的选择：\n";
        cin >> choice;
        switch (choice) {
            case 1: {
                cout << "********************************************************\n";
                /***************显示首个分块的基站中的数据(西北角)*******************/
                cout << "西北区域的所有基站\n";
                printf("矩形 区域的范围是：38000,40000,-100,2000\n");
                Region regionNW;
                initRegion(&regionNW, 38000, 40000, -100, 2000);
                queryArea(&root, &regionNW);
                puts("");
                ///***************显示末尾分块的基站中的数据(东南角)*******************/
                cout << "东南区域的所有基站\n";
                printf("矩形区域的范围是：-100,2000,108000,110000\n");
                Region regionSE;
                initRegion(&regionSE, -100, 2000, 108000, 110000);
                queryArea(&root, &regionSE);
                puts("");
                cout << "********************************************************\n";
                cout << endl;
            }
                break;
            case 2:
                printf("任务二如下\n");
                {
                    cout << "********************************************************\n";
                    /****************显示西北角分块树叶东侧的基站********************************/
                    cout << "西北区域东侧的所有基站\n";
                    printf("矩形区域的范围是：38000, 40000, 2000, 4000\n");
                    Region regionNWE;
                    initRegion(&regionNWE, 38000, 40000, 2000, 4000);
                    queryArea(&root, &regionNWE);
                    puts("");
                    /****************显示西北角分块树叶南侧的基站********************************/
                    cout << "西北区域南侧的所有基站\n";
                    printf("矩形区域的范围是：36000, 38000, -100, 2000\n");
                    Region regionNWS;
                    initRegion(&regionNWS, 36000, 38000, -100, 2000);
                    queryArea(&root, &regionNWS);
                    puts("");
                    cout << "********************************************************\n";
                    /****************显示东南角分块树叶北侧的基站********************************/
                    cout << "东南区域北侧的所有基站\n";
                    printf("矩形区域的范围是：2000, 4000, 108000, 110000\n");
                    Region regionSEN;
                    initRegion(&regionSEN, 2000, 4000, 108000, 110000);
                    queryArea(&root, &regionSEN);
                    puts("");
                    /****************显示东南角分块树叶西侧的基站********************************/
                    cout << "东南区域西侧的所有基站\n";
                    printf("矩形区域的范围是：-100, 2000, 106000, 108000\n");
                    Region regionSEW;
                    initRegion(&regionSEW, -100, 2000, 106000, 108000);
                    queryArea(&root, &regionSEW);
                    puts("");
                    cout << "********************************************************\n";
                    cout << "\n";
                }
                break;
            case 3:
                printf("任务三如下\n");
                {
                    cout << "********************************************************\n";
                    ElePoint Point1, Point2, Point3;
                    Point1.x = 101000;
                    Point1.y = 23500;
                    Point2.x = 18291;
                    Point2.y = 26354;
                    Point3.x = 85000;
                    Point3.y = 28000;
                    cout << "点一\n";
                    queryEle(root, Point1);
                    cout << "点二\n";
                    queryEle(root, Point2);
                    cout << "点三\n";
                    queryEle(root, Point3);
                    cout << "********************************************************\n";
                    cout << "\n";
                }
                break;
            case 4:
                printf("任务四如下\n");
                {
                    cout << "********************************************************\n";
                    ElePoint Point4, Point5, Point6;
                    Point4.x = 3000;
                    Point4.y = 36900;
                    Point5.x = 70000;
                    Point5.y = 35000;
                    Point6.x = 100000;
                    Point6.y = 7200;
                    cout << "点四\n";
                    queryEle(root, Point4);
                    cout << "点五\n";
                    queryEle(root, Point5);
                    cout << "点六\n";
                    queryEle(root, Point6);
                    cout << "********************************************************\n";
                    puts("");
                }
                break;
            case 5:
                printf("任务五如下\n");
                {
                    cout << "*************************************************************************\n";
                    //先读取移动端的坐标信息，并且存放到容器YDzuobiao中，这里还有两点的斜率信息！
                    for (int i = 0; i < pn; i++) {
                        printf("进入第%02d段轨迹    ", i + 1);
                        printf("当前时间是: (%02d:%02d) \n", YDzuobiao[i].hour, YDzuobiao[i].minute);
                        cout << "***************************************************************************\n";
                        for (auto t: Moves[i]) {
                            //printf("当前时间是：%2d:%02d ",hours,minutes);
                            //cout<<"当前移动坐标为："<<"("<<t.x<<","<<t.y<<")"<<endl;
                            MoveSearch(root, t, i);

                        }
                        cout << "这一段变化的次数为:" << AllJZ << endl;
                        AllJZ = 0;
                        cout << "***************************************************************************\n";
                    }
                }
                break;
            case 6: {
                printf("二分调查轨迹一的进入首个基站和离开时间区域\n");
                ElePoint One = YDzuobiao[0];
                //cout<<One.Begintime<<" "<<One.Endtime;
                for (auto t: Moves[0]) {
                    FindPoint(root, t, 0);
                    if (pflag == 1) {
                        One = t;
                        break;
                    }
                }
                double lv = vp[0];
                double x01 = YDzuobiao[0].x1;
                double y01 = YDzuobiao[0].y1;
                double x0 = JIZHAN->x;
                double y0 = JIZHAN->y;
//    cout<<x01<<" "<<y01<<endl;
//    cout<<lv<<endl;
//    cout<<ltime<<endl;
//    cout<<DIS<<" "<<x0<<" "<<y0<<endl;
                ltime = ltime;
                rtime = ltime + 1;
                while (rtime - ltime > 0.1) {
                    double midtime = (ltime + rtime) / 2;
                    x01 = YDzuobiao[0].x1 + lv * midtime;
                    double NowDis = sqrt(pow(x01 - x0, 2) + pow(y01 - y0, 2));
                    if (NowDis <= DIS) {
                        rtime -= 0.01;
                    } else {
                        ltime += 0.01;
                    }
                }
                // cout<<ltime<<" "<<rtime<<endl;
                cout << "轨迹01进入基站范围时的初始时间为：\n";
                Get2Time(One, 0);
                printf("%.1lf秒\n", rtime);
                puts("***************************************");
                pflag = 0;
                rtime = 0;
                for (auto t: Moves[0]) {
                    FindPoint(root, t, 0);
                    if (pflag == 1 && vflag == 1)break;
                }
                // cout<<ltime<<endl;
                rtime = ltime + 1;
                while (rtime - ltime > 0.1) {
                    double midtime = (rtime + ltime) / 2;
                    x01 = YDzuobiao[0].x1 + lv * midtime;
                    double NowDis = sqrt(pow(x01 - x0, 2) + pow(y01 - y0, 2));
                    if (NowDis >= DIS) {
                        rtime -= 0.01;
                    } else {
                        ltime += 0.01;
                    }
                }
                //cout<<ltime<<" "<<rtime<<endl;
                cout << "轨迹01离开首个基站范围时的初始时间为：\n";
                Get2Time(One, 0);
                printf("%.1lf秒\n", rtime);
                puts("***************************************\n");
            }
                break;
            case 7:
                cout << "查找重叠区域的信号变化过程\n";

                {
                    cout << "先对第三段进行分析:\n";
                    ElePoint Three = YDzuobiao[2];
//    cout<<vp[2]<<endl;
//    cout<<YDzuobiao[2].Begintime<<endl;
//    base(YDzuobiao[2].Begintime);
//    cout<<Three.x1<<" "<<Three.y1<<endl;
                    allnum = 0;
                    for (auto t: Moves[2]) {
                        // cout<<t.x<<" "<<t.y<< endl;
                        FindCover_1(root, t);

                        if (allnum == 2) {
                            Three = t;
                            break;
                        }
                    }
                    double x03 = Three.x;
                    double y03 = Three.y;
//    puts("");
//    cout<<A->index<<" "<<B->index;
//    puts("");
//    cout<<A->x<<" "<<A->y<<" "<<B->x<<" "<<B->y<<endl;
//    cout<<Three.x<<" "<<Three.y<<endl;
//    cout<<A->TrueR<<" "<<B->TrueR<<endl;
                    double d = sqrt(pow((YDzuobiao[2].x1 - Three.x), 2) + pow((YDzuobiao[2].y1 - Three.y), 2));
                    // cout<<d<<endl;
                    double t01 = d / vp[2];
                    rtime = t01 + 1;
                    //cout<<rtime<<endl;
                    while (rtime >= 0) {
                        double dis1, dis2;
                        x03 = YDzuobiao[2].x1 - vp[2] * rtime;
                        dis1 = sqrt(pow((A->x - x03), 2) + pow(A->y - y03, 2));
                        dis2 = sqrt(pow((B->x - x03), 2) + pow(B->y - y03, 2));
                        //cout<<dis1<<" "<<dis2<<endl;
                        if (dis1 < A->TrueR && dis2 < B->TrueR) { rtime = rtime - 0.1; }
                        else break;
                    }
                    int onetime = rtime;
                    //cout<<onetime<<endl;
                    int LEFTTIME = onetime + YDzuobiao[2].Begintime;
                    cout << "首次进入重合区域的时间为： \n";
                    base_2(LEFTTIME);
                    printf("%.1lf秒\n", rtime - onetime);
                    //cout << rtime - onetime << "秒\n";
                    cout << "***************************************************\n";
                    rtime = t01;
                    while (1) {
                        double dis1, dis2;
                        x03 = YDzuobiao[2].x1 - vp[2] * rtime;
                        dis1 = sqrt(pow((A->x - x03), 2) + pow(A->y - y03, 2));
                        dis2 = sqrt(pow((B->x - x03), 2) + pow(B->y - y03, 2));
                        if (dis1 <= A->TrueR && dis2 <= B->TrueR)
                            rtime += 5;
                        else break;
                    }
                    while (rtime >= 0) {
                        double dis1, dis2;
                        x03 = YDzuobiao[2].x1 - vp[2] * rtime;
                        dis1 = sqrt(pow((A->x - x03), 2) + pow(A->y - y03, 2));
                        dis2 = sqrt(pow((B->x - x03), 2) + pow(B->y - y03, 2));
                        if (dis1 < A->TrueR && dis2 >= B->TrueR)
                            rtime = rtime - 0.1;
                        else break;
                    }
//cout<<rtime<<endl;
                    onetime = rtime;
                    LEFTTIME = onetime + YDzuobiao[2].Begintime;
//cout<<LEFTTIME<<endl;
                    cout << "首次离开重合区域的时间为： \n";
                    base_2(LEFTTIME);
                    cout << rtime - onetime << "秒\n";
                    cout << "***************************************************\n";
                    puts("");

//***********************************************************************
                    cout << "对第六段进行分析:\n";
                    ElePoint Six = YDzuobiao[5];
//    cout<<vp[5]<<endl;
//    cout<<YDzuobiao[5].Begintime<<endl;
//    base(YDzuobiao[5].Begintime);
                    // cout<<Three.x1<<" "<<Three.y1<<endl;
                    allnum = 0;
                    for (auto t: Moves[5]) {
                        //   cout<<t.x<<" "<<t.y<<endl;
                        FindCover_1(root, t);
                        if (allnum == 2) {
                            Six = t;
                            break;
                        }
                    }
                    // cout<<Six.x<<" "<<Six.y<<endl;
                    int linshi_flag = 1;
                    if (allnum < 2) {
                        cout << "没有重合部分\n";
                        linshi_flag = 0;
                        //goto FLI;
                    }
                    if (linshi_flag) {
                        double x06 = Six.x;
                        double y06 = Six.y;
                        // cout<<x06<<" "<<y06;
//    puts("");
//    cout<<A->index<<" "<<B->index;
//    puts("");
//    cout<<A->x<<" "<<A->y<<" "<<B->x<<" "<<B->y<<endl;
//    cout<<Six.x<<" "<<Six.y<<endl;
//    cout<<A->TrueR<<" "<<B->TrueR<<endl;
                        d = sqrt(pow((YDzuobiao[5].x1 - Six.x), 2) + pow((YDzuobiao[5].y1 - Six.y), 2));
                        //cout<<d<<endl;
                        t01 = d / vp[5];
                        double seita = ::atan(YDzuobiao[5].k);
                        double dx = abs(::cos(seita));
                        double dy = abs(::sin(seita));
                        // cout<<t01<<endl;
                        rtime = t01;
                        // cout<<rtime<<endl;
                        while (rtime >= 0) {
                            double dis1, dis2;
                            x06 = YDzuobiao[5].x1 + vp[5] * rtime * dx;
                            y06 = YDzuobiao[5].y1 + vp[5] * rtime * dy;
                            dis1 = sqrt(pow((A->x - x06), 2) + pow(A->y - y06, 2));
                            dis2 = sqrt(pow((B->x - x06), 2) + pow(B->y - y06, 2));
                            //cout<<dis1<<" "<<dis2<<endl;
                            if (dis1 < A->TrueR && dis2 < B->TrueR) { rtime = rtime - 0.01; }
                            else break;
                        }
                        int twotime = rtime;
                        int LLEFTIME = twotime + YDzuobiao[5].Begintime;
                        cout << "首次进入重合区域的时间为： \n";
                        base_2(LLEFTIME);
                        printf("%.2lf秒\n", rtime - twotime);
                        cout << "***************************************************\n";
                        rtime = t01;
                        while (1) {
                            double dis1, dis2;
                            x06 = YDzuobiao[5].x1 + vp[5] * rtime * dx;
                            y06 = YDzuobiao[5].y1 + vp[5] * rtime * dy;
                            dis1 = sqrt(pow((A->x - x06), 2) + pow(A->y - y06, 2));
                            dis2 = sqrt(pow((B->x - x06), 2) + pow(B->y - y06, 2));
                            if (dis1 < A->TrueR && dis2 < B->TrueR)
                                rtime += 1;
                            else break;
                        }
                        while (rtime >= 0) {
                            double dis1, dis2;
                            x06 = YDzuobiao[5].x1 + vp[5] * rtime * dx;
                            y06 = YDzuobiao[5].y1 + vp[5] * rtime * dy;
                            dis1 = sqrt(pow((A->x - x06), 2) + pow(A->y - y06, 2));
                            dis2 = sqrt(pow((B->x - x06), 2) + pow(B->y - y06, 2));
                            if (dis1 < A->TrueR && dis2 > B->TrueR)
                                rtime = rtime - 0.01;
                            else break;
                        }
//cout<<rtime;
                        twotime = rtime;
                        LLEFTIME = twotime + YDzuobiao[5].Begintime;
//cout<<LEFTTIME<<endl;
                        cout << "首次离开重合区域的时间为： \n";
                        base_2(LLEFTIME);
                        printf("%.2lf秒\n", rtime - twotime);
                    } else {
                        cout << "***************************************************\n";
                        puts("");
                    }
                }
                break;

            case 8: {
                ::puts("");
                cout << "升级功能的实现：\n";
                cout << "先对第十二段轨迹进行分析：\n";
                double RTIME = 0, LTIME = 1e9;
                cout << "***************************************\n";
                for (auto t: WJZzuobiao) {
                    // cout<<GetDis(t)<<" ";
                    int CostTime = GetDis(t) / (t.v / 3.6);
                    //  cout<<GetDis(t)/(t.v/3.6)<<" ";
                    t.Endsecond = CostTime % 60;
                    t.Endminute = (CostTime / 60 + t.minute) % 60;
                    t.Endhour = (CostTime / 60 + t.minute) / 60 + t.hour;
                    t.Endtime = t.Endhour * 3600 + t.Endminute * 60 + t.Endsecond;
                    //cout<<t.Begintime<<" "<<t.Endtime<<endl;
                    if (t.Endtime >= YDzuobiao[11].Begintime && t.Begintime <= YDzuobiao[11].Endtime) {
//
//       base(t.Endtime);
                        printf("这是在时间区间上与终端有交集的伪基站的编号： ");
                        cout << t.index << endl;
                        cout << "终端所连接伪基站的时间序列如下：\n";
                        //先统一时间区间，再研究空间距离

                        double SearchTime_1 = max(t.Begintime, YDzuobiao[11].Begintime);
                        double SearchTime_2 = min(t.Endtime, YDzuobiao[11].Endtime);
//        base(SearchTime_1);
//cout<<SearchTime_1<<" "<<SearchTime_2<<endl;
                        for (double i = SearchTime_1; i <= SearchTime_2; i += 0.1)//在这个时间区间进行研究
                        {
                            double d1 = 1.0 * (i - YDzuobiao[11].Begintime) * vp[11];
                            double d2 = 1.0 * (i - t.Begintime) * (t.v / 3.6);

                            //  cout<<d1<<" "<<d2<<endl;//d1和d2是没有问题的。
                            // cout<<YDzuobiao[11].k<<endl;
                            double dis = 0;
                            double x01, x02, y01, y02;
                            //确定每秒中的终端的坐标x1,y1;
                            if (YDzuobiao[11].k == 0) {
                                if (YDzuobiao[11].x2 > YDzuobiao[11].x1) {
                                    y01 = YDzuobiao[11].y1;
                                    x01 = YDzuobiao[11].x1 + d1;
                                } else {
                                    y01 = YDzuobiao[11].y1;
                                    x02 = YDzuobiao[11].x1 - d1;
                                }
                            } else if (YDzuobiao[11].k == 6666) {
                                if (YDzuobiao[11].y1 < YDzuobiao[11].y2) {
                                    x01 = YDzuobiao[11].x1;
                                    y01 = YDzuobiao[11].y1 + d1;
                                } else {
                                    x01 = YDzuobiao[11].x1;
                                    y01 = YDzuobiao[11].y1 - d1;
                                }
                            } else {
                                double sita = atan(YDzuobiao[11].k);
                                if (YDzuobiao[11].k > 0) {
                                    if (YDzuobiao[11].x1 < YDzuobiao[11].x2) {
                                        x01 = YDzuobiao[11].x1 + d1 * abs(cos(sita));
                                        y01 = YDzuobiao[11].y1 + d1 * abs(sin(sita));
                                    } else {
                                        x01 = YDzuobiao[11].x1 - d1 * abs(cos(sita));
                                        y01 = YDzuobiao[11].y1 - d1 * abs(sin(sita));
                                    }
                                } else {
                                    if (YDzuobiao[11].x1 < YDzuobiao[11].x2) {
                                        x01 = YDzuobiao[11].x1 + d1 * abs(cos(sita));
                                        y01 = YDzuobiao[11].y1 - d1 * abs(sin(sita));
                                    } else {
                                        x01 = YDzuobiao[11].x1 - d1 * abs(cos(sita));
                                        y01 = YDzuobiao[11].y1 + d1 * abs(sin(sita));
                                    }
                                }
                            }
                            //确定每秒钟伪基站的坐标x2,y2;
                            if (t.k == 0) {
                                if (t.x2 > t.x1) {
                                    y02 = t.y1;
                                    x02 = t.x1 + d2;
                                } else {
                                    y02 = t.y1;
                                    x02 = t.x1 - d2;
                                }
                            } else if (t.k == 6666) {
                                if (t.y1 < t.y2) {
                                    x02 = t.x1;
                                    y02 = t.y1 + d2;
                                } else {
                                    x02 = t.x1;
                                    y02 = t.y1 - d2;
                                }
                            } else {
                                double sita = atan(t.k);
                                if (t.k > 0) {
                                    if (t.x1 < t.x2) {
                                        x02 = t.x1 + d2 * abs(cos(sita));
                                        y02 = t.y1 + d2 * abs(sin(sita));
                                    } else {
                                        x02 = t.x1 - d2 * cos(sita);
                                        y02 = t.y1 - d2 * sin(sita);
                                    }
                                } else {
                                    if (t.x1 < t.x2) {
                                        x02 = t.x1 + d2 * abs(cos(sita));
                                        y02 = t.y1 - d2 * abs(sin(sita));
                                    } else {
                                        x02 = t.x1 - d2 * cos(sita);
                                        y02 = t.y1 + d2 * sin(sita);
                                    }
                                }
                            }

                            dis = sqrt(pow((x01 - x02), 2) + pow((y01 - y02), 2));
                            if (dis <= 40) {
                                printf("此时的距离为: %.2lf米\t  ", dis);
                                printf("此时的时间为：");
                                int zhengshu = i;
                                int h = zhengshu / 3600;
                                int mi = (zhengshu - h * 3600) / 60;
                                int se = zhengshu % 60;
                                double xiaoshu = i - zhengshu;
                                printf("%02d时%02d分%02d秒+%.2lf秒\n", h, mi, se, xiaoshu);
                                //int tem =(i+SearchTime_1);
//                                        base(i);
                                LTIME = min(LTIME, i);
                                RTIME = max(RTIME, i);
                            }
                        }
                    }
                }
                cout << "持续的时间为:" << RTIME - LTIME << "秒\n";
                cout << "***************************************\n";
                cout << "再对第九段轨迹进行分析：\n";
                LTIME = 1e9;
                RTIME = 0;
                for (auto t: WJZzuobiao) {
                    // cout<<GetDis(t)<<" ";
                    int CostTime = GetDis(t) / (t.v / 3.6);
                    //  cout<<GetDis(t)/(t.v/3.6)<<" ";
                    t.Endsecond = CostTime % 60;
                    t.Endminute = (CostTime / 60 + t.minute) % 60;
                    t.Endhour = (CostTime / 60 + t.minute) / 60 + t.hour;
                    t.Endtime = t.Endhour * 3600 + t.Endminute * 60 + t.Endsecond;
                    //cout<<t.Begintime<<" "<<t.Endtime<<endl;
                    if (t.Endtime >= YDzuobiao[8].Begintime && t.Begintime <= YDzuobiao[8].Endtime) {
                        printf("这是在时间区间上与终端有交集的伪基站的编号： ");
                        cout << t.index << endl;
                        cout << "终端所连接伪基站的时间序列如下：\n";
                        double SearchTime_1 = max(t.Begintime, YDzuobiao[8].Begintime);
                        double SearchTime_2 = min(t.Endtime, YDzuobiao[8].Endtime);
                        cout << SearchTime_1 << " " << SearchTime_2 << endl;
//        base(SearchTime_1);
                        for (double i = SearchTime_1; i <= SearchTime_2; i += 0.1)//在这个时间区间进行研究
                        {
                            double d1 = (i - YDzuobiao[8].Begintime) * vp[8];
                            double d2 = (i - t.Begintime) * (t.v / 3.6);
                            //cout<<d1<<" "<<d2<<endl;//d1和d2是没有问题的。
                            double dis = 0;
                            double x01, x02, y01, y02;
                            //确定每秒中的终端的坐标x1,y1;
                            if (YDzuobiao[8].k == 0) {
                                if (YDzuobiao[8].x2 > YDzuobiao[8].x1) {
                                    y01 = YDzuobiao[8].y1;
                                    x01 = YDzuobiao[8].x1 + d1;
                                } else {
                                    y01 = YDzuobiao[8].y1;
                                    x02 = YDzuobiao[8].x1 - d1;
                                }
                            } else if (YDzuobiao[8].k == 6666) {
                                if (YDzuobiao[8].y1 < YDzuobiao[11].y2) {
                                    x01 = YDzuobiao[8].x1;
                                    y01 = YDzuobiao[8].y1 + d1;
                                } else {
                                    x01 = YDzuobiao[8].x1;
                                    y01 = YDzuobiao[8].y1 - d1;
                                }
                            } else {
                                double sita = atan(YDzuobiao[8].k);
                                // cout<<sita<<" "<<cos(sita)<<" "<<sin(sita)<<endl;
                                if (YDzuobiao[8].k > 0) {
                                    if (YDzuobiao[8].x1 < YDzuobiao[8].x2) {
                                        x01 = YDzuobiao[8].x1 + d1 * abs(cos(sita));
                                        y01 = YDzuobiao[8].y1 + d1 * abs(sin(sita));
                                    } else {
                                        x01 = YDzuobiao[8].x1 - d1 * abs(cos(sita));
                                        y01 = YDzuobiao[8].y1 - d1 * abs(sin(sita));
                                    }
                                } else {
                                    if (YDzuobiao[8].x1 < YDzuobiao[8].x2) {
                                        //cout<<"6\n";
                                        x01 = YDzuobiao[8].x1 + d1 * abs(cos(sita));
                                        y01 = YDzuobiao[8].y1 - d1 * abs(sin(sita));
                                    } else {
                                        x01 = YDzuobiao[8].x1 - d1 * abs(cos(sita));
                                        y01 = YDzuobiao[8].y1 + d1 * abs(sin(sita));
                                    }
                                }
                            }
                            //确定每秒钟伪基站的坐标x2,y2;
                            if (t.k == 0) {
                                if (t.x2 > t.x1) {
                                    y02 = t.y1;
                                    x02 = t.x1 + d2;
                                } else {
                                    y02 = t.y1;
                                    x02 = t.x1 - d2;
                                }
                            } else if (t.k == 6666) {
                                if (t.y1 < t.y2) {
                                    x02 = t.x1;
                                    y02 = t.y1 + d2;
                                } else {
                                    x02 = t.x1;
                                    y02 = t.y1 - d2;
                                }
                            } else {
                                double sita = atan(t.k);
                                if (t.k > 0) {
                                    if (t.x1 < t.x2) {
                                        x01 = t.x1 + d2 * abs(cos(sita));
                                        y01 = t.y1 + d2 * abs(sin(sita));
                                    } else {
                                        x02 = t.x1 - d2 * abs(cos(sita));
                                        y02 = t.y1 - d2 * abs(sin(sita));
                                    }
                                } else {
                                    if (t.x1 < t.x2) {
                                        //cout<<"6\n";
                                        x02 = t.x1 + d2 * abs(cos(sita));
                                        y02 = t.y1 - d2 * abs(sin(sita));
                                    } else {
                                        x02 = t.x1 - d2 * abs(cos(sita));
                                        y02 = t.y1 + d2 * abs(sin(sita));
                                    }
                                }
                            }
                            dis = sqrt(pow((x01 - x02), 2) + pow((y01 - y02), 2));
                            if (dis <= 40) {
                                printf("此时的距离为：%lf ", dis);
                                printf("此时的时间为：");
                                int zhengshu = i;
                                int h = zhengshu / 3600;
                                int mi = (zhengshu - h * 3600) / 60;
                                int se = zhengshu % 60;
                                double xiaoshu = i - zhengshu;
                                printf("%02d时%02d分%02d秒+%.2lf秒\n", h, mi, se, xiaoshu);
                                LTIME = min(LTIME, i);
                                RTIME = max(RTIME, i);
                            }
                        }
                    }

                }
                cout << "持续的时间为:" << RTIME - LTIME << "秒\n";
                break;
            }
            case 9: {
                double l, r, n, s;
                printf("请输入区域的左边界：\n");
                cout << "左边界: ";
                cin >> l;
                printf("请输入区域的右边界：\n");
                cout << "右边界: ";
                cin >> r;
                printf("请输入区域的下边界：\n");
                cout << "下边界: ";
                cin >> s;
                printf("请输入区域的上边界：\n");
                cout << "上边界: ";
                cin >> n;
                cout << "查询区域的基站如下：\n";
                Region SeaR;
                initRegion(&SeaR, s, n, l, r);
                queryArea(&root, &SeaR);
                cout << "******************************************\n";
                break;
            }
            case 0: {
                printf("结束查询，欢迎下次使用!\n");
                return 0;
            }
        }
    }
}
