using System;

namespace This
{
    class Employee
    {
        private string Name;
        private string Position;

        public void SetName(string Name)
        {
            this.Name = Name;
        }

        public string GetName()
        {
            return Name;
        }

        public void SetPosition(string Position)
        {
            this.Position = Position;
        }

        public string GetPosition()
        {
            return this.Position;
        }
    }

    class MainApp
    {
        static void Main(string[] args)
        {
            Employee pooh = new Employee();
            pooh.SetName("Pooh");
            pooh.SetPosition("Waiter");
            Console.WriteLine("{0} {1}", pooh.GetName(), pooh.GetPosition());

            Employee tigger = new Employee();
            tigger.SetName("Tigger");
            tigger.SetPosition("Cleaner");
            Console.WriteLine("{0} {1}", tigger.GetName(), tigger.GetPosition());
        }
    }
}
