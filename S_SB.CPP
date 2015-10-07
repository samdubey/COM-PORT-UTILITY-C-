#include"graphics.h"
#include"stdio.h"
#include"iostream.h"
#include"math.h"
class StatusBar
{
	public:
	int m_x,m_y;
	int height,length;
	int BarColor;
	long int min,max;
	long int value;
	void ShowBar(int m_x,int m_y,int height,int length);
	void Refresh(long int v);
	int CalcX();
	StatusBar(int x,int y,int h,int l)
	{
		m_x=x;
		m_y=y;
		height=h;
		length=l;
		BarColor=4;
		min=0;
		max=100;
		value=50;
		setcolor(15);
		setfillstyle(1,0);
		bar3d(m_x-length,m_y-height,m_x+length/2,m_y+height,0,0);
		Refresh(value);
	}
	StatusBar()
	{
		m_x=100;
		m_y=100;
		height=10;
		length=100;
		BarColor=4;
		min=0;
		max=100;
		value=50;
	}
	~StatusBar(){}
	};
	void StatusBar::Refresh(long int v)
	{
		value=v;
		setcolor(15);
		setfillstyle(1,0);
		bar3d(m_x-length/2,m_y-height,m_x+length/2,m_y+height,0,0);
		setfillstyle(1,BarColor);
		int xinc;
		xinc=CalcX();
		bar3d(m_x+2-length/2,m_y+2-height,(m_x+2-length/2)+abs(xinc),m_y-2+height,0,0);
		setfillstyle(1,0);
		bar3d((m_x+2-length/2)+abs(xinc),m_y+2-height,(m_x+length/2)-2,m_y-2+height,0,0);
	}
	int StatusBar::CalcX()
	{
		int perc,percx;
		long int total;
		total=max-min;
		perc=(value*100)/total;
		percx=((length*perc)/100)-3;
		if(percx>length)
		{
			return 0;
		}
		else
		{
			return percx;
		}
	}






