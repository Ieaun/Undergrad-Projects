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
    /// Interaction logic for ManagerMenu.xaml
    /// </summary>
    public partial class ManagerMenu : Window
    {
        // Variables
        bool customerRep;
        bool manager;
        bool bookingOfficer;
        bool newsLetter;
        MainWindow main = new MainWindow();


        public void setMenu(MainWindow pMain)
        {
            main = pMain;
            customerRep = main.getCustomerRep();
            manager = main.getManager();
            bookingOfficer = main.getBookingOfficer();
            newsLetter = main.getNewsLetterEditor();
        }

        // Constructor
        public ManagerMenu()
        {
            InitializeComponent();
        }

        // Allows the manager to make a new database
        private void newDBButton_Click(object sender, RoutedEventArgs e)
        {
            // Checks whether the user is a manager
            if (manager == true)
            { 
                // Yes or no prompt message
                if (MessageBox.Show("Existing database will be deleted, are you sure?", "Question", MessageBoxButton.YesNo, MessageBoxImage.Warning) == MessageBoxResult.No)
                {
                    return;
                }
                else
                {
                    // Creates the database
                    try
                    {
                        CreateSQL.CreateDatabase();
                    }
                    catch (Exception) {
                        MessageBox.Show("Error making database.");
                        return;
                    }
                }
                
            }
            else
            {
                MessageBox.Show("You must be a manager to access this.");
            }
        }

        // Navigates to the reports page
        private void viewReportButton_Click(object sender, RoutedEventArgs e)
        {
            // Checks the user permissions
            if (manager == true || newsLetter == true)
            {
                // Switches to the reports page
                Reports repo = new Reports();
                this.Close();
                repo.ShowDialog();
            }
            else
            {
                MessageBox.Show("You must be a manager or news letter editor to access this.");
            }
        }

        // Navigates to the schedule page
        private void manageScheduleButton_Click(object sender, RoutedEventArgs e)
        {
            // Checks the user permissions
            if (manager == true || bookingOfficer == true)
            {
                // Switches to the schedule page
                Schedule sched = new Schedule();
                this.Close();
                sched.ShowDialog();
            }
            else
            {
                MessageBox.Show("You must be a manager or booking officer to access this.");
            }
        }

        // Navigates to the view bookings page
        private void makeBookingButton_Click(object sender, RoutedEventArgs e)
        {
            // Checks the users permissions
            if (manager == true || bookingOfficer == true)
            {
                // Switches to the view bookings page
                ViewBookings mBook = new ViewBookings();
                this.Close();
                mBook.ShowDialog();
            }
            else
            {
                MessageBox.Show("You must be a manager or booking officer to access this.");
            }
        }

        // Navigates to the manage customers page
        private void manageCustomersButton_Click(object sender, RoutedEventArgs e)
        {
            // Checks user permissions
            if (manager == true || customerRep == true)
            {
                // Switches to the manage customers page
                Window1 manaCust = new Window1();
                this.Close();
                manaCust.ShowDialog();
            }
            else
            {
                MessageBox.Show("You must be a manager or customer rep to access this.");
            }
                    
        }

        // Navigates to the gold club page
        private void goldClubButton_Click(object sender, RoutedEventArgs e)
        {
            // Checks user permissions
            if (manager == true || customerRep == true)
            {
                // Switches to the gold club page
                GoldMemberPage gp = new GoldMemberPage();
                this.Close();
                gp.ShowDialog();
            }
            else
            {
                MessageBox.Show("You must be a manager or customer rep to access this.");
            }
        }

        // Returns to the main window
        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            MainWindow main = new MainWindow();
            this.Close();
            main.ShowDialog();
        }
    }
}
