#include<io.h>
#include<dos.h>
#include<string.h>
#include<fcntl.h>
/*#include"stdio.h"*/
#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<share.h>
#include<stdlib.h>
#include<stat.h>
#include"s_forms.cpp"
#include"s_menu.cpp"
#include"S_SB.Cpp"
#define PORT1 0x3F8
	/*DEFINE SERIAL PORT BASE ADDRESS*/
	/*COM1 0x3F8
	  COM2 0x2F8
	  COM3 0X3E8
	  COM4 0X2E8*/
#define BufferSize 1000
	void init_port();/*PORT SETTING*/
	void main()
	{
		init_port();/*Initilize the COM port for communication*/

		int gd=VGA,gm=VGAHI;/*InIt Graphics Driver*/
		long int HRead,BRead;/*file stream handler and number of bytes read*/
		char RBuffer[BufferSize];/*read buffer*/
		unsigned long int FileSize=0;/*file size*/
		unsigned long int NoOfByD=0;/*number of byte done*/
		unsigned long int NumBuff1000;/*number of buffers.*/
		int GotFromPort;/*to store data received from port*/
		unsigned long int CurPos=0;/*pointer position in file*/
		unsigned int i,g;
		char FileName[30];/*FILE NAME*/
		char FileSizeC[30];/*file size in char form*/
		char NoOfBuffC[30];/* no of buffer in char form*/
		char x[1];/*to convert int to num from CP.*/
		int KeyInput=0,sta=1;
		initgraph(&gd,&gm,"\\tc\\bgi");/*init graphics*/
		cleardevice();
		Form InputBox(30,60,360,180,0,"S E L E C T");/*object*/
		Form MsgBox(80,260,450,120,4,"S E L E C T");/*object of form class*/
		Form MainFr;/*objects*/
		MainFr.Caption="COM PORT COMMUNICATION UTILITY";
		MenuItem B1(InputBox.Left+10,InputBox.Top+50,InputBox.Width-20,"1.Recieve File.");
		MenuItem B2(InputBox.Left+10,InputBox.Top+80,InputBox.Width-20,"2.Send File.");
		MenuItem B3(InputBox.Left+10,InputBox.Top+110,InputBox.Width-20,"3.Chat Utility.");
		MenuItem B4(InputBox.Left+10,InputBox.Top+140,InputBox.Width-20,"4.Exit.");
		StatusBar StatBar(InputBox.Left+170,200,10,150);
		StatBar.Refresh(0);
		MainFr.Show();
		InputBox.Show();
		setcolor(14);
		outtextxy(InputBox.Left+60,InputBox.Top+30,"COM PORT Communication Utility.");
		outtextxy(450,430,"Sameer Rajendra Dubey");
		outtextxy(450,450,"T.Y.B.Sc ELECTRONICS");
		outtextxy(450,440,"ROLL NUMBER : 317");
		B1.Draw(1);
		B2.Draw(0);
		B3.Draw(0);
		B4.Draw(0);
		for(;;)
		{
			KeyInput=getch();
			if(KeyInput == 27)
			{
				exit(0);
			}
			else if(KeyInput == 80)/*Down arrow key*/
			{
				switch(sta)
				{
					case 1:
					{
						B1.Draw(0);
						B2.Draw(1);
						B3.Draw(0);
						B4.Draw(0);
						sta=2;
						break;
					}
					case 2:
					{
						B1.Draw(0);
						B2.Draw(0);
						B3.Draw(1);
						B4.Draw(0);
						sta=3;
						break;
					}
					case 3:
					{
						B1.Draw(0);
						B2.Draw(0);
						B3.Draw(0);
						B4.Draw(1);
						sta=4;
						break;
					}
					case 4:
					{
						B1.Draw(1);
						B2.Draw(0);
						B3.Draw(0);
						B4.Draw(0);
						sta=1;
						break;
					}
				}
			}
			else if(KeyInput==72)/*Uparrow key*/
			{
				switch(sta)
				{
					case 1:
					{
						B1.Draw(0);
						B2.Draw(0);
						B3.Draw(0);
						B4.Draw(1);
						sta=4;
						break;
					}
					case 2:
					{
						B1.Draw(1);
						B2.Draw(0);
						B3.Draw(0);
						B4.Draw(0);
						sta=1;
						break;
					}
					case 3:
					{
						B1.Draw(0);
						B2.Draw(1);
						B3.Draw(0);
						B4.Draw(0);
						sta=2;
						break;
					}
					case 4:
					{
						B1.Draw(0);
						B2.Draw(0);
						B3.Draw(1);
						B4.Draw(0);
						sta=3;
						break;
					}
				}
			}
			else if(KeyInput == 13)/*enter key*/
			{
				if(sta==4)
				{
					exit(0);
				}
				else
				{
					break;
				}
			}
		}
		if(sta==1)/*recieve file*/
		{
			gotoxy(14,10);
			InputBox.Caption="Recieve File";
			InputBox.Show();
			setcolor(15);
			outtextxy(InputBox.Left+10,InputBox.Top+30,"Enter File Name with Full Path.");
			outtextxy(InputBox.Left+10,InputBox.Top+40,"File to be copied.(file name should be");
			outtextxy(InputBox.Left+10,InputBox.Top+50,"in DOS format i.e. maximum of 11 characters");
			outtextxy(InputBox.Left+10,InputBox.Top+60,"for file name and 3 for extension ");
			outtextxy(InputBox.Left+10,InputBox.Top+90,"Type..> ");
			cin>>FileName;
			HRead=sopen(FileName,O_RDWR|O_BINARY|O_CREAT,SH_DENYNO,S_IREAD|S_IWRITE);/*OPEN FILE*/
			outtextxy(InputBox.Left+10,InputBox.Top+120,"This terminal is ready to recieve a file.");
			setcolor(14);
			outtextxy(InputBox.Left+10,InputBox.Top+140,"when done press Esc to Exit");
			int c,ch;
			c=inport(PORT1+5);/*CHECK IF RECIEVE DATA*/
			if(c&1)
			{
				ch=inport(PORT1);
			}
			outportb(PORT1,100);/*SEND CHARACTER 'd' TO REMOTE TERMINAL.*/
			for(;;) /*start copy*/
			{
				c=inportb(PORT1+5);
					if(c & 1)
					{
						ch=inport(PORT1);
						x[0]=char(ch);
						BRead=write(HRead,x,1);
						outportb(PORT1,100);
					}
					if(kbhit())
					{
						char T=getch();
						if(T == 27)
						{
							close(HRead);
							exit(0);
						}
					}
				}
			}
			else if(sta == 2)
			{
				MsgBox.Top=260;
				MsgBox.Left=80;
				char choice;
				for(;;)/*Do until we get a valid file name */
				{
					gotoxy(14,10);
					MainFr.Show();
					InputBox.Show();
					setcolor(15);
					outtextxy(InputBox.Left+10,InputBox.Top+30,"Enter File Name with Full Path.");
					outtextxy(InputBox.Left+10,InputBox.Top+40,"File to be copied.(file name should be");
					outtextxy(InputBox.Left+10,InputBox.Top+50,"in DOS format i.e. maximum of 11 characters");
					outtextxy(InputBox.Left+10,InputBox.Top+60,"for file name and 3 for extension ");
					outtextxy(InputBox.Left+10,InputBox.Top+90,"Type..> ");
					cin>>FileName;
					HRead=open(FileName,O_RDONLY|O_BINARY);
					FileSize=filelength(HRead);
					if(HRead>0)/*valid file*/
					{
						if(FileSize>BufferSize)/*calculate the number of buffers.*/
						{
							NumBuff1000=(FileSize/BufferSize);
						}
						else
						{
							NumBuff1000=1;
						}
						if(NumBuff1000*BufferSize<FileSize)
						{
							+ + NumBuff1000;
						}
						StatBar.min=0;/*assign min max values to status bar*/
						StatBar.max=NumBuff1000;
						InputBox.Caption="Send File";
						InputBox.Height=300;
						InputBox.Show();
						setcolor(15);
						outtextxy(InputBox.Left+10,InputBox.Top+30,"File Name:");
						outtextxy(InputBox.Left+10,InputBox.Top+40,"File Size:");
						outtextxy(InputBox.Left+10,InputBox.Top+50,"Number Of Buffer:");
						ltoa(FileSize,FileSizeC,10);
						ltoa(NumBuff1000,NoOfBuffC,10);
						outtextxy(InputBox.Left+150,InputBox.Top+50,NoOfBuffC);
						outtextxy(InputBox.Left+150,InputBox.Top+40,FileSizeC);
						outtextxy(InputBox.Left+10,InputBox.Top+80,"after making other terminal");
						outtextxy(InputBox.Left+10,InputBox.Top+90,"Ready press any key to start.");
						setcolor(15);
						StatBar.Refresh(0);
						KeyInput=getch();
						if(KeyInput == 27)
						{
							exit(0);
						}
						int c=0;
						for(i=1;i<=NumBuff1000;i++)/*all buffers send one by one */
						{
							CurPos=tell(HRead);/*get current pos of pointer*/
							BRead=read(HRead,RBuffer,BufferSize);
							CurPos+=BufferSize;
							lseek(HRead,CurPos,SEEK_SET);/*update ptr*/
							CurPos=tell(HRead);
							g=0;
							StatBar.Refresh(i);
							do
							{
								c=inportb(PORT1+5);/*CHECK THE DATA*/
								if(c & 1)
								{
									GotFromPort=inportb(PORT1);/*get data*/
									if(GotFromPort == 100)/*if we get d*/
									{
										outportb(PORT1,RBuffer[g]);/*send char to serial port*/
										NoOfByD ++;
										g ++;
									}
								}
							}while(g<BRead);
						}               /*end for*/
						break;
					}/*end if (valid file)*/
					else
					{
						MsgBox.Caption="    Error !!!";
						MsgBox.Show();
						setcolor(15);
						outtextxy(MsgBox.Left+10,MsgBox.Top+30,"incorrect file name or file does not exist.");
						outtextxy(MsgBox.Left+10,MsgBox.Top+40,"press any key to reenter file name or Esc to Cancel");
						outtextxy(MsgBox.Left+10,MsgBox.Top+90,"Esc-Exit");
						choice=getch();
						if(choice==27)
						{
							break;
						}
					}
				}/*end for(;;)*/
			}/*end of menu if*/
			else if(sta==3)
			{
				closegraph();
				clrscr();
				cout<<char(201);
				for(int i=1;i<=78;i++)
				{
					cout<<char(205);
				}
					cout<<char(187)<<char(186);
					gotoxy(29,2);
					cout<<"COM PORT CHAT UTILITY";
					gotoxy(80,2);
					cout<<char(186)<<char(200);
					for(i=1;i<=78;i++)
					{
						cout<<char(205);
					}
					cout<<char(188);
					int c,ch;
					char UserName1[30],UserName2[30]="";
					int GotName=0,GaveName=0;/*flags*/
					int INBuffer[100],OUTBuffer[100];/*output BUFFERS*/
					int INPtr=0,OUTPtr=0;
					int v=0,flag=0,sl;
					char s;
					i=0;
					cout<<"\nenter your name :";
					cin>>UserName1;
					sl=strlen(UserName1);
					do
					{
						if(GotName && GaveName)
						{
							if(!flag)
							{
								cout<<"\n"<<UserName1<<":";
								flag=1;
							}
							c=inportb(PORT1+5);/*check to see if char has been recieved.*/
							if(c & 1)
							{
								ch=inportb(PORT1);/*IF SO ,then get char*/
								if(ch==13)
								{
									cout<<"\n"<<UserName2<<":";
									for(i=0;i<INPtr-1;i++)
									{
										cout<<char(INBuffer[i]);
									}
									INPtr=0;
									cout<<"\n"<<UserName1<<":";
								}/*end of our data,as we got the name.*/
								else
								{
									INBuffer[INPtr]=ch;
									INPtr++;
								}
							}/*&c*/
						}/*G&G*/
						if(kbhit())
						{
							ch=getch();/*if key pressed,get char*/
							if((ch == 13) && GaveName && GotName)
							{
								for(i=0;i<=OUTPtr;i++)
								{
									outportb(PORT1,OUTBuffer[i]);
									delay(1);
								}
								outportb(PORT1,13);
								cout<<"\n"<<UserName1<<":";
								OUTPtr=0;
							}
							else if(GaveName && GotName)
							{
								OUTBuffer[OUTPtr]=ch;
								OUTPtr++;
								cout<<char(ch);
							}
						}
						if(!GotName)/*we want the name of the user on other computer*/
						{
							c=inportb(PORT1+5);/*check to see if char has been recieved.*/
							if(c&1)
							{
								ch=inportb(PORT1);/*IF SO THE GET CHAR*/
								if(ch==13)
								{
									i=0;
									cout<<"\n user on remote computer:"<<UserName2;
									cout<<"\n press Esc to Exit";
									GotName=1;
								}/*end of our data, as we got the name*/
								else
								{
									s=char(ch);
									UserName2[i]=s;/*store name*/
									i++;
								}
							}
						}/*end of got name*/
						if(!GaveName)
						{
							outportb(PORT1,UserName1[v]);/*send name char by char*/
							v++;
							if(v == sl)
							{
								outportb(PORT1,13);
								GaveName=1;
							}
						}
					}while(ch!=27);/*Quit when Esc(ASC27) is pressed*/
				}
				closegraph();/*end of chat part*/
				}

			void init_port()/*initilize COM port for communication.*/
			{
				outportb(PORT1+1,0);/*turn offinterrupts-port1*/
				outportb(PORT1+3,0x80);/*set DLAB ON*/
				/*Default 0x01 = 115,200 BPS
					  0x02 = 57,600 BPS
					  0x06 = 19,200 BPS
					  0x0C =  9,600 BPS
					  0x18 =  4,800 BPS
					  0x30 =  2,400 BPS*/
				outportb(PORT1 + 0,0x0C);/*set boudrate-divisor latch low byte default 0x03 = 38,400 BPS*/
				outportb(PORT1 + 1,0x00);/*set boudrate-divisor latch high byte */
				outportb(PORT1 + 3,0x03);/*8 bits,no parity,1 stop bit */
				outportb(PORT1 + 2,0xC7);/*FIFO control Register */
				outportb(PORT1 + 4,0x0B);/*Turn on DTR,RTS, and UOUT@ */
			}