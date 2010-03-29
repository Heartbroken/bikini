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
        public const UInt64 BadID = 0xffffffffffffffff;

        public static Boolean Update(float _dt)
        {
            XmlTextWriter l_xml = StartWriteRequest("Update");
            WriteRequestArgument(l_xml, _dt);
            String l_request = EndWriteRequest(l_xml);

            //String l_response = request(l_request);
            Object l_result = ReadResult(request(l_request));

            if (l_result is bool && Convert.ToBoolean(l_result)) return true;
            return false;
        }
        public static UInt64 CreateGuiView(IntPtr _handle)
        {
            XmlTextWriter l_xml = StartWriteRequest("CreateGuiView");
            WriteRequestArgument(l_xml, _handle);
            String l_request = EndWriteRequest(l_xml);

            //String l_response = request(l_request);
            Object l_result = ReadResult(request(l_request));

            if (l_result is double) return Convert.ToUInt64(l_result);
            return Convert.ToUInt64(-1);
        }
        public static void DestroyGuiView(UInt64 _ID)
        {
            XmlTextWriter l_xml = StartWriteRequest("DestroyGuiView");
            WriteRequestArgument(l_xml, _ID);
            String l_request = EndWriteRequest(l_xml);

            //String l_response = request(l_request);
            Object l_result = ReadResult(request(l_request));
        }
        public static Boolean Test(int _int, string _string)
        {
            XmlTextWriter l_xml = StartWriteRequest("Test");
            WriteRequestArgument(l_xml, _int);
            WriteRequestArgument(l_xml, _string);
            String l_request = EndWriteRequest(l_xml);

            //String l_request = WriteRequest("Test");

            //String l_response = request(l_request);
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
        static Object ReadResult(IntPtr _response)
        {
            String l_response = Marshal.PtrToStringUni(_response);
            Object l_result = null;

            if (_response == null) return l_result;

            byte[] l_byteArray = Encoding.ASCII.GetBytes(l_response);
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
        public static extern IntPtr request(String _command);
    }
}
