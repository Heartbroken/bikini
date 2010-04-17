using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Studio.WinFormsUI.Docking;

namespace Studio
{
    public partial class DummySolutionExplorer : ToolWindow
    {
        public DummySolutionExplorer()
        {
            InitializeComponent();
        }

        protected override void OnRightToLeftLayoutChanged(EventArgs e)
        {
            m_treeView.RightToLeftLayout = RightToLeftLayout;
        }

        private void m_treeView_BeforeExpand(object sender, TreeViewCancelEventArgs e)
        {
            if (e.Node.ImageIndex == 2) e.Node.ImageIndex = 1;
        }

        private void m_treeView_BeforeCollapse(object sender, TreeViewCancelEventArgs e)
        {
            if (e.Node.ImageIndex == 1) e.Node.ImageIndex = 2;
        }
    }
}