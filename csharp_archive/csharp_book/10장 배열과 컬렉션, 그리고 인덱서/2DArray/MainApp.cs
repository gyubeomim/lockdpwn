using System;

namespace _2DArray
{
    class MainApp
    {
        static void Main(string[] args)
        {
            int[,] arr = new int[2, 3]{ {1, 2, 3}, {4, 5, 6} };
            
            for (int i = 0; i < arr.GetLength(0); i++)
            {
                for (int j = 0; j < arr.GetLength(1); j++)
                {
                    Console.Write("[{0}, {1}] : {2} ", i, j, arr[i, j]);
                }
                Console.WriteLine();
            }
            Console.WriteLine();


            int[,] arr2 = new int[,] { { 1, 2, 3 }, { 4, 5, 6 } };

            for (int i = 0; i < arr2.GetLength(0); i++)
            {
                for (int j = 0; j < arr2.GetLength(1); j++)
                {
                    Console.Write("[{0}, {1}] : {2} ", i, j, arr2[i, j]);
                }
                Console.WriteLine();
            }
            Console.WriteLine();

            int[,] arr3 = { { 1, 2, 3 }, { 4, 5, 6 } };

            for (int i = 0; i < arr2.GetLength(0); i++)
            {
                for (int j = 0; j < arr2.GetLength(1); j++)
                {
                    Console.Write("[{0}, {1}] : {2} ", i, j, arr3[i, j]);
                }
                Console.WriteLine();
            }
            Console.WriteLine();
        }
    }
}
