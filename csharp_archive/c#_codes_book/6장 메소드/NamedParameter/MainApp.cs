using System;

namespace NamedParameter
{
    class MainApp
    {
        static void PrintProfile(string name, string phone)
        {
            Console.WriteLine("Name:{0}, Phone:{1}", name, phone); 
        }

        static void Main(string[] args)
        {
            PrintProfile(name: "박찬호", phone: "010-123-1234");
            PrintProfile(phone: "010-987-9876", name: "박지성");
            PrintProfile("박세리", "010-222-2222");
            PrintProfile("박상현", phone:"010-567-5678");
        }
    }
}
