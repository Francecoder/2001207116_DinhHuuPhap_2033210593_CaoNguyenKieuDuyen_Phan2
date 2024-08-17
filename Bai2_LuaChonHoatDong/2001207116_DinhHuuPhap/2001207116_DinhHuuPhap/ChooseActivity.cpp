
#include <iostream>
#include <iomanip>
#include <fstream>  // For file input operations
using namespace std;
struct HoatDong {
    char Ten[20];
    float Si, Ei;
};
void SapXep(HoatDong hd[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (hd[i].Ei > hd[j].Ei)
                swap(hd[i], hd[j]);
}
// So sánh hai hoạt động dựa trên thời gian kết thúc


// Hàm Greedy để chọn các hoạt động
void activitySelection(HoatDong* hd, int n, HoatDong*& selectedActivities, int& selectedCount) {
    // Sắp xếp các hoạt động theo thời gian kết thúc

    // Tạo mảng để lưu các hoạt động được chọn
    selectedActivities = new HoatDong[n];
    selectedCount = 0;
    int lastEndTime = -1;

    for (int i = 0; i < n; ++i) {
        if (hd[i].Si > lastEndTime) {
            selectedActivities[selectedCount++] = hd[i];
            lastEndTime = hd[i].Ei;
        }
    }
}

int main()
{
    /*
Bài 1. Cài đặt chương trình giải bài toán Lựa chọn hoạt động
 Cho tập các hoạt động A1, A2, ... An (ví dụ : các cuộc họp, người thuyết trình,...)
 Mỗi hoạt động có thời gian bắt đầu (start time - Si) và thời gian kết thúc (end time – Ei).
 Các hoạt động sẽ sử dụng chung nguồn tài nguyên (ví dụ : phòng họp, ...).
 Mục tiêu của bài toán : tối đa hóa số lượng các hoạt động sử dụng nguồn tài nguyên, với điều
kiện không có hai hoạt động bị trùng lắp.
Gợi ý:
- Tạo file dữ liệu txt (hoặc xml) chứa thông tin n hoạt động, mỗi hoạt động có tên Ai, thời gian bắt
đầu Si và thời gian kết thúc Ei.
- Tổ chức cấu trúc lưu thông tin vật
+ Ten: Lưu trữ tên hoạt động.
+ Si: Lưu trữ thời gian bắt đầu của hoạt động.
+ Ei: Lưu trữ thời gian kết thúc của hoạt động
- Tạo danh sách (mảng, list) chứa danh sách các hoạt động.
- Sắp xếp danh sách tăng dần theo Ei.
- Thực hiện theo giải thuật đã nêu ở lý thuyết.
*/
    int n;
    ifstream file("input_bai2.txt");

    if (!file) {
        cerr << "Unable to open file input.txt";
        exit(1); // call system to stop
    }
    file >> n;
    HoatDong* hd = new HoatDong[n];

    for (int i = 0; i < n; i++) {
        file >> hd[i].Ten >> hd[i].Si >> hd[i].Ei;
    }


    file.close();

    SapXep(hd, n);

    cout << "\nDanh sach cac hoat dong:\n";
    cout << setw(10) << left << "Ten"
        << setw(20) << "Thoi gian bat dau"
        << setw(10) << "Thoi gian ket thuc"
        << endl;
    for (int i = 0; i < n; i++)
    {
        cout << setw(20) << hd[i].Ten
            << setw(15) << hd[i].Si
            << setw(15) << hd[i].Ei
            << endl;
    }
    // thuc hien giai thuat
    HoatDong* selectedActivities = nullptr;
    int selectedCount = 0;
    activitySelection(hd, n, selectedActivities, selectedCount);
    cout << "\nDanh sach cac hoat dong duoc chon:\n";
    cout << setw(10) << left << "Ten"
        << setw(10) << "Bat dau"
        << setw(10) << "Ket thuc"
        << endl;

    for (int i = 0; i < selectedCount; ++i) {
        cout << setw(10) << left << selectedActivities[i].Ten
            << setw(10) << selectedActivities[i].Si
            << setw(10) << selectedActivities[i].Ei
            << endl;
    }
    // Giải phóng bộ nhớ
    delete[] hd;
    delete[] selectedActivities;

    return 0;
}
