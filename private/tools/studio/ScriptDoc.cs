using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Studio.Alsing;
using Studio.Alsing.Windows.Forms;
using Studio.Alsing.SourceCode;
using Studio.WinFormsUI.Docking;

namespace Studio
{
    public partial class ScriptDoc : DockContent
    {
        public ScriptDoc()
        {
            InitializeComponent();

            //
            syntaxBoxControl1.Document.Parser.Init("Squirrel.syn");
        }
    }
}
