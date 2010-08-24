using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace Studio
{
    static class Program
    {
        static private MainForm m_mainForm = null;
		static public MainForm MainWindow { get { return m_mainForm; } }

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            if (Bikini.CreateWorkspace())
            {
                Application.EnableVisualStyles();
                Application.SetCompatibleTextRenderingDefault(false);
                Application.Idle += new EventHandler(Application_Idle);
                m_mainForm = new MainForm();
                Application.Run(m_mainForm);
                Bikini.DestroyWorkspace();
            }
        }

        static private void Application_Idle(Object sender, EventArgs e)
        {
            m_mainForm.UpdateViews();
            Bikini.Update();
        }
    }
}