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
    /// Interaction logic for Reports.xaml
    /// </summary>
    public partial class Reports : Window
    {
        //list of all plays
        List<string> listOfPlays = new List<string>();


        //list of all gold members
        List<string> goldMembers = new List<string>();
        //attributes to be added to goldmember listbox.

        //forUpcoming plays
        List<Play> playsList = new List<Play>();
        List<Performance> performance = new List<Performance>();
        Seats currentSeats;
        string performanceID = "";
        int seatsSold;
        int totalSeats;

        // Constructor
        public Reports()
        {
            InitializeComponent();
            
            // Gets the plays from the database
            playsList = SQL.PlaySQL.QueryFromDB();
            // Checks if any plays exist, if so gets the first id
            try
            {
                performance = SQL.PerformanceSQL.QueryFromDB(playsList[0].getID());
            }
            catch (ArgumentOutOfRangeException)
            {
                MessageBox.Show("No Plays found.");
            }
            // Loops through and adds plays to the combo
            foreach (Play item in playsList)
            {
                playsReportCombobox.Items.Add(item.getName());
            }
            // Loops through and adds performances to the listbox
            foreach (Performance item in performance)
            {
                upcomingPlaysListBox.Items.Add(item.getDate());
            }
            if (playsReportCombobox.Items.Count != 0)
            {
                playsReportCombobox.SelectedIndex = 0;
            }
            //Add plays to report combobox
            for (int i = 0; i < listOfPlays.Count; i++)
            {
                playsReportCombobox.Items.Add(listOfPlays[i]);
            }

        }

        private void updateUpperCircle()
        {

        }

        private void updateDressCircle()
        {

        }

        private void updateStalls()
        {

        }


        private void printSoldUnsoldSeats(List<string> uCircle, List<string> dCircle, List<string> stalls)
        {
            
        }

        private void printUpcomingPlays(List<string> plays)
        {

        }

        private void printGoldMembers(List<string> goldM)
        {

        }


        // Updates the dates when a play is selected
        private void playsReportCombobox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            // Clears the list box
            upcomingPlaysListBox.Items.Clear();
            int index = playsReportCombobox.SelectedIndex; // Gets the index
            performance = SQL.PerformanceSQL.QueryFromDB(playsList[index].getID()); // Gets the performances
            // Loops through adding them to the lsitbox
            foreach (Performance item in performance)
            {
                upcomingPlaysListBox.Items.Add(item.getDate());
            }
        }

        private void printSoldUnSold_Click(object sender, RoutedEventArgs e)
        {

        }

        private void PrintGoldmembers_Click(object sender, RoutedEventArgs e)
        {

        }

        // Returns to the main window
        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            MainWindow manaMen = new MainWindow();
            this.Close();
            manaMen.ShowDialog();
        }

        // Displays all the seats for a performance when a date is selected
        private void upcomingPlaysListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            try
            {
                seatsSold = 0;
                totalSeats = 0;
                // Gets the current seats from the database
                performanceID = SQL.PerformanceSQL.QueryID(upcomingPlaysListBox.SelectedItem.ToString());
                currentSeats = SQL.SeatSQL.ReturnSeats(performanceID);
                // Row and seat ids to be displayed
                int rowID = 1;
                int seatID = 1;
                // Clears the list box
                seatingSoldListbox.Items.Clear();
                // Loops through each row of the stalls seats
                foreach (List<string> row in currentSeats.getStalls()) {
                    // Loops through each seat in the row adding it to the list box
                    foreach (string seat in row) {
                        seatingSoldListbox.Items.Add("Stalls - Row: " + rowID + "  -  #" + seatID + " - " + seat);
                        // If the seat is booked increases seats sold
                        if (seat.Equals("booked")) { seatsSold++; }
                        // Increments total seats and the seat id
                        totalSeats++;
                        seatID++;
                    }
                    // Increase row id and resets the seat id
                    rowID++;
                    seatID = 1;
                }
                // Resets row id and seat id
                rowID = 1;
                seatID = 1;
                // Loops through each row of the upper circle seats
                foreach (List<string> row in currentSeats.getUpperSeats())
                {
                    // Loops through each seat in the row adding it to the list box
                    foreach (string seat in row)
                    {
                        seatingSoldListbox.Items.Add("Upper - Row: " + rowID + "  -  #" + seatID + " - " + seat);
                        // If the seat is booked increases seats sold
                        if (seat.Equals("booked")) { seatsSold++; }
                        // Increments total seats and the seat id
                        totalSeats++;
                        seatID++;
                    }
                    // Increase row id and resets the seat id
                    rowID++;
                    seatID = 1;
                }
                // Resets row id and seat id
                rowID = 1;
                seatID = 1;
                // Loops through each row of the dress circle seats
                foreach (List<string> row in currentSeats.getDressSeats())
                {
                    // Loops through each seat in the row adding it to the list box
                    foreach (string seat in row)
                    {
                        seatingSoldListbox.Items.Add("Dress - Row: " + rowID + "  -  #" + seatID + " - " + seat);
                        // If the seat is booked increases seats sold
                        if (seat.Equals("booked")) { seatsSold++; }
                        // Increments total seats and the seat id
                        totalSeats++;
                        seatID++;
                    }
                    // Increase row id and resets the seat id
                    rowID++;
                    seatID = 1;
                }
                // Displays the total seats and seats sold to the window
                SeatsSoldLabel.Content = "Seats Sold: " + seatsSold;
                TotalSeatsLabel.Content = "Total Seats: " + totalSeats;
            }
            catch (Exception)
            {
            }
        }
    }
}
