using System;
using System.Reflection;

namespace DynamicInstance
{
    class Profile
    {
        private string name;
        private string phone;
        public Profile()
        {
            name = ""; phone = "";
        }

        public Profile(string name, string phone)
        {
            this.name = name;
            this.phone = phone;
        }

        public void Print()
        {
            Console.WriteLine("{0}, {1}", name, phone);
        }

        public string Name
        {
            get { return name; }
            set { name = value; }
        }

        public string Phone
        {
            get { return phone; }
            set { phone = value; }
        }
    }

    class MainApp
    {
        static void Main(string[] args)
        {
            Type type = Type.GetType("DynamicInstance.Profile");
            MethodInfo methodInfo = type.GetMethod("Print");
            PropertyInfo nameProperty = type.GetProperty("Name");
            PropertyInfo phoneProperty = type.GetProperty("Phone");

            object profile = Activator.CreateInstance(type, "박상현", "512-1234");            
            methodInfo.Invoke(profile, null);

            profile = Activator.CreateInstance(type);            
            nameProperty.SetValue(profile, "박찬호", null);            
            phoneProperty.SetValue(profile, "997-5511", null);

            Console.WriteLine("{0}, {1}",
                nameProperty.GetValue(profile, null),
                phoneProperty.GetValue(profile, null));
        }
    }
}
