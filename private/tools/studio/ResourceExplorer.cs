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

            //String l_name = _xml.GetAttribute("name");
            Guid l_guid = new Guid(_xml.GetAttribute("GUID"));
            tmp = 0;
            TreeNode l_projectNode = AddNode(new Bikini.Project(l_guid), m_treeView.Nodes);
            Bikini.Project l_project = (Bikini.Project)l_projectNode.Tag;
            tmp = l_project.Path.Length;
            if (!_xml.IsEmptyElement)
            {
                while (_xml.Read())
                {
                    if (_xml.IsStartElement())
                    {
                        if (_xml.Name == "package") OpenPackageFile(_xml, l_projectNode);
                        else if (_xml.Name == "folder") ParseFolderStructure(_xml, l_projectNode);
                    }
                    else
                    {
                        if (_xml.Name == "project") break;
                    }
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
            String l_name = _xml.GetAttribute("name");
            Guid l_guid = new Guid(_xml.GetAttribute("GUID"));
            //TreeNode l_packageNode = AddNode(new Bikini.Package(l_name, l_guid), _parentNode.Nodes);

            if (!_xml.IsEmptyElement) while (_xml.Read())
                {
                    if (_xml.IsStartElement())
                    {
                        if (_xml.Name == "stage") OpenStageFile(_xml, _parentNode);
                    }
                    else
                    {
                        if (_xml.Name == "package") break;
                    }
                }
        }
        private void ParseFolderStructure(XmlTextReader _xml, TreeNode _parentNode)
        {
            String l_name = _xml.GetAttribute("name");
            Guid l_guid = new Guid(_xml.GetAttribute("GUID"));
            //TreeNode l_folderNode = AddNode(new Bikini.Folder(l_name, true, l_guid), _parentNode.Nodes);
            if (!_xml.IsEmptyElement)
            {
                while (_xml.Read())
                {
                    if (_xml.IsStartElement())
                    {
                        if (_xml.Name == "package") OpenPackageFile(_xml, _parentNode);
                        else if (_xml.Name == "folder") ParseFolderStructure(_xml, _parentNode);
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
                        if (_xml.Name == "stage") OpenStageFile(_xml, _parentNode);
                    }
                    else
                    {
                        if (_xml.Name == "stage") break;
                    }
                }
        }

        int tmp = 0;
        private TreeNode AddNode(Bikini.WorkspaceObject _item, TreeNodeCollection _nodes)
        {
            String l_name = tmp != 0 ? _item.Path.Substring(tmp + 1) : _item.FullName();
            TreeNode l_node = _nodes.Add("", l_name, _item.Type, _item.Type);
            l_node.Tag = _item; _item.treeNode = l_node;

            return l_node;
        }
    }
}
