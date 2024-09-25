#include<iostream>
#include<cmath>
#include<fstream>
using namespace std; 
struct point 
{
	float x;
	float y;
};
struct tree
{
	point position;
	int type;
};
struct plantation
{
	tree trees[10000];
	int n;			//number of trees
};
int Countnumberoftree(plantation p,int type)
{
	int total=0;
	for (int i=0;i<p.n;i++)
	{
		if(p.trees[i].type==type)
			total++;				//coffe 0, tea 1
	}
	return total;
}
int countCoffeTree(plantation p)
{
	return Countnumberoftree(p,0);
}
int countTeaTree(plantation p)
{
	return Countnumberoftree(p,1);
}
void findUpperLeft(plantation p,point& a1)
{
	float xmin=p.trees[0].position.x,ymax=p.trees[0].position.y;
	for (int i=0;i<p.n;i++)
	{
		if(xmin>p.trees[i].position.x)
			xmin= p.trees[i].position.x;
		if(ymax<p.trees[i].position.y)
			ymax=p.trees[i].position.y;
	}
	a1.x=xmin;
	a1.y=ymax;
}
void findLowerRight(plantation p,point& a2)
{
	float xmax=p.trees[0].position.x,ymin=p.trees[0].position.y;
	for(int i=0;i<p.n;i++)
	{
		if(xmax<p.trees[i].position.x)
			xmax=p.trees[i].position.x;
		if(ymin>p.trees[i].position.y)
			ymin=p.trees[i].position.y;
	}
	a2.x=xmax;
	a2.y=ymin;
}
float CalcFenceLength(plantation p)
{
	float Total;
	point upper,lower;
	findUpperLeft(p,upper);
	findLowerRight(p,lower);
	Total=((lower.x-upper.x)+(upper.y-lower.y))*2;
	return Total;
}
void findPump(plantation p,point& pump)
{
	float total_x=0,total_y=0;
	for (int i=0;i<p.n;i++)
	{
		total_x=total_x+p.trees[i].position.x; 
		total_y=total_y+p.trees[i].position.y;
	}
	float x_arv,y_arv;
	x_arv=total_x/p.n;
	y_arv=total_y/p.n;
	point a3;					// tim trung binh cong de tim ra vi tri o giua cac cay la a3
	a3.x=x_arv;
	a3.y=y_arv;			
	float MinDistance;				//Tim cay co khoang cach nho nhat so voi a3 va pump dat ngay cho do
	MinDistance=sqrt(pow(a3.x-p.trees[0].position.x,2)+pow(a3.y-p.trees[0].position.y,2));	//dat khoang cach nho nhat la cay 0
	pump.x=p.trees[0].position.x;
	pump.y=p.trees[0].position.y;
	for(int i=1;i<p.n;i++)
	{
		if(sqrt(pow(a3.x-p.trees[i].position.x,2)+pow(a3.y-p.trees[i].position.y,2))>MinDistance)
		{
			MinDistance=sqrt(pow(a3.x-p.trees[i].position.x,2)+pow(a3.y-p.trees[i].position.y,2));// Sau do so sanh voi nhau va thay doi lan luot ket qua
			pump.x=p.trees[i].position.x;
			pump.y=p.trees[i].position.y;
		}	
	}
}
float CalculateLength(plantation p,point& pump)
{
	float distance;
	float Sum=0;
	for(int i=0;i<p.n;i++)
	{
		distance=sqrt(pow(pump.x-p.trees[i].position.x,2)+pow(pump.y-p.trees[i].position.y,2));//Tu do cong cac khoang cach lai voi nhau
		Sum=Sum+distance;
		distance=0;
	}
	return Sum;
}
int main()
{
	plantation vuon;
	point pump;
	ifstream f1("NongTrai.in.txt");
	if(!f1.is_open())
	{
        cout << "Can not open file" << endl;
    }
    else
    {
    	f1>>vuon.n;
    	for(int i=0;i<vuon.n;i++)
    	{
    		f1>>vuon.trees[i].position.x;
    		f1>>vuon.trees[i].position.y;
    		f1>>vuon.trees[i].type;
		}
		ofstream result("NongTrai.out.txt");
			{
				result<<countCoffeTree(vuon)<<" "<<countTeaTree(vuon)<<endl;
				result<<CalcFenceLength(vuon)<<endl;
				findPump(vuon,pump);
				result<<CalculateLength(vuon,pump)<<endl;
			}
			result.close();
		f1.close();
	}
	return 0;
}
