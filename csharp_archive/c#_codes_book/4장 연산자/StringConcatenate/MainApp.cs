using System;

namespace StringConcatenate
{
    class MainApp
    {
        static void Main(string[] args)
        {
            string result = "123" + "456";
            Console.WriteLine(result);

            result = "Hello" + " " + "World!";

            Console.WriteLine(result);
        }
    }
}
