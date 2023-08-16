#include <bits/stdc++.h>
using namespace std;

const int MOD=1e18;

void dd(int ti)//等待
{
	long long now=time(0)%MOD;
	while(time(0)%MOD<now+ti)
	{

	}
}

int n,m;//真人人数、人机人数
string player[25];//玩家昵称
bool fl[25];//0:玩家存活 1:玩家淘汰
int bomb;//炸弹数字
int l,r;//左边界、右边界
bool flag;//标记这一局完后是否有玩家淘汰
string numt;//玩家输入的数（防字符）
int num;//玩家输入的数

void player_init()//玩家初始化
{
	cout<<"玩家昵称：\n";
	for(int i=1;i<=n;i++)
		cin>>player[i];
	cout<<"人机昵称：\n";
	for(int i=1;i<=m;i++)
	{
		player[n+i]="机器人";
		player[n+i]+=i/10+'0';
		player[n+i]+=i%10+'0';
		cout<<player[n+i]<<endl;
	}
}

void player_in(int i)//玩家输入
{
	if(i<=n)//真人玩家
	{
		cin>>numt;
	}
	else//人机玩家
	{
		dd(1);//等待1s
		srand(time(0));//为确保随机性，每次随机前都更新一下种子
		num=rand()%(r-l+1)+l;//l~r随机数
		cout<<num<<endl;
		numt=to_string(num);//将num转为numt，以便后续操作
		dd(1);//等待1s
	}
}

void player_op(int T,int t,int i)//玩家操作
{
	while(1)//如果输入错误就一直停留再循环，否则退出循环
	{
		printf("\t\t第%d.%d.%d局\n",T,t,i);
		printf("\t\t%d~%d\n",l,r);
		cout<<"\t\t"<<player[i]<<":";
		player_in(i);
		bool Flag=1;
		for(int i=0;i<numt.size();i++)
			if(!isdigit(numt[i]))//判断每一位是否合法
			{
				Flag=0;
				break;
			}
		if(!Flag)//包含其他字符
		{
			cout<<"\t\t包含非数字字符,请重新输入。"<<endl;
			dd(1);//等待1s
			continue;
		}
		num=stoi(numt);
		if(num>r||num<l)//不在范围
		{
			cout<<"\t\t不在范围内,请重新输入。"<<endl;
			dd(1);//等待1s
			continue;
		}
		if(num==bomb)//猜中炸弹数字
		{
			fl[i]=1;
			flag=1;
			cout<<"回合结束\n\t玩家 "<<player[i]<<" 淘汰。\n\t恭喜玩家 ";
			int cnt=0;//存活玩家数量
			for(int k=1;k<=n+m;k++)//输出存活玩家
				if(!fl[k])
				{
					cnt++;
					if(cnt>1)//如果不是第一个的话在前面加上顿号分隔玩家昵称
						cout<<"、";
					cout<<player[k];
				}
			cout<<" 存活。\n";
			dd(2);//等待2s
			break;
		}
		else if(num<bomb)//猜小了
		{
			cout<<"\t\t猜小了"<<endl;
			l=num+1;
		}
		else//猜大了
		{
			cout<<"\t\t猜大了"<<endl;
			r=num-1;
		}
		cout<<endl;
		break;
	}
}

void win()//结算
{
	int cnt=0;//存活人数
	int ans;
	for(int i=1;i<=n+m;i++)
	{
		if(!fl[i])
		{
			cnt++;
			ans=i;
		}
	}
	if(cnt==1)//如果只剩一人存活
	{
		cout<<"恭喜玩家 "<<player[ans]<<" 胜出！";
		exit(0);//结束程序
	}
}

void rule()//规则
{
	printf("数字炸弹\n");
	printf(
		"游戏规则：\n"
		"	1.多人轮流输入范围内的数字（左闭右闭）。\n"
		"	2.如果不是炸弹，数字范围缩小：\n"
		"		(1)输大了，右边界更新为那个数。\n"
		"		(2)输小了，左边界更新为那个数。\n"
		"	3.如果是炸弹数字，那个人淘汰，其他人继续。\n"
		"	4.最后只剩一个人时那个人获胜。\n"
	);
}

int main()
{
	srand(time(0));
	rule();
	dd(3);//等待3s
	while(1)
	{
		cout<<"玩家人数(上限10人)：";
		cin>>n;
		cout<<"人机人数(上限10人)：";
		cin>>m;
		if(n>10||m>10)
		{
			cout<<"人数超限,请重新输入。\n";
			dd(1);
			continue;
		}
		break;
	}
	player_init();//玩家初始化:第24行
	dd(1);//等待1s
	for(int T=1;T<=n+m;T++)
	{
		printf("第%d回合\n",T);
		flag=0;
		srand(time(0));//为确保随机性，每次随机前都更新一下种子
		bomb=rand()%100+1;//炸弹数字初始为1~100随机性
		l=1,r=100;//边界初始化
		for(int t=1;;t++)
		{
			cout<<"\t";
			printf("第%d.%d圈\n",T,t);
			for(int i=1;i<=n+m;i++)
			{
				if(fl[i])//如果这个人已经被淘汰，直接下一个
				{
					continue;
				}
				player_op(T,t,i);//玩家操作:第57行
				dd(1);//等待1s
				win();//结算:第118行
				if(flag)//如果已经有玩家死了，直接进入下一回合
				{
					break;
				}
			}
			if(flag)//如果已经有玩家死了，直接进入下一回合
			{
				break;
			}
		}
		win();//结算:第118行
	}
	return 0;
}