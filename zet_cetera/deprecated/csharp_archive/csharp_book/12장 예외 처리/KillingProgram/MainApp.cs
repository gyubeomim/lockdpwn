using System;

namespace KillingProgram
{
    class MainApp
    {
        static void Main(string[] args)
        {
            int[] arr = {1, 2, 3};

            for (int i = 0; i < 5; i++)
            {
                Console.WriteLine(arr[i]);
            }

            Console.WriteLine("종료");
        }
    }
}
