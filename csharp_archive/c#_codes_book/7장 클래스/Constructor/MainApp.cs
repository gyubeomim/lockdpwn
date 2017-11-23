using System;

namespace Constructor
{
    class Cat
    {
        public Cat()
        {
            Name = "";
            Color = "";
        }

        public Cat(string _Name, string _Color)
        {
            Name = _Name;
            Color = _Color;
        }

        ~Cat()
        {
            Console.WriteLine("{0} : 잘가", Name);
        }

        public string Name;
        public string Color;

        public void Meow()
        {
            Console.WriteLine("{0} : 야옹", Name);
        }
    }

    class MainApp
    {
        static void Main(string[] args)
        {
            Cat kitty = new Cat("키티", "하얀색");
            kitty.Meow();
            Console.WriteLine("{0} : {1}", kitty.Name, kitty.Color);

            Cat nero = new Cat("네로", "검은색");
            nero.Meow();
            Console.WriteLine("{0} : {1}", nero.Name, nero.Color);
        }
    }
}
