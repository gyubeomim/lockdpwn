using System;

namespace ForSequence
{
    class MainApp
    {
        public static int Init()
        {
            Console.WriteLine("초기자");
            return 0;
        }

        public static int Comp()
        {
            Console.WriteLine("비교");
            return 5;
        }

        public static int Inc(int i)
        {
            Console.WriteLine("반복");
            return ++i;
        }
        static void Main(string[] args)
        {
            for (int i = Init(); i < Comp(); i = Inc(i))
                Console.WriteLine("ㅇㅇㅇ");
        }
    }
}
