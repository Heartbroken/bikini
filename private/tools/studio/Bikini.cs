using System;
using System.Drawing;
using System.Runtime.InteropServices;
using System.IO;
using System.Text;
using System.Xml;
using System.Globalization;
using System.ComponentModel;
using System.Windows.Forms;
using System.Diagnostics;

namespace Studio
{
    static class Bikini
    {
        public const UInt64 BadID = 0xffffffffffffffff;

        public static Boolean Create()
        {
            Object l_result = ReadResult(request(WriteRequest("Create")));

            if (l_result is bool && Convert.ToBoolean(l_result)) return true;
            return false;
        }
        public static void Destroy()
        {
            request(WriteRequest("Destroy"));
        }
        public static Boolean Update()
        {
            Object l_result = ReadResult(request(WriteRequest("Update")));

            if (l_result is bool) return Convert.ToBoolean(l_result);
            return false;
        }

		public static Guid NewProject(String _location, String _name)
        {
			XmlTextWriter l_xml = StartWriteRequest("NewProject");
			WriteRequestArgument(l_xml, _location);
			WriteRequestArgument(l_xml, _name);
			String l_request = EndWriteRequest(l_xml);

            Object l_result = ReadResult(request(l_request));

			if (l_result is Guid) return (Guid)l_result;
			return Guid.Empty;
        }
		public static Guid OpenProject(String _path)
		{
			XmlTextWriter l_xml = StartWriteRequest("OpenProject");
			WriteRequestArgument(l_xml, _path);
			String l_request = EndWriteRequest(l_xml);

			Object l_result = ReadResult(request(l_request));

			if (l_result is Guid) return (Guid)l_result;
			return Guid.Empty;
		}
		public static Guid NewPackage(Guid _parent, String _name)
		{
			XmlTextWriter l_xml = StartWriteRequest("NewPackage");
			WriteRequestArgument(l_xml, _parent);
			WriteRequestArgument(l_xml, _name);
			String l_request = EndWriteRequest(l_xml);

			Object l_result = ReadResult(request(l_request));

			if (l_result is Guid) return (Guid)l_result;
			return Guid.Empty;
		}
		public static Guid NewFolder(Guid _parent, String _name)
		{
			XmlTextWriter l_xml = StartWriteRequest("NewFolder");
			WriteRequestArgument(l_xml, _parent);
			WriteRequestArgument(l_xml, _name);
			String l_request = EndWriteRequest(l_xml);

			Object l_result = ReadResult(request(l_request));

			if (l_result is Guid) return (Guid)l_result;
			return Guid.Empty;
		}
        public static Guid NewStage(Guid _parent, String _name)
        {
            XmlTextWriter l_xml = StartWriteRequest("NewStage");
            WriteRequestArgument(l_xml, _parent);
            WriteRequestArgument(l_xml, _name);
            String l_request = EndWriteRequest(l_xml);

            Object l_result = ReadResult(request(l_request));

            if (l_result is Guid) return (Guid)l_result;
            return Guid.Empty;
        }
        public static String ObjectStructure(Guid _object)
		{
			XmlTextWriter l_xml = StartWriteRequest("ObjectStructure");
			WriteRequestArgument(l_xml, _object);
			String l_request = EndWriteRequest(l_xml);

			Object l_result = ReadResult(request(l_request));

			if (l_result is String) return Convert.ToString(l_result);
			return "";
		}
		public static Boolean RenameObject(Guid _object, String _name)
		{
			XmlTextWriter l_xml = StartWriteRequest("RenameObject");
			WriteRequestArgument(l_xml, _object);
			WriteRequestArgument(l_xml, _name);
			String l_request = EndWriteRequest(l_xml);

			Object l_result = ReadResult(request(l_request));

			if (l_result is bool && Convert.ToBoolean(l_result)) return true;
			return false;
		}
        public static Boolean MoveObject(Guid _object, Guid _newParent)
        {
            XmlTextWriter l_xml = StartWriteRequest("MoveObject");
            WriteRequestArgument(l_xml, _object);
            WriteRequestArgument(l_xml, _newParent);
            String l_request = EndWriteRequest(l_xml);

            Object l_result = ReadResult(request(l_request));

            if (l_result is bool && Convert.ToBoolean(l_result)) return true;
            return false;
        }
        public static Boolean RemoveObject(Guid _object)
		{
			XmlTextWriter l_xml = StartWriteRequest("RemoveObject");
			WriteRequestArgument(l_xml, _object);
			String l_request = EndWriteRequest(l_xml);

			Object l_result = ReadResult(request(l_request));

			if (l_result is bool && Convert.ToBoolean(l_result)) return true;
			return false;
		}
		public static Boolean SaveAll()
		{
			String l_request = WriteRequest("SaveAll");

			Object l_result = ReadResult(request(l_request));

			if (l_result is bool && Convert.ToBoolean(l_result)) return true;
			return false;
		}

