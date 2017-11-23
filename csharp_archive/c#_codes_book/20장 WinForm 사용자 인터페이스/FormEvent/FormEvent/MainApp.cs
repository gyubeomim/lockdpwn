using System;
using System.Windows.Forms;

namespace FormEvent
{
    class MainApp : Form
    {
        public void MyMouseHandler(object sender, MouseEventArgs e)
        {
            Console.WriteLine("Sender : {0}", ((Form)sender).Text);
            Console.WriteLine("X:{0}, Y:{1}", e.X, e.Y);
            Console.WriteLine("Button:{0}, Clicks:{1}", e.Button, e.Clicks);
            Console.WriteLine();
        }

        public MainApp(string title)
        {
            this.Text = title;
            this.MouseDown +=
                new MouseEventHandler(MyMouseHandler);
        }

        static void Main(string[] args)
        {
            Application.Run(new MainApp("Mouse Event Test"));
        }
    }
}
