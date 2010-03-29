using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Studio.WinFormsUI.Docking;

namespace Studio
{
    public partial class BikiniGuiView : DockContent
    {
        public BikiniGuiView()
        {
            InitializeComponent();
        }

        protected override string GetPersistString()
        {
            // Add extra information into the persist string for this document
            // so that it is available when deserialized.
            return GetType().ToString() + "," + "" + "," + Text;
        }

        UInt64 m_ID = 0;
        IntPtr m_handle = (IntPtr)0;
        private void BikiniGuiView_Paint(object sender, PaintEventArgs e)
        {
            if (m_handle != panel1.Handle)
            {
                if (m_ID != 0) Bikini.DestroyGuiView(m_ID);
                m_ID = Bikini.CreateGuiView(panel1.Handle);
                m_handle = panel1.Handle;
            }
            if (!Visible)
            {

            }
        }

        private void guiViewTimer_Tick(object sender, EventArgs e)
        {
            Refresh();
        }
    }
}
