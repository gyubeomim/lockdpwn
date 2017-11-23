using System;

namespace PropertiesInInterface
{
    interface INamedValue
    {
        string Name
        {
            get;
            set;
        }

        string Value
        {
            get;
            set;
        }
    }

    class NamedValue : INamedValue
    {
        public string Name
        {
            get;
            set;
        }

        public string Value
        {
            get;
            set;
        }
    }    

    class MainApp
    {
        static void Main(string[] args)
        {
            NamedValue name = new NamedValue() 
            { Name = "이름", Value = "박상현" };

            NamedValue height = new NamedValue() 
            { Name = "키", Value = "177Cm" };

            NamedValue weight = new NamedValue() 
            { Name = "몸무게", Value = "90Kg" };

            Console.WriteLine("{0} : {1}", name.Name, name.Value);
            Console.WriteLine("{0} : {1}", height.Name, height.Value);
            Console.WriteLine("{0} : {1}", weight.Name, weight.Value);
        }
    }
}
