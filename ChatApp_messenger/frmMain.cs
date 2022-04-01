using MaterialSkin.Controls;
using MaterialSkin;
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
    public partial class frmMain : MaterialForm
    {
        public static frmMain _instance;
        public static frmMain Instance
        {
            get {
                if (_instance == null)
                    _instance = new frmMain();
                return _instance;
            }
        }

        public frmMain()
        {
            InitializeComponent();
            MaterialSkinManager manager = MaterialSkinManager.Instance;
            manager.AddFormToManage(this);
            manager.Theme = MaterialSkinManager.Themes.LIGHT;
            manager.ColorScheme = new ColorScheme(Primary.Blue400, Primary.Blue500,Primary.Blue500, Accent.LightBlue200,TextShade.WHITE);

        }

        public Panel Content
        {
            get { return MainContainer; }
            set { MainContainer = value; }
        }

        private void frmMain_Load(object sender, EventArgs e)
        {
           _instance = this;
            MainContainer.Controls.Add(new ucLogin() { Dock=DockStyle.Fill}); 

        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
             
        }
    }
}
