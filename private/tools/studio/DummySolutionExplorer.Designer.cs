namespace Studio
{
    partial class DummySolutionExplorer
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(DummySolutionExplorer));
			this.m_treeView = new System.Windows.Forms.TreeView();
			this.imageList1 = new System.Windows.Forms.ImageList(this.components);
			this.SuspendLayout();
			// 
			// m_treeView
			// 
			this.m_treeView.AllowDrop = true;
			this.m_treeView.Dock = System.Windows.Forms.DockStyle.Fill;
			this.m_treeView.ImageIndex = 0;
			this.m_treeView.ImageList = this.imageList1;
			this.m_treeView.Indent = 19;
			this.m_treeView.LabelEdit = true;
			this.m_treeView.Location = new System.Drawing.Point(0, 24);
			this.m_treeView.Name = "m_treeView";
			this.m_treeView.SelectedImageIndex = 5;
			this.m_treeView.ShowRootLines = false;
			this.m_treeView.Size = new System.Drawing.Size(245, 297);
			this.m_treeView.TabIndex = 0;
			this.m_treeView.BeforeExpand += new System.Windows.Forms.TreeViewCancelEventHandler(this.m_treeView_BeforeExpand);
			this.m_treeView.DoubleClick += new System.EventHandler(this.m_treeView_DoubleClick);
			this.m_treeView.BeforeCollapse += new System.Windows.Forms.TreeViewCancelEventHandler(this.m_treeView_BeforeCollapse);
			this.m_treeView.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.m_treeView_AfterSelect);
			this.m_treeView.MouseDown += new System.Windows.Forms.MouseEventHandler(this.m_treeView_MouseDown);
			this.m_treeView.BeforeLabelEdit += new System.Windows.Forms.NodeLabelEditEventHandler(this.m_treeView_BeforeLabelEdit);
			// 
			// imageList1
			// 
			this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
			this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
			this.imageList1.Images.SetKeyName(0, "");
			this.imageList1.Images.SetKeyName(1, "FolderOpen");
			this.imageList1.Images.SetKeyName(2, "Folder");
			this.imageList1.Images.SetKeyName(3, "Package");
			this.imageList1.Images.SetKeyName(4, "Substages");
			this.imageList1.Images.SetKeyName(5, "Project");
			this.imageList1.Images.SetKeyName(6, "Stage");
			this.imageList1.Images.SetKeyName(7, "");
			this.imageList1.Images.SetKeyName(8, "Menu");
			this.imageList1.Images.SetKeyName(9, "Scene");
			this.imageList1.Images.SetKeyName(10, "Resources");
			this.imageList1.Images.SetKeyName(11, "");
			this.imageList1.Images.SetKeyName(12, "reseditui_27001.ico");
			this.imageList1.Images.SetKeyName(13, "reseditui_26928.ico");
			this.imageList1.Images.SetKeyName(14, "reseditui_27003.ico");
			this.imageList1.Images.SetKeyName(15, "reseditui_27006.ico");
			this.imageList1.Images.SetKeyName(16, "");
			this.imageList1.Images.SetKeyName(17, "Package.bmp");
			this.imageList1.Images.SetKeyName(18, "");
			this.imageList1.Images.SetKeyName(19, "");
			this.imageList1.Images.SetKeyName(20, "Project.bmp");
			// 
			// DummySolutionExplorer
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.ClientSize = new System.Drawing.Size(245, 322);
			this.Controls.Add(this.m_treeView);
			this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.HideOnClose = true;
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.Name = "DummySolutionExplorer";
			this.Padding = new System.Windows.Forms.Padding(0, 24, 0, 1);
			this.ShowHint = Studio.WinFormsUI.Docking.DockState.DockRight;
			this.TabText = "Project Explorer";
			this.Text = "Project Explorer - WinFormsUI";
			this.ResumeLayout(false);

		}
		#endregion

        private System.Windows.Forms.ImageList imageList1;
        public System.Windows.Forms.TreeView m_treeView;
    }
}