using System;
using System.Runtime.CompilerServices;

namespace CallerInfo
{
    public static class Trace  
    {  
        public static void WriteLine(string message,  
            [CallerFilePath] string file = "",  
            [CallerLineNumber] int line = 0,  
            [CallerMemberName] string member = "")  
        {  
            Console.WriteLine(
                "{0}(Line:{1}) {2}: {3}", file, line, member, message);  
        }  
    }  

    class MainApp
    {
        static void Main(string[] args)
        {
            Trace.WriteLine("즐거운 프로그래밍!");
        }
    }
}
