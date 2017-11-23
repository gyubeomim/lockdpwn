using System;
using System.Collections;

namespace UsingList
{
    class MainApp
    {
        static void Main(string[] args)
        {
            ArrayList list = new ArrayList();
            for (int i = 0; i < 5; i++)
                list.Add(i);

            foreach (object obj in list)
                Console.Write("{0} ", obj);
            Console.WriteLine();

            list.RemoveAt(2);

            foreach (object obj in list)
                Console.Write("{0} ", obj);
            Console.WriteLine();

            list.Insert(2, 2);

            foreach (object obj in list)
                Console.Write("{0} ", obj);
            Console.WriteLine();

            list.Add("abc");
            list.Add("def");

            for ( int i=0; i<list.Count; i++ )
                Console.Write("{0} ", list[i]);
            Console.WriteLine();
       }
    }
}


