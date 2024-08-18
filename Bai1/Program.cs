using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bai1
{
    class DoVat
    {
        public string Ten;
        public float TrongLuong, GiaTri, DonGia;
        public int PhuongAn;
        public int SoLuong; // Số lượng tối đa của mỗi đồ vật, biến thể 4
    }

    class Program
    {
        const int MAX_SIZE = 100;

        static void Swap(ref DoVat a, ref DoVat b)
        {
            DoVat temp = a;
            a = b;
            b = temp;
        }

        static void SapXepTheoDonGia(DoVat[] dsdv, int n)
        {
            for (int i = 0; i < n - 1; i++)
            {
                for (int j = 0; j < n - i - 1; j++)
                {
                    if (dsdv[j].DonGia < dsdv[j + 1].DonGia)
                    {
                        Swap(ref dsdv[j], ref dsdv[j + 1]);
                    }
                }
            }
        }

        static int Chon(float trongLuong, float W, int soLuong)
        {
            int soLuongChon = (int)(W / trongLuong);
            return (soLuongChon < soLuong) ? soLuongChon : soLuong;
        }

        static void Greedy(DoVat[] dsdv, int n, float W, int loaiBaiToan)
        {
            SapXepTheoDonGia(dsdv, n);
            for (int i = 0; i < n; i++)
            {
                if (loaiBaiToan == 1)
                {
                    dsdv[i].PhuongAn = Chon(dsdv[i].TrongLuong, W, dsdv[i].SoLuong);
                }
                else if (loaiBaiToan == 2)
                {
                    dsdv[i].PhuongAn = (W >= dsdv[i].TrongLuong) ? 1 : 0;
                }
                W = W - dsdv[i].PhuongAn * dsdv[i].TrongLuong;
            }
        }

        static void Main()
        {
            DoVat[] dsdv = new DoVat[MAX_SIZE];
            int n, loaiBaiToan;
            float W;

            Console.Write("1: Gioi han so luong \n2: Moi do vat chi co mot cai: \nChon loai bai toan: ");
            loaiBaiToan = int.Parse(Console.ReadLine());

            Console.Write("Nhap trong luong toi da cua ba lo: ");
            W = float.Parse(Console.ReadLine());

            Console.Write("Nhap so luong loai do vat: ");
            n = int.Parse(Console.ReadLine());

            for (int i = 0; i < n; i++)
            {
                dsdv[i] = new DoVat();
                Console.WriteLine("Nhap thong tin cho do vat thu {0}:", i + 1);
                Console.Write("Ten: ");
                dsdv[i].Ten = Console.ReadLine();
                Console.Write("Trong luong: ");
                dsdv[i].TrongLuong = float.Parse(Console.ReadLine());
                Console.Write("Gia tri: ");
                dsdv[i].GiaTri = float.Parse(Console.ReadLine());
                dsdv[i].DonGia = dsdv[i].GiaTri / dsdv[i].TrongLuong;

                if (loaiBaiToan == 1)
                {
                    Console.Write("So luong toi da: ");
                    dsdv[i].SoLuong = int.Parse(Console.ReadLine());
                }
                else
                {
                    dsdv[i].SoLuong = 1;
                }
            }

            Greedy(dsdv, n, W, loaiBaiToan);

            Console.WriteLine("\nPhuong an chon:");
            float tongGiaTri = 0, tongTrongLuong = 0;
            for (int i = 0; i < n; i++)
            {
                if (dsdv[i].PhuongAn > 0)
                {
                    Console.WriteLine("{0}: {1}", dsdv[i].Ten, dsdv[i].PhuongAn);
                    tongGiaTri += dsdv[i].PhuongAn * dsdv[i].GiaTri;
                    tongTrongLuong += dsdv[i].PhuongAn * dsdv[i].TrongLuong;
                }
            }

            Console.WriteLine("Tong trong luong: {0:F2}", tongTrongLuong);
            Console.WriteLine("Tong gia tri: {0:F2}", tongGiaTri);

            Console.ReadKey();
        }
    }
}