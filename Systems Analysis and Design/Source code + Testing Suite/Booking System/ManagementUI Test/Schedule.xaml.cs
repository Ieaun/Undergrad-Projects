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
    /// Interaction logic for Schedule.xaml
    /// </summary>
    public partial class Schedule : Window
    {
        // Variables
        List<Play> playsList = new List<Play>();
        List<Performance> performanceList = new List<Performance>();

        // Constructor
        public Schedule()
        {
            InitializeComponent();
            updatePlaysLists(); // Updates the list of plays when the page loads
            
        }

        // Deletes the selected play from the system
        private void deleteSelectedPlayButton_Click(object sender, RoutedEventArgs e)
        {
            // Gets the index of the selected Play
            if (PlaysListbox.SelectedIndex == -1)
            {
                return;
            }
            int playIndex = PlaysListbox.SelectedIndex;
            // Gets the play to delete from the lsit of plays
            Play playToDelete = playsList[playIndex];
            // Removes it from the lsit box
            PlaysListbox.Items.RemoveAt(PlaysListbox.Items.IndexOf(PlaysListbox.SelectedItem));

            // Deletes the Play from the database
            SQL.PlaySQL.DeleteFromDB(playToDelete);

            updatePlaysLists(); // Updates the list of plays
        }

        // Creates a play using infromation in fields
        private void createPlayButton_Click(object sender, RoutedEventArgs e)
        {
            // Creates a new Play Object
            string type = "";
            double stalls;
            double upper;
            double dress;
            double length;

            // Radio button Validation
            if (mainplayRadioButton.IsChecked == true) { type = "Main Play"; } 
            else if (repeatingRadionButton.IsChecked == true) { type = "Repeating"; }
            else {
                MessageBox.Show("You must select a type of play.", "",MessageBoxButton.OK, MessageBoxImage.Information);
                return;
            }
            // Play name validation
            if (playNameTextbox.Text.Equals("")) {
                MessageBox.Show("You must set a valid play name.");
                return;
            }
            // Stall price validation
            try { stalls = Convert.ToDouble(stallsPriceTextbox.Text); }
            catch (Exception) {
                MessageBox.Show("You must set a valid price for the stalls.");
                return;
            }
            // Upper circle price validation
            try { upper = Convert.ToDouble(upperCirclePriceTextbox.Text); }
            catch (Exception)
            {
                MessageBox.Show("You must set a valid price for the upper circle.");
                return;
            }
            // Dress circle price validation
            try { dress = Convert.ToDouble(dressCirclePriceTextbox.Text); }
            catch (Exception)
            {
                MessageBox.Show("You must set a valid price for the dress circle.");
                return;
            }
            // Play length validation
            try { length = Convert.ToDouble(playLengthTextbox.Text); }
            catch (Exception)
            {
                MessageBox.Show("You must set a valid length of the play.");
                return;
            }

            // Constructs a new play using information from user
            Play newPlay = new Play("", playNameTextbox.GetLineText(0),type, stalls, upper, dress, length);

            // Adds it to the database
            SQL.PlaySQL.AddToDB(newPlay);

            // Then updates the lists 
            updatePlaysLists();

            // Clears all the fields

            playNameTextbox.Text = "";
            stallsPriceTextbox.Text = "";
            upperCirclePriceTextbox.Text = "";
            dressCirclePriceTextbox.Text = "";
            playLengthTextbox.Text = "";
        }

        // Updates the list of plays 
        private void updatePlaysLists()
        {
            // Updates the list of Plays from the database
            playsList = SQL.PlaySQL.QueryFromDB();

            PlaysListbox.Items.Clear();
            // Loops through the list adding them to the list box
            foreach (Play play in playsList)
            {
                PlaysListbox.Items.Add(play.getID() + " | " + play.getName());
            }
        }

        // Deletes the selected performance
        private void deleteSelectedPerformanceButton_Click(object sender, RoutedEventArgs e)
        {
            // Checks if a date is selected
            if (performanceListBox.SelectedIndex == -1)
            {
                return;
            }
            // Gets the index
            int performanceIndex = performanceListBox.SelectedIndex;
            // Gets the performance from the list
            Performance performanceToDelete = performanceList[performanceIndex];
            // Removes it from the list box
            performanceListBox.Items.RemoveAt(performanceListBox.Items.IndexOf(performanceListBox.SelectedItem));

            // Deletes the customer from the database
            SQL.PerformanceSQL.DeleteFromDB(performanceToDelete);
            SQL.SeatSQL.DeleteAllSeats(performanceToDelete);
            updatePerformancesDates(); // Updates the performance dates list
        }

        

        

        // Used to update the ListBox for performances
        private void updatePerformancesDates()
        {
           try
           {
                string playID = PlaysListbox.SelectedItem.ToString()[0].ToString();
                // Updates the list of performances from the database 
                performanceList = SQL.PerformanceSQL.QueryFromDB(playID);

                performanceListBox.Items.Clear();
                // Loops through the list adding them to the list box
                foreach (Performance performance in performanceList)
                {
                    performanceListBox.Items.Add(performance.getDate());
                }
            }
            catch (Exception)
            {

            }
        }

        // Returns to the main window
        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            MainWindow manaMenu = new MainWindow();
            this.Close();
            manaMenu.ShowDialog();
        }

        // Adds a new performance to the database
        private void AddDateButton_Click(object sender, RoutedEventArgs e)
        {
            // Checks if a play is selected
            if (PlaysListbox.SelectedItem != null)
            {
                // Checks if a date is selected
                try { DateTime date = dateField.SelectedDate.Value; }
                catch (Exception)
                {
                    MessageBox.Show("Please select a date.");
                    return;
                }
                // Updates performance dates
                updatePerformancesDates();
                // Checks if a performance on that date exists
                if (performanceListBox.Items.Contains(dateField.SelectedDate.Value.Date.ToShortDateString()))
                {
                    MessageBox.Show("Performance already on that day");
                    return;
                }
                else {
                    // Adds the performance to the database
                    Performance newPerformance = new Performance("", PlaysListbox.SelectedItem.ToString()[0].ToString(), dateField.SelectedDate.Value.Date.ToShortDateString());
                    newPerformance.mSeats.setSeatsEmpty();
                    SQL.PerformanceSQL.AddToDB(newPerformance);
                    string playID = SQL.PerformanceSQL.QueryID(dateField.SelectedDate.Value.Date.ToShortDateString());
                    newPerformance.setID(playID);
                    SQL.SeatSQL.AddSeats(newPerformance);
                    updatePerformancesDates(); // Updates the list of performances
                }
                
            }
            else
            {
                MessageBox.Show("Please select a play.");
                return;
            }
        }

        // Calls the update performance dates function when the play that is selected changes
        private void PlaysListbox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            updatePerformancesDates();
        }

        
    }
}
