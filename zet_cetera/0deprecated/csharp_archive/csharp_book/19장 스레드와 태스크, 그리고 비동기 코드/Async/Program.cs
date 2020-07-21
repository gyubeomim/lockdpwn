using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Async
{
    class Program
    {
        async static private void AsyncFunction(int count)
        {

            await Task.Run(async () =>
                {
                    for (int i = 1; i <= count; i++)
                    {
                        await Task.Delay(1000);
                        Console.WriteLine("{0}/{1} ...", i, count);
                    }
                    
                    Console.WriteLine("All Done!!");
                });
            
        }

        static void DoAsyncJob()
        {
            Console.WriteLine("Before Calling AsyncFunction()");
            AsyncFunction(7);
            Console.WriteLine("After Calling AsyncFunction()");
        }

        static void Main(string[] args)
        {
            DoAsyncJob();

            Console.WriteLine("(종료하고 싶으면 엔터 키를 누르세요.)");
            Console.ReadLine(); // 프로그램 종료 방지
        }
    }
}
