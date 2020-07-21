using System;
using System.Reflection;
using System.Reflection.Emit;

namespace EmitAndDynamic
{
    class MainApp
    {
        static void Main(string[] args)
        {
            AssemblyBuilder newAssembly =
             AppDomain.CurrentDomain.DefineDynamicAssembly(
                 new AssemblyName("CalculatorAssembly"), AssemblyBuilderAccess.Run);

            ModuleBuilder newModule = newAssembly.DefineDynamicModule("Calculator", true);
            TypeBuilder newType = newModule.DefineType("Sum1To100");

            MethodBuilder newMethod = newType.DefineMethod(
                "Calculate",
                MethodAttributes.Public,
                typeof(int),    // 반환 형식
                new Type[0]);   // 매개 변수

            ILGenerator generator = newMethod.GetILGenerator();

            generator.Emit(OpCodes.Ldc_I4, 1);

            for (int i = 2; i <= 100; i++)
            {
                generator.Emit(OpCodes.Ldc_I4, i);
                generator.Emit(OpCodes.Add);
            }

            generator.Emit(OpCodes.Ret);
            newType.CreateType();
            Console.WriteLine(newType.FullName);
            //newAssembly.Save("CalculatorAssembly.dll");

            // object sum1To100 = Activator.CreateInstance(newType);
            // MethodInfo Calculate = sum1To100.GetType().GetMethod("Calculate");
            // Console.WriteLine(Calculate.Invoke(sum1To100, null));
            
            
            Type t = newAssembly.GetType("Sum1To100");

            dynamic sum1To100 = Activator.CreateInstance(t);
            Type a = sum1To100.GetType();
            MethodInfo Calculate = a.GetMethod("Calculate");
            Console.WriteLine(Calculate.Invoke(sum1To100, null));
            sum1To100.Calculate();
        }
    }
}
