#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
int main()
{
	ifstream in;
	in.open("pmts");
	int n;
	in>>n;
	cout<<":mixt vacuum 1e-9 1 G4_AIR 1"<<endl;
	cout<<":volu hall BOX 0.7*m 0.7*m 0.7*m  vacuum"<<endl;

	double out[n][7];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<7;j++)
		{
			in>>out[i][j];
		}
	}
	for(int i=0;i<n;i++)
	{
		cout<<":volu v"<<i+1<<" TUBE 0*cm 2.52*cm 4*micrometer  G4_Au"<<endl;
	}
	for(int i=0;i<n;i++)
	{
		cout<<":rotm r"<<i+1<<" "<<out[i][4]<<" "<<out[i][5]<<" "<<out[i][6]<<endl;
	}
	for(int i=0;i<n;i++)
	{
		cout<<":place v"<<i+1<<" 1 hall r"<<i+1<<" "<< out[i][1]<<" "<<out[i][2]<<" "<<out[i][3]<<endl;
	}
	for(int i=0;i<n;i++)
	{
		cout<<":color v"<<i+1<<" 0 0 1"<<endl;
	}
	cout<<":vis hall OFF";
}
