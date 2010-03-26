using System;
using System.Drawing;
using System.Runtime.InteropServices;
using System.IO;
using System.Text;
using System.Xml;

namespace Studio
{
    class Bikini
    {
        public static Boolean Test()
        {
            MemoryStream l_stream = new MemoryStream();

            XmlTextWriter l_xmlOut = new XmlTextWriter(l_stream, Encoding.UTF8);
            l_xmlOut.Formatting = Formatting.Indented;

            l_xmlOut.WriteStartElement("Test");
            l_xmlOut.WriteEndElement();

            l_xmlOut.Flush();

            l_stream.Seek(0, SeekOrigin.Begin);
            StreamReader l_streamReader = new StreamReader(l_stream);
            String l_request = l_streamReader.ReadToEnd();
            String l_response = request(l_request);

            if (l_response.Length > 0) return true;
            return false;
        }

        ///////////////////////////////////////////////////////////////////////////////////////////
        // P/Invoke
        ///////////////////////////////////////////////////////////////////////////////////////////
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
        ///////////////////////////////////////////////////////////////////////////////////////////
    }
}