        // test
        public static UInt64 CreateView(IntPtr _handle)
        {
            XmlTextWriter l_xml = StartWriteRequest("CreateView");
            WriteRequestArgument(l_xml, _handle);
            String l_request = EndWriteRequest(l_xml);

            Object l_result = ReadResult(request(l_request));

            if (l_result is double) return Convert.ToUInt64(l_result);
            return Convert.ToUInt64(-1);
        }
        public static void ResetView(UInt64 _ID, IntPtr _handle)
        {
            XmlTextWriter l_xml = StartWriteRequest("ResetView");
            WriteRequestArgument(l_xml, _ID);
            WriteRequestArgument(l_xml, _handle);
            String l_request = EndWriteRequest(l_xml);

            ReadResult(request(l_request));
        }
        public static void DestroyView(UInt64 _ID)
        {
            XmlTextWriter l_xml = StartWriteRequest("DestroyView");
            WriteRequestArgument(l_xml, _ID);
            String l_request = EndWriteRequest(l_xml);

            ReadResult(request(l_request));
        }
        public static Boolean Test(int _int, string _string)
        {
            XmlTextWriter l_xml = StartWriteRequest("Test");
            WriteRequestArgument(l_xml, _int);
            WriteRequestArgument(l_xml, _string);
            String l_request = EndWriteRequest(l_xml);

            Object l_result = ReadResult(request(l_request));

            if (l_result is bool && Convert.ToBoolean(l_result)) return true;
            return false;
        }

        // Request/Response

        static XmlTextWriter StartWriteRequest(String _name)
        {
            MemoryStream l_stream = new MemoryStream();

            XmlTextWriter l_xml = new XmlTextWriter(l_stream, Encoding.UTF8);
            l_xml.Formatting = Formatting.Indented;

            l_xml.WriteStartElement("command");
            l_xml.WriteAttributeString("name", _name);
            l_xml.WriteStartElement("arguments");

            return l_xml;
        }
        static String GetType<_T>(_T _v)
        {
            if (_v is Boolean) return "boolean";
            if (_v is Int16) return "number";
            if (_v is UInt16) return "number";
            if (_v is Int32) return "number";
            if (_v is UInt32) return "number";
            if (_v is Int64) return "number";
            if (_v is UInt64) return "number";
            if (_v is IntPtr) return "number";
            if (_v is UIntPtr) return "number";
            if (_v is Single) return "number";
            if (_v is Double) return "number";
            if (_v is String) return "string";
            return _v.GetType().ToString();
        }
        static String ToString<_T>(_T _v)
        {
            if (_v is Single) return Convert.ToSingle(_v).ToString(CultureInfo.InvariantCulture);
            if (_v is Double) return Convert.ToDouble(_v).ToString(CultureInfo.InvariantCulture);
            //if (_v is String) return Encoding.UTF8.GetString(Encoding.Unicode.GetBytes(Convert.ToString(_v)));
            return _v.ToString();
        }
        static void WriteRequestArgument<_T>(XmlTextWriter _xml, _T _v)
        {
            _xml.WriteStartElement(GetType(_v));
            _xml.WriteString(ToString(_v));
            _xml.WriteEndElement();
        }
        static String EndWriteRequest(XmlTextWriter _xml)
        {
            _xml.WriteEndElement();
            _xml.WriteEndElement();

            _xml.Flush();
            _xml.BaseStream.Seek(0, SeekOrigin.Begin);

            StreamReader l_streamReader = new StreamReader(_xml.BaseStream);
            String l_request = l_streamReader.ReadToEnd();

            return l_request;
        }
        static String WriteRequest(String _name)
        {
            return EndWriteRequest(StartWriteRequest(_name));
        }
        static Object ReadResult(String _response)
        {
            Object l_result = null;

            if (_response == null) return l_result;

            byte[] l_byteArray = Encoding.ASCII.GetBytes(_response);
            MemoryStream l_streamIn = new MemoryStream(l_byteArray);
            XmlTextReader l_xmlIn = new XmlTextReader(l_streamIn);
            l_xmlIn.WhitespaceHandling = WhitespaceHandling.None;
            l_xmlIn.MoveToContent();

            if (l_xmlIn.Name == "result" && l_xmlIn.IsStartElement())
            {
                l_xmlIn.ReadStartElement();
                if (l_xmlIn.IsStartElement())
                {
                    if (l_xmlIn.Name == "boolean")
                        l_result = Convert.ToBoolean(l_xmlIn.ReadString());
                    else if (l_xmlIn.Name == "number")
                        l_result = Convert.ToDouble(l_xmlIn.ReadString(), CultureInfo.InvariantCulture);
                    else if (l_xmlIn.Name == "string")
                        l_result = l_xmlIn.ReadString();
                    else if (l_xmlIn.Name == "GUID")
                        l_result = new Guid(l_xmlIn.ReadString());

                    l_xmlIn.ReadEndElement();
                    l_xmlIn.ReadEndElement();
                }
            }

            return l_result;
        }

