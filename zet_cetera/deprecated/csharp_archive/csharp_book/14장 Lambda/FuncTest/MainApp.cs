using System;

namespace FuncTest
{
    class MainApp
    {
        static void Main(string[] args)
        {
            Func<int> func1 = () => 10;
            Console.WriteLine("func1() : {0}", func1());

            Func<int, int> func2 = (x) => x * 2;
            Console.WriteLine("func2(4) : {0}", func2(4));

            Func<double, double, double> func3 =
                (x, y) => x / y;
            Console.WriteLine("func3(22/7) : {0}", func3(22, 7));                
        }
    }
}
