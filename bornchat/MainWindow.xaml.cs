using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace bornchat
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void OneOnOneChatting_Btn_Click(object sender, RoutedEventArgs e)
        {


            if (String.IsNullOrWhiteSpace(NameTextBox.Text))
            {

                MessageBox.Show("이름을 입력해주세요.", "Information", MessageBoxButton.OK, MessageBoxImage.Information);
            }
            else {

                string nameCheck = string.Format("{0} 으로 접속합니다.", NameTextBox.Text);
                MessageBoxResult nameMessageBoxResult = MessageBox.Show(nameCheck, "Question", MessageBoxButton.YesNo, MessageBoxImage.Question);

                if (nameMessageBoxResult == MessageBoxResult.No)
                {
                    return;
                }
            }

            
        }
    }

    
}
