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
using System.IO;
using System.Xml;
using System.Diagnostics;

namespace Studio
{
	public partial class ProjectExplorer : ToolWindow
	{
		const Int32 StartDragDist = 3;

		public ProjectExplorer()
		{
			InitializeComponent();
		}

        private XmlTextReader ObjectStructure(Guid _object)
        {
            String l_objecttStructure = Bikini.ObjectStructure(_object);

            byte[] l_byteArray = Encoding.ASCII.GetBytes(l_objecttStructure);
            MemoryStream l_stream = new MemoryStream(l_byteArray);
            XmlTextReader l_xml = new XmlTextReader(l_stream);
            l_xml.WhitespaceHandling = WhitespaceHandling.None;

            return l_xml;
        }
		public void UpdateTreeView(Guid _project)
		{
			m_treeView.Nodes.Clear();

            XmlTextReader l_xml = ObjectStructure(_project);

            while (l_xml.Read())
            {
                if (l_xml.IsStartElement() && l_xml.Name == "project")
                {
                    ParseProjectStructure(l_xml);
                    break;
                }
            }
		}
		private void ParseProjectStructure(XmlTextReader _xml)
		{
            Debug.Assert(_xml.IsStartElement() && _xml.Name == "project");

            //String l_name = _xml.GetAttribute("name");
            Guid l_guid = new Guid(_xml.GetAttribute("GUID"));
            TreeNode l_projectNode = AddNode(new Bikini.Project(l_guid), m_treeView.Nodes);
            if (!_xml.IsEmptyElement) while (_xml.Read())
            {
                if (_xml.IsStartElement())
                {
                    if (_xml.Name == "stage") OpenStageFile(_xml, l_projectNode);
                    //if (_xml.Name == "package") OpenPackageFile(_xml, l_projectNode);
                    //else if (_xml.Name == "folder") ParseFolderStructure(_xml, l_projectNode);
                }
                else
                {
                    if (_xml.Name == "project") break;
                }
            }

            l_projectNode.Expand();
		}
        private void OpenPackageFile(XmlTextReader _xml, TreeNode _parentNode)
        {
            Guid l_package = new Guid(_xml.GetAttribute("GUID"));
            
            XmlTextReader l_xml = ObjectStructure(l_package);

            while (l_xml.Read())
            {
                if (l_xml.IsStartElement() && l_xml.Name == "package")
                {
                    ParsePackageStructure(l_xml, _parentNode);
                    break;
                }
            }
        }
        private void ParsePackageStructure(XmlTextReader _xml, TreeNode _parentNode)
        {
            //String l_name = _xml.GetAttribute("name");
            Guid l_guid = new Guid(_xml.GetAttribute("GUID"));
            TreeNode l_packageNode = AddNode(new Bikini.Package(l_guid), _parentNode.Nodes);

            if (!_xml.IsEmptyElement) while (_xml.Read())
            {
                if (_xml.IsStartElement())
                {
                    if (_xml.Name == "stage") OpenStageFile(_xml, l_packageNode);
                }
                else
                {
                    if (_xml.Name == "package") break;
                }
            }
        }
        private void ParseFolderStructure(XmlTextReader _xml, TreeNode _parentNode)
        {
            //String l_name = _xml.GetAttribute("name");
            Guid l_guid = new Guid(_xml.GetAttribute("GUID"));
            TreeNode l_folderNode = AddNode(new Bikini.Folder(true, l_guid), _parentNode.Nodes);
            if (!_xml.IsEmptyElement)
            {
                while (_xml.Read())
                {
                    if (_xml.IsStartElement())
                    {
                        if (_xml.Name == "package") OpenPackageFile(_xml, l_folderNode);
                        else if (_xml.Name == "folder") ParseFolderStructure(_xml, l_folderNode);
                    }
                    else
                    {
                        if (_xml.Name == "folder") break;
                    }
                }
            }
        }
        private void OpenStageFile(XmlTextReader _xml, TreeNode _parentNode)
        {
            Guid l_stage = new Guid(_xml.GetAttribute("GUID"));

            XmlTextReader l_xml = ObjectStructure(l_stage);

            while (l_xml.Read())
            {
                if (l_xml.IsStartElement() && l_xml.Name == "stage")
                {
                    ParseStageStructure(l_xml, _parentNode);
                    break;
                }
            }
        }
        private void ParseStageStructure(XmlTextReader _xml, TreeNode _parentNode)
        {
            //String l_name = _xml.GetAttribute("name");
            Guid l_guid = new Guid(_xml.GetAttribute("GUID"));
            TreeNode l_folderNode = AddNode(new Bikini.Stage(l_guid), _parentNode.Nodes);
            if (!_xml.IsEmptyElement) while (_xml.Read())
            {
                if (_xml.IsStartElement())
                {
                    if (_xml.Name == "stage") OpenStageFile(_xml, l_folderNode);
                }
                else
                {
                    if (_xml.Name == "stage") break;
                }
            }
        }

