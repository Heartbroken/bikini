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

        bool m_cancelExpand = false;

        private void m_treeView_MouseDown(object sender, MouseEventArgs e)
        {
            m_cancelExpand = e.Clicks > 1;
        }

        private void m_treeView_BeforeExpand(object sender, TreeViewCancelEventArgs e)
        {
            if (m_cancelExpand) e.Cancel = true;
            else
            {
                if (e.Node.ImageIndex == 2)
                {
                    e.Node.ImageIndex = 1;
                    e.Node.SelectedImageIndex = 1;
                }
            }
        }

        private void m_treeView_BeforeCollapse(object sender, TreeViewCancelEventArgs e)
        {
            if (m_cancelExpand) e.Cancel = true;
            else
            {
                if (e.Node.ImageIndex == 1)
                {
                    e.Node.ImageIndex = 2;
                    e.Node.SelectedImageIndex = 2;
                }
            }
        }

        private void m_treeView_DoubleClick(object sender, EventArgs e)
        {

        }

        private void m_treeView_BeforeLabelEdit(object sender, NodeLabelEditEventArgs e)
        {

        }
    }
}