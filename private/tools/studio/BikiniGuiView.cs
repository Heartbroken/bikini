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
        ~BikiniGuiView()
        {
            if (m_viewID != Bikini.BadID) Bikini.DestroyGuiView(m_viewID);
        }

        protected override string GetPersistString()
        {
            // Add extra information into the persist string for this document
            // so that it is available when deserialized.
            return GetType().ToString() + "," + "" + "," + Text;
        }

        UInt64 m_viewID = Bikini.BadID;
        IntPtr m_handle = (IntPtr)0;
        private void BikiniGuiView_Paint(object sender, PaintEventArgs e)
        {

        }

        private void guiViewTimer_Tick(object sender, EventArgs e)
        {
            if (m_handle != panel1.Handle)
            {
                if (m_viewID != Bikini.BadID) Bikini.DestroyGuiView(m_viewID);
                m_viewID = Bikini.CreateGuiView(panel1.Handle);
                m_handle = panel1.Handle;
            }
            Refresh();
        }
    }
}
