using System;
using System.Linq.Expressions;

namespace ExpTreeSum1To100
{
    class MainApp
    {
        static void Main(string[] args)
        {
            Expression exp = Expression.Constant(1);

            for (int i = 2; i <= 100; i++)
            {
                exp = Expression.Add(exp, Expression.Constant(i));
            }

            Expression<Func<int>> sum1to100 =
                Expression<Func<int>>.Lambda<Func<int>>(exp, null);

            Console.WriteLine( sum1to100.Compile().Invoke() );
        }
    }
}
