#ifndef DATATYPE_H
#define DATATYPE_H 
#include <stdbool.h>
 
struct Date {
	int month, day, year;
};

struct Transaction{
	char transferId[10];//ma giao dich chuyen tien
	char receivingId[10];//ma nhan tien
	double amount;//so tien
	char type[10];//loai giao dich(chuyen khoan / rut tien)
	char message[50];//tin nhan kem giao dich
	struct Date transactionDate;//ngay giao dich(su dung cau truc date)
	
};
struct AccountInfo{
	char userId[20];//ma nguoi dung
	float balance;//so du tai khoan
	bool status;//Trang thai tai khoan(hoat dong hoac khoa)
	struct Transaction transactionHistory;//lich su giao dich
};
struct AccountInfo accountInfo[100]; 
struct User{
	char userId[20];//ma nguoi dung
	char name[50];//ten nguoi dung
	struct Date dateOfBirth;//ngay sinh nguoi dung
	int gender;//gioi tinh
	char phone[11];//so dien thoai nguoi dung
	char email[40];//dia chi email
	char username[50];//ten tai khoan
	
};
struct User users[100];
#endif
