// *
// * Copyright (C) 2008 Roger Studio.Alsing : http://www.RogerAlsing.com
// *
// * This library is free software; you can redistribute it and/or modify it
// * under the terms of the GNU Lesser General Public License 2.1 or later, as
// * published by the Free Software Foundation. See the included license.txt
// * or http://www.gnu.org/copyleft/lesser.html for details.
// *
// *

using System.Collections;
using System.ComponentModel.Design;
using System.Windows.Forms.Design;
using Studio.Alsing.SourceCode;

namespace Studio.Alsing.Windows.Forms.SyntaxBox
{
    /// <summary>
    /// Designer for the SyntaxBoxControl
    /// </summary>
    public class SyntaxBoxDesigner : ControlDesigner
    {
        protected ISelectionService SelectionService
        {
            get { return (ISelectionService) GetService(typeof (ISelectionService)); }
        }

        protected virtual IDesignerHost DesignerHost
        {
            get { return (IDesignerHost) base.GetService(typeof (IDesignerHost)); }
        }

        //protected void OnActivate(object s, EventArgs e) {}

        public override void InitializeNewComponent(IDictionary defaultValues)
        {
            base.InitializeNewComponent(defaultValues);
            if (DesignerHost != null)
            {
                DesignerTransaction trans = DesignerHost.CreateTransaction("Adding Syntaxdocument");
                var sd = DesignerHost.CreateComponent(typeof (SyntaxDocument)) as SyntaxDocument;

                var sb = Control as SyntaxBoxControl;

                if (sb == null)
                {
                    trans.Cancel();
                }
                else
                {
                    sb.Document = sd;
                    trans.Commit();
                }
            }
        }
    }
}