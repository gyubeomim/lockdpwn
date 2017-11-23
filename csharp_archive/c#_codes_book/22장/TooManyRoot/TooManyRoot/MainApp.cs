using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TooManyRoot
{
    class Counter
    {
        public int A {get;set;}
    }

    class MainApp
    {
        public static void Recursive(Counter counter)
        {
            counter.A++;
            
            Console.WriteLine(counter.A);
            Recursive(counter);
        }

        static void Main(string[] args)
        {
            Recursive(new Counter());
        }
    }
}
