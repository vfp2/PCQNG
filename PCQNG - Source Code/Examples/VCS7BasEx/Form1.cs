using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;

namespace VCS7BasEx
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class Form1 : System.Windows.Forms.Form
	{
		private AxQWPCQNGLib.AxPCQNG axPCQNG1;
		private System.Windows.Forms.GroupBox Selection;
		private System.Windows.Forms.RadioButton Uniform;
		private System.Windows.Forms.RadioButton Normal;
		private System.Windows.Forms.RadioButton Int32;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label Out;
		private System.Windows.Forms.Button Go;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public Form1()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			System.Resources.ResourceManager resources = new System.Resources.ResourceManager(typeof(Form1));
			this.axPCQNG1 = new AxQWPCQNGLib.AxPCQNG();
			this.Selection = new System.Windows.Forms.GroupBox();
			this.Uniform = new System.Windows.Forms.RadioButton();
			this.Normal = new System.Windows.Forms.RadioButton();
			this.Int32 = new System.Windows.Forms.RadioButton();
			this.label1 = new System.Windows.Forms.Label();
			this.Out = new System.Windows.Forms.Label();
			this.Go = new System.Windows.Forms.Button();
			((System.ComponentModel.ISupportInitialize)(this.axPCQNG1)).BeginInit();
			this.Selection.SuspendLayout();
			this.SuspendLayout();
			// 
			// axPCQNG1
			// 
			this.axPCQNG1.Enabled = true;
			this.axPCQNG1.Location = new System.Drawing.Point(8, 8);
			this.axPCQNG1.Name = "axPCQNG1";
			this.axPCQNG1.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axPCQNG1.OcxState")));
			this.axPCQNG1.Size = new System.Drawing.Size(32, 32);
			this.axPCQNG1.TabIndex = 0;
			// 
			// Selection
			// 
			this.Selection.Controls.AddRange(new System.Windows.Forms.Control[] {
																					this.Int32,
																					this.Normal,
																					this.Uniform});
			this.Selection.Location = new System.Drawing.Point(16, 72);
			this.Selection.Name = "Selection";
			this.Selection.Size = new System.Drawing.Size(128, 120);
			this.Selection.TabIndex = 1;
			this.Selection.TabStop = false;
			this.Selection.Text = "Selection";
			// 
			// Uniform
			// 
			this.Uniform.Location = new System.Drawing.Point(16, 24);
			this.Uniform.Name = "Uniform";
			this.Uniform.TabIndex = 0;
			this.Uniform.Text = "Uniform";
			// 
			// Normal
			// 
			this.Normal.Location = new System.Drawing.Point(16, 56);
			this.Normal.Name = "Normal";
			this.Normal.TabIndex = 1;
			this.Normal.Text = "Normal";
			// 
			// Int32
			// 
			this.Int32.Location = new System.Drawing.Point(16, 88);
			this.Int32.Name = "Int32";
			this.Int32.TabIndex = 2;
			this.Int32.Text = "Int32";
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(168, 104);
			this.label1.Name = "label1";
			this.label1.TabIndex = 2;
			this.label1.Text = "Random Value:";
			// 
			// Out
			// 
			this.Out.Location = new System.Drawing.Point(168, 128);
			this.Out.Name = "Out";
			this.Out.TabIndex = 3;
			this.Out.Text = "Out";
			// 
			// Go
			// 
			this.Go.Location = new System.Drawing.Point(176, 32);
			this.Go.Name = "Go";
			this.Go.TabIndex = 4;
			this.Go.Text = "Go";
			this.Go.Click += new System.EventHandler(this.Go_Click);
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(292, 273);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.Go,
																		  this.Out,
																		  this.label1,
																		  this.Selection,
																		  this.axPCQNG1});
			this.Name = "Form1";
			this.Text = "Form1";
			((System.ComponentModel.ISupportInitialize)(this.axPCQNG1)).EndInit();
			this.Selection.ResumeLayout(false);
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new Form1());
		}

		private void Go_Click(object sender, System.EventArgs e)
		{
			axPCQNG1.Open();
		
			if (Int32.Checked)
				Out.Text = axPCQNG1.RandInt32.ToString();

			if (Uniform.Checked)
				Out.Text = axPCQNG1.RandUniform.ToString();

			if (Normal.Checked)
				Out.Text = axPCQNG1.RandNormal.ToString();
	
			axPCQNG1.Close();
		}
	}
}
