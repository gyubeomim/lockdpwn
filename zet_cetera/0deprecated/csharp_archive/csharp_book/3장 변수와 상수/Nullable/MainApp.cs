using System; 
     
namespace Nullalble 
{ 
    class MainApp 
    { 
        static void Main(string[] args) 
        { 
            int? a = null; 
     
            Console.WriteLine(a.HasValue); 
            Console.WriteLine(a != null); 
                             
            a = 3; 
     
            Console.WriteLine(a.HasValue); 
            Console.WriteLine(a != null); 
            Console.WriteLine(a.Value); 
        } 
    } 
} 
