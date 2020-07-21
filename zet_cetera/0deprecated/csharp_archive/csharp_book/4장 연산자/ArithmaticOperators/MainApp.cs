using System;

namespace ArithmaticOperators
{
    class MainApp
    {
        static void Main(string[] args)
        {
            int a = 111 + 222;
            Console.WriteLine("a : {0}", a);

            int b = a - 100;
            Console.WriteLine("b : {0}", b);

            int c = b * 10;
            Console.WriteLine("c : {0}", c);

            double d = c / 6.3;
            Console.WriteLine("d : {0}", d);

            Console.WriteLine("22 / 7 = {0}({1})", 22 / 7, 22 / 7);
        }
    }
}
