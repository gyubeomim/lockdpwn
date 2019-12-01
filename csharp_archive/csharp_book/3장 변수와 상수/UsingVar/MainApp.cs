using System;

namespace UsingVar
{
    class MainApp
    {
        static void Main(string[] args)
        {
            var a = 20;
            Console.WriteLine("Type: {0}, Value: {1}", a.GetType(), a);

            var b = 3.1414213;
            Console.WriteLine("Type: {0}, Value: {1}", b.GetType(), b);

            var c = "Hello, World!";
            Console.WriteLine("Type: {0}, Value: {1}", c.GetType(), c);

            var d = new int[] { 10, 20, 30 };
            Console.Write("Type: {0}, Value: ", d.GetType());
            foreach (var e in d)
                Console.Write("{0} ", e);

            Console.WriteLine();
        }
    }
}
