#include <iostream.h>
#include <conio.h>

#define SUNDAY		0
#define	MONDAY		1
#define	TUESDAY		2
#define	WEDNESDAY	3
#define	THURSTDAY	4
#define	FRIDAY		5
#define	SATURDAY	6

int isValidDate(int ngay, int thang, long nam)
{
	if (thang<=0 || thang>12)
		return 0;

	return 1;
}

int isNamNhuan(long nam)
{
	if ( (nam %100 == 0) && (nam %400 != 0) )
		return 0;
	return (nam % 4 == 0);
}

////////////////////////////////////////////////
//	Chuyen doi ngay thang nam sang ngay trong tuan
//	=-1:	ngay thang nam ko hop le !
//	= 0:	->Sunday,
//	= 1:	->Monday,	= 2:	->Tuesday,	= 3:	->Wednesday
//	= 4:	->Thursday,	= 5:	->Friday,	= 6:	->Saturday
int DayToWeekday(int ngay, int thang, long nam)
{
	if (!isValidDate(ngay, thang, nam))
		return -1;
	static	int arraymonth[12] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};
	long	_nam = long(nam*1.2425);
	int 	_ngay = ngay - 1;
	int		_thang = arraymonth[thang-1];
	if (isNamNhuan(nam) && thang != 1 && thang != 2)
		_thang++;
	return (_ngay + _thang + _nam) % 7;
}

void main()
{
	clrscr();
	char weekday[][10] = {"SUNDAY","MONDAY","TUESDAY","WEDNESDAY",
					"THURSDAY","FRIDAY","SATURDAY"};
	cout<<weekday[DayToWeekday(25,5,2011)]<<endl;
	cout<<weekday[DayToWeekday(1,1,2011)]<<endl;
	cout<<weekday[DayToWeekday(3,2,2010)]<<endl;
	cout<<weekday[DayToWeekday(15,6,2012)]<<endl;
	cout<<weekday[DayToWeekday(1,1,2012)]<<endl;
	cout<<weekday[DayToWeekday(30,1,2016)]<<endl;
	cout<<weekday[DayToWeekday(10,6,2000)]<<endl;
	//getch();
}
//	int 	_ngay = ngay;// - 1;
//	int		_thang = arraymonth[thang-1];
//	if ( !(isNamNhuan(nam) && thang != 1 && thang != 2))
//		_thang--;
