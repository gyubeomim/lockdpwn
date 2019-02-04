using System;
using System.Drawing;
using System.Windows.Forms;

namespace FormBackground
{
    class MainApp : Form
    {
        Random rand;
        public MainApp()
        {
            rand = new Random();
            
            this.MouseWheel += new MouseEventHandler(MainApp_MouseWheel);
            this.MouseDown += new MouseEventHandler(MainApp_MouseDown);
        }

        void MainApp_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                Color oldColor = this.BackColor;
                this.BackColor = Color.FromArgb(rand.Next(0, 255),
                                                rand.Next(0, 255),
                                                rand.Next(0, 255));
            }
            else if (e.Button == MouseButtons.Right)
            {
                if (this.BackgroundImage != null)
                {
                    this.BackgroundImage = null;
                    return;
                }

                string file = "sample.jpg";
                if (System.IO.File.Exists(file) == false)
                    MessageBox.Show("이미지 파일이 없습니다.");
                else
                    this.BackgroundImage = Image.FromFile(file);
            }            
        }

        void MainApp_MouseWheel(object sender, MouseEventArgs e)
        {
            this.Opacity = this.Opacity + ( e.Delta>0?0.1:-0.1 );
            Console.WriteLine("Opacity: {0}", this.Opacity);
        }

        static void Main(string[] args)
        {
            Application.Run(new MainApp());
        }
    }
}
