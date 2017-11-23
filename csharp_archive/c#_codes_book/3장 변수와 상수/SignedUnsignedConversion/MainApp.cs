using System; 
 
namespace SignedUnsignedConversion 
{ 
    class MainApp 
    { 
        static void Main(string[] args) 
        { 
            int a = 500; 
            Console.WriteLine(a); 
 
            uint b = (uint)a; 
            Console.WriteLine(b); 
 
            int x = -30; 
            Console.WriteLine(x); 
             
            uint y = (uint)x; 
            Console.WriteLine(y); 
        } 
    } 
} 
