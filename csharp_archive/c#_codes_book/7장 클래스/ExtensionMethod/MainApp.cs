using System;
using MyExtension;

namespace MyExtension
{
    public static class IntegerExtension
    {
        public static int Square(this int myInt)
        {
            return myInt * myInt;
        }

        public static int Power(this int myInt, int exponent)
        {
            int result = myInt;
            for (int i = 1; i < exponent; i++)
                result = result * myInt;

            return result;
        }
    }
}

namespace ExtensionMethod
{
    class MainApp
    {
        static void Main(string[] args)
        {
            Console.WriteLine("{0}^2 : {1}", 3, 3.Square());
            Console.WriteLine("{0}^{1} : {2}", 3, 4, 3.Power(4));
            Console.WriteLine("{0}^{1} : {2}", 2, 10, 2.Power(10));
        }
    }
}
