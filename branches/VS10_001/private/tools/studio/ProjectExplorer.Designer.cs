namespace Studio
{
    partial class ProjectExplorer
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ProjectExplorer));
            this.m_treeView = new System.Windows.Forms.TreeView();
            this.m_projectContextMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.buildToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.viewCodeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newPackageToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newFolderToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newStageToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newResourceToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newMenuToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.removeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.m_treeViewImageList = new System.Windows.Forms.ImageList(this.components);
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.m_projectContextMenu.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_treeView
            // 
            this.m_treeView.AllowDrop = true;
            this.m_treeView.ContextMenuStrip = this.m_projectContextMenu;
            this.m_treeView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_treeView.HideSelection = false;
            this.m_treeView.ImageIndex = 0;
            this.m_treeView.ImageList = this.m_treeViewImageList;
            this.m_treeView.Indent = 19;
            this.m_treeView.LabelEdit = true;
            this.m_treeView.Location = new System.Drawing.Point(0, 24);
            this.m_treeView.Name = "m_treeView";
            this.m_treeView.SelectedImageIndex = 5;
            this.m_treeView.ShowRootLines = false;
            this.m_treeView.Size = new System.Drawing.Size(245, 297);
            this.m_treeView.TabIndex = 0;
            this.m_treeView.BeforeLabelEdit += new System.Windows.Forms.NodeLabelEditEventHandler(this.m_treeView_BeforeLabelEdit);
            this.m_treeView.AfterLabelEdit += new System.Windows.Forms.NodeLabelEditEventHandler(this.m_treeView_AfterLabelEdit);
            this.m_treeView.BeforeCollapse += new System.Windows.Forms.TreeViewCancelEventHandler(this.m_treeView_BeforeCollapse);
            this.m_treeView.BeforeExpand += new System.Windows.Forms.TreeViewCancelEventHandler(this.m_treeView_BeforeExpand);
            this.m_treeView.BeforeSelect += new System.Windows.Forms.TreeViewCancelEventHandler(this.m_treeView_BeforeSelect);
            this.m_treeView.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.m_treeView_AfterSelect);
            this.m_treeView.Click += new System.EventHandler(this.m_treeView_Click);
            this.m_treeView.DragDrop += new System.Windows.Forms.DragEventHandler(this.m_treeView_DragDrop);
            this.m_treeView.DragOver += new System.Windows.Forms.DragEventHandler(this.m_treeView_DragOver);
            this.m_treeView.DoubleClick += new System.EventHandler(this.m_treeView_DoubleClick);
            this.m_treeView.MouseDown += new System.Windows.Forms.MouseEventHandler(this.m_treeView_MouseDown);
            this.m_treeView.MouseMove += new System.Windows.Forms.MouseEventHandler(this.m_treeView_MouseMove);
            this.m_treeView.MouseUp += new System.Windows.Forms.MouseEventHandler(this.m_treeView_MouseUp);
            // 
            // m_projectContextMenu
            // 
            this.m_projectContextMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.buildToolStripMenuItem,
            this.openToolStripMenuItem,
            this.viewCodeToolStripMenuItem,
            this.addToolStripMenuItem,
            this.removeToolStripMenuItem});
            this.m_projectContextMenu.Name = "treeViewContextMenu";
            this.m_projectContextMenu.Size = new System.Drawing.Size(153, 136);
            this.m_projectContextMenu.Opening += new System.ComponentModel.CancelEventHandler(this.m_projectContextMenu_Opening);
            // 
            // buildToolStripMenuItem
            // 
            this.buildToolStripMenuItem.Name = "buildToolStripMenuItem";
            this.buildToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.buildToolStripMenuItem.Tag = "Project";
            this.buildToolStripMenuItem.Text = "Build";
            this.buildToolStripMenuItem.Click += new System.EventHandler(this.buildToolStripMenuItem_Click);
            // 
            // viewCodeToolStripMenuItem
            // 
            this.viewCodeToolStripMenuItem.Name = "viewCodeToolStripMenuItem";
            this.viewCodeToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.viewCodeToolStripMenuItem.Tag = "Stage";
            this.viewCodeToolStripMenuItem.Text = "Edit Script";
            this.viewCodeToolStripMenuItem.Click += new System.EventHandler(this.viewCodeToolStripMenuItem_Click);
            // 
            // addToolStripMenuItem
            // 
            this.addToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newPackageToolStripMenuItem,
            this.newFolderToolStripMenuItem,
            this.newStageToolStripMenuItem,
            this.newResourceToolStripMenuItem});
            this.addToolStripMenuItem.Name = "addToolStripMenuItem";
            this.addToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.addToolStripMenuItem.Text = "Add";
            // 
            // newPackageToolStripMenuItem
            // 
            this.newPackageToolStripMenuItem.Image = global::Studio.Properties.Resources.Package2;
            this.newPackageToolStripMenuItem.Name = "newPackageToolStripMenuItem";
            this.newPackageToolStripMenuItem.Size = new System.Drawing.Size(149, 22);
            this.newPackageToolStripMenuItem.Tag = "";
            this.newPackageToolStripMenuItem.Text = "New Package";
            this.newPackageToolStripMenuItem.Click += new System.EventHandler(this.newPackageToolStripMenuItem_Click);
            // 
            // newFolderToolStripMenuItem
            // 
            this.newFolderToolStripMenuItem.Image = global::Studio.Properties.Resources.FolderOpen;
            this.newFolderToolStripMenuItem.Name = "newFolderToolStripMenuItem";
            this.newFolderToolStripMenuItem.Size = new System.Drawing.Size(149, 22);
            this.newFolderToolStripMenuItem.Tag = "";
            this.newFolderToolStripMenuItem.Text = "New Folder";
            this.newFolderToolStripMenuItem.Click += new System.EventHandler(this.newFolderToolStripMenuItem_Click);
            // 
            // newStageToolStripMenuItem
            // 
            this.newStageToolStripMenuItem.Image = global::Studio.Properties.Resources.Substage;
            this.newStageToolStripMenuItem.Name = "newStageToolStripMenuItem";
            this.newStageToolStripMenuItem.Size = new System.Drawing.Size(149, 22);
            this.newStageToolStripMenuItem.Tag = "Project|Stage";
            this.newStageToolStripMenuItem.Text = "New Stage";
            this.newStageToolStripMenuItem.Click += new System.EventHandler(this.newStageToolStripMenuItem_Click);
            // 
            // newResourceToolStripMenuItem
            // 
            this.newResourceToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newMenuToolStripMenuItem});
            this.newResourceToolStripMenuItem.Image = global::Studio.Properties.Resources.Resources2;
            this.newResourceToolStripMenuItem.Name = "newResourceToolStripMenuItem";
            this.newResourceToolStripMenuItem.Size = new System.Drawing.Size(149, 22);
            this.newResourceToolStripMenuItem.Tag = "Stage";
            this.newResourceToolStripMenuItem.Text = "New Resource";
            // 
            // newMenuToolStripMenuItem
            // 
            this.newMenuToolStripMenuItem.Image = global::Studio.Properties.Resources.Interface;
            this.newMenuToolStripMenuItem.Name = "newMenuToolStripMenuItem";
            this.newMenuToolStripMenuItem.Size = new System.Drawing.Size(132, 22);
            this.newMenuToolStripMenuItem.Text = "New Menu";
            this.newMenuToolStripMenuItem.Click += new System.EventHandler(this.newMenuToolStripMenuItem_Click);
            // 
            // removeToolStripMenuItem
            // 
            this.removeToolStripMenuItem.Name = "removeToolStripMenuItem";
            this.removeToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.removeToolStripMenuItem.Tag = "Package|PFolder|Stage|Resources|RFolder|Menu";
            this.removeToolStripMenuItem.Text = "Remove";
            this.removeToolStripMenuItem.Click += new System.EventHandler(this.removeToolStripMenuItem_Click);
            // 
            // m_treeViewImageList
            // 
            this.m_treeViewImageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("m_treeViewImageList.ImageStream")));
            this.m_treeViewImageList.TransparentColor = System.Drawing.Color.Transparent;
            this.m_treeViewImageList.Images.SetKeyName(0, "");
            this.m_treeViewImageList.Images.SetKeyName(1, "FolderOpen");
            this.m_treeViewImageList.Images.SetKeyName(2, "Folder");
            this.m_treeViewImageList.Images.SetKeyName(3, "Package");
            this.m_treeViewImageList.Images.SetKeyName(4, "Substages");
            this.m_treeViewImageList.Images.SetKeyName(5, "Project");
            this.m_treeViewImageList.Images.SetKeyName(6, "Stage");
            this.m_treeViewImageList.Images.SetKeyName(7, "");
            this.m_treeViewImageList.Images.SetKeyName(8, "Menu");
            this.m_treeViewImageList.Images.SetKeyName(9, "Scene");
            this.m_treeViewImageList.Images.SetKeyName(10, "Resources");
            this.m_treeViewImageList.Images.SetKeyName(11, "");
            this.m_treeViewImageList.Images.SetKeyName(12, "reseditui_27001.ico");
            this.m_treeViewImageList.Images.SetKeyName(13, "reseditui_26928.ico");
            this.m_treeViewImageList.Images.SetKeyName(14, "reseditui_27003.ico");
            this.m_treeViewImageList.Images.SetKeyName(15, "reseditui_27006.ico");
            this.m_treeViewImageList.Images.SetKeyName(16, "");
            this.m_treeViewImageList.Images.SetKeyName(17, "Package.bmp");
            this.m_treeViewImageList.Images.SetKeyName(18, "");
            this.m_treeViewImageList.Images.SetKeyName(19, "");
            this.m_treeViewImageList.Images.SetKeyName(20, "Project.bmp");
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.openToolStripMenuItem.Tag = "Stage";
            this.openToolStripMenuItem.Text = "Open";
            this.openToolStripMenuItem.Click += new System.EventHandler(this.openToolStripMenuItem_Click);
            // 
            // ProjectExplorer
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.ClientSize = new System.Drawing.Size(245, 322);
            this.Controls.Add(this.m_treeView);
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.HideOnClose = true;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "ProjectExplorer";
            this.Padding = new System.Windows.Forms.Padding(0, 24, 0, 1);
            this.ShowHint = Studio.WinFormsUI.Docking.DockState.DockRight;
            this.TabText = "Project Explorer";
            this.Text = "Project Explorer - WinFormsUI";
            this.m_projectContextMenu.ResumeLayout(false);
            this.ResumeLayout(false);

		}
		#endregion

        private System.Windows.Forms.ImageList m_treeViewImageList;
        public System.Windows.Forms.TreeView m_treeView;
		private System.Windows.Forms.ContextMenuStrip m_projectContextMenu;
		private System.Windows.Forms.ToolStripMenuItem addToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem newPackageToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem newFolderToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem buildToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem newStageToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem removeToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem newResourceToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem newMenuToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem viewCodeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
    }
}