using System;

namespace StackTrace
{
    class MainApp
    {
        static void Main(string[] args)
        {
            try
            {
                int a = 1;
                Console.WriteLine(3 / --a);
            }
            catch (DivideByZeroException e)
            {
                Console.WriteLine(e.StackTrace);
            }
        }
    }
}
