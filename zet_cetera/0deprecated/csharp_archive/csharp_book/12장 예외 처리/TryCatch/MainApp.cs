using System;

namespace TryCatch
{
    class MainApp
    {
        static void Main(string[] args)
        {
            int[] arr = { 1, 2, 3 };

            try
            {
                for (int i = 0; i < 5; i++)
                {
                    Console.WriteLine(arr[i]);
                }
            }
            catch( IndexOutOfRangeException e )
            {
                Console.WriteLine("예외가 발생했습니다 : {0}", e.Message);
            }

            Console.WriteLine("종료");
        }
    }
}

