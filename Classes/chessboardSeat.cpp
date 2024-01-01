#include "chessboardSeat.h"
#include"myPosition.h"
chessboardSeat::chessboardSeat(int isme) {
	
	Size = 5;
	mine = isme;
	seats = new myPosition[5];
	//�����ҷ�Ӣ�۵�λ��
	if(isme)
	{
		seats[0] = myPosition(709, 540);
		seats[1] = myPosition(954, 540);
		seats[2] = myPosition(609, 372);
		seats[3] = myPosition(874, 372);
		seats[4] = myPosition(1199, 372);
	}
	else {
		//����ط�Ӣ�۵�λ��
		seats[0] = myPosition(726, 693);
		seats[1] = myPosition(995, 693);
		seats[2] = myPosition(539, 805);
		seats[3] = myPosition(826, 805);
		seats[4] = myPosition(1093, 805);
	}
}

chessboardSeat::~chessboardSeat() {
	delete[]seats;
}