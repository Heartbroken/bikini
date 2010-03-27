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
            MemoryStream l_streamOut = new MemoryStream();

            XmlTextWriter l_xmlOut = new XmlTextWriter(l_streamOut, Encoding.UTF8);
            l_xmlOut.Formatting = Formatting.Indented;

            l_xmlOut.WriteStartElement("request");
            {
                l_xmlOut.WriteStartElement("command");
                l_xmlOut.WriteAttributeString("name", "Test");
                {
                    l_xmlOut.WriteStartElement("arguments");
                    l_xmlOut.WriteEndElement();
                }
                l_xmlOut.WriteEndElement();
            }
            l_xmlOut.WriteEndElement();

            l_xmlOut.Flush();
            l_streamOut.Seek(0, SeekOrigin.Begin);

            StreamReader l_streamReader = new StreamReader(l_streamOut);
            String l_request = l_streamReader.ReadToEnd();

            String l_response = request(l_request);

            byte[] l_byteArray = Encoding.ASCII.GetBytes(l_response);
            MemoryStream l_streamIn = new MemoryStream(l_byteArray);
            XmlTextReader l_xmlIn = new XmlTextReader(l_streamIn);
            l_xmlIn.WhitespaceHandling = WhitespaceHandling.None;
            l_xmlIn.MoveToContent();

            if (l_xmlIn.Name == "response" && l_xmlIn.IsStartElement())
            {
                l_xmlIn.ReadStartElement();
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
                l_xmlIn.ReadEndElement();
            }

            return false;
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
