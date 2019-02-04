using System;

namespace ConditionalOperator
{
    class MainApp
    {
        static void Main(string[] args)
        {
            string result = (10 % 2) == 0 ? "짝수" : "홀수";

            Console.WriteLine(result);
        }
    }
}
