#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Date
{
    int Day, Month, Year;
};

struct SinhVien {
    string MSSV;
    string Ten;
    string Lop;
    Date NgaySinh;
    double DTB;
};

void Swap(SinhVien &a, SinhVien &b) {
    SinhVien temp = a;
    a = b;
    b = temp;
}

void HeapifyMintoMaxWithMSSV(SinhVien*& Arr, int n, int i)  {
    int Max = i;
    int left = i * 2 + 1;
    int right = left + 1;
    if (left < n && Arr[left].MSSV > Arr[Max].MSSV)
    {
        Max = left;
    }
    if (right < n && Arr[right].MSSV > Arr[Max].MSSV)   {
        Max = right;
    }
    if (Max != i)    {
        Swap(Arr[i], Arr[Max]);
        HeapifyMintoMaxWithMSSV(Arr, n, Max);
    }
}

void HeapSortMintoMaxWithMSSV(SinhVien*& Arr, int n)    {
    for (int i = n / 2 - 1; i >= 0; i--)
        HeapifyMintoMaxWithMSSV(Arr, n, i);
    for (int j = n - 1; j > 0; j--)    {
        Swap(Arr[0], Arr[j]);
        HeapifyMintoMaxWithMSSV(Arr, j, 0);
    }
}

void HeapifyMintoMaxWithDTB(SinhVien*& Arr, int n, int i)   {
    int Max = i;
    int left = i * 2 + 1;
    int right = left + 1;
    if (left < n && Arr[left].DTB > Arr[Max].DTB)   {
        Max = left;
    }
    if (right < n && Arr[right].DTB > Arr[Max].DTB) {
        Max = right;
    }
    if (Max != i)   {
        Swap(Arr[i], Arr[Max]);
        HeapifyMintoMaxWithDTB(Arr, n, Max);
    }
}

void HeapSortMintoMaxWithDTB(SinhVien*& Arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        HeapifyMintoMaxWithDTB(Arr, n, i);
    for (int j = n - 1; j > 0; j--)    {
        Swap(Arr[0], Arr[j]);
        HeapifyMintoMaxWithDTB(Arr, j, 0);
    }
}

int CheckArr() {
    int i = 0;
    ifstream ifs("input.csv");
    if (!ifs) {
        cerr << "Loi: File input chua mo !." << endl;
        return 0;
    }
    string line;
    getline(ifs, line);
    while (ifs)
    {
        i++;
        getline(ifs, line);
    }
    ifs.close();
    i--;
    return i;
}

void ReadData(SinhVien*& Arr, int n) {
    string temp;
    int i = 0;
    ifstream ifs("input.csv");
    if (!ifs) {
        cerr << "Loi: File input chua mo !." << endl;
        return;
    }
    getline(ifs, temp);
    string::size_type sz;
    while (i < n)
    {
        getline(ifs, temp, ',');
        Arr[i].MSSV = temp;
        getline(ifs, temp, ',');
        Arr[i].Ten = temp; 
        getline(ifs, temp, ',');
        Arr[i].Lop = temp;
        getline(ifs, temp, '/');
        Arr[i].NgaySinh.Day = stoi(temp,&sz);
        getline(ifs, temp, '/');
        Arr[i].NgaySinh.Month = stoi(temp, &sz);
        getline(ifs, temp, ',');
        Arr[i].NgaySinh.Year = stoi(temp, &sz);
        getline(ifs, temp);
        Arr[i].DTB = stoi(temp, &sz);
        i++;
    }
    ifs.close();
}

void InsectData(SinhVien*& Arr, int &input) {
    int n;
    cout << "Nhap so luong sinh vien can nhap: ";
    cin >> n;
    input = n;
    system("cls");
    Arr = new SinhVien[n];
    for (int i = 0; i < n; i++) {
        cout << "======= Nhap sinh vien thu " << i + 1 << " =======" << endl;
        cout << "Nhap MSSV: ";
        cin >> Arr[i].MSSV;
        cout << "Nhap Ho va Ten: ";
        cin >> Arr[i].Ten;
        cout << "Nhap lop: ";
        cin >> Arr[i].Lop;
        cout << "nhap ngay, thang, nam sinh (vd: 28 1 2000): ";
        cin >> Arr[i].NgaySinh.Day >> Arr[i].NgaySinh.Month >> Arr[i].NgaySinh.Year;
        cout << "Nhap Diem trung binh: ";
        cin >> Arr[i].DTB;
        cout << "----------------------------------------------" << endl;
    }
}

