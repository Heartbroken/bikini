using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Xml;
using System.Diagnostics;

namespace Studio
{
    public partial class ResourceExplorer : ToolWindow
    {
        public ResourceExplorer()
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

            String l_name = _xml.GetAttribute("name");
            Guid l_guid = new Guid(_xml.GetAttribute("GUID"));
            TreeNode l_projectNode = AddNode(new Bikini.Project(l_name, l_guid), m_treeView.Nodes);
            if (!_xml.IsEmptyElement)
            {
                while (_xml.Read())
                {
                    if (_xml.IsStartElement())
                    {
                        //if (_xml.Name == "package") OpenPackageFile(_xml, l_projectNode);
                        //else if (_xml.Name == "folder") ParseFolderStructure(_xml, l_projectNode);
                    }
                    else
                    {
                        if (_xml.Name == "project") break;
                    }
                }
            }

            l_projectNode.Expand();
        }

        private TreeNode AddNode(Bikini.ProjectItem _item, TreeNodeCollection _nodes)
        {
            TreeNode l_node = _nodes.Add("", _item.FullName(), _item.Type, _item.Type);
            l_node.Tag = _item; _item.treeNode = l_node;

            return l_node;
        }
    }
}
