/*
 *  c# ==> 뇌자극c# p410, 이벤트라는 개념을 활용해 본 코드
 */
using System;

namespace testcsharp {
    delegate void EventHandler(string message);

    class test {
        public event EventHandler something;

        public void DoSomething(int number) {
            int temp = number % 10;

            if (temp != 0 && temp % 3 == 0) {
                something(string.Format("{0} : 짝", number));
            }
        }

    class MainApp {
            static public void Myhandler(string message) {
                Console.WriteLine(message);
				
            }

            static void Main(string[] args) {
                test test = new test();
                test.something += new EventHandler(Myhandler);

                for(int i =1; i < 30; i++) {
                    test.DoSomething(i);
                }
            }
        }


    }
}
