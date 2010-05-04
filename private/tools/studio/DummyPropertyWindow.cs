using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Studio.WinFormsUI.Docking;

namespace Studio
{
    public partial class DummyPropertyWindow : ToolWindow
    {
        public DummyPropertyWindow()
        {
            InitializeComponent();
        }

        private void comboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            propertyGrid.SelectedObject = comboBox.SelectedItem;
        }

		public Object SelectedObject { set
		{
			comboBox.Items.Clear();
			propertyGrid.SelectedObject = null;

			if (value is Bikini.ProjectItem)
			{
				Bikini.ProjectItem l_item = (Bikini.ProjectItem)value;
				l_item.comboBox = comboBox;

				comboBox.Items.Add(l_item);
				comboBox.SelectedIndex = 0;
			}
		}}
    }
}