namespace ARTeam_DateConverter
{
    partial class main
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(main));
            this.cbBias = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.Exit = new System.Windows.Forms.Button();
            this.ckbWindowTop = new System.Windows.Forms.CheckBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.cbFormat = new System.Windows.Forms.ComboBox();
            this.txtExample = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.txtValueToDecode = new System.Windows.Forms.TextBox();
            this.txtDateTime = new System.Windows.Forms.TextBox();
            this.ClearButton = new System.Windows.Forms.Button();
            this.DecodeButton = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.SuspendLayout();
            // 
            // cbBias
            // 
            this.cbBias.FormattingEnabled = true;
            this.cbBias.Items.AddRange(new object[] {
            "UTC -12:00",
            "UTC -11:00",
            "UTC -10:00",
            "UTC -09:00",
            "UTC -08:00",
            "UTC -07:00",
            "UTC -06:00",
            "UTC -05:00",
            "UTC -04:00",
            "UTC -03:30",
            "UTC -03:00",
            "UTC -02:00",
            "UTC -01:00",
            "UTC 00:00",
            "UTC +01:00",
            "UTC +02:00",
            "UTC +03:00",
            "UTC +03:30",
            "UTC +04:00",
            "UTC +04:30",
            "UTC +05:00",
            "UTC +05:30",
            "UTC +05:45",
            "UTC +06:00",
            "UTC +06:30",
            "UTC +07:00",
            "UTC +08:00",
            "UTC +09:00",
            "UTC +09:30",
            "UTC +10:00",
            "UTC +11:00",
            "UTC +12:00",
            "UTC +13:00"});
            this.cbBias.Location = new System.Drawing.Point(115, 29);
            this.cbBias.Name = "cbBias";
            this.cbBias.Size = new System.Drawing.Size(163, 21);
            this.cbBias.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(54, 37);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(55, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Add Bias: ";
            // 
            // Exit
            // 
            this.Exit.Location = new System.Drawing.Point(348, 177);
            this.Exit.Name = "Exit";
            this.Exit.Size = new System.Drawing.Size(75, 23);
            this.Exit.TabIndex = 2;
            this.Exit.Text = "E&xit";
            this.Exit.UseVisualStyleBackColor = true;
            this.Exit.Click += new System.EventHandler(this.Exit_Click);
            // 
            // ckbWindowTop
            // 
            this.ckbWindowTop.AutoSize = true;
            this.ckbWindowTop.Location = new System.Drawing.Point(284, 33);
            this.ckbWindowTop.Name = "ckbWindowTop";
            this.ckbWindowTop.Size = new System.Drawing.Size(102, 17);
            this.ckbWindowTop.TabIndex = 3;
            this.ckbWindowTop.Text = "Window on Top";
            this.ckbWindowTop.UseVisualStyleBackColor = true;
            this.ckbWindowTop.CheckedChanged += new System.EventHandler(this.ckbWindowTop_CheckedChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(26, 65);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(83, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "Decode Format:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(59, 93);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(50, 13);
            this.label3.TabIndex = 5;
            this.label3.Text = "Example:";
            // 
            // cbFormat
            // 
            this.cbFormat.FormattingEnabled = true;
            this.cbFormat.Items.AddRange(new object[] {
            "Windows: 64Bit Hex Value - Little Endian",
            "Windows: 64Bit Hex Value - Big Endian",
            "Windows: IE Cookie Date (Lo Value, Hi Value)",
            "Windows: 32bit FileTime [xxxxxxxx:xxxxxxxx]",
            "Windows: OLE Automation Format (64bit Double)",
            "Windows: 128 bit System Structure",
            "Unix: 32 bit Hex Value - Little Endian",
            "Unix: 32 bit Hex Value - Big Endian",
            "Unix: Numeric Value",
            "Unix: Milisecond Value",
            "Google ChromeWebKit Value",
            "Google Chrome",
            "MAC: Absolute Time",
            "MS-DOS: 32 bit Hex Value",
            "MS-DOS: wFatDate wFatTime",
            "HFS: 32 bit Hex Value - Little Endian",
            "HFS: 32 bit Hex Value - Big Endian",
            "HFS+: 32 bit Hex Value - Little Endian",
            "HFS+: 32 bit Hex Value - Big Endian",
            "Mozilla Firefox PRTime",
            "Safari DateTime"});
            this.cbFormat.Location = new System.Drawing.Point(115, 57);
            this.cbFormat.Name = "cbFormat";
            this.cbFormat.Size = new System.Drawing.Size(308, 21);
            this.cbFormat.TabIndex = 6;
            this.cbFormat.SelectedIndexChanged += new System.EventHandler(this.cbFormat_SelectedIndexChanged);
            // 
            // txtExample
            // 
            this.txtExample.Location = new System.Drawing.Point(115, 86);
            this.txtExample.Name = "txtExample";
            this.txtExample.ReadOnly = true;
            this.txtExample.Size = new System.Drawing.Size(308, 20);
            this.txtExample.TabIndex = 7;
            this.txtExample.Text = "FF03D2315FE1C701";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(19, 121);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(90, 13);
            this.label4.TabIndex = 8;
            this.label4.Text = "Value to Decode:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(44, 149);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(65, 13);
            this.label5.TabIndex = 9;
            this.label5.Text = "Date && Time";
            // 
            // txtValueToDecode
            // 
            this.txtValueToDecode.Location = new System.Drawing.Point(115, 114);
            this.txtValueToDecode.Name = "txtValueToDecode";
            this.txtValueToDecode.Size = new System.Drawing.Size(308, 20);
            this.txtValueToDecode.TabIndex = 10;
            // 
            // txtDateTime
            // 
            this.txtDateTime.Location = new System.Drawing.Point(115, 142);
            this.txtDateTime.Name = "txtDateTime";
            this.txtDateTime.Size = new System.Drawing.Size(308, 20);
            this.txtDateTime.TabIndex = 11;
            // 
            // ClearButton
            // 
            this.ClearButton.Location = new System.Drawing.Point(272, 177);
            this.ClearButton.Name = "ClearButton";
            this.ClearButton.Size = new System.Drawing.Size(75, 23);
            this.ClearButton.TabIndex = 12;
            this.ClearButton.Text = "Clear";
            this.ClearButton.UseVisualStyleBackColor = true;
            this.ClearButton.Click += new System.EventHandler(this.ClearButton_Click);
            // 
            // DecodeButton
            // 
            this.DecodeButton.Location = new System.Drawing.Point(195, 177);
            this.DecodeButton.Name = "DecodeButton";
            this.DecodeButton.Size = new System.Drawing.Size(75, 23);
            this.DecodeButton.TabIndex = 13;
            this.DecodeButton.Text = "Decode";
            this.DecodeButton.UseVisualStyleBackColor = true;
            this.DecodeButton.Click += new System.EventHandler(this.DecodeButton_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Location = new System.Drawing.Point(13, 13);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(434, 194);
            this.groupBox1.TabIndex = 14;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Settings";
            // 
            // main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(459, 219);
            this.Controls.Add(this.DecodeButton);
            this.Controls.Add(this.ClearButton);
            this.Controls.Add(this.txtDateTime);
            this.Controls.Add(this.txtValueToDecode);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.txtExample);
            this.Controls.Add(this.cbFormat);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.ckbWindowTop);
            this.Controls.Add(this.Exit);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.cbBias);
            this.Controls.Add(this.groupBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "main";
            this.Text = "DateConverter";
            this.Load += new System.EventHandler(this.main_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox cbBias;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button Exit;
        private System.Windows.Forms.CheckBox ckbWindowTop;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox cbFormat;
        private System.Windows.Forms.TextBox txtExample;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox txtValueToDecode;
        private System.Windows.Forms.TextBox txtDateTime;
        private System.Windows.Forms.Button ClearButton;
        private System.Windows.Forms.Button DecodeButton;
        private System.Windows.Forms.GroupBox groupBox1;
    }
}

