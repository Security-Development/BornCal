using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ChatApp_messenger
{
    public partial class ucLogin : UserControl
    {
        public ucLogin()
        {
            InitializeComponent();
        }

        private void ucLogin_Load(object sender, EventArgs e)
        {

        }

        private void btnSignIn_Click(object sender, EventArgs e)
        {
            frmMain.Instance.Content.Controls.Add(new ucMain() { Dock = DockStyle.Fill });
            frmMain.Instance.Content.Controls[0].SendToBack();
        }
    }
}
