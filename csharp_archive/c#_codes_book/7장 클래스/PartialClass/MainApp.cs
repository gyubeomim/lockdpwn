using System;

namespace PartialClass
{
    partial class MyClass
    {
        public void Method1()
        {
            Console.WriteLine("Method1");
        }

        public void Method2()
        {
            Console.WriteLine("Method2");
        }
    }

    partial class MyClass
    {
        public void Method3()
        {
            Console.WriteLine("Method3");
        }

        public void Method4()
        {
            Console.WriteLine("Method4");
        }
    }

    class MainApp
    {
        static void Main(string[] args)
        {
            MyClass obj = new MyClass();
            obj.Method1();
            obj.Method2();
            obj.Method3();
            obj.Method4();
        }
    }
}
