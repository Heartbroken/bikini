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
            XmlTextWriter l_xmlOut = StartWriteRequest("Test");
            WriteArgument(l_xmlOut, 54321);
            String l_request = EndWriteRequest(l_xmlOut);

            //String l_request = WriteRequest("Test");

            String l_response = request(l_request);

            byte[] l_byteArray = Encoding.ASCII.GetBytes(l_response);
            MemoryStream l_streamIn = new MemoryStream(l_byteArray);
            XmlTextReader l_xmlIn = new XmlTextReader(l_streamIn);
            l_xmlIn.WhitespaceHandling = WhitespaceHandling.None;
            l_xmlIn.MoveToContent();

            if (l_xmlIn.Name == "result" && l_xmlIn.IsStartElement())
            {
                l_xmlIn.ReadStartElement();
                if (l_xmlIn.Name == "int")
                {
                    int l_r = Convert.ToInt32(l_xmlIn.GetAttribute("value"));
                    l_xmlIn.ReadStartElement();
                }
                else if (l_xmlIn.Name == "real")
                {
                    double l_r = Convert.ToDouble(l_xmlIn.GetAttribute("value"), CultureInfo.InvariantCulture);
                    l_xmlIn.ReadStartElement();
                }
                l_xmlIn.ReadEndElement();
            }

            return false;
        }

        static XmlTextWriter StartWriteRequest(String _name)
        {
            MemoryStream l_stream = new MemoryStream();

            XmlTextWriter l_xml = new XmlTextWriter(l_stream, Encoding.UTF8);
            //l_xml.Formatting = Formatting.Indented;

            l_xml.WriteStartElement("command");
            l_xml.WriteAttributeString("name", "Test");
            l_xml.WriteStartElement("arguments");

            return l_xml;
        }
        static void WriteArgument<_T>(XmlTextWriter _xml, _T _v)
        {
            _xml.WriteStartElement(_v.GetType().ToString());
            _xml.WriteAttributeString("value", _v.ToString());
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
