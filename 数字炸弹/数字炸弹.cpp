#include <bits/stdc++.h>
using namespace std;

const int MOD=1e18;

void dd(int ti)//�ȴ�
{
	long long now=time(0)%MOD;
	while(time(0)%MOD<now+ti)
	{

	}
}

int n,m;//�����������˻�����
string player[25];//����ǳ�
bool fl[25];//0:��Ҵ�� 1:�����̭
int bomb;//ը������
int l,r;//��߽硢�ұ߽�
bool flag;//�����һ������Ƿ��������̭
string numt;//���������������ַ���
int num;//����������

void player_init()//��ҳ�ʼ��
{
	cout<<"����ǳƣ�\n";
	for(int i=1;i<=n;i++)
		cin>>player[i];
	cout<<"�˻��ǳƣ�\n";
	for(int i=1;i<=m;i++)
	{
		player[n+i]="������";
		player[n+i]+=i/10+'0';
		player[n+i]+=i%10+'0';
		cout<<player[n+i]<<endl;
	}
}

void player_in(int i)//�������
{
	if(i<=n)//�������
	{
		cin>>numt;
	}
	else//�˻����
	{
		dd(1);//�ȴ�1s
		srand(time(0));//Ϊȷ������ԣ�ÿ�����ǰ������һ������
		num=rand()%(r-l+1)+l;//l~r�����
		cout<<num<<endl;
		numt=to_string(num);//��numתΪnumt���Ա��������
		dd(1);//�ȴ�1s
	}
}

void player_op(int T,int t,int i)//��Ҳ���
{
	while(1)//�����������һֱͣ����ѭ���������˳�ѭ��
	{
		printf("\t\t��%d.%d.%d��\n",T,t,i);
		printf("\t\t%d~%d\n",l,r);
		cout<<"\t\t"<<player[i]<<":";
		player_in(i);
		bool Flag=1;
		for(int i=0;i<numt.size();i++)
			if(!isdigit(numt[i]))//�ж�ÿһλ�Ƿ�Ϸ�
			{
				Flag=0;
				break;
			}
		if(!Flag)//���������ַ�
		{
			cout<<"\t\t�����������ַ�,���������롣"<<endl;
			dd(1);//�ȴ�1s
			continue;
		}
		num=stoi(numt);
		if(num>r||num<l)//���ڷ�Χ
		{
			cout<<"\t\t���ڷ�Χ��,���������롣"<<endl;
			dd(1);//�ȴ�1s
			continue;
		}
		if(num==bomb)//����ը������
		{
			fl[i]=1;
			flag=1;
			cout<<"�غϽ���\n\t��� "<<player[i]<<" ��̭��\n\t��ϲ��� ";
			int cnt=0;//����������
			for(int k=1;k<=n+m;k++)//���������
				if(!fl[k])
				{
					cnt++;
					if(cnt>1)//������ǵ�һ���Ļ���ǰ����϶ٺŷָ�����ǳ�
						cout<<"��";
					cout<<player[k];
				}
			cout<<" ��\n";
			dd(2);//�ȴ�2s
			break;
		}
		else if(num<bomb)//��С��
		{
			cout<<"\t\t��С��"<<endl;
			l=num+1;
		}
		else//�´���
		{
			cout<<"\t\t�´���"<<endl;
			r=num-1;
		}
		cout<<endl;
		break;
	}
}

void win()//����
{
	int cnt=0;//�������
	int ans;
	for(int i=1;i<=n+m;i++)
	{
		if(!fl[i])
		{
			cnt++;
			ans=i;
		}
	}
	if(cnt==1)//���ֻʣһ�˴��
	{
		cout<<"��ϲ��� "<<player[ans]<<" ʤ����";
		exit(0);//��������
	}
}

void rule()//����
{
	printf("����ը��\n");
	printf(
		"��Ϸ����\n"
		"	1.�����������뷶Χ�ڵ����֣�����ұգ���\n"
		"	2.�������ը�������ַ�Χ��С��\n"
		"		(1)����ˣ��ұ߽����Ϊ�Ǹ�����\n"
		"		(2)��С�ˣ���߽����Ϊ�Ǹ�����\n"
		"	3.�����ը�����֣��Ǹ�����̭�������˼�����\n"
		"	4.���ֻʣһ����ʱ�Ǹ��˻�ʤ��\n"
	);
}

int main()
{
	srand(time(0));
	rule();
	dd(3);//�ȴ�3s
	while(1)
	{
		cout<<"�������(����10��)��";
		cin>>n;
		cout<<"�˻�����(����10��)��";
		cin>>m;
		if(n>10||m>10)
		{
			cout<<"��������,���������롣\n";
			dd(1);
			continue;
		}
		break;
	}
	player_init();//��ҳ�ʼ��:��24��
	dd(1);//�ȴ�1s
	for(int T=1;T<=n+m;T++)
	{
		printf("��%d�غ�\n",T);
		flag=0;
		srand(time(0));//Ϊȷ������ԣ�ÿ�����ǰ������һ������
		bomb=rand()%100+1;//ը�����ֳ�ʼΪ1~100�����
		l=1,r=100;//�߽��ʼ��
		for(int t=1;;t++)
		{
			cout<<"\t";
			printf("��%d.%dȦ\n",T,t);
			for(int i=1;i<=n+m;i++)
			{
				if(fl[i])//���������Ѿ�����̭��ֱ����һ��
				{
					continue;
				}
				player_op(T,t,i);//��Ҳ���:��57��
				dd(1);//�ȴ�1s
				win();//����:��118��
				if(flag)//����Ѿ���������ˣ�ֱ�ӽ�����һ�غ�
				{
					break;
				}
			}
			if(flag)//����Ѿ���������ˣ�ֱ�ӽ�����һ�غ�
			{
				break;
			}
		}
		win();//����:��118��
	}
	return 0;
}