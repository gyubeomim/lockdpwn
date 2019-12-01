using System;
using System.Threading;

namespace BasicThread
{
    class MainApp
    {
        static void DoSomething()
        {
            for (int i = 0; i < 5; i++)
            {
                Console.WriteLine("DoSomething : {0}", i);
                Thread.Sleep(10);
            }
        }

        static void Main(string[] args)
        {            
            Thread t1 = new Thread(new ThreadStart(DoSomething));

            Console.WriteLine("Starting thread...");
            t1.Start();

            for (int i = 0; i < 5; i++)
            {
                Console.WriteLine("Main : {0}", i);
                Thread.Sleep(10);
            }
            
            Console.WriteLine("Wating until thread stops...");
            t1.Join();

            Console.WriteLine("Finished");
        }
    }
}
