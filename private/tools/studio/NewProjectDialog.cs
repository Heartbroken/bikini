using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Studio
{
	public partial class NewProjectDialog : Form
	{
		public NewProjectDialog()
		{
			InitializeComponent();
		}

		public String ProjectName { get { return m_projectName.Text; } }

		public String ProjectLocation
		{
			get { return m_projectLocation.Text; }
			set
			{
				m_projectLocation.Text = value;
			}
		}

		private void buttonBrowse_Click(object sender, EventArgs e)
		{
			m_folderBrowser.SelectedPath = ProjectLocation;

			if (m_folderBrowser.ShowDialog(this) == DialogResult.OK)
			{
				ProjectLocation = m_folderBrowser.SelectedPath;
			}
		}
	}
}
