using System; 
 
namespace IntegralConversion 
{ 
    class MainApp 
    { 
        static void Main(string[] args) 
        { 
            sbyte a = 127; 
            Console.WriteLine(a); 
 
            int   b = (int)a; 
            Console.WriteLine(b); 
 
            int x = 128; // sbyte의 최대값 127보다 1 큰 수 
            Console.WriteLine(x); 
 
            sbyte y = (sbyte)x; 
            Console.WriteLine(y); 
        } 
    } 
} 
