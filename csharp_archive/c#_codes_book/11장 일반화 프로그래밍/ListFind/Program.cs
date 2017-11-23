using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ListFind
{
    class Program
    {
        static void Main(string[] args)
        {
            List<string> list = new List<string>();
            list.Add("abc");
            list.Add("edf");
            list.Add("123");

            //string result = list.Find(

            //    (string a) =>
            //    {
            //        return a == "abc";
            //    }

            //    );

            string result = list.Find(
                delegate(string a) 
                {
                    return a == "abc";
                }
            );


            Console.WriteLine(result);
        }
    }
}
