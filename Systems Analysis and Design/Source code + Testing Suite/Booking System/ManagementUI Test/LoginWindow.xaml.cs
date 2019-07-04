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

namespace ManagementUI_Test
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        bool customerRep;
        bool manager;
        bool bookingOfficer;
        bool newsLetter;

        public MainWindow()
        {
            InitializeComponent();

            customerRep = false;
            manager = false;
            bookingOfficer = false;
            newsLetter = false;

        }

        private void CustomerRep_Click(object sender, RoutedEventArgs e)
        {
            customerRep = true;
        }

        private void ManagerButton_Click(object sender, RoutedEventArgs e)
        {
            manager = true;
        }

        private void BookingOfficer_Click(object sender, RoutedEventArgs e)
        {
            bookingOfficer = true;
        }

        private void NewsLetterEditor_Click(object sender, RoutedEventArgs e)
        {
            newsLetter = true;
        }


        public bool getCustomerRep()
        {
            return customerRep;
        }

        public bool getManager()
        {
            return manager;
        }

        public bool getBookingOfficer()
        {
            return bookingOfficer;
        }

        public bool getNewsLetterEditor()
        {
            return newsLetter;
        }

    }
}
