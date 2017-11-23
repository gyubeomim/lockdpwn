using System;
using System.Windows.Forms;

namespace FormAndControl
{
    class MainApp : Form
    {
        static void Main(string[] args)
        {
            Button button = new Button();

            button.Text = "Click Me!";
            button.Left = 100;
            button.Top = 50;

            button.Click += 
                (object sender, EventArgs e) =>
                {
                    MessageBox.Show("딸깍!");
                };

            MainApp form = new MainApp();
            form.Text = "Form & Control";
            form.Height = 150;

            form.Controls.Add(button);

            Application.Run(form);
        }
    }
}
