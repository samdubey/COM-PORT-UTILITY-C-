/*Simple COM port Communication program using polling method
 only one charecter send and received at a time.
 name :Sameer Rajendra Dubey
	T.Y.B.Sc [ELECTONICS]
	P.O.NAHATA COLLEGE BHUSAWAL
 Email:sameerdubey6@yahoo.com
 */
 #include"dos.h"
 #include"stdio.h"
 #include"conio.h"
 #define PORT1 0x3F8
 void main(void)
 {
	int c;
	int ch;
	outportb(PORT1+1,0);
	outportb(PORT1+3,0x80);
	outportb(PORT1+0,0x03);
	outportb(PORT1+1,0x00);
	outportb(PORT1+3,0x03);
	outportb(PORT1+2,0xC7);
	outportb(PORT1+4,0x0B);
	do
	{
		c=inportb(PORT1+5);
		if(c & 1)
		{
			ch=inportb(PORT1);
			printf("\nECHO %s",ch);
		}
		if(kbhit())
		{
			ch=getch();
			outportb(PORT1,ch);
		}
	}while(ch != 27);
 }