        static String request(String _command)
        {
            byte[] l_command = Encoding.UTF8.GetBytes(_command);
            IntPtr l_responsePtr = request(Marshal.UnsafeAddrOfPinnedArrayElement(l_command, 0));
            int l_responseLength = Marshal.PtrToStringAnsi(l_responsePtr).Length;
            byte[] l_response = new byte[l_responseLength];
            Marshal.Copy(l_responsePtr, l_response, 0, l_responseLength);
            return Encoding.UTF8.GetString(l_response);
        }

        // P/Invoke

#       if DEBUG
#           if Win32
                [DllImport("bikini (Win32!Debug).dll", CharSet = CharSet.Ansi)]
#           elif x64
                [DllImport("bikini (x64!Debug).dll", CharSet = CharSet.Unicode)]
#           endif
#       elif RELEASE
#           if Win32
                [DllImport("bikini (Win32!Release).dll", CharSet = CharSet.Unicode)]
#           elif x64
                [DllImport("bikini (x64!Release).dll", CharSet = CharSet.Unicode)]
#           endif
#       endif
        public static extern IntPtr request(IntPtr _command);

        // PropertyGrid objects

		public abstract class ProjectItem
        {
			public TreeNode treeNode;
            public ComboBox comboBox;

			public ProjectItem() { m_guid = Guid.NewGuid(); }
			public ProjectItem(Guid _guid) { m_guid = _guid; }

            // GUID
            private Guid m_guid;
            [CategoryAttribute("Object ID"), DescriptionAttribute("Object's identity")]
            public Guid GUID { get { return m_guid; } }

			// Type
			[CategoryAttribute("Object ID"), DescriptionAttribute("Object's type")]
			public abstract String Type { get; }

			public override string ToString() { return Type; }
			public virtual String FullName() { return Type; }
			public virtual String ItemType() { return Type; }
			public virtual String SubItems() { return ""; }
		}
		public abstract class NamedProjectItem : ProjectItem
		{
			public NamedProjectItem(String _name) { m_name = _name; }
			public NamedProjectItem(String _name, Guid _guid) : base(_guid) { m_name = _name; }

            // Name
            private String m_name;
			[CategoryAttribute("Object ID"), DescriptionAttribute("You always can change the name. All references to the object are made by its GUID")]
			public virtual String Name
            {
                get { return m_name; }
                set
                {
                    m_name = value;
					if (treeNode != null) treeNode.Text = this.FullName();
					Debug.Assert(comboBox == null || comboBox.SelectedItem == this);
					if (comboBox != null && comboBox.SelectedItem == this) comboBox.Items[comboBox.SelectedIndex] = this;
                }
            }

			public override string ToString() { return Type + " '" + Name + "'"; }
			public override String FullName() { return Name; }
		}

        // Project
		public class Project : NamedProjectItem
        {
			public Project(String _name, Guid _guid) : base(_name, _guid) { }
			public override String Type { get { return "Project"; } }
			public override String FullName() { return ToString(); }
			public override String SubItems() { return "PFolder|Package"; }
		}
        // Folder
		public class Folder : NamedProjectItem
        {
			Boolean m_projectFolder;
			public Folder(String _name, Boolean _projectFolder, Guid _guid) : base(_name, _guid) { m_projectFolder = _projectFolder; }
			public override String Type { get { return "Folder"; } }
			public override String ItemType() { return m_projectFolder ? "PFolder" : "RFolder"; }
			public override String SubItems() { return m_projectFolder ? "PFolder|Package" : "RFolder|Menu"; }
		}
        // Package
		public class Package : NamedProjectItem
        {
			public Package(String _name, Guid _guid) : base(_name, _guid) { }
			public override String Type { get { return "Package"; } }
			public override String SubItems() { return "Stage"; }
		}
        // Stage
		public class Stage : NamedProjectItem
        {
            public Stage(String _name, Guid _guid) : base(_name, _guid) { }
			public override String Type { get { return "Stage"; } }
			public override String SubItems() { return "Stage|Resources"; }
		}
		// Resources
		public class Resources : ProjectItem
		{
			public Resources() { }
			public override String Type { get { return "Resources"; } }
			public override String SubItems() { return "Menu|RFolder"; }
		}

		// Resource item
		public abstract class ResourceItem : NamedProjectItem
		{
			public ResourceItem(String _name) : base(_name) {}
			public override String FullName() { return Name + "." + Type.ToLower(); }
		}
		// Menu
		public class Menu : ResourceItem
		{
			public Menu(String _name) : base(_name) {}
			public override String Type { get { return "Menu"; } }
		}
	}
}
