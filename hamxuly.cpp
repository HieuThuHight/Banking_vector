#include "hamkhaibao.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>

using namespace std;

dangnhap::dangnhap() {
    sodu = 0;
}

dangnhap :: dangnhap(string tkx, string mkx, string stkx, string tenx, long sodux){
	this->tk = tkx;
    this->mk = mkx;
    this->stk = stkx;
    this->ten = tenx;
    this->sodu = sodux;
}
void dangnhap::nhap() {
	string mkx;
    srand(time(0)); // Khởi tạo seed để mỗi lần chạy ra 1 số khác  nhau
	int x,xn;
    cout << "\n  Tai khoan: "; cin >> tk;
    cout << "  Mat khau: "; cin >> mk;
    cin.ignore();
    cout << "  Ho va Ten: "; getline(cin, ten);
    do{
		int y = rand();
		x = y;
		fflush(stdin);
		cout << "  Nhap lai mat khau: "; cin >>  mkx;
		cout << "  Ma xac thuc:\t" << x << endl;
		cout << "  Nhap ma xac thuc: "; cin >> xn;
		cout << endl << endl;
	}while(mk != mkx|| x != xn);
	cout << "\t\t\t-Dang ky thanh cong-!";
	stk = Stk();
	
}


string dangnhap::gettk() const { return tk; }
string dangnhap::getmk() const { return mk; }
string dangnhap::getten() const { return ten; }
string dangnhap :: getstk() const{ return stk; }
string dangnhap :: Stk() const{
	string STK = "";
    for(int i = 0; i < 12; i++){
        int digit = rand() % 10;
        if(i == 0 && digit == 0) digit = 1;
        STK += char(digit + '0');
    }
    return STK;
}
long dangnhap::getsodu() const { return sodu; }

void dangnhap::trutien(long t) {
    sodu -= t;
}
void dangnhap :: naptien(long t){
	sodu += t;
}
void chuyentien(vector<dangnhap>& ds, int nguoigui){
	string stknhan;
	long tien;
	cout << "STK nguoi nhan: "; cin >> stknhan;
	if(stknhan == ds[nguoigui].getstk()){
		cout << "Khong the chuyen cho chinh minh!!\n";
		return;
	}
	cout << "Nhap so tien can chuyen: "; cin >> tien;
	if(tien <= 0){
		cout << "So tien khong hop le!!\n";
		return;
	}
	if(tien > ds[nguoigui].getsodu()){
		cout << "Tai khoan quy khach khong du!!\n";
		return;
	}
	
	// TIm nguoi nhan.
	for(int i = 0; i < ds.size(); i++){
		if(ds[i].getstk() == stknhan){
			cout << "Ten nguoi nhan: " << ds[i].getten() << endl;
			ds[nguoigui].trutien(tien);		//tru tien nguoi chuyen
			ds[i].naptien(tien);			//nap tien nguoi nhan
			
			cout<< "Chuyen tien thanh cong!!\n";
			cout << "So du con lai: " << ds[nguoigui].getsodu() << endl;
			return;
		}
	}
}






// ========= FILE =========
void ghiFile(const vector<dangnhap>& ds) {
    ofstream f("taikhoan.txt");
    f << left << "Tk"
    << "\t" << "Mk \t"
    << setw(16) << "Stk"
    << setw(20) << "Ten"
    <<  "\t " << "So du\n";
    for (auto &x : ds) {
        f << x.gettk() << "\t"
          << x.getmk() << "\t"
          << x.getstk() << "\t"
          << x.getten() << "\t"
          << x.getsodu() << endl;
    }
    f.close();
}

void docFile(vector<dangnhap>& ds) {
    ifstream f("taikhoan.txt");
    string line; 
    getline(f, line);		// bo qua dong tieu de
    string tk, mk, stk, ten;
    long sodu;

    while (f >> tk >> mk >> stk) {
        f.ignore();
        getline(f, ten, '\t');
        f >> sodu;

        dangnhap x = dangnhap(tk, mk, stk, ten, sodu);
        ds.push_back(x);
    }
    f.close();
}

// ========= ĐĂNG NHẬP =========
int dangNhap(vector<dangnhap>& ds) {
    string tk, mk;
    cout << "\t Tai khoan: ";
    cin >> tk;
    cout << "\t Mat khau: ";
    cin >> mk;

    for (int i = 0; i < ds.size(); i++) {
        if (ds[i].gettk() == tk && ds[i].getmk() == mk)
            return i;
    }
    cout << "Khong tim thay tai khoan !!\n";
    return -1;
}

// ========= MENU =========
void menuTaiKhoan(vector<dangnhap>& x, int vt) {
	system("cls");
    int lc;
    do {
       cout << "\n \t\t\t\t================================================";
        cout << left << "\n \t\t\t\t| Ten: " << setw(40) << x[vt].getten()  << "|";
        cout << "\n \t\t\t\t| STK: " << setw(18) << x[vt].getstk() << "So du: "  << setw(15) << x[vt].getsodu()<< "|";
        cout << "\n \t\t\t\t================================================";
        cout << setw(53) <<"\n \t\t\t\t| 1. Chuyen tien." << "|";
        cout << setw(53) <<"\n \t\t\t\t| 2. Nap tien." << "|";
        cout << setw(53) <<"\n \t\t\t\t| 3. Dang xuat." << "|";
        cout << "\n \t\t\t\t================================================";
        cout << "\n \t\t -->Lua chon: "; cin >> lc;
        
        if (lc == 1){
            	chuyentien(x, vt);
		} 
        else if (lc == 2) {
        	long t;
            cout << "Nhap so tien: ";
            cin >> t;
            if(t >= 0){
            	x[vt].naptien(t);	
			}else cout << "So tien khong hop le!\n";
        }
        else return;
    } while (1);
}

// ========= GIAO DIEN =========
void giaodien() {
    vector<dangnhap> ds;
    docFile(ds);

    int lc;
    do {
        cout << "\n \t\t\t\t\t==============================\n";
        cout << "   \t\t\t\t\t|   <Ngan hang thien gioi>   |";
        cout << "\n \t\t\t\t\t==============================";
        cout << "\n \t\t\t\t\t|  1. Dang nhap.             |";
        cout << "\n \t\t\t\t\t|  2. Dang ky.               |";
        cout << "\n \t\t\t\t\t|  3. Exit.                  |";
        cout << "\n \t\t\t\t\t==============================";
        int lc;
        cout << "\n -->Nhap lua chon: "; cin >> lc;
        
        if (lc == 1) {
            // Tìm vị trí tk đăng nhập
            int vt = dangNhap(ds);
            if (vt != -1) {
            	cout << "Dang nhap thanh cong @@@@\n\n";
                // Hiển thị thông tin tài khoản
                menuTaiKhoan(ds, vt);
            	ghiFile(ds);
            } else cout << "Sai tai khoan!\n";
        }
        else if (lc == 2) {
            dangnhap x;
            x.nhap();
            ds.push_back(x);
            ghiFile(ds);
        }
        else return;
    } while (1);
}
