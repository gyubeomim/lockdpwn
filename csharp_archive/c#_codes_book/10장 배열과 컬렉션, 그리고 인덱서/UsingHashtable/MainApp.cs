using System;
using System.Collections;

namespace UsingHashtable
{
    class MainApp
    {
        static void Main(string[] args)
        {
            Hashtable ht = new Hashtable();
            ht["하나"] = "one";
            ht["둘"]   = "two";
            ht["셋"]   = "three";
            ht["넷"]   = "four";
            ht["다섯"] = "five";

            Console.WriteLine( ht["하나"] ) ;
            Console.WriteLine( ht["둘"]   );
            Console.WriteLine( ht["셋"]   );
            Console.WriteLine( ht["넷"]   );
            Console.WriteLine( ht["다섯"] );
        }
    }
}
