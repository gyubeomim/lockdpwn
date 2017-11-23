using System;
using System.Windows.Forms;

namespace FormSize
{
    class MainApp : Form
    {
        static void Main(string[] args)
        {
            MainApp form = new MainApp();
            form.Width = 300;
            form.Height = 200;

            form.MouseDown += new MouseEventHandler(form_MouseDown);

            Application.Run(form);
        }

        static void form_MouseDown(object sender, MouseEventArgs e)
        {
            Form form = (Form)sender;
            int oldWidth  = form.Width;
            int oldHeight = form.Height;

            if (e.Button == MouseButtons.Left)
            {
                if (oldWidth < oldHeight)
                {
                    form.Width  = oldHeight;
                    form.Height = oldWidth;
                }
            }
            else if (e.Button == MouseButtons.Right)
            {                
                if (oldHeight < oldWidth)
                {
                    form.Width = oldHeight;
                    form.Height = oldWidth;
                }
            }
            Console.WriteLine("윈도우의 크기가 변경되었습니다");
            Console.WriteLine("Width: {0}, Height: {1}", form.Width, form.Height);
        }
    }
}
