using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bai2
{
    class HoatDong
    {
        public int BatDau { get; set; }
        public int KetThuc { get; set; }
    }

    class Program
    {
        static void LuaChonHoatDong(List<HoatDong> activities)
        {
            activities.Sort((a, b) => a.KetThuc.CompareTo(b.KetThuc));
            Console.Write("Cac hoat dong duoc chon: 1 ");
            int i = 0;
            for (int j = 1; j < activities.Count; j++)
            {
                if (activities[j].BatDau > activities[i].KetThuc)
                {
                    Console.Write("{0} ", j + 1);
                    i = j;
                }
            }
            Console.WriteLine();
        }

        static void Main(string[] args)
        {
            Console.Write("Nhap so luong hoat dong: ");
            int n = int.Parse(Console.ReadLine());

            List<HoatDong> activities = new List<HoatDong>();

            for (int i = 0; i < n; i++)
            {
                Console.Write("Nhap thoi gian bat dau va ket thuc cua hoat dong {0}: ", i + 1);
                string[] input = Console.ReadLine().Split();
                activities.Add(new HoatDong
                {
                    BatDau = int.Parse(input[0]),
                    KetThuc = int.Parse(input[1])
                });
            }

            LuaChonHoatDong(activities);

            Console.ReadKey();
        }
    }
}