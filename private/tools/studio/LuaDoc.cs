using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Alsing;
using Alsing.Windows.Forms;
using Alsing.SourceCode;
using Studio.WinFormsUI.Docking;

namespace Studio
{
    public partial class LuaDoc : DockContent
    {
        public LuaDoc()
        {
            InitializeComponent();

            //
            syntaxBoxControl1.Document.Parser.Init("Lua.syn");
        }
    }
}
