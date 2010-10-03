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
        private Guid m_object;

        public ScriptDoc(Guid _object)
        {
            m_object = _object;

            InitializeComponent();

            //
            String l_script = Bikini.ObjectScript(m_object);
            syntaxBoxControl1.Document.Text = l_script;
            syntaxBoxControl1.Document.Parser.Init("Squirrel.syn");
        }

        //public String Code
        //{
        //    get
        //    {
        //        return syntaxBoxControl1.Document.Text;
        //    }
        //    set
        //    {
        //        syntaxBoxControl1.Document.Text = value;
        //    }
        //}

        private void syntaxDocument1_Change(object sender, EventArgs e)
        {
            Bikini.ChangeObjectScript(m_object, syntaxBoxControl1.Document.Text);
        }
    }
}
