using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace Studio
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Idle += new EventHandler(Application_Idle);
            Application.Run(new MainForm());
        }

        static private void Application_Idle(Object sender, EventArgs e)
        {
            Bikini.Update(1.0f / 30.0f);
        }
    }
}