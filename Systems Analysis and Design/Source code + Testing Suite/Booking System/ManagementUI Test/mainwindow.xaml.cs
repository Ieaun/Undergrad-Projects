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
        // Variables
        bool customerRep;
        bool manager;
        bool bookingOfficer;
        bool newsLetter;

        public MainWindow()
        {
            InitializeComponent();
        }

        // Sets the current user to customer representative
        private void CustomerRep_Click(object sender, RoutedEventArgs e)
        {
            customerRep = true;
            manager = false;
            bookingOfficer = false;
            newsLetter = false;
            // Changes the current window to the Menu window
            ManagerMenu maMenu = new ManagerMenu();
            maMenu.setMenu(this);
            this.Close();
            maMenu.ShowDialog();
        }

        // Sets the current user to the manager
        private void ManagerButton_Click(object sender, RoutedEventArgs e)
        {
            manager = true;
            customerRep = false;
            bookingOfficer = false;
            newsLetter = false;
            // Changes the current window to the Menu window
            ManagerMenu maMenu = new ManagerMenu();
            maMenu.setMenu(this);
            this.Close();
            maMenu.ShowDialog();       
        }

        private void BookingOfficer_Click(object sender, RoutedEventArgs e)
        {
            bookingOfficer = true;
            manager = false;
            customerRep = false;
            newsLetter = false;
            // Changes the current window to the Menu window
            ManagerMenu maMenu = new ManagerMenu();
            maMenu.setMenu(this);
            this.Close();
            maMenu.ShowDialog();
        }

        private void NewsLetterEditor_Click(object sender, RoutedEventArgs e)
        {
            newsLetter = true;
            manager = false;
            bookingOfficer = false;
            customerRep = false;
            // Changes the current window to the Menu window
            ManagerMenu maMenu = new ManagerMenu();
            maMenu.setMenu(this);
            this.Close();
            maMenu.ShowDialog();
        }

        // Returns the customer rep variable
        public bool getCustomerRep()
        {
            return customerRep;
        }

        // Returns the manager variable
        public bool getManager()
        {
            return manager;
        }

        // Returns the booking officer variable
        public bool getBookingOfficer()
        {
            return bookingOfficer;
        }

        // Returns the news letter variable
        public bool getNewsLetterEditor()
        {
            return newsLetter;
        }

        // Returns the main window 
        public MainWindow GetMainWindow()
        {
            return this;
        }

        // Closes the application
        private void CloseButton_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.Application.Current.Shutdown();
        }

    }
}
