using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Reflection;
using System.Windows.Forms;
using System.IO;
using Studio.WinFormsUI.Docking;
using Studio.Customization;

namespace Studio
{
    public partial class MainForm : Form
    {
        private bool m_bSaveLayout = true;
		private DeserializeDockContent m_deserializeDockContent;
		private DummySolutionExplorer m_solutionExplorer = new DummySolutionExplorer();
		private DummyPropertyWindow m_propertyWindow = new DummyPropertyWindow();
		private DummyToolbox m_toolbox = new DummyToolbox();
		private DummyOutputWindow m_outputWindow = new DummyOutputWindow();
		private DummyTaskList m_taskList = new DummyTaskList();

		public DummyPropertyWindow PropertyWindow { get { return m_propertyWindow; } }

        public MainForm()
        {
            InitializeComponent();
            showRightToLeft.Checked = (RightToLeft == RightToLeft.Yes);
            RightToLeftLayout = showRightToLeft.Checked;
            m_solutionExplorer = new DummySolutionExplorer();
            m_solutionExplorer.RightToLeftLayout = RightToLeftLayout;
            //m_solutionExplorer.m_treeView.Nodes["solutionNode"].Expand();
			m_deserializeDockContent = new DeserializeDockContent(GetContentFromPersistString);

            //Bikini.Test(-125, "Test call");
        }

		private void menuItemExit_Click(object sender, System.EventArgs e)
		{
			Close();
		}

		private void menuItemSolutionExplorer_Click(object sender, System.EventArgs e)
		{
			m_solutionExplorer.Show(dockPanel);
		}

		private void menuItemPropertyWindow_Click(object sender, System.EventArgs e)
		{
			m_propertyWindow.Show(dockPanel);
		}

		private void menuItemToolbox_Click(object sender, System.EventArgs e)
		{
			m_toolbox.Show(dockPanel);
		}

		private void menuItemOutputWindow_Click(object sender, System.EventArgs e)
		{
			m_outputWindow.Show(dockPanel);
		}

		private void menuItemTaskList_Click(object sender, System.EventArgs e)
		{
			m_taskList.Show(dockPanel);
		}

		private void menuItemAbout_Click(object sender, System.EventArgs e)
		{
			AboutDialog aboutDialog = new AboutDialog();
			aboutDialog.ShowDialog(this);
		}

		private IDockContent FindDocument(string text)
		{
			if (dockPanel.DocumentStyle == DocumentStyle.SystemMdi)
			{
				foreach (Form form in MdiChildren)
					if (form.Text == text)
						return form as IDockContent;
				
				return null;
			}
			else
			{
				foreach (IDockContent content in dockPanel.Documents)
					if (content.DockHandler.TabText == text)
						return content;

				return null;
			}
		}

        public void UpdateViews()
        {
            for (int index = dockPanel.Contents.Count - 1; index >= 0; index--)
            {
                if (dockPanel.Contents[index] is BikiniView)
                {
                    BikiniView content = (BikiniView)dockPanel.Contents[index];
                    content.UpdateView();
                }
            }
        }

		private void menuItemNew_Click(object sender, System.EventArgs e)
		{
			NewProjectDialog l_newProjectDlg = new NewProjectDialog();
			l_newProjectDlg.ProjectLocation = Directory.GetCurrentDirectory();

			if (l_newProjectDlg.ShowDialog(this) == DialogResult.OK)
			{
				Guid l_project = Bikini.NewProject(l_newProjectDlg.ProjectLocation, l_newProjectDlg.ProjectName);
				m_solutionExplorer.UpdateTreeView(l_project);
			}

			/////////

			////DummyDoc dummyDoc = CreateNewDocument();
			//BikiniView dummyDoc = CreateNewGuiView();
			////ScriptDoc dummyDoc = CreateNewLuaDoc();
			//if (dockPanel.DocumentStyle == DocumentStyle.SystemMdi)
			//{
			//    dummyDoc.MdiParent = this;
			//    dummyDoc.Show();
			//}
			//else
			//    dummyDoc.Show(dockPanel);
		}

        private ScriptDoc CreateNewLuaDoc()
        {
            ScriptDoc l_luaDoc = new ScriptDoc();

            int l_count = 1;
            string l_text = "Document" + l_count.ToString();
            while (FindDocument(l_text) != null)
            {
                l_count++;
                l_text = "Document" + l_count.ToString();
            }
            l_luaDoc.Text = l_text;
            return l_luaDoc;
        }

        private BikiniView CreateNewGuiView()
        {
            BikiniView l_guiView = new BikiniView();

            int l_count = 1;
            string l_text = "Document" + l_count.ToString();
            while (FindDocument(l_text) != null)
            {
                l_count++;
                l_text = "Document" + l_count.ToString();
            }
            l_guiView.Text = l_text;
            return l_guiView;
        }

