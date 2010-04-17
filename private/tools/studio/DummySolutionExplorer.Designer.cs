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
            System.Windows.Forms.TreeNode treeNode1 = new System.Windows.Forms.TreeNode("Main.gui", 8, 8);
            System.Windows.Forms.TreeNode treeNode2 = new System.Windows.Forms.TreeNode("Pause.gui", 8, 8);
            System.Windows.Forms.TreeNode treeNode3 = new System.Windows.Forms.TreeNode("GUIs", 2, 1, new System.Windows.Forms.TreeNode[] {
            treeNode1,
            treeNode2});
            System.Windows.Forms.TreeNode treeNode4 = new System.Windows.Forms.TreeNode("MainMenu.scene", 9, 9);
            System.Windows.Forms.TreeNode treeNode5 = new System.Windows.Forms.TreeNode("Scenes", 2, 1, new System.Windows.Forms.TreeNode[] {
            treeNode4});
            System.Windows.Forms.TreeNode treeNode6 = new System.Windows.Forms.TreeNode("Resources", 2, 1, new System.Windows.Forms.TreeNode[] {
            treeNode3,
            treeNode5});
            System.Windows.Forms.TreeNode treeNode7 = new System.Windows.Forms.TreeNode("Main.stage", 7, 7);
            System.Windows.Forms.TreeNode treeNode8 = new System.Windows.Forms.TreeNode("Main", 3, 3, new System.Windows.Forms.TreeNode[] {
            treeNode6,
            treeNode7});
            System.Windows.Forms.TreeNode treeNode9 = new System.Windows.Forms.TreeNode("Solution \'Grrr\' (2 projects)", 5, 5, new System.Windows.Forms.TreeNode[] {
            treeNode8});
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(DummySolutionExplorer));
            this.treeView1 = new System.Windows.Forms.TreeView();
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.SuspendLayout();
            // 
            // treeView1
            // 
            this.treeView1.AllowDrop = true;
            this.treeView1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.treeView1.ImageIndex = 0;
            this.treeView1.ImageList = this.imageList1;
            this.treeView1.Indent = 19;
            this.treeView1.LabelEdit = true;
            this.treeView1.Location = new System.Drawing.Point(0, 24);
            this.treeView1.Name = "treeView1";
            treeNode1.ImageIndex = 8;
            treeNode1.Name = "";
            treeNode1.SelectedImageIndex = 8;
            treeNode1.Text = "Main.gui";
            treeNode2.ImageIndex = 8;
            treeNode2.Name = "";
            treeNode2.SelectedImageIndex = 8;
            treeNode2.Text = "Pause.gui";
            treeNode3.ImageIndex = 2;
            treeNode3.Name = "";
            treeNode3.SelectedImageIndex = 1;
            treeNode3.Text = "GUIs";
            treeNode4.ImageIndex = 9;
            treeNode4.Name = "";
            treeNode4.SelectedImageIndex = 9;
            treeNode4.Text = "MainMenu.scene";
            treeNode5.ImageIndex = 2;
            treeNode5.Name = "";
            treeNode5.SelectedImageIndex = 1;
            treeNode5.Text = "Scenes";
            treeNode6.ImageIndex = 2;
            treeNode6.Name = "";
            treeNode6.SelectedImageIndex = 1;
            treeNode6.Text = "Resources";
            treeNode7.ImageIndex = 7;
            treeNode7.Name = "";
            treeNode7.SelectedImageIndex = 7;
            treeNode7.Text = "Main.stage";
            treeNode8.ImageIndex = 3;
            treeNode8.Name = "";
            treeNode8.SelectedImageIndex = 3;
            treeNode8.Text = "Main";
            treeNode9.ImageIndex = 5;
            treeNode9.Name = "";
            treeNode9.SelectedImageIndex = 5;
            treeNode9.Text = "Solution \'Grrr\' (2 projects)";
            this.treeView1.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode9});
            this.treeView1.SelectedImageIndex = 0;
            this.treeView1.ShowRootLines = false;
            this.treeView1.Size = new System.Drawing.Size(245, 297);
            this.treeView1.TabIndex = 0;
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
            this.Controls.Add(this.treeView1);
            this.DockAreas = ((Studio.WinFormsUI.Docking.DockAreas)((((Studio.WinFormsUI.Docking.DockAreas.DockLeft | Studio.WinFormsUI.Docking.DockAreas.DockRight)
                        | Studio.WinFormsUI.Docking.DockAreas.DockTop)
                        | Studio.WinFormsUI.Docking.DockAreas.DockBottom)));
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

        private System.Windows.Forms.TreeView treeView1;
        private System.Windows.Forms.ImageList imageList1;
    }
}