class MenuItem
{
	public:
	int Top;
	int Left;
	int Width;
	char* Text;
	int Active;
	void Draw(int);
	MenuItem(int L,int To,int W,char *T)
	{
		Top=To;
		Left=L;
		Width=W;
		Text=T;
		Active=1;
	}
};
	void MenuItem::Draw(int Active)
	{
		setfillstyle(0,0);
		if(Active)
		{
			setcolor(15);
		}
		else
		{
			setcolor(8);
		}
		bar3d(Left,Top,Left+Width,Top+20,0,0);
		outtextxy(Left+5,Top+7,Text);
	}