		private DummyDoc CreateNewDocument()
		{
			DummyDoc dummyDoc = new DummyDoc();

			int count = 1;
			//string text = "C:\\MADFDKAJ\\ADAKFJASD\\ADFKDSAKFJASD\\ASDFKASDFJASDF\\ASDFIJADSFJ\\ASDFKDFDA" + count.ToString();
            string text = "Document" + count.ToString();
            while (FindDocument(text) != null)
			{
				count ++;
                //text = "C:\\MADFDKAJ\\ADAKFJASD\\ADFKDSAKFJASD\\ASDFKASDFJASDF\\ASDFIJADSFJ\\ASDFKDFDA" + count.ToString();
                text = "Document" + count.ToString();
            }
			dummyDoc.Text = text;
			return dummyDoc;
		}

		private DummyDoc CreateNewDocument(string text)
		{
			DummyDoc dummyDoc = new DummyDoc();
			dummyDoc.Text = text;
			return dummyDoc;
		}

		private void menuItemOpen_Click(object sender, System.EventArgs e)
		{
			if (openProjectDialog.ShowDialog() == DialogResult.OK)
			{
				Bikini.OpenProject(openProjectDialog.FileName);
			}

			//OpenFileDialog openFile = new OpenFileDialog();

			//openFile.InitialDirectory = Application.ExecutablePath;
			//openFile.Filter = "rtf files (*.rtf)|*.rtf|txt files (*.txt)|*.txt|All files (*.*)|*.*" ;
			//openFile.FilterIndex = 1;
			//openFile.RestoreDirectory = true ;

			//if(openFile.ShowDialog() == DialogResult.OK)
			//{
			//    string fullName = openFile.FileName;
			//    string fileName = Path.GetFileName(fullName);

			//    if (FindDocument(fileName) != null)
			//    {
			//        MessageBox.Show("The document: " + fileName + " has already opened!");
			//        return;
			//    }

			//    DummyDoc dummyDoc = new DummyDoc();
			//    dummyDoc.Text = fileName;
			//    if (dockPanel.DocumentStyle == DocumentStyle.SystemMdi)
			//    {
			//        dummyDoc.MdiParent = this;
			//        dummyDoc.Show();
			//    }
			//    else
			//        dummyDoc.Show(dockPanel);
			//    try
			//    {
			//        dummyDoc.FileName = fullName;
			//    }
			//    catch (Exception exception)
			//    {
			//        dummyDoc.Close();
			//        MessageBox.Show(exception.Message);
			//    }

			//}
		}

		private void menuItemFile_Popup(object sender, System.EventArgs e)
		{
			if (dockPanel.DocumentStyle == DocumentStyle.SystemMdi)
			{
				menuItemClose.Enabled = menuItemCloseAll.Enabled = (ActiveMdiChild != null);
			}
			else
			{
				menuItemClose.Enabled = (dockPanel.ActiveDocument != null);
				menuItemCloseAll.Enabled = (dockPanel.DocumentsCount > 0);
			}
		}

		private void menuItemClose_Click(object sender, System.EventArgs e)
		{
			if (dockPanel.DocumentStyle == DocumentStyle.SystemMdi)
				ActiveMdiChild.Close();
			else if (dockPanel.ActiveDocument != null)
				dockPanel.ActiveDocument.DockHandler.Close();
		}

		private void menuItemCloseAll_Click(object sender, System.EventArgs e)
		{
			CloseAllDocuments();
		}

		private void CloseAllDocuments()
		{
			if (dockPanel.DocumentStyle == DocumentStyle.SystemMdi)
			{
				foreach (Form form in MdiChildren)
					form.Close();
			}
			else
			{
                for (int index = dockPanel.Contents.Count - 1; index >= 0; index--)
                {
                    if (dockPanel.Contents[index] is IDockContent)
                    {
                        IDockContent content = (IDockContent)dockPanel.Contents[index];
                        content.DockHandler.Close();
                    }
                }
			}
		}

