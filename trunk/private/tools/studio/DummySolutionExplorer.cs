using System;
using System.Collections;
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

            // test
			Queue l_queue = new Queue();
			l_queue.Enqueue(m_treeView.Nodes[0]);

			while (l_queue.Count > 0)
            {
				TreeNode l_node = (TreeNode)l_queue.Dequeue();

                switch (l_node.ImageKey)
                {
                    case "Project" :
                        l_node.Tag = new Bikini.Project();
                        break;
					case "Package":
						l_node.Tag = new Bikini.Package();
						break;
					case "Stage":
						l_node.Tag = new Bikini.Stage();
						break;
					case "Folder":
					case "FolderOpen":
						l_node.Tag = new Bikini.Folder();
						break;
				}

				foreach (TreeNode l_child in l_node.Nodes) l_queue.Enqueue(l_child);
            }
            // test
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
                if (e.Node.ImageKey == "Folder")
					e.Node.ImageKey = e.Node.SelectedImageKey = "FolderOpen";
            }
        }

        private void m_treeView_BeforeCollapse(object sender, TreeViewCancelEventArgs e)
        {
			if (m_cancelExpand || e.Node.ImageKey == "Project") e.Cancel = true;
            else
            {
                if (e.Node.ImageKey == "FolderOpen")
                    e.Node.ImageKey = e.Node.SelectedImageKey = "Folder";
            }
        }

        private void m_treeView_DoubleClick(object sender, EventArgs e)
        {

        }

        private void m_treeView_BeforeLabelEdit(object sender, NodeLabelEditEventArgs e)
        {

        }

		private void m_treeView_AfterSelect(object sender, TreeViewEventArgs e)
		{
			Program.MainWindow.PropertyWindow.SelectedObject = e.Node.Tag;
		}
    }
}