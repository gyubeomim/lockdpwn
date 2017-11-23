using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ComplexPointers
{
    class A
    {
        public C c;
    }

    class B
    {
        public A a;
    }

    class C
    {
        public A a;
        public B[] b;
    }

    class D
    {
        public A a;
        public B b;
        public C c;
    }

    class MainApp
    {
        static void Main(string[] args)
        {
            A a = new A();
            B b = new B();
            C c = new C();
            D d = new D();

            a.c = c;
            b.a = a;
            c.a = a;
            c.b = new B[] { b, new B() };
            c.b[1].a = a;
            d.a = a;
            d.b = b;
            d.c = c;
        }
    }
}
