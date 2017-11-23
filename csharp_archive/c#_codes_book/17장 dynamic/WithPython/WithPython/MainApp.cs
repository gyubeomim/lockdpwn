using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Microsoft.Scripting;
using Microsoft.Scripting.Hosting;
using IronPython.Hosting;

namespace WithPython
{
    class MainApp
    {
        static void Main(string[] args)
        {
            ScriptEngine engine = Python.CreateEngine();
            ScriptScope scope = engine.CreateScope();
            scope.SetVariable("n", "박상현");
            scope.SetVariable("p", "010-123-4566");
            
            ScriptSource source = engine.CreateScriptSourceFromString(
                @"
class NameCard :
    name = ''
    phone = ''

    def __init__(self, name, phone) : 
        self.name = name 
        self.phone = phone

    def printNameCard(self) : 
        print self.name + ', ' + self.phone

NameCard(n, p)
");
            dynamic result = source.Execute(scope);
            result.printNameCard();

            Console.WriteLine("{0}, {1}", result.name, result.phone);
        }
    }
}
