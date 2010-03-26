using System;
using System.Drawing;
using System.Runtime.InteropServices;

namespace Studio
{
    class Bikini
    {
#if DEBUG
#   if x86
        [DllImport("bikini (Win32!Debug).dll", CharSet = CharSet.Auto)]
#   elif x64
        [DllImport("bikini (x64!Debug).dll", CharSet = CharSet.Auto)]
#   endif
#elif RELEASE
#   if x86
        [DllImport("bikini (Win32!Release).dll", CharSet = CharSet.Auto)]
#   elif x64
        [DllImport("bikini (x64!Release).dll", CharSet = CharSet.Auto)]
#   endif
#endif
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern String Request([MarshalAs(UnmanagedType.LPStr)] String _XML);
    }
}
