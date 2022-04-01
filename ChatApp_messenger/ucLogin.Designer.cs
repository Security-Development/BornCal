
namespace ChatApp_messenger
{
    partial class ucLogin
    {
        /// <summary> 
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region 구성 요소 디자이너에서 생성한 코드

        /// <summary> 
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.materialLabel1 = new MaterialSkin.Controls.MaterialLabel();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.btnSignIn = new MaterialSkin.Controls.MaterialFlatButton();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::ChatApp_messenger.Properties.Resources.imgKaKao;
            this.pictureBox1.Location = new System.Drawing.Point(95, 71);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(100, 100);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // materialLabel1
            // 
            this.materialLabel1.AutoSize = true;
            this.materialLabel1.Depth = 0;
            this.materialLabel1.Font = new System.Drawing.Font("Roboto", 11F);
            this.materialLabel1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(222)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))));
            this.materialLabel1.Location = new System.Drawing.Point(12, 234);
            this.materialLabel1.MouseState = MaterialSkin.MouseState.HOVER;
            this.materialLabel1.Name = "materialLabel1";
            this.materialLabel1.Size = new System.Drawing.Size(100, 24);
            this.materialLabel1.TabIndex = 1;
            this.materialLabel1.Text = "Your name";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(16, 261);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(260, 25);
            this.textBox1.TabIndex = 2;
            // 
            // btnSignIn
            // 
            this.btnSignIn.AutoSize = true;
            this.btnSignIn.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.btnSignIn.Depth = 0;
            this.btnSignIn.Location = new System.Drawing.Point(95, 372);
            this.btnSignIn.Margin = new System.Windows.Forms.Padding(4, 6, 4, 6);
            this.btnSignIn.MinimumSize = new System.Drawing.Size(100, 0);
            this.btnSignIn.MouseState = MaterialSkin.MouseState.HOVER;
            this.btnSignIn.Name = "btnSignIn";
            this.btnSignIn.Primary = false;
            this.btnSignIn.Size = new System.Drawing.Size(100, 36);
            this.btnSignIn.TabIndex = 4;
            this.btnSignIn.Text = "Go";
            this.btnSignIn.UseVisualStyleBackColor = true;
            this.btnSignIn.Click += new System.EventHandler(this.btnSignIn_Click);
            // 
            // ucLogin
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.btnSignIn);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.materialLabel1);
            this.Controls.Add(this.pictureBox1);
            this.Name = "ucLogin";
            this.Size = new System.Drawing.Size(290, 506);
            this.Load += new System.EventHandler(this.ucLogin_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBox1;
        private MaterialSkin.Controls.MaterialLabel materialLabel1;
        private System.Windows.Forms.TextBox textBox1;
        private MaterialSkin.Controls.MaterialFlatButton btnSignIn;
    }
}
