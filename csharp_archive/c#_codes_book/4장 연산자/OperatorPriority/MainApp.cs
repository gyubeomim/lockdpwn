using System;

namespace OperatorPriority
{
    class MainApp
    {
        static void Main(string[] args)
        {
            Console.WriteLine( 1 * 2 + 3 * 4 );

            Console.WriteLine( 1 * (2 + 3) * 4 );

            Console.WriteLine( 4 - (3 + 2) / 1 );
        }
    }
}
