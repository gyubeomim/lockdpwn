using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace FileTest
{
    class MainApp
    {
        static void Main(string[] args)
        {
            DirectoryInfo dir = new DirectoryInfo("a");
            dir.MoveTo("b");

            Directory.Move("a", "b");
            string[] files =
                Directory.GetFiles("a");
            

        }
    }
}
