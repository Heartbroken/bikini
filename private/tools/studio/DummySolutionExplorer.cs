using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Studio.WinFormsUI.Docking;
using System.Runtime.InteropServices;

namespace Studio
{
    public partial class DummySolutionExplorer : ToolWindow
    {
        public DummySolutionExplorer()
		{
			InitializeComponent();

			// test
			{
				TreeNode l_projectNode = AddNode(new Bikini.Project("Grrr"), m_treeView.Nodes);
				l_projectNode.Expand();
				{
					TreeNode l_packageNode = AddNode(new Bikini.Package("Grrr"), l_projectNode.Nodes);
					{
						TreeNode l_stageNode = AddNode(new Bikini.Stage("Main"), l_packageNode.Nodes);
					}
				}
				{
					TreeNode l_folderNode = AddNode(new Bikini.Folder("Episodes"), l_projectNode.Nodes);
					{
						TreeNode l_packageNode = AddNode(new Bikini.Package("E1"), l_folderNode.Nodes);
						{
							TreeNode l_stageNode = AddNode(new Bikini.Stage("E1S1"), l_packageNode.Nodes);
						}
					}
				}
			}
			//
			//if (m_treeView.Nodes.Count > 0)
			//{
			//    Queue l_queue = new Queue();
			//    l_queue.Enqueue(m_treeView.Nodes[0]);

			//    while (l_queue.Count > 0)
			//    {
			//        TreeNode l_node = (TreeNode)l_queue.Dequeue();

			//        switch (l_node.ImageKey)
			//        {
			//            case "Project":
			//                l_node.Tag = new Bikini.Project();
			//                break;
			//            case "Package":
			//                l_node.Tag = new Bikini.Package();
			//                break;
			//            case "Stage":
			//                l_node.Tag = new Bikini.Stage();
			//                break;
			//            case "Folder":
			//            case "FolderOpen":
			//                l_node.Tag = new Bikini.Folder();
			//                break;
			//        }

			//        foreach (TreeNode l_child in l_node.Nodes) l_queue.Enqueue(l_child);
			//    }
			//}
			// test
		}

		private TreeNode AddNode(Bikini.ProjectItem _item, TreeNodeCollection _nodes)
		{
			TreeNode l_node = _nodes.Add("", _item.FullName(), _item.Type, _item.Type);
			l_node.Tag = _item; _item.treeNode = l_node;

			return l_node;
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

		private void m_treeView_MouseUp(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Right)
			{
				TreeNode l_node = m_treeView.GetNodeAt(e.Location);
				if (l_node != null)
				{
					m_treeView.SelectedNode = l_node;
					if (l_node.Tag is Bikini.Project)
						m_projectContextMenu.Show(m_treeView.PointToScreen(e.Location));
				}
			}
			//else if (e.Button == MouseButtons.Left)
			//{
			//    TreeNode l_node = m_treeView.GetNodeAt(e.Location);
			//    if (l_node != null && l_node == m_treeView.SelectedNode)
			//    {
			//        Bikini.ProjectItem l_item = (Bikini.ProjectItem)l_node.Tag;
			//        l_node.Text = l_item.Name;
			//        m_treeView.LabelEdit = true;
			//        if (l_node.IsEditing) l_node.BeginEdit();
			//    }
			//}
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

		private void m_treeView_Click(object sender, EventArgs e)
		{
		//	TreeNode l_node = m_treeView.GetNodeAt(e.Location);
		}

        private void m_treeView_DoubleClick(object sender, EventArgs e)
        {

        }

		[DllImport("User32.dll", CharSet = CharSet.Auto)]
		private static extern IntPtr SendMessage(IntPtr hWnd, int Msg, IntPtr wParam, IntPtr lParam);
		private const int TV_FIRST = 0x1100;
		private const int TVM_GETEDITCONTROL = TV_FIRST + 15;
		private const int WM_SETTEXT = 0x000C;
        private void m_treeView_BeforeLabelEdit(object sender, NodeLabelEditEventArgs e)
        {
			if (e.Node.Tag is Bikini.ProjectItem)
			{
			    Bikini.ProjectItem l_item = (Bikini.ProjectItem)e.Node.Tag;
				IntPtr l_editBoxHandle = SendMessage(m_treeView.Handle, TVM_GETEDITCONTROL, IntPtr.Zero, IntPtr.Zero);
				SendMessage(l_editBoxHandle, WM_SETTEXT, IntPtr.Zero, Marshal.UnsafeAddrOfPinnedArrayElement(Encoding.Unicode.GetBytes(l_item.Name), 0));
			}
		}

		private void m_treeView_AfterLabelEdit(object sender, NodeLabelEditEventArgs e)
		{
			e.CancelEdit = true;
			e.Node.EndEdit(true);

			if (e.Node.Tag is Bikini.ProjectItem)
			{
				Bikini.ProjectItem l_item = (Bikini.ProjectItem)e.Node.Tag;
				l_item.Name = (e.Label != null && e.Label.Length > 0) ? e.Label : l_item.Name;
			}
		}

		private void m_treeView_BeforeSelect(object sender, TreeViewCancelEventArgs e)
		{

		}

		private void m_treeView_AfterSelect(object sender, TreeViewEventArgs e)
		{
			Program.MainWindow.PropertyWindow.SelectedObject = e.Node.Tag;
		}

		private void newPackageToolStripMenuItem_Click(object sender, EventArgs e)
		{
			if (m_treeView.SelectedNode.Tag is Bikini.Project)
			{
				TreeNode l_projectNode = m_treeView.SelectedNode;
				TreeNode l_packageNode = AddNode(new Bikini.Package("New"), l_projectNode.Nodes);
			}
		}

		private void newFolderToolStripMenuItem_Click(object sender, EventArgs e)
		{
			if (m_treeView.SelectedNode.Tag is Bikini.Project)
			{
				TreeNode l_projectNode = m_treeView.SelectedNode;
				TreeNode l_folderNode = AddNode(new Bikini.Folder("New"), l_projectNode.Nodes);
			}
		}

		private void buildToolStripMenuItem_Click(object sender, EventArgs e)
		{

		}
    }
}