using System;

namespace ForEach
{
    class MainApp
    {
        static void Main(string[] args)
        {
            int[] arr = new int[]{0, 1, 2, 3, 4};

            foreach (int a in arr)
            {
                Console.WriteLine(a);
            }
        }
    }
}