void WriteData(SinhVien *Arr, int n) {
    ofstream ofs("output.csv");
    if (!ofs) {
        cerr << "Loi: File output chua mo !." << endl;
        return;
    }
    ofs << "MSSV" << ',' << "Ho va Ten" << ',' << "Lop" << ',' << "Ngay sinh" << ',' << "Diem trung binh" << endl;
    for (int i = 0; i < n; i++) {
        ofs << Arr[i].MSSV << ',' << Arr[i].Ten << ',' << Arr[i].Lop << ',' << Arr[i].NgaySinh.Day << '/' << Arr[i].NgaySinh.Month << '/' << Arr[i].NgaySinh.Year << ',' << Arr[i].DTB << endl;
    }
    ofs.close();               
}

void CoutData(SinhVien* Arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << "======== Sinh vien thu " << i + 1 << " ========" << endl;
        cout << "MSSV: " << Arr[i].MSSV << endl;
        cout << "Ho va Ten: " << Arr[i].Ten << endl;
        cout << "Lop: " << Arr[i].Lop << endl;
        cout << "Ngay sinh: " << Arr[i].NgaySinh.Day << "/" << Arr[i].NgaySinh.Month << "/" << Arr[i].NgaySinh.Year << endl;
        cout << "Diem trung binh: " << Arr[i].DTB << endl;
        cout << "-----------------------------------------------" << endl;
    }
}

int main()
{
back:
    cout << "=================================================" << endl;
    cout << "--- Chuong trinh sap xep danh sach sinh vien ---" << endl;
    cout << "   Nhap 1: Nhap danh sach tu ban phim !" << endl;
    cout << "   Nhap 2: Nhap danh sach tu file input.csv" << endl;
    cout << "=================================================" << endl;
    cout << "Nhap tuy chon: ";
    int Optional;
    cin >> Optional;
    int n;
    SinhVien* Arr;
    switch (Optional)
    {
    case 1: {
        system("cls");
        InsectData(Arr, n);
        break;
    }
    case 2: {
        system("cls");
        n = CheckArr();
        Arr = new SinhVien[n];
        ReadData(Arr, n);
        break;
    }
    default: {
        cout << "sai tuy chon, moi nhap lai !" << endl;
        system("pause");
        system("cls");
        goto back;
    }
    }
back4blood:
    system("cls");
    cout << "====================================================================" << endl;
    cout << "------------- Chuong trinh sap xep danh sach sinh vien -------------" << endl;
    cout << "   Nhap 1: Sap xep danh sach sinh vien theo MSSV tu be toi lon" << endl;
    cout << "   Nhap 2: Sap xep danh sach sinh vien theo MSSV tu lon toi be" << endl;
    cout << "   Nhap 3: Sap xep danh sach sinh vien theo DTB tu be toi lon" << endl;
    cout << "   Nhap 4: Sap xep danh sach sinh vien theo DTB tu lon toi be" << endl;
    cout << "====================================================================" << endl;
    cout << "Nhap tuy chon: ";
    cin >> Optional;
    switch (Optional) {
    case 1: {
        HeapSortMintoMaxWithMSSV(Arr, n);
        break;
    }
    case 2: {

    }
    case 3: {
        HeapSortMintoMaxWithDTB(Arr, n);
        break;
    }
    case 4: {

    }
    default: {
        cout << "sai tuy chon, moi nhap lai !" << endl;
        system("pause");
        system("cls");
        goto back4blood;
    }
    }
    cout << "------------ Danh sach sinh vien sau khi duoc sap xep la ------------" << endl;
    CoutData(Arr, n);
    cout << "Danh sach sinh vien sau khi sap xep da duoc ghi vao file: output.csv" << endl;
    WriteData(Arr, n);
    return 0;
}