		private TreeNode AddNode(Bikini.WorkspaceObject _item, TreeNodeCollection _nodes)
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
		Point m_pickPoint;

		private void m_treeView_MouseDown(object sender, MouseEventArgs e)
		{
			m_cancelExpand = e.Clicks > 1;

			TreeNode l_node = m_treeView.GetNodeAt(e.Location);

			if (l_node != null && e.Button == MouseButtons.Left)
			{
				m_pickedNode = l_node;
				m_pickPoint = e.Location;
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
            Point l_dist = Point.Subtract(e.Location, new Size(m_pickPoint));

			if (m_pickedNode != null &&
				!(m_pickedNode.Tag is Bikini.Project) &&
				e.Button == MouseButtons.Left &&
				(Math.Abs(l_dist.X) > StartDragDist || Math.Abs(l_dist.Y) > StartDragDist))
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

				Bikini.WorkspaceObject l_draggedItem = (Bikini.WorkspaceObject)m_pickedNode.Tag;
				Bikini.WorkspaceObject l_targetItem = (Bikini.WorkspaceObject)l_node.Tag;

				if (l_targetItem.SubItems().IndexOf(l_draggedItem.ItemType()) > -1)
				{
					e.Effect = DragDropEffects.Move;
				}
			}
		}

		private void m_treeView_DragDrop(object sender, DragEventArgs e)
		{
			e.Effect = DragDropEffects.None;

			TreeNode l_node = m_treeView.GetNodeAt(m_treeView.PointToClient(Control.MousePosition));

            Bikini.WorkspaceObject l_draggedItem = (Bikini.WorkspaceObject)m_pickedNode.Tag;
            Bikini.WorkspaceObject l_targetItem = (Bikini.WorkspaceObject)l_node.Tag;

			if (l_node != null && l_node != m_pickedNode)
			{
                if (l_draggedItem.MoveTo(l_targetItem))
                {
				    m_pickedNode.Remove();
				    l_node.Nodes.Add(m_pickedNode);
				    m_treeView.SelectedNode = m_pickedNode;
				    m_pickedNode.EnsureVisible();

				    e.Effect = DragDropEffects.Move;
                }
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
			if (e.Node.Tag is Bikini.NamedWorkspaceObject)
			{
				Bikini.NamedWorkspaceObject l_item = (Bikini.NamedWorkspaceObject)e.Node.Tag;
				IntPtr l_editBoxHandle = SendMessage(m_treeView.Handle, TVM_GETEDITCONTROL, IntPtr.Zero, IntPtr.Zero);
				SendMessage(l_editBoxHandle, WM_SETTEXT, IntPtr.Zero, Marshal.UnsafeAddrOfPinnedArrayElement(Encoding.Unicode.GetBytes(l_item.Name), 0));
			}
			else
			{
				e.CancelEdit = true;
			}
		}

		private void m_treeView_AfterLabelEdit(object sender, NodeLabelEditEventArgs e)
		{
			e.CancelEdit = true;
			e.Node.EndEdit(true);

			if (e.Node.Tag is Bikini.NamedWorkspaceObject && e.Label != null && e.Label.Length > 0)
			{
				Bikini.NamedWorkspaceObject l_item = (Bikini.NamedWorkspaceObject)e.Node.Tag;
				l_item.Name = e.Label;
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
				Bikini.WorkspaceObject l_parentItem = (Bikini.WorkspaceObject)l_parentNode.Tag;
				Guid l_guid = Bikini.NewPackage(l_parentItem.GUID, "NewPackage");
				if (l_guid != Guid.Empty)
				{
					TreeNode l_newNode = AddNode(new Bikini.Package(l_guid), l_parentNode.Nodes);
					m_treeView.SelectedNode = l_newNode;
					l_newNode.BeginEdit();
				}
			}
		}

		private Boolean FindResourcesItem(TreeNode _node)
		{
			TreeNode l_node = _node;

			while (l_node.Parent != null)
			{
				if (l_node.Tag is Bikini.Resources) return true;
				l_node = l_node.Parent;
			}

			return false;
		}
		private void newFolderToolStripMenuItem_Click(object sender, EventArgs e)
		{
			if (m_treeView.SelectedNode.Tag is Bikini.Project ||
                m_treeView.SelectedNode.Tag is Bikini.Folder ||
                m_treeView.SelectedNode.Tag is Bikini.Resources)
			{
				TreeNode l_parentNode = m_treeView.SelectedNode;
				Boolean l_projectFolder = !FindResourcesItem(l_parentNode);
				Bikini.WorkspaceObject l_parentItem = (Bikini.WorkspaceObject)l_parentNode.Tag;

				Guid l_guid = Bikini.NewFolder(l_parentItem.GUID, "NewFolder");
				if (l_guid != Guid.Empty)
				{
					TreeNode l_newNode = AddNode(new Bikini.Folder(l_projectFolder, l_guid), l_parentNode.Nodes);
					m_treeView.SelectedNode = l_newNode;
					l_newNode.BeginEdit();
				}
			}
		}

		private void newStageToolStripMenuItem_Click(object sender, EventArgs e)
		{
			if (m_treeView.SelectedNode.Tag is Bikini.Project ||
				m_treeView.SelectedNode.Tag is Bikini.Stage)
			{
				TreeNode l_parentNode = m_treeView.SelectedNode;
                Bikini.WorkspaceObject l_parentItem = (Bikini.WorkspaceObject)l_parentNode.Tag;
                Guid l_guid = Bikini.NewStage(l_parentItem.GUID, "NewStage");
                if (l_guid != Guid.Empty)
                {
                    TreeNode l_newNode = AddNode(new Bikini.Stage(l_guid), l_parentNode.Nodes);
                    m_treeView.SelectedNode = l_newNode;
                    l_newNode.BeginEdit();
                }
            }
		}

		private void newMenuToolStripMenuItem_Click(object sender, EventArgs e)
		{
			if (m_treeView.SelectedNode.Tag is Bikini.Stage ||
				m_treeView.SelectedNode.Tag is Bikini.Resources ||
				m_treeView.SelectedNode.Tag is Bikini.Folder)
			{
                //TreeNode l_parentNode = m_treeView.SelectedNode;
                //if (m_treeView.SelectedNode.Tag is Bikini.Stage)
                //{
                //    TreeNode l_resourcesNode = l_parentNode.Nodes["Resources"];
                //    if (l_resourcesNode == null)
                //    {
                //        l_resourcesNode = AddNode(new Bikini.Resources(), l_parentNode.Nodes);
                //        l_resourcesNode.Name = "Resources";
                //    }
                //    l_parentNode = l_resourcesNode;
                //}
                //TreeNode l_newNode = AddNode(new Bikini.Menu("New"), l_parentNode.Nodes);
                //m_treeView.SelectedNode = l_newNode;
                //l_newNode.BeginEdit();
			}
		}

		private void removeToolStripMenuItem_Click(object sender, EventArgs e)
		{
            TreeNode l_selectedNode = m_treeView.SelectedNode;
            Bikini.WorkspaceObject l_selectedItem = (Bikini.WorkspaceObject)l_selectedNode.Tag;

            if (Bikini.RemoveObject(l_selectedItem.GUID))
			    m_treeView.SelectedNode.Remove();
		}

		private void m_projectContextMenu_Opening(object sender, CancelEventArgs e)
		{
			TreeNode l_node = m_treeView.GetNodeAt(m_treeView.PointToClient(Control.MousePosition));

			if (l_node == null || !(l_node.Tag is Bikini.WorkspaceObject))
			{
				e.Cancel = true;
				return;
			}

			Bikini.WorkspaceObject l_item = (Bikini.WorkspaceObject)l_node.Tag;

			SetMenuVisibleItems(m_projectContextMenu, l_item);

			m_treeView.SelectedNode = l_node;
		}

		private Int32 SetMenuVisibleItems(ToolStrip _menu, Bikini.WorkspaceObject _projectItem)
		{
			Int32 l_hiddenCount = 0;

			foreach (ToolStripItem l_stripItem in _menu.Items)
			{
				Boolean l_showStripItem = true;

				if (l_stripItem.Tag is String)
				{
					String l_tag = (String)l_stripItem.Tag;
					if (l_tag.IndexOf(_projectItem.ItemType()) == -1)
					{
						l_showStripItem = false;
						++l_hiddenCount;
					}
				}

				l_stripItem.Visible = l_showStripItem;

				if (l_showStripItem)
				{
					if (l_stripItem is ToolStripMenuItem)
					{
						ToolStripMenuItem l_stripMenuItem = (ToolStripMenuItem)l_stripItem;

						if (l_stripMenuItem.DropDown != null && l_stripMenuItem.DropDown.Items.Count > 0)
						{
							if (SetMenuVisibleItems(l_stripMenuItem.DropDown, _projectItem) == 0)
							{
								l_stripItem.Visible = false;
								++l_hiddenCount;
							}
						}
					}
				}
			}

			return _menu.Items.Count - l_hiddenCount;
		}

        private void viewCodeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            TreeNode l_node = m_treeView.SelectedNode;
            //TreeNode l_node = m_treeView.GetNodeAt(m_treeView.PointToClient(Control.MousePosition));

            if (l_node != null && l_node.Tag is Bikini.Stage)
            {
                Bikini.Stage l_stage = (Bikini.Stage)l_node.Tag;
                Program.MainWindow.OpenStageCode(l_stage.GUID);
            }
        }
	}
}