namespace Studio
{
    partial class ResourceExplorer
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
            System.Windows.Forms.TreeNode treeNode1 = new System.Windows.Forms.TreeNode("Tisiphone\\main\\menu");
            System.Windows.Forms.TreeNode treeNode2 = new System.Windows.Forms.TreeNode("Tisiphone\\main\\menu\\game");
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ResourceExplorer));
            this.m_treeView = new System.Windows.Forms.TreeView();
            this.m_treeViewImageList = new System.Windows.Forms.ImageList(this.components);
            this.SuspendLayout();
            // 
            // m_treeView
            // 
            this.m_treeView.AllowDrop = true;
            this.m_treeView.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_treeView.HideSelection = false;
            this.m_treeView.ImageIndex = 0;
            this.m_treeView.ImageList = this.m_treeViewImageList;
            this.m_treeView.Indent = 19;
            this.m_treeView.LabelEdit = true;
            this.m_treeView.Location = new System.Drawing.Point(0, 24);
            this.m_treeView.Name = "m_treeView";
            treeNode1.Name = "";
            treeNode1.Text = "Tisiphone\\main\\menu";
            treeNode2.Name = "";
            treeNode2.Text = "Tisiphone\\main\\menu\\game";
            this.m_treeView.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode1,
            treeNode2});
            this.m_treeView.SelectedImageIndex = 0;
            this.m_treeView.ShowRootLines = false;
            this.m_treeView.Size = new System.Drawing.Size(292, 241);
            this.m_treeView.TabIndex = 3;
            // 
            // m_treeViewImageList
            // 
            this.m_treeViewImageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("m_treeViewImageList.ImageStream")));
            this.m_treeViewImageList.TransparentColor = System.Drawing.Color.Transparent;
            this.m_treeViewImageList.Images.SetKeyName(0, "Stage");
            // 
            // ResourceExplorer
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(292, 266);
            this.Controls.Add(this.m_treeView);
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "ResourceExplorer";
            this.TabText = "Resource Explorer";
            this.Text = "Resource Explorer";
            this.ResumeLayout(false);

        }

        #endregion

        public System.Windows.Forms.TreeView m_treeView;
        private System.Windows.Forms.ImageList m_treeViewImageList;

    }
}