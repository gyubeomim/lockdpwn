using System;
using System.IO;

namespace Touch
{
    class MainApp
    {
        static void OnWrongPathType(string type)
        {
            Console.WriteLine("{0} is wrong type", type);
            return;
        }

        static void Main(string[] args)
        {
            if (args.Length == 0)
            {
                Console.WriteLine(
                    "Usage : Touch.exe <Path> [Type:File/Directory]");
                return;
            }

            string path = args[0];
            string type = "File";
            if (args.Length > 1)
                type = args[1];

            if (File.Exists(path) || Directory.Exists(path))
            {
                if (type == "File")
                    File.SetLastWriteTime(path, DateTime.Now);
                else if (type == "Directory")
                    Directory.SetLastWriteTime(path, DateTime.Now);
                else
                {
                    OnWrongPathType(path);
                    return;
                }
                Console.WriteLine("Updated {0} {1}", path, type);
            }
            else
            {            
                if (type == "File")
                    File.Create(path).Close();
                else if (type == "Directory")
                    Directory.CreateDirectory(path);
                else
                {
                    OnWrongPathType(path);
                    return;
                }
                
                Console.WriteLine("Created {0} {1}", path, type);
            }                        
        }
    }
}
