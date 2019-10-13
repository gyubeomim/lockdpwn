using System;

namespace ModifierOnAccessor
{
    public class NameCard
    {
        private string name;
        private string phoneNumber;

        public string Name
        {
            get { return name; }
            private set { name = value; }
        }

        public string PhoneNumber
        {
            get { return phoneNumber; }
            private set { phoneNumber = value; }
        }
    }

    class MainClass
    {
        static void Main()
        {
            

            System.Console.WriteLine("Base: {0}, {1}", b1.Name, b1.Id);
            System.Console.WriteLine("Derived: {0}, {1}", d1.Name, d1.Id);

            // Keep the console window open in debug mode.
            System.Console.WriteLine("Press any key to exit.");
            System.Console.ReadKey();
        }
    }
}
