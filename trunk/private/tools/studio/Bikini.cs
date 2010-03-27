using System;
using System.Drawing;
using System.Runtime.InteropServices;
using System.IO;
using System.Text;
using System.Xml;
using System.Globalization;

namespace Studio
{
    class Bikini
    {
        public static Boolean Test()
        {
            XmlTextWriter l_xml = StartWriteRequest("Test");
            WriteRequestArgument(l_xml, 54321);
            WriteRequestArgument(l_xml, "Second argument");
            String l_request = EndWriteRequest(l_xml);

            //String l_request = WriteRequest("Test");

            String l_response = request(l_request);
            Object l_result = ReadResult(l_response);

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
            l_xml.WriteAttributeString("name", "Test");
            l_xml.WriteStartElement("arguments");

            return l_xml;
        }
        static String GetType<_T>(_T _v)
        {
            //switch (_v.GetType().ToString())
            //{
            //    case "System.Boolean": return "boolean";
            //    case "System.Int16": return "number";
            //    case "System.UInt16": return "number";
            //    case "System.Int32": return "number";
            //    case "System.UInt32": return "number";
            //    case "System.Int64": return "number";
            //    case "System.UInt64": return "number";
            //    case "System.IntPtr": return "number";
            //    case "System.UIntPtr": return "number";
            //    case "System.Single": return "number";
            //    case "System.Double": return "number";
            //    case "System.String": return "string";
            //}
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
            //switch (_v.GetType().ToString())
            //{
            //    case "System.Single": return Convert.ToSingle(_v).ToString(CultureInfo.InvariantCulture);
            //    case "System.Double": return Convert.ToDouble(_v).ToString(CultureInfo.InvariantCulture);
            //}
            if (_v is Single) return Convert.ToSingle(_v).ToString(CultureInfo.InvariantCulture);
            if (_v is Double) return Convert.ToDouble(_v).ToString(CultureInfo.InvariantCulture);
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
                }
                l_xmlIn.ReadEndElement();
            }

            return l_result;
        }

        // P/Invoke

#       if DEBUG
#           if Win32
                [DllImport("bikini (Win32!Debug).dll", CharSet = CharSet.Unicode)]
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
        public static extern String request(String _command);
    }
}
