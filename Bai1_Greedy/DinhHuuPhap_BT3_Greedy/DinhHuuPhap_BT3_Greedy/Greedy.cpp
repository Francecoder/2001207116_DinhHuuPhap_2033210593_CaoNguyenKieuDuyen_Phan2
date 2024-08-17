#include <iostream>
#include <iomanip>
#include <fstream>  // For file input operations

using namespace std;

struct DoVat {
    char Ten[20];
    float TrongLuong, GiaTri, DonGia;
    int PhuongAn; // so luong do vat chon
};

void TinhDonGia(DoVat sp[], int n)
{
    for (int i = 0; i < n; i++)
        sp[i].DonGia = sp[i].GiaTri / sp[i].TrongLuong;
}

void swap(DoVat& a, DoVat& b)
{
    DoVat temp = a;
    a = b;
    b = temp;
}

void SapXep(DoVat sp[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (sp[i].DonGia < sp[j].DonGia)
                swap(sp[i], sp[j]);
}

void Greedy(DoVat sp[], int n, float W)
{
    for (int i = 0; i < n; i++) {
        sp[i].PhuongAn = W / sp[i].TrongLuong;
        /*
         Nếu không ràng buộc lấy mỗi món ít nhất 1 lần thì bỏ dòng này
         */
        if (sp[i].PhuongAn > 1) {
            sp[i].PhuongAn = 1;
        }

        W -= sp[i].PhuongAn * sp[i].TrongLuong;
    }
}

void write_complexity(const std::string& filename) {
    // Mở file để ghi
    std::ofstream file(filename);

    // Kiểm tra xem file có mở thành công không
    if (!file) {
        std::cerr << "Error opening file " << filename << std::endl;
        return;
    }

    // Nội dung bạn muốn ghi vào file
    const std::string content =
        "Độ phức tạp của thuật toán Greedy cho bài toán Balo:\n\n"
        "1. Tính toán tỷ lệ giá trị trên trọng lượng: O(n)\n"
        "2. Sắp xếp các đối tượng theo tỷ lệ giá trị trên trọng lượng: O(n log n)\n"
        "3. Chọn các đối tượng để đưa vào balo: O(n)\n\n"
        "Tổng độ phức tạp của thuật toán Greedy là: O(n log n)\n";

    // Ghi nội dung vào file
    file << content;

    // Đóng file sau khi ghi xong
    file.close();

    std::cout << "Nội dung đã được ghi vào file " << filename << std::endl;
}



int main()
{
    int n;
    float W;
    ifstream file("input.txt");

    if (!file) {
        cerr << "Unable to open file input.txt";
        exit(1); // call system to stop
    }

    file >> n;

    DoVat* sp = new DoVat[n];

    for (int i = 0; i < n; i++) {
        file >> sp[i].Ten >> sp[i].TrongLuong >> sp[i].GiaTri;
    }

    file >> W;
    file.close();

    TinhDonGia(sp, n);
    SapXep(sp, n);
    Greedy(sp, n, W);

    cout << "\nDanh sach cac do vat duoc chon:\n";
    cout << setw(20) << left << "Ten"
        << setw(15) << "Trong Luong"
        << setw(10) << "Gia Tri"
        << setw(10) << "Don Gia"
        << setw(10) << "Phuong An"
        << endl;

    for (int i = 0; i < n; i++) {
        if (sp[i].PhuongAn > 0) {
            cout << setw(20) << left << sp[i].Ten
                << setw(15) << sp[i].TrongLuong
                << setw(10) << sp[i].GiaTri
                << setw(10) << sp[i].DonGia
                << setw(10) << sp[i].PhuongAn
                << endl;
        }
    }
    write_complexity("D:\\30_2001207116_DinhHuuPhap_Lan2\\Bai3_GiaiThuatThamLam\\DinhHuuPhap_BT3_Greedy\\dpt.txt");
    return 0;
}
