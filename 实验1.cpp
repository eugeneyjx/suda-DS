#include <iostream>
using namespace std;
const int maxrow=20, maxcol=60;
class Life
{
	int grid[maxrow+2][maxcol+2];
	int neighbor_count(int row,int col)
	{
		int count=0;
		for(int i=row-1;i<=row+1;i++)
			for(int j=col-1;j<=col+1;j++)
				count+=grid[i][j];
		count-=grid[row][col];
		return count;
	}
public:
	void initialize()
	{
		int r,c;
		for(r=0;r<=maxrow+1;r++)
			for(c=0;c<=maxcol+1;c++)
				grid[r][c]=0;
		cout<<"List the coordinates for living cells.\n";
		cout<<"Terminate the list with the special pair '-1 -1'\n";
		cin>>r>>c;
		while(r!=-1||c!=-1)
		{
			if(r>=1&&r<=maxrow)
			{
				if(c>=1&&c<=maxcol) 
				{
					grid[r][c]=1;
				}
				else 
					cout<<"Colomn "<<c<<" is out of range."<<endl;
			}
			else 
				cout<<"Row "<<r<<" is out of range."<<endl;
			cin>>r>>c;
		}
	}

	void print()
	{
		int r,c;
		cout<<"\nThe current configuration is :\n";
		for(r=1;r<=maxrow;r++)
		{
			for(c=1;c<=maxcol;c++)
			{	
				if(grid[r][c]==1) cout<<"*";
				else cout<<" ";
			}
			cout<<endl;
		}
		cout<<endl;
	}

	void update()
	{
		int r,c,new_grid[maxrow+2][maxcol+2];
		for(r=1;r<=maxrow;r++)
			for(c=1;c<=maxcol;c++)
				switch(neighbor_count(r,c))
				{
					case 2: new_grid[r][c]=grid[r][c]; break;
					case 3: new_grid[r][c]=1; break;
					default: new_grid[r][c]=0;
				}
		for(r=1; r<=maxrow;r++)
			for (c=1;c<=maxcol;c++)
				grid[r][c]=new_grid[r][c];
	}
};

bool user_says_yes()
{
	int c;
	bool ini_response=true;
	do
	{
		if(ini_response) cout<<"y or n?"<<endl;
		else cout<<"Type in y or n"<<endl;
		do
		{
			c=cin.get();
		} while(c=='\n'||c==' '||c=='\t');
		ini_response=false;
	} while (c!='y'&&c!='Y'&&c!='n'&&c!='N');
	return (c=='y'||c=='Y');
}

int main()
{
	Life configuration;
	cout<<"Welcome to Game of Life.\n";
	cout<<"This game uses a grid of size "<<maxrow<<" by "<<maxcol<<" in which each\n";
	cout<<"cell can either be occupied by an organism or not.\n";
	cout<<"The occupied cells change from generation to generation according to how many neighboring cells are alive.\n";
	configuration.initialize();
	configuration.print();
	cout<<"Continue?"<<endl;
	while(user_says_yes())
	{
		configuration.update();
		configuration.print();
		cout<<"Continue?"<<endl;
	}
}
