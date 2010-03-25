using System;
using System.Drawing;
using System.Runtime.InteropServices;

namespace Studio
{
    class Bikini
    {
#if DEBUG
#   if x86
        [DllImport("bikini (Win32!Debug).dll", EntryPoint = "bikini_command")]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern String Command([MarshalAs(UnmanagedType.LPStr)] String _XML);
#   elif x64
        [DllImport("bikini (x64!Debug).dll", EntryPoint = "bikini_command")]
        public static extern String Command(String _XML);
#   endif
#elif RELEASE
#   if x86
        [DllImport("bikini (Win32!Release).dll", EntryPoint = "bikini_command")]
        public static extern String Command(String _XML);
#   elif x64
        [DllImport("bikini (x64!Release).dll", EntryPoint = "bikini_command")]
        public static extern String Command(String _XML);
#   endif
#endif
    }
}
