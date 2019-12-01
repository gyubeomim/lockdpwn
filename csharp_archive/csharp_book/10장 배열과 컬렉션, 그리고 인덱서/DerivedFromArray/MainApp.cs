using System;

namespace DerivedFromArray
{
    class MainApp
    {
        static void Main(string[] args)
        {
            int[] array = new int[] { 10, 30, 20, 7, 1 };
            Console.WriteLine("Type Of array : {0}", array.GetType());
            Console.WriteLine("Base type Of array : {0}", array.GetType().BaseType);
        }
    }
}
