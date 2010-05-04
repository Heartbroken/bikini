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
				TreeNode l_projectNode = AddNode(new Bikini.Project("New"), m_treeView.Nodes);
				//l_projectNode.Expand();
				//{
				//    TreeNode l_packageNode = AddNode(new Bikini.Package("Grrr"), l_projectNode.Nodes);
				//    {
				//        TreeNode l_stageNode = AddNode(new Bikini.Stage("Main"), l_packageNode.Nodes);
				//    }
				//}
				//{
				//    TreeNode l_folderNode = AddNode(new Bikini.Folder("Episodes"), l_projectNode.Nodes);
				//    {
				//        TreeNode l_packageNode = AddNode(new Bikini.Package("E1"), l_folderNode.Nodes);
				//        {
				//            TreeNode l_stageNode = AddNode(new Bikini.Stage("E1S1"), l_packageNode.Nodes);
				//        }
				//    }
				//}
			}
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
		TreeNode m_pickedNode = null;

        private void m_treeView_MouseDown(object sender, MouseEventArgs e)
        {
            m_cancelExpand = e.Clicks > 1;

			TreeNode l_node = m_treeView.GetNodeAt(e.Location);

			if (l_node != null && e.Button == MouseButtons.Left)
			{
				m_pickedNode = l_node;
			}
        }

		private void m_treeView_MouseUp(object sender, MouseEventArgs e)
		{
			if (m_pickedNode != null && e.Button == MouseButtons.Left)
			{
				m_pickedNode = null;
			}
		}

		private void m_treeView_MouseMove(object sender, MouseEventArgs e)
		{
			if (m_pickedNode != null)
			{
				m_treeView.DoDragDrop(m_pickedNode, DragDropEffects.Move);
			}
		}

		private void m_treeView_DragOver(object sender, DragEventArgs e)
		{
			e.Effect = DragDropEffects.None;

			if (m_pickedNode != null)
			{
				TreeNode l_node = m_treeView.GetNodeAt(m_treeView.PointToClient(Control.MousePosition));

				if (l_node == null) return;

				m_treeView.SelectedNode = l_node;
				e.Effect = DragDropEffects.Move;
			}
		}

		private void m_treeView_DragDrop(object sender, DragEventArgs e)
		{
			e.Effect = DragDropEffects.None;

			TreeNode l_node = m_treeView.GetNodeAt(m_treeView.PointToClient(Control.MousePosition));

			if (l_node != null && l_node != m_pickedNode)
			{
				m_pickedNode.Remove();
				l_node.Nodes.Add(m_pickedNode);
				m_treeView.SelectedNode = m_pickedNode;
				m_pickedNode.EnsureVisible();

				e.Effect = DragDropEffects.Move;
			}

			m_pickedNode = null;
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

		private void buildToolStripMenuItem_Click(object sender, EventArgs e)
		{

		}

		private void newPackageToolStripMenuItem_Click(object sender, EventArgs e)
		{
			if (m_treeView.SelectedNode.Tag is Bikini.Project ||
				m_treeView.SelectedNode.Tag is Bikini.Folder)
			{
				TreeNode l_parentNode = m_treeView.SelectedNode;
				TreeNode l_newNode = AddNode(new Bikini.Package("New"), l_parentNode.Nodes);
				m_treeView.SelectedNode = l_newNode;
				l_newNode.BeginEdit();
			}
		}

		private void newFolderToolStripMenuItem_Click(object sender, EventArgs e)
		{
			if (m_treeView.SelectedNode.Tag is Bikini.Project ||
				m_treeView.SelectedNode.Tag is Bikini.Folder)
			{
				TreeNode l_parentNode = m_treeView.SelectedNode;
				TreeNode l_newNode = AddNode(new Bikini.Folder("New"), l_parentNode.Nodes);
				m_treeView.SelectedNode = l_newNode;
				l_newNode.BeginEdit();
			}
		}

		private void newStageToolStripMenuItem_Click(object sender, EventArgs e)
		{
			if (m_treeView.SelectedNode.Tag is Bikini.Package ||
				m_treeView.SelectedNode.Tag is Bikini.Stage)
			{
				TreeNode l_parentNode = m_treeView.SelectedNode;
				TreeNode l_newNode = AddNode(new Bikini.Stage("New"), l_parentNode.Nodes);
				m_treeView.SelectedNode = l_newNode;
				l_newNode.BeginEdit();
			}
		}

		private void removeToolStripMenuItem_Click(object sender, EventArgs e)
		{
			m_treeView.SelectedNode.Remove();
		}

		private void m_projectContextMenu_Opening(object sender, CancelEventArgs e)
		{
			TreeNode l_node = m_treeView.GetNodeAt(m_treeView.PointToClient(Control.MousePosition));

			if (l_node == null || !(l_node.Tag is Bikini.ProjectItem))
			{
				e.Cancel = true;
				return;
			}

			Bikini.ProjectItem l_item = (Bikini.ProjectItem)l_node.Tag;

			SetMenuVisibleItems(m_projectContextMenu, l_item);

			m_treeView.SelectedNode = l_node;
		}

		private void SetMenuVisibleItems(ToolStrip _menu, Bikini.ProjectItem _projectItem)
		{
			foreach (ToolStripItem l_stripItem in _menu.Items)
			{
				Boolean l_showStripItem = true;

				if (l_stripItem.Tag is String)
				{
					String l_tag = (String)l_stripItem.Tag;
					if (l_tag.IndexOf(_projectItem.Type) == -1)
					{
						l_showStripItem = false;
					}
				}

				l_stripItem.Visible = l_showStripItem;

				if (l_showStripItem)
				{
					if (l_stripItem is ToolStripMenuItem)
					{
						ToolStripMenuItem l_stripMenuItem = (ToolStripMenuItem)l_stripItem;

						if (l_stripMenuItem.DropDown != null)
						{
							SetMenuVisibleItems(l_stripMenuItem.DropDown, _projectItem);
						}
					}
				}
			}
		}
    }
}