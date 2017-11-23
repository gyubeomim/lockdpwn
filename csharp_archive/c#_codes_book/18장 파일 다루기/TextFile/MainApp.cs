using System;
using System.IO;

namespace TextFile
{
    class MainApp
    {
        static void Main(string[] args)
        {
            StreamWriter sw =
                new StreamWriter(
                    new FileStream("a.txt", FileMode.Create));

            sw.WriteLine(int.MaxValue);
            sw.WriteLine("Good morning!");
            sw.WriteLine(uint.MaxValue);
            sw.WriteLine("안녕하세요!");
            sw.WriteLine(double.MaxValue);

            sw.Close();

            StreamReader sr =
                new StreamReader(
                    new FileStream("a.txt", FileMode.Open));

            Console.WriteLine("File size : {0} bytes", sr.BaseStream.Length);

            while (sr.EndOfStream == false)
            {
                Console.WriteLine(sr.ReadLine());
            }

            sr.Close();
        }
    }
}
