﻿using System;
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

        public static Boolean CreateSolution()
        {
            XmlTextWriter l_xml = StartWriteRequest("CreateSolution");
            WriteRequestArgument(l_xml, "Русские буквы");
            String l_request = EndWriteRequest(l_xml);

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

			public ProjectItem(String _name) { m_name = _name; }

            // GUID
            private Guid m_guid = Guid.NewGuid();
            [CategoryAttribute("ID"), DescriptionAttribute("Object's identity")]
            public Guid GUID { get { return m_guid; } }

            // Name
            private String m_name = "Grrr";
			[CategoryAttribute("ID"), DescriptionAttribute("You always can change the name. All references to the object are made by its GUID")]
            public String Name
            {
                get { return m_name; }
                set
                {
                    m_name = value;
					if (treeNode != null) treeNode.Text = this.ToString();
					Debug.Assert(comboBox == null || comboBox.SelectedItem == this);
					if (comboBox != null && comboBox.SelectedItem == this) comboBox.Items[comboBox.SelectedIndex] = this;
                }
            }

			// Type
            [CategoryAttribute("ID"), DescriptionAttribute("Object's type")]
			public abstract String Type { get; }

			// To string
			public override string ToString() { return Type + " '" + Name + "'"; }
        }

        // Project
        public class Project : ProjectItem
        {
			public Project(String _name) : base(_name) {}
			public override String Type { get { return "Project"; } }
        }
        // Folder
        public class Folder : ProjectItem
        {
			public Folder(String _name) : base(_name) { }
			public override String Type { get { return "Folder"; } }
			public override string ToString() { return Name; }
		}
        // Package
        public class Package : ProjectItem
        {
			public Package(String _name) : base(_name) {}
			public override String Type { get { return "Package"; } }
		}
        // Stage
        public class Stage : ProjectItem
        {
			public Stage(String _name) : base(_name) {}
			public override String Type { get { return "Stage"; } }
		}
    }
}
