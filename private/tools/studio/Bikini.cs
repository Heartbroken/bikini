using System;
using System.Drawing;
using System.Runtime.InteropServices;

namespace Studio
{
    class Bikini
    {
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
        public static extern String Request(String _XML);
    }
}
