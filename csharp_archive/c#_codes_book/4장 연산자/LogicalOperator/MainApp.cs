using System;

namespace LogicalOperator
{
    class MainApp
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Testing && ... ");
            Console.WriteLine("1 > 0 && 4 < 5 : {0}", 1 > 0 && 4 < 5);
            Console.WriteLine("1 > 0 && 4 > 5 : {0}", 1 > 0 && 4 > 5);
            Console.WriteLine("1 == 0 && 4 > 5 : {0}", 1 == 0 && 4 > 5);
            Console.WriteLine("1 == 0 && 4 < 5 : {0}", 1 == 0 && 4 < 5);

            Console.WriteLine("\nTesting || ... ");
            Console.WriteLine("1 > 0 || 4 < 5 : {0}", 1 > 0 || 4 < 5);
            Console.WriteLine("1 > 0 || 4 > 5 : {0}", 1 > 0 || 4 > 5);
            Console.WriteLine("1 == 0 || 4 > 5 : {0}", 1 == 0 || 4 > 5);
            Console.WriteLine("1 == 0 || 4 < 5 : {0}", 1 == 0 || 4 < 5);

            Console.WriteLine("\nTesting ! ...");
            Console.WriteLine("!True : {0}", !true);
            Console.WriteLine("!False: {0}", !false);
        }
    }
}
