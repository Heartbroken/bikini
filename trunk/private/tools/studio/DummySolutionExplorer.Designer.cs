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
            System.Windows.Forms.TreeNode treeNode1 = new System.Windows.Forms.TreeNode("Intro.screen", 6, 6);
            System.Windows.Forms.TreeNode treeNode2 = new System.Windows.Forms.TreeNode("Menu.screen", 6, 6);
            System.Windows.Forms.TreeNode treeNode3 = new System.Windows.Forms.TreeNode("Main.screen", 6, 6, new System.Windows.Forms.TreeNode[] {
            treeNode1,
            treeNode2});
            System.Windows.Forms.TreeNode treeNode4 = new System.Windows.Forms.TreeNode("MainMenu.interface", 8, 8);
            System.Windows.Forms.TreeNode treeNode5 = new System.Windows.Forms.TreeNode("PauseMenu.interface", 8, 8);
            System.Windows.Forms.TreeNode treeNode6 = new System.Windows.Forms.TreeNode("Interfaces", 2, 1, new System.Windows.Forms.TreeNode[] {
            treeNode4,
            treeNode5});
            System.Windows.Forms.TreeNode treeNode7 = new System.Windows.Forms.TreeNode("MainMenu.scene", 9, 9);
            System.Windows.Forms.TreeNode treeNode8 = new System.Windows.Forms.TreeNode("Scenes", 2, 1, new System.Windows.Forms.TreeNode[] {
            treeNode7});
            System.Windows.Forms.TreeNode treeNode9 = new System.Windows.Forms.TreeNode("Resources", 2, 1, new System.Windows.Forms.TreeNode[] {
            treeNode6,
            treeNode8});
            System.Windows.Forms.TreeNode treeNode10 = new System.Windows.Forms.TreeNode("Main", 3, 3, new System.Windows.Forms.TreeNode[] {
            treeNode3,
            treeNode9});
            System.Windows.Forms.TreeNode treeNode11 = new System.Windows.Forms.TreeNode("Solution \'Grrr\' (2 projects)", 5, 5, new System.Windows.Forms.TreeNode[] {
            treeNode10});
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
            treeNode1.Text = "Intro.screen";
            treeNode2.ImageIndex = 6;
            treeNode2.Name = "";
            treeNode2.SelectedImageIndex = 6;
            treeNode2.Text = "Menu.screen";
            treeNode3.ImageIndex = 6;
            treeNode3.Name = "";
            treeNode3.SelectedImageIndex = 6;
            treeNode3.Text = "Main.screen";
            treeNode4.ImageIndex = 8;
            treeNode4.Name = "";
            treeNode4.SelectedImageIndex = 8;
            treeNode4.Text = "MainMenu.interface";
            treeNode5.ImageIndex = 8;
            treeNode5.Name = "";
            treeNode5.SelectedImageIndex = 8;
            treeNode5.Text = "PauseMenu.interface";
            treeNode6.ImageIndex = 2;
            treeNode6.Name = "";
            treeNode6.SelectedImageIndex = 1;
            treeNode6.Text = "Interfaces";
            treeNode7.ImageIndex = 9;
            treeNode7.Name = "";
            treeNode7.SelectedImageIndex = 9;
            treeNode7.Text = "MainMenu.scene";
            treeNode8.ImageIndex = 2;
            treeNode8.Name = "";
            treeNode8.SelectedImageIndex = 1;
            treeNode8.Text = "Scenes";
            treeNode9.ImageIndex = 2;
            treeNode9.Name = "";
            treeNode9.SelectedImageIndex = 1;
            treeNode9.Text = "Resources";
            treeNode10.ImageIndex = 3;
            treeNode10.Name = "";
            treeNode10.SelectedImageIndex = 3;
            treeNode10.Text = "Main";
            treeNode11.ImageIndex = 5;
            treeNode11.Name = "solutionNode";
            treeNode11.SelectedImageIndex = 5;
            treeNode11.Text = "Solution \'Grrr\' (2 projects)";
            this.m_treeView.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode11});
            this.m_treeView.SelectedImageIndex = 5;
            this.m_treeView.ShowRootLines = false;
            this.m_treeView.Size = new System.Drawing.Size(245, 297);
            this.m_treeView.TabIndex = 0;
            this.m_treeView.BeforeExpand += new System.Windows.Forms.TreeViewCancelEventHandler(this.m_treeView_BeforeExpand);
            this.m_treeView.BeforeCollapse += new System.Windows.Forms.TreeViewCancelEventHandler(this.m_treeView_BeforeCollapse);
            // 
            // imageList1
            // 
            this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList1.Images.SetKeyName(0, "");
            this.imageList1.Images.SetKeyName(1, "");
            this.imageList1.Images.SetKeyName(2, "");
            this.imageList1.Images.SetKeyName(3, "");
            this.imageList1.Images.SetKeyName(4, "");
            this.imageList1.Images.SetKeyName(5, "");
            this.imageList1.Images.SetKeyName(6, "");
            this.imageList1.Images.SetKeyName(7, "");
            this.imageList1.Images.SetKeyName(8, "");
            this.imageList1.Images.SetKeyName(9, "");
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
            this.TabText = "Solution Explorer";
            this.Text = "Solution Explorer - WinFormsUI";
            this.ResumeLayout(false);

		}
		#endregion

        private System.Windows.Forms.ImageList imageList1;
        public System.Windows.Forms.TreeView m_treeView;
    }
}