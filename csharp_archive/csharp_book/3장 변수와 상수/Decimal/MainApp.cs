using System; 
 
namespace Decimal 
{ 
    class MainApp 
    { 
        static void Main(string[] args) 
        { 
            float   a = 3.141592653589793238462643383279f; 
            double  b = 3.141592653589793238462643383279; 
            decimal c = 3.141592653589793238462643383279m; 
 
            Console.WriteLine(a); 
            Console.WriteLine(b); 
            Console.WriteLine(c);             	
        } 
    } 
} 
