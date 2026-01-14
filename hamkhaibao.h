
#include <string>
#include <vector>
using namespace std;

class dangnhap {
protected:
    string tk, mk, ten, stk;
    long sodu;

public:
    dangnhap();
	dangnhap(string tkx, string mkx, string stkx, string tenx, long sodux);
    void nhap();

    string gettk() const;
    string getmk() const;
    string getten() const;
    string getstk() const;
    string Stk() const;
    long getsodu() const;

    void trutien(long t);
    void naptien(long t);
    void chuyentien(vector<dangnhap> &ds, int nguoigui);
};

void ghiFile(const vector<dangnhap>& ds);
void docFile(vector<dangnhap>& ds);
int dangNhap(vector<dangnhap>& ds);
void menuTaiKhoan(dangnhap& x);
void giaodien();

