﻿using System;
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
    public partial class BikiniView : DockContent
    {
        private UInt64 m_viewID = Bikini.BadID;
        private IntPtr m_handle = (IntPtr)0;

        public BikiniView()
        {
            InitializeComponent();
            m_viewID = Bikini.CreateView(panel1.Handle);
            m_handle = panel1.Handle;

            // test
			//Bikini.CreateProject();
        }
        ~BikiniView()
        {
            Bikini.DestroyView(m_viewID);
        }

        protected override string GetPersistString()
        {
            // Add extra information into the persist string for this document
            // so that it is available when deserialized.
            return GetType().ToString() + "," + "" + "," + Text;
        }

        public void UpdateView()
        {
            if (m_handle != panel1.Handle)
            {
                Bikini.ResetView(m_viewID, panel1.Handle);
                m_handle = panel1.Handle;
            }
            Refresh();
        }
    }
}
