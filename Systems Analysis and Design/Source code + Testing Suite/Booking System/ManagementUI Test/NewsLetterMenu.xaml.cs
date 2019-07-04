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
using System.Windows.Shapes;

namespace ManagementUI_Test
{
    /// <summary>
    /// Interaction logic for NewsLetterMenu.xaml
    /// </summary>
    public partial class NewsLetterMenu : Window
    {
        public NewsLetterMenu()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            MainWindow m = new MainWindow();
            this.Close();
            m.ShowDialog();
        }

        private void ViewReportButton_Click(object sender, RoutedEventArgs e)
        {
            Reports r = new Reports();
            this.Close();
            r.ShowDialog();
        }
    }
}
