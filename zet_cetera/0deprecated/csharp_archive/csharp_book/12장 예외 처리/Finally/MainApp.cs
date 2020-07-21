using System;

namespace Finally
{
    class MainApp
    {
        static int Divide(int divisor, int dividend)
        {
            try
            {
                Console.WriteLine("Divide() 시작");
                return divisor / dividend;
            }
            catch (DivideByZeroException e)
            {
                Console.WriteLine("Divide() 예외 발생");
                throw e;
            }
            finally
            {
                Console.WriteLine("Divide()  끝");
            }
        }

        static void Main(string[] args)
        {
            try
            {
                Console.Write("제수를 입력하세요. :");
                String temp = Console.ReadLine();
                int divisor = Convert.ToInt32(temp);

                Console.Write("피제수를 입력하세요. : ");
                temp = Console.ReadLine();
                int dividend = Convert.ToInt32(temp);

                Console.WriteLine("{0}/{1} = {2}",
                    divisor, dividend, Divide(divisor, dividend));
            }
            catch (FormatException e)
            {
                Console.WriteLine("에러 : " + e.Message);
            }
            catch (DivideByZeroException e)
            {
                Console.WriteLine("에러 : " + e.Message);
            }
            finally
            {
                Console.WriteLine("프로그램을 종료합니다.");
            }
        }
    }
}
