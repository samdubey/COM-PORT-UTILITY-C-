class Form /*form class ,displays form of a size ,color etc.*/
{
	public:
	int Left;
	int Top;
	int Width;
	int Height;
	int BackColor;
	char *Caption;
	Form(int L,int T,int W,int H,int BC,char *C)/*constructor*/
	{
		Left=L;
		Top=T;
		Width=W;
		Height=H;
		BackColor=BC;
		Caption=C;
	}
	Form()/*constructor*/
	{
		Width=getmaxx()-2;/*init all the values*/
		Height=getmaxy()-2;
		Left=1;
		Top=1;
		BackColor=1;
		Caption="Shree";
	}
	void Show();/*member function to display the form*/
	};
	void Form::Show()
	{
		setcolor(15);
		setfillstyle(1,BackColor);
		bar3d(Left,Top,Left+Width,Top+Height,0,0);
		setcolor(7);
		setfillstyle(1,7);
		bar3d(Left+3,Top+3,Left+Width-3,Top+20,0,0);
		setcolor(0);
		settextstyle(0,0,0);
		outtextxy(Left+Width/3+10,Top+10,Caption);
	}



