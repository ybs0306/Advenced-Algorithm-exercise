#include<iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int leftShift(int);
int* getPos(int,int*);
int checkAdj(int*);

int main()
{
	//int randnum;
	
					
	//srand((unsigned)time(0)); 
    //randnum = (rand()%13)+1; 
    
    int testcase,*userInput,*position,twoPos[13];
    cin>>testcase;
	userInput=new int[testcase];
	
	for(int i=0;i<testcase;i++)
		cin>>userInput[i];
	
	for(int i=0;i<13;i++)
		twoPos[i]=leftShift(i);
		
	for(int i=0;i<testcase;i++)
	{
		position=getPos(userInput[i],twoPos);
		//cout<<"position[0]="<<position[0]<<endl;
		//cout<<"position[1]="<<position[1]<<endl;
		userInput[i]=checkAdj(position);
	}
	
	for(int i=0;i<testcase;i++)
	{
		cout<<userInput[i]<<" ";
	}
	//int *d=getPos(64+2,twoPos);
	//cout<<d[0]<<d[1];
} 

int leftShift(int pos)
{
	if(pos==0)
		return 1;
	else 
		return 2<<pos-1;
}

int* getPos(int num,int *twoPos)
{
	int *pos=new int[13],j=1;
	for(int i=12;i>=0;i--)
	{
		if(num==0)
			break;
			
		if(num>=twoPos[i])
		{
			num=num-twoPos[i];
			pos[j]=i;
			j++;
		}
	}
	pos[0]=j-1;
	for(int i=0;i<14;i++)
		cout << pos[0] << ' ';
	/*cout<<"in getpos pos[0]="<<pos[0]<<endl;
	cout<<"in getpos pos[1]="<<pos[1]<<endl;
	cout<<"in getpos pos[2]="<<pos[2]<<endl;*/
	return pos;
}

int checkAdj(int *position)
{
	int map[13][13]={{0,0,1,1,0,0,0,0,0,0,0,0,0},
					 {0,0,1,0,0,1,0,0,0,0,0,0,0},
					 {1,1,0,1,0,1,1,0,0,0,0,0,0},
					 {1,0,1,0,1,0,1,1,0,0,0,0,0},
					 {0,0,0,1,0,0,0,1,0,0,0,0,0},
					 {0,1,1,0,0,0,1,0,1,1,0,0,0},
					 {0,0,1,1,0,1,0,1,0,1,1,0,0},
					 {0,0,0,1,1,0,1,0,0,0,1,1,0},
					 {0,0,0,0,0,1,0,0,0,1,0,0,0},
					 {0,0,0,0,0,1,1,0,1,0,1,0,1},
					 {0,0,0,0,0,0,1,1,0,1,0,1,1},
					 {0,0,0,0,0,0,0,1,0,0,1,0,0},
					 {0,0,0,0,0,0,0,0,0,1,1,0,0}};

	switch(position[0])
	{
		case 1:
			return 0;
		case 2:
			return 1;
		case 3:
			if(map[position[1]][position[2]]||map[position[2]][position[3]]||map[position[1]][position[3]])
				return 1;
			else
				return 0;
	}
}
