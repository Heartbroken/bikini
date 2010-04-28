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
            System.Windows.Forms.TreeNode treeNode1 = new System.Windows.Forms.TreeNode("Stage \'Menu\'", 6, 6);
            System.Windows.Forms.TreeNode treeNode2 = new System.Windows.Forms.TreeNode("Stage \'Loading\'", 6, 6);
            System.Windows.Forms.TreeNode treeNode3 = new System.Windows.Forms.TreeNode("Stage \'Game\'", 6, 6);
            System.Windows.Forms.TreeNode treeNode4 = new System.Windows.Forms.TreeNode("Substages", 4, 4, new System.Windows.Forms.TreeNode[] {
            treeNode1,
            treeNode2,
            treeNode3});
            System.Windows.Forms.TreeNode treeNode5 = new System.Windows.Forms.TreeNode("Main.menu", 8, 8);
            System.Windows.Forms.TreeNode treeNode6 = new System.Windows.Forms.TreeNode("Pause.menu", 8, 8);
            System.Windows.Forms.TreeNode treeNode7 = new System.Windows.Forms.TreeNode("Loading.menu", 8, 8);
            System.Windows.Forms.TreeNode treeNode8 = new System.Windows.Forms.TreeNode("Menus", 2, 2, new System.Windows.Forms.TreeNode[] {
            treeNode5,
            treeNode6,
            treeNode7});
            System.Windows.Forms.TreeNode treeNode9 = new System.Windows.Forms.TreeNode("Main.scene", 9, 9);
            System.Windows.Forms.TreeNode treeNode10 = new System.Windows.Forms.TreeNode("Loading.scene", 9, 9);
            System.Windows.Forms.TreeNode treeNode11 = new System.Windows.Forms.TreeNode("Scenes", 2, 2, new System.Windows.Forms.TreeNode[] {
            treeNode9,
            treeNode10});
            System.Windows.Forms.TreeNode treeNode12 = new System.Windows.Forms.TreeNode("Resources", 10, 10, new System.Windows.Forms.TreeNode[] {
            treeNode8,
            treeNode11});
            System.Windows.Forms.TreeNode treeNode13 = new System.Windows.Forms.TreeNode("Stage \'Main\'", 6, 6, new System.Windows.Forms.TreeNode[] {
            treeNode4,
            treeNode12});
            System.Windows.Forms.TreeNode treeNode14 = new System.Windows.Forms.TreeNode("Package \'Grrr\'", 3, 3, new System.Windows.Forms.TreeNode[] {
            treeNode13});
            System.Windows.Forms.TreeNode treeNode15 = new System.Windows.Forms.TreeNode("Stage \'E1L1\'", 6, 6);
            System.Windows.Forms.TreeNode treeNode16 = new System.Windows.Forms.TreeNode("Stage \'E1L2\'", 6, 6);
            System.Windows.Forms.TreeNode treeNode17 = new System.Windows.Forms.TreeNode("Substages", 4, 4, new System.Windows.Forms.TreeNode[] {
            treeNode15,
            treeNode16});
            System.Windows.Forms.TreeNode treeNode18 = new System.Windows.Forms.TreeNode("Resources", 10, 10);
            System.Windows.Forms.TreeNode treeNode19 = new System.Windows.Forms.TreeNode("Stage \'E1\'", 6, 6, new System.Windows.Forms.TreeNode[] {
            treeNode17,
            treeNode18});
            System.Windows.Forms.TreeNode treeNode20 = new System.Windows.Forms.TreeNode("Package \'Grrr_E1\'", 3, 3, new System.Windows.Forms.TreeNode[] {
            treeNode19});
            System.Windows.Forms.TreeNode treeNode21 = new System.Windows.Forms.TreeNode("Project \'Grrr\'", 5, 5, new System.Windows.Forms.TreeNode[] {
            treeNode14,
            treeNode20});
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
            treeNode1.ImageIndex = 6;
            treeNode1.Name = "";
            treeNode1.SelectedImageIndex = 6;
            treeNode1.Text = "Stage \'Menu\'";
            treeNode2.ImageIndex = 6;
            treeNode2.Name = "";
            treeNode2.SelectedImageIndex = 6;
            treeNode2.Text = "Stage \'Loading\'";
            treeNode3.ImageIndex = 6;
            treeNode3.Name = "";
            treeNode3.SelectedImageIndex = 6;
            treeNode3.Text = "Stage \'Game\'";
            treeNode4.ImageIndex = 4;
            treeNode4.Name = "";
            treeNode4.SelectedImageIndex = 4;
            treeNode4.Text = "Substages";
            treeNode5.ImageIndex = 8;
            treeNode5.Name = "";
            treeNode5.SelectedImageIndex = 8;
            treeNode5.Text = "Main.menu";
            treeNode6.ImageIndex = 8;
            treeNode6.Name = "";
            treeNode6.SelectedImageIndex = 8;
            treeNode6.Text = "Pause.menu";
            treeNode7.ImageIndex = 8;
            treeNode7.Name = "";
            treeNode7.SelectedImageIndex = 8;
            treeNode7.Text = "Loading.menu";
            treeNode8.ImageIndex = 2;
            treeNode8.Name = "";
            treeNode8.SelectedImageIndex = 2;
            treeNode8.Text = "Menus";
            treeNode9.ImageIndex = 9;
            treeNode9.Name = "";
            treeNode9.SelectedImageIndex = 9;
            treeNode9.Text = "Main.scene";
            treeNode10.ImageIndex = 9;
            treeNode10.Name = "";
            treeNode10.SelectedImageIndex = 9;
            treeNode10.Text = "Loading.scene";
            treeNode11.ImageIndex = 2;
            treeNode11.Name = "";
            treeNode11.SelectedImageIndex = 2;
            treeNode11.Text = "Scenes";
            treeNode12.ImageIndex = 10;
            treeNode12.Name = "";
            treeNode12.SelectedImageIndex = 10;
            treeNode12.Text = "Resources";
            treeNode13.ImageIndex = 6;
            treeNode13.Name = "";
            treeNode13.SelectedImageIndex = 6;
            treeNode13.Text = "Stage \'Main\'";
            treeNode14.ImageIndex = 3;
            treeNode14.Name = "";
            treeNode14.SelectedImageIndex = 3;
            treeNode14.Text = "Package \'Grrr\'";
            treeNode15.ImageIndex = 6;
            treeNode15.Name = "";
            treeNode15.SelectedImageIndex = 6;
            treeNode15.Text = "Stage \'E1L1\'";
            treeNode16.ImageIndex = 6;
            treeNode16.Name = "";
            treeNode16.SelectedImageIndex = 6;
            treeNode16.Text = "Stage \'E1L2\'";
            treeNode17.ImageIndex = 4;
            treeNode17.Name = "";
            treeNode17.SelectedImageIndex = 4;
            treeNode17.Text = "Substages";
            treeNode18.ImageIndex = 10;
            treeNode18.Name = "";
            treeNode18.SelectedImageIndex = 10;
            treeNode18.Text = "Resources";
            treeNode19.ImageIndex = 6;
            treeNode19.Name = "";
            treeNode19.SelectedImageIndex = 6;
            treeNode19.Text = "Stage \'E1\'";
            treeNode20.ImageIndex = 3;
            treeNode20.Name = "";
            treeNode20.SelectedImageIndex = 3;
            treeNode20.Text = "Package \'Grrr_E1\'";
            treeNode21.ImageIndex = 5;
            treeNode21.Name = "solutionNode";
            treeNode21.SelectedImageIndex = 5;
            treeNode21.Text = "Project \'Grrr\'";
            this.m_treeView.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode21});
            this.m_treeView.SelectedImageIndex = 5;
            this.m_treeView.ShowRootLines = false;
            this.m_treeView.Size = new System.Drawing.Size(245, 297);
            this.m_treeView.TabIndex = 0;
            this.m_treeView.BeforeExpand += new System.Windows.Forms.TreeViewCancelEventHandler(this.m_treeView_BeforeExpand);
            this.m_treeView.DoubleClick += new System.EventHandler(this.m_treeView_DoubleClick);
            this.m_treeView.BeforeCollapse += new System.Windows.Forms.TreeViewCancelEventHandler(this.m_treeView_BeforeCollapse);
            this.m_treeView.MouseDown += new System.Windows.Forms.MouseEventHandler(this.m_treeView_MouseDown);
            this.m_treeView.BeforeLabelEdit += new System.Windows.Forms.NodeLabelEditEventHandler(this.m_treeView_BeforeLabelEdit);
            // 
            // imageList1
            // 
            this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList1.Images.SetKeyName(0, "");
            this.imageList1.Images.SetKeyName(1, "FolderOpen.bmp");
            this.imageList1.Images.SetKeyName(2, "FolderClose.bmp");
            this.imageList1.Images.SetKeyName(3, "Package2.bmp");
            this.imageList1.Images.SetKeyName(4, "Substages.bmp");
            this.imageList1.Images.SetKeyName(5, "Project2.bmp");
            this.imageList1.Images.SetKeyName(6, "Substage.bmp");
            this.imageList1.Images.SetKeyName(7, "");
            this.imageList1.Images.SetKeyName(8, "Interface.bmp");
            this.imageList1.Images.SetKeyName(9, "Scene.bmp");
            this.imageList1.Images.SetKeyName(10, "Resources.bmp");
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