		private IDockContent GetContentFromPersistString(string persistString)
		{
			if (persistString == typeof(DummySolutionExplorer).ToString())
				return m_solutionExplorer;
			else if (persistString == typeof(DummyPropertyWindow).ToString())
				return m_propertyWindow;
			else if (persistString == typeof(DummyToolbox).ToString())
				return m_toolbox;
			else if (persistString == typeof(DummyOutputWindow).ToString())
				return m_outputWindow;
			else if (persistString == typeof(DummyTaskList).ToString())
				return m_taskList;
			else
			{
                // DummyDoc overrides GetPersistString to add extra information into persistString.
                // Any DockContent may override this value to add any needed information for deserialization.

				string[] parsedStrings = persistString.Split(new char[] { ',' });
				if (parsedStrings.Length != 3)
					return null;

				if (parsedStrings[0] != typeof(DummyDoc).ToString())
					return null;

				DummyDoc dummyDoc = new DummyDoc();
				if (parsedStrings[1] != string.Empty)
					dummyDoc.FileName = parsedStrings[1];
				if (parsedStrings[2] != string.Empty)
					dummyDoc.Text = parsedStrings[2];

				return dummyDoc;
			}
		}

		private void MainForm_Load(object sender, System.EventArgs e)
		{
			string configFile = Path.Combine(Path.GetDirectoryName(Application.ExecutablePath), "studio.layout");

			if (File.Exists(configFile))
				dockPanel.LoadFromXml(configFile, m_deserializeDockContent);
		}

		private void MainForm_Closing(object sender, System.ComponentModel.CancelEventArgs e)
		{
            string configFile = Path.Combine(Path.GetDirectoryName(Application.ExecutablePath), "studio.layout");
            if (m_bSaveLayout)
                dockPanel.SaveAsXml(configFile);
            else if (File.Exists(configFile))
                File.Delete(configFile);
		}

		private void menuItemToolBar_Click(object sender, System.EventArgs e)
		{
			toolBar.Visible = menuItemToolBar.Checked = !menuItemToolBar.Checked;
		}

		private void menuItemStatusBar_Click(object sender, System.EventArgs e)
		{
			statusBar.Visible = menuItemStatusBar.Checked = !menuItemStatusBar.Checked;
		}

        private void toolBar_ButtonClick(object sender, System.Windows.Forms.ToolStripItemClickedEventArgs e)
        {
            if (e.ClickedItem == toolBarButtonNew)
                menuItemNew_Click(null, null);
            else if (e.ClickedItem == toolBarButtonOpen)
                menuItemOpen_Click(null, null);
            else if (e.ClickedItem == toolBarButtonSolutionExplorer)
                menuItemSolutionExplorer_Click(null, null);
            else if (e.ClickedItem == toolBarButtonPropertyWindow)
                menuItemPropertyWindow_Click(null, null);
            else if (e.ClickedItem == toolBarButtonToolbox)
                menuItemToolbox_Click(null, null);
            else if (e.ClickedItem == toolBarButtonOutputWindow)
                menuItemOutputWindow_Click(null, null);
            else if (e.ClickedItem == toolBarButtonTaskList)
                menuItemTaskList_Click(null, null);
            else if (e.ClickedItem == toolBarButtonLayoutByCode)
                menuItemLayoutByCode_Click(null, null);
            else if (e.ClickedItem == toolBarButtonLayoutByXml)
                menuItemLayoutByXml_Click(null, null);
        }

		private void menuItemNewWindow_Click(object sender, System.EventArgs e)
		{
			MainForm newWindow = new MainForm();
			newWindow.Text = newWindow.Text + " - New";
			newWindow.Show();
		}

		private void menuItemTools_Popup(object sender, System.EventArgs e)
		{
			menuItemLockLayout.Checked = !this.dockPanel.AllowEndUserDocking;
		}

		private void menuItemLockLayout_Click(object sender, System.EventArgs e)
		{
			dockPanel.AllowEndUserDocking = !dockPanel.AllowEndUserDocking;
		}

		private void menuItemLayoutByCode_Click(object sender, System.EventArgs e)
		{
			dockPanel.SuspendLayout(true);

			m_solutionExplorer.Show(dockPanel, DockState.DockRight);
			m_propertyWindow.Show(m_solutionExplorer.Pane, m_solutionExplorer);
			m_toolbox.Show(dockPanel, new Rectangle(98, 133, 200, 383));
			m_outputWindow.Show(m_solutionExplorer.Pane, DockAlignment.Bottom, 0.35);
			m_taskList.Show(m_toolbox.Pane, DockAlignment.Left, 0.4);

			CloseAllDocuments();
			DummyDoc doc1 = CreateNewDocument("Document1");
			DummyDoc doc2 = CreateNewDocument("Document2");
			DummyDoc doc3 = CreateNewDocument("Document3");
			DummyDoc doc4 = CreateNewDocument("Document4");
			doc1.Show(dockPanel, DockState.Document);
			doc2.Show(doc1.Pane, null);
			doc3.Show(doc1.Pane, DockAlignment.Bottom, 0.5);
			doc4.Show(doc3.Pane, DockAlignment.Right, 0.5);

			dockPanel.ResumeLayout(true, true);
		}

		private void menuItemLayoutByXml_Click(object sender, System.EventArgs e)
		{
			dockPanel.SuspendLayout(true);

			// In order to load layout from XML, we need to close all the DockContents
			CloseAllContents();

			Assembly assembly = Assembly.GetAssembly(typeof(MainForm));
			Stream xmlStream = assembly.GetManifestResourceStream("DockSample.Resources.DockPanel.xml");
			dockPanel.LoadFromXml(xmlStream, m_deserializeDockContent);
			xmlStream.Close();

			dockPanel.ResumeLayout(true, true);
		}

		private void CloseAllContents()
		{
			// we don't want to create another instance of tool window, set DockPanel to null
			m_solutionExplorer.DockPanel = null;
			m_propertyWindow.DockPanel = null;
			m_toolbox.DockPanel = null;
			m_outputWindow.DockPanel = null;
			m_taskList.DockPanel = null;

			// Close all other document windows
			CloseAllDocuments();
		}

		private void SetSchema(object sender, System.EventArgs e)
		{
			CloseAllContents();

			if (sender == menuItemSchemaVS2005)
				Extender.SetSchema(dockPanel, Extender.Schema.VS2005);
			else if (sender == menuItemSchemaVS2003)
				Extender.SetSchema(dockPanel, Extender.Schema.VS2003);

            menuItemSchemaVS2005.Checked = (sender == menuItemSchemaVS2005);
            menuItemSchemaVS2003.Checked = (sender == menuItemSchemaVS2003);
		}

		private void SetDocumentStyle(object sender, System.EventArgs e)
		{
			DocumentStyle oldStyle = dockPanel.DocumentStyle;
			DocumentStyle newStyle;
			if (sender == menuItemDockingMdi)
				newStyle = DocumentStyle.DockingMdi;
			else if (sender == menuItemDockingWindow)
				newStyle = DocumentStyle.DockingWindow;
			else if (sender == menuItemDockingSdi)
				newStyle = DocumentStyle.DockingSdi;
			else
				newStyle = DocumentStyle.SystemMdi;
			
			if (oldStyle == newStyle)
				return;

			if (oldStyle == DocumentStyle.SystemMdi || newStyle == DocumentStyle.SystemMdi)
				CloseAllDocuments();

			dockPanel.DocumentStyle = newStyle;
			menuItemDockingMdi.Checked = (newStyle == DocumentStyle.DockingMdi);
			menuItemDockingWindow.Checked = (newStyle == DocumentStyle.DockingWindow);
			menuItemDockingSdi.Checked = (newStyle == DocumentStyle.DockingSdi);
			menuItemSystemMdi.Checked = (newStyle == DocumentStyle.SystemMdi);
			menuItemLayoutByCode.Enabled = (newStyle != DocumentStyle.SystemMdi);
			menuItemLayoutByXml.Enabled = (newStyle != DocumentStyle.SystemMdi);
			toolBarButtonLayoutByCode.Enabled = (newStyle != DocumentStyle.SystemMdi);
			toolBarButtonLayoutByXml.Enabled = (newStyle != DocumentStyle.SystemMdi);
		}

		private void menuItemCloseAllButThisOne_Click(object sender, System.EventArgs e)
		{
			if (dockPanel.DocumentStyle == DocumentStyle.SystemMdi)
			{
				Form activeMdi = ActiveMdiChild;
				foreach (Form form in MdiChildren)
				{
					if (form != activeMdi)
						form.Close();
				}
			}
			else
			{
				foreach (IDockContent document in dockPanel.DocumentsToArray())
				{
					if (!document.DockHandler.IsActivated)
						document.DockHandler.Close();
				}
			}
		}

		private void menuItemShowDocumentIcon_Click(object sender, System.EventArgs e)
		{
			dockPanel.ShowDocumentIcon = menuItemShowDocumentIcon.Checked= !menuItemShowDocumentIcon.Checked;
		}

        private void showRightToLeft_Click(object sender, EventArgs e)
        {
            CloseAllContents();
            if (showRightToLeft.Checked)
            {
                this.RightToLeft = RightToLeft.No;
                this.RightToLeftLayout = false;
            }
            else
            {
                this.RightToLeft = RightToLeft.Yes;
                this.RightToLeftLayout = true;
            }
            m_solutionExplorer.RightToLeftLayout = this.RightToLeftLayout;
            showRightToLeft.Checked = !showRightToLeft.Checked;
        }

        private void exitWithoutSavingLayout_Click(object sender, EventArgs e)
        {
            m_bSaveLayout = false;
            Close();
            m_bSaveLayout = true;
        }

		private void toolStripButtonSaveAll_Click(object sender, EventArgs e)
		{
			Bikini.SaveAll();
		}
    }
